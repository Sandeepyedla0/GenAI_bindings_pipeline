import os
from pathlib import Path

def extract_class_content(file_path, target_class_name, line_number):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    class_content = ''
    opening_braces = 0
    closing_braces = 0

    for line in lines[line_number - 1:]:
        class_content += line

        opening_braces += line.count('{')
        closing_braces += line.count('}')

        if opening_braces > 0 and opening_braces == closing_braces:
            break
    print(class_content)

def write_to_file(content):
    with open("output_class.cpp", 'w') as output_file:
        output_file.write(content)


if __name__ == "__main__":
    # Example usage
    # cpp_file_path = "nyxus/src/nyx/nested_feature_aggregation.h"
    # target_class_name = "ChildFeatureAggregation"
    # target_line_number = 9

    cpp_file_path = "external_proj/simdjson/singleheader/simdjson.h"
    target_class_name = "padded_string_view"
    target_line_number = 3656

    extract_class_content(cpp_file_path, target_class_name, target_line_number)

