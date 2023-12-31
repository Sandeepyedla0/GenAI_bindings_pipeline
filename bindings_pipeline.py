import os
import extract_class
import clang_parser
import opensource_codellm
import argparse

class CodeGenerator:
    def __init__(self, proj_dir, output_dir):
        self.proj_dir = proj_dir
        self.output_dir = output_dir
        self.create_output_dir()

    def create_output_dir(self):
        if not os.path.exists(self.output_dir):
            os.makedirs(self.output_dir)

    def write_data(self, content, save_path):
        with open(save_path, 'w', encoding='utf-8') as file:
            file.write(content)

    def output_destination(self,new_dir):
        output_fname = self.proj_dir.split("/")[-1]
        return os.path.join(new_dir, f"parsed_{output_fname}.txt")

    def generate_binding(self, user_choice, class_definition):
        generated_promt = opensource_codellm.promt_generation(class_definition)
        if user_choice == 1:
            print("Selected : SCB NCAT LLM server")
            axle_llms = { 1: 'Phind/Phind-CodeLlama-34B-v2',
                          2: 'WizardLM/WizardCoder-Python-34B-V1.0',
                          3: 'CodeLlama-34b'}
            # Provide user options to select
            print("Available options:")
            for key, value in axle_llms.items():
                print(f"{key}: {value}")
            # Get user input
            # selected_option = int(input("Select an option  "))
            selected_option = 1
            #  selected option is valid
            if selected_option in axle_llms:
                selected_LLM_model = axle_llms[selected_option]
                print(f"Selected Model: {selected_LLM_model}")
            else:
                print("Invalid option. Please select a valid option.")
            if  selected_option == 1:
                model = phindllm
            elif selected_option == 2:
                model = wizardllm
            return opensource_codellm.phind_LLM(selected_LLM_model, generated_promt, model)
        elif user_choice == 2:
            print("Code generation from together.ai API")
            generated_code, execution_time = opensource_codellm.together_api(generated_promt)
            ## for cmake
            cmake_input = opensource_codellm.cmake_promt_generation(generated_code)
            cmake_generated_content, cmake_gen_time = opensource_codellm.together_api(cmake_input)
            return generated_code, execution_time, cmake_generated_content, cmake_gen_time
        else:
            print("Invalid option. Please select a valid option (1 or 2).")
            return None, None, None

    def run(self):
        if not os.path.exists(self.proj_dir.split('/')[-1]):
            os.makedirs(self.proj_dir.split('/')[-1])
        new_dir = os.path.join(self.output_dir, self.proj_dir.split('/')[-1])
        if not os.path.exists(new_dir):
            os.makedirs(new_dir)

        output_dest = self.output_destination(new_dir)
        class_definition, selected_class = extract_class.extract_class_main(self.proj_dir, output_dest)

        self.write_data(class_definition, os.path.join(new_dir, f"{self.proj_dir.split('/')[-1]}_{selected_class}_class.cpp"))

        print("Select an option:")
        print("1. Generate code from SCB NCAT LLM server (Internal server)")
        print("2. Generate code from together.ai API")
        
        user_choice = int(input("Enter the number of your choice: "))

        # user_choice = 2

        # print("By default - Chosing together.ai API server")
        generated_binding, binding_generation_time,cmake_generated_content,cmake_gen_time = self.generate_binding(user_choice, class_definition)
        
        print(f" Model bindings code generation time: {binding_generation_time}")
        print(f" Model cmake generation time: {cmake_gen_time}")
        
        if generated_binding and cmake_generated_content:
            
            self.write_data(generated_binding, os.path.join(new_dir, f"GenAi_{selected_class}_binding.cpp"))
            self.write_data(cmake_generated_content, os.path.join(new_dir, f"GenAi_bindings_cmake.txt"))
        else:
            print("Writing files failed")

if __name__ == "__main__":
    phindllm, wizardllm = opensource_codellm.load_model_checkpoints()
    
    parser = argparse.ArgumentParser(description='Generate bindings.')
    parser.add_argument('--proj_dir', type=str, required=True, help='Project directory')
    parser.add_argument('--output_dir', type=str, required=True, help='Output directory')
    # #parser.add_argument('--class_name', type=str, required=True, help='Output directory')
    args = parser.parse_args()

    print(" Project parsing in process ")
    generator = CodeGenerator(args.proj_dir, args.output_dir)
    generator.run()

    # proj_dir = "filepattern"
    # output_dir = 'output_dir'
    # generator = CodeGenerator(proj_dir, output_dir)
    # generator.run()
