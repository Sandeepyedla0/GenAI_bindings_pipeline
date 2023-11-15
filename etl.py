import os
import extract_class
import clang_parser
import opensource_codellm

def write_data(generated_binding,save_path):
    # Write the content to the .cpp file
    with open(save_path, 'w', encoding='utf-8') as cpp_file:
        cpp_file.write(generated_binding)

def output_destination(proj_dir):
    output_fname = proj_dir.split("/")[-1]
    output_dir = "output_folder"
    
    # Create the output folder if it doesn't exist
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    output_dest = os.path.join(output_dir, f"parsed_{output_fname}.txt")
    return output_dest

if __name__ == "__main__":

    proj_dir = "filepattern"

    output_dest = output_destination(proj_dir)
    class_definition = extract_class.extract_class_main(proj_dir,output_dest)
    # print(class_definition)
    print("Select an option:")
    print("1. Generate code from SCB NCAT LLM server (Internal server)")
    print("2. Generate code from together.ai API")
    
    # Get user input
    user_choice = input("Enter the number of your choice: ")
    generated_promt = opensource_codellm.promt_generation(class_definition)
    # print(generated_promt)
    save_path = 'bindings.cpp'
    
    if user_choice == '1':
        print("Selected : SCB NCAT LLM server")
        model = opensource_codellm.init_axle_models()
        generated_binding,execution_time = opensource_codellm.phind_LLM("Phind/Phind-CodeLlama-34B-v2", generated_promt, model)

    elif user_choice == '2':
        # Option 2: Code generation from together.ai API
        print("Code generation from together.ai API")
        generated_binding, execution_time = opensource_codellm.together_api(generated_promt)

    else:
        print("Invalid option. Please select a valid option (1 or 2).")
    print(f" Model code generation time: {execution_time}")
    write_data (generated_binding,save_path)