import os
import clang.cindex
import sys
# import libclang

def is_pybind11_usable_class(node):
    # Filter function for Pybind11-usable classes

    # class is part of C++ standard library
    parent = node.semantic_parent
    while parent.kind != clang.cindex.CursorKind.TRANSLATION_UNIT:
        if parent.spelling == "std":
            return False
        parent = parent.semantic_parent

    # class is public
    if node.access_specifier != clang.cindex.AccessSpecifier.PUBLIC:
        return False

    # class has a public constructor
    has_public_constructor = any(
        child.kind == clang.cindex.CursorKind.CONSTRUCTOR and 
        child.access_specifier == clang.cindex.AccessSpecifier.PUBLIC
        for child in node.get_children()
    )
    if not has_public_constructor:
        return False

    # # class does not have complex C++ features
    has_complex_features = any(
        child.kind in {
            clang.cindex.CursorKind.TEMPLATE_TYPE_PARAMETER, # Ignore classes with template type parameters
            clang.cindex.CursorKind.CXX_BASE_SPECIFIER, # Ignore classes with base classes
            clang.cindex.CursorKind.FUNCTION_TEMPLATE, # Ignore classes with function templates
            clang.cindex.CursorKind.CLASS_TEMPLATE, # Ignore classes with class templates
            clang.cindex.CursorKind.CLASS_TEMPLATE_PARTIAL_SPECIALIZATION # # Ignore classes with class template partial specializations
        }
        for child in node.get_children()
    )
    if has_complex_features:
        return False

    return True

def traverse(node, output_file, processed_classes, file_paths):
    if node.kind == clang.cindex.CursorKind.CLASS_DECL and is_pybind11_usable_class(node):
        class_name = node.spelling
        if class_name not in processed_classes:
            # print(class_name)
            processed_classes.add(class_name)
            file_path = node.location.file.name
            start_line = node.location.line 
            end_line = node.extent.end.line  # Get the end line number of the class declaration
            file_paths[class_name] = {
                'path': file_path,
                'class_start_line': start_line,
                'class_end_line': end_line
            }  # Store class name, file path, start line number, and end line number in the dictionary
            output_line = f"Class: {class_name}, Path: {file_path}, Start Line: {start_line}, End Line: {end_line}\n" 
            output_file.write(output_line)

        # # Traverse and print the methods of this class
        # for child in node.get_children():
        #     if child.kind == clang.cindex.CursorKind.CXX_METHOD:
        #         method_name = 'Method: ' + child.spelling
        #         print(method_name)
        #         output_file.write(method_name + '\n')

    # Recurse for children of this node
    for child in node.get_children():
        traverse(child, output_file,processed_classes,file_paths)

def parse_cpp_files(directory, valid_extensions, output_file,file_paths):
    index = clang.cindex.Index.create()
    processed_classes = set()
    for dirpath, dirnames, filenames in os.walk(directory):
        for filename in filenames:
            if any(filename.endswith(ext) for ext in valid_extensions):
                filepath = os.path.join(dirpath, filename)
                tu = index.parse(filepath)
                traverse(tu.cursor, output_file, processed_classes,file_paths)
    return file_paths

# if __name__ == "__main__":
    
#     valid_extensions = ['.cpp', '.cxx', '.cc', '.C', '.c++', '.h', '.hh', '.h++', '.hxx', '.hpp', '.H']
#     proj_dir = "filepattern"
#     output_fname = proj_dir.split("/")[-1]

#     output_dir = "parsed_output"
#     # Create the output folder if it doesn't exist
#     if not os.path.exists(output_dir):
#         os.makedirs(output_dir)
#     output_destination = os.path.join(output_dir, f"parsed_{output_fname}.txt")

#     with open(output_destination, 'w') as output_file:
#         file_paths = parse_cpp_files(proj_dir, valid_extensions, output_file, {})




