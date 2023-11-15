import os
from pathlib import Path
import clang_parser
import clang_parser


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

    proj_dir = "filepattern"
    output_fname = proj_dir.split("/")[-1]

    output_dir = "parsed_output"
    # Create the output folder if it doesn't exist
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    output_destination = os.path.join(output_dir, f"parsed_{output_fname}.txt")

    valid_extensions = ['.cpp', '.cxx', '.cc', '.C', '.c++', '.h', '.hh', '.h++', '.hxx', '.hpp', '.H']
    # file_paths = {}
    # with open(output_destination, 'w') as output_file:
    #     file_paths = file_paths = clang_parser.parse_cpp_files(proj_dir, valid_extensions, output_file, file_paths)
    file_paths = {'FilesystemStream': {'Path': 'filepattern/src/filepattern/cpp/util/fs_stream.hpp', 'Start Line': 31, 'End Line': 182}, 
    'FilePattern': {'Path': 'filepattern/src/filepattern/cpp/include/filepattern.h', 'Start Line': 36, 'End Line': 108}, 
    'ExternalMergeSort': {'Path': 'filepattern/src/filepattern/cpp/util/sort.hpp', 'Start Line': 37, 'End Line': 152}}
    print(file_paths)
    # # Display options to the user
    # print("Available classes:")
    print("Available classes:")
    for class_name, class_info in file_paths.items():
        print(f"{class_name} : {class_info['Path']}")

    # Example usage
    # cpp_file_path = "nyxus/src/nyx/nested_feature_aggregation.h"
    # target_class_name = "ChildFeatureAggregation"
    # target_line_number = 9

    # cpp_file_path = "external_proj/simdjson/singleheader/simdjson.h"
    # target_class_name = "padded_string_view"
    # target_line_number = 3656

    # extract_class_content(cpp_file_path, target_class_name, target_line_number)

