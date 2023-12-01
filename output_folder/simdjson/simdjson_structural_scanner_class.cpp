class structural_scanner {
public:

simdjson_inline structural_scanner(dom_parser_implementation &_parser, stage1_mode _partial)
  : buf{_parser.buf},
    next_structural_index{_parser.structural_indexes.get()},
    parser{_parser},
    len{static_cast<uint32_t>(_parser.len)},
    partial{_partial} {
}

simdjson_inline void add_structural() {
  *next_structural_index = idx;
  next_structural_index++;
}

simdjson_inline bool is_continuation(uint8_t c) {
  return (c & 0xc0) == 0x80;
}

simdjson_inline void validate_utf8_character() {
  // Continuation
  if (simdjson_unlikely((buf[idx] & 0x40) == 0)) {
    // extra continuation
    error = UTF8_ERROR;
    idx++;
    return;
  }

  // 2-byte
  if ((buf[idx] & 0x20) == 0) {
    // missing continuation
    if (simdjson_unlikely(idx+1 > len || !is_continuation(buf[idx+1]))) {
      if (idx+1 > len && is_streaming(partial)) { idx = len; return; }
      error = UTF8_ERROR;
      idx++;
      return;
    }
    // overlong: 1100000_ 10______
    if (buf[idx] <= 0xc1) { error = UTF8_ERROR; }
    idx += 2;
    return;
  }

  // 3-byte
  if ((buf[idx] & 0x10) == 0) {
    // missing continuation
    if (simdjson_unlikely(idx+2 > len || !is_continuation(buf[idx+1]) || !is_continuation(buf[idx+2]))) {
      if (idx+2 > len && is_streaming(partial)) { idx = len; return; }
      error = UTF8_ERROR;
      idx++;
      return;
    }
    // overlong: 11100000 100_____ ________
    if (buf[idx] == 0xe0 && buf[idx+1] <= 0x9f) { error = UTF8_ERROR; }
    // surrogates: U+D800-U+DFFF 11101101 101_____
    if (buf[idx] == 0xed && buf[idx+1] >= 0xa0) { error = UTF8_ERROR; }
    idx += 3;
    return;
  }

  // 4-byte
  // missing continuation
  if (simdjson_unlikely(idx+3 > len || !is_continuation(buf[idx+1]) || !is_continuation(buf[idx+2]) || !is_continuation(buf[idx+3]))) {
    if (idx+2 > len && is_streaming(partial)) { idx = len; return; }
    error = UTF8_ERROR;
    idx++;
    return;
  }
  // overlong: 11110000 1000____ ________ ________
  if (buf[idx] == 0xf0 && buf[idx+1] <= 0x8f) { error = UTF8_ERROR; }
  // too large: > U+10FFFF:
  // 11110100 (1001|101_)____
  // 1111(1___|011_|0101) 10______
  // also includes 5, 6, 7 and 8 byte characters:
  // 11111___
  if (buf[idx] == 0xf4 && buf[idx+1] >= 0x90) { error = UTF8_ERROR; }
  if (buf[idx] >= 0xf5) { error = UTF8_ERROR; }
  idx += 4;
}

// Returns true if the string is unclosed.
simdjson_inline bool validate_string() {
  idx++; // skip first quote
  while (idx < len && buf[idx] != '"') {
    if (buf[idx] == '\\') {
      idx += 2;
    } else if (simdjson_unlikely(buf[idx] & 0x80)) {
      validate_utf8_character();
    } else {
      if (buf[idx] < 0x20) { error = UNESCAPED_CHARS; }
      idx++;
    }
  }
  if (idx >= len) { return true; }
  return false;
}

simdjson_inline bool is_whitespace_or_operator(uint8_t c) {
  switch (c) {
    case '{': case '}': case '[': case ']': case ',': case ':':
    case ' ': case '\r': case '\n': case '\t':
      return true;
    default:
      return false;
  }
}

//
// Parse the entire input in STEP_SIZE-byte chunks.
//
simdjson_inline error_code scan() {
  bool unclosed_string = false;
  for (;idx<len;idx++) {
    switch (buf[idx]) {
      // String
      case '"':
        add_structural();
        unclosed_string |= validate_string();
        break;
      // Operator
      case '{': case '}': case '[': case ']': case ',': case ':':
        add_structural();
        break;
      // Whitespace
      case ' ': case '\r': case '\n': case '\t':
        break;
      // Primitive or invalid character (invalid characters will be checked in stage 2)
      default:
        // Anything else, add the structural and go until we find the next one
        add_structural();
        while (idx+1<len && !is_whitespace_or_operator(buf[idx+1])) {
          idx++;
        };
        break;
    }
  }
  // We pad beyond.
  // https://github.com/simdjson/simdjson/issues/906
  // See json_structural_indexer.h for an explanation.
  *next_structural_index = len; // assumed later in partial == stage1_mode::streaming_final
  next_structural_index[1] = len;
  next_structural_index[2] = 0;
  parser.n_structural_indexes = uint32_t(next_structural_index - parser.structural_indexes.get());
  if (simdjson_unlikely(parser.n_structural_indexes == 0)) { return EMPTY; }
  parser.next_structural_index = 0;
  if (partial == stage1_mode::streaming_partial) {
    if(unclosed_string) {
      parser.n_structural_indexes--;
      if (simdjson_unlikely(parser.n_structural_indexes == 0)) { return CAPACITY; }
    }
    // We truncate the input to the end of the last complete document (or zero).
    auto new_structural_indexes = find_next_document_index(parser);
    if (new_structural_indexes == 0 && parser.n_structural_indexes > 0) {
      if(parser.structural_indexes[0] == 0) {
        // If the buffer is partial and we started at index 0 but the document is
        // incomplete, it's too big to parse.
        return CAPACITY;
      } else {
        // It is possible that the document could be parsed, we just had a lot
        // of white space.
        parser.n_structural_indexes = 0;
        return EMPTY;
      }
    }
    parser.n_structural_indexes = new_structural_indexes;
  } else if(partial == stage1_mode::streaming_final) {
    if(unclosed_string) { parser.n_structural_indexes--; }
    // We truncate the input to the end of the last complete document (or zero).
    // Because partial == stage1_mode::streaming_final, it means that we may
    // silently ignore trailing garbage. Though it sounds bad, we do it
    // deliberately because many people who have streams of JSON documents
    // will truncate them for processing. E.g., imagine that you are uncompressing
    // the data from a size file or receiving it in chunks from the network. You
    // may not know where exactly the last document will be. Meanwhile the
    // document_stream instances allow people to know the JSON documents they are
    // parsing (see the iterator.source() method).
    parser.n_structural_indexes = find_next_document_index(parser);
    // We store the initial n_structural_indexes so that the client can see
    // whether we used truncation. If initial_n_structural_indexes == parser.n_structural_indexes,
    // then this will query parser.structural_indexes[parser.n_structural_indexes] which is len,
    // otherwise, it will copy some prior index.
    parser.structural_indexes[parser.n_structural_indexes + 1] = parser.structural_indexes[parser.n_structural_indexes];
    // This next line is critical, do not change it unless you understand what you are
    // doing.
    parser.structural_indexes[parser.n_structural_indexes] = uint32_t(len);
    if (parser.n_structural_indexes == 0) { return EMPTY; }
  } else if(unclosed_string) { error = UNCLOSED_STRING; }
  return error;
}

private:
  const uint8_t *buf;
  uint32_t *next_structural_index;
  dom_parser_implementation &parser;
  uint32_t len;
  uint32_t idx{0};
  error_code error{SUCCESS};
  stage1_mode partial;
}; // structural_scanner
