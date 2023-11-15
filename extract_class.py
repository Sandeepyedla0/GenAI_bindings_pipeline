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
    return class_content



def extract_class_main(proj_dir,output_dest):

    valid_extensions = ['.cpp', '.cxx', '.cc', '.C', '.c++', '.h', '.hh', '.h++', '.hxx', '.hpp', '.H']

    file_paths = {}
    with open(output_dest, 'w') as output_file:
        file_paths = clang_parser.parse_cpp_files(proj_dir, valid_extensions, output_file, file_paths)
    
    # file_paths = {'FilesystemStream': {'path': 'filepattern/src/filepattern/cpp/util/fs_stream.hpp', 'class_start_line': 31, 'class_end_line': 182}, 
    # 'FilePattern': {'path': 'filepattern/src/filepattern/cpp/include/filepattern.h', 'class_start_line': 36, 'class_end_line': 108}, 
    # 'ExternalMergeSort': {'path': 'filepattern/src/filepattern/cpp/util/sort.hpp', 'class_start_line': 37, 'class_end_line': 152}}
    #print(file_paths)
    
    # # Display options to the user
    print("Available classes:")
    for index, (class_name, class_info) in enumerate(file_paths.items(), start=1):
        print(f"{index}. {class_name} : {class_info['path']}")
    
    while True:
        # Get user input for class selection
        user_input = input("Enter the number corresponding to the class you want to select: ")

        try:
            selected_index = int(user_input)
            if 1 <= selected_index <= len(file_paths):
                selected_class = list(file_paths.keys())[selected_index - 1]
                print(f"Selected class: {selected_class}")
                print(f"File: {file_paths[selected_class]['path']}")
                break
            else:
                print("Invalid input. Please enter a valid number.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")


    class_def = extract_class_content(file_paths[selected_class]['path'], selected_class, file_paths[selected_class]['class_start_line'])
    return class_def,selected_class
