class json_scanner {
public:
  json_scanner() = default;
  simdjson_inline json_block next(const simd::simd8x64<uint8_t>& in);
  // Returns either UNCLOSED_STRING or SUCCESS
  simdjson_inline error_code finish();

private:
  // Whether the last character of the previous iteration is part of a scalar token
  // (anything except whitespace or a structural character/'operator').
  uint64_t prev_scalar = 0ULL;
  json_string_scanner string_scanner{};
};
