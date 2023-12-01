import os
import extract_class
import clang_parser
import opensource_codellm

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
        if user_choice == '1':
            print("Selected : SCB NCAT LLM server")
            model = opensource_codellm.init_axle_models()
            return opensource_codellm.phind_LLM("Phind/Phind-CodeLlama-34B-v2", generated_promt, model)
        elif user_choice == '2':
            print("Code generation from together.ai API")
            return opensource_codellm.together_api(generated_promt)
        else:
            print("Invalid option. Please select a valid option (1 or 2).")
            return None, None

    def run(self):
        new_dir = os.path.join(self.output_dir, self.proj_dir.split('/')[-1])
        if not os.path.exists(new_dir):
            os.makedirs(new_dir)

        output_dest = self.output_destination(new_dir)
        class_definition, selected_class = extract_class.extract_class_main(self.proj_dir, output_dest)
        self.write_data(class_definition, os.path.join(new_dir, f"{self.proj_dir.split('/')[-1]}_{selected_class}_class.cpp"))

        print("Select an option:")
        print("1. Generate code from SCB NCAT LLM server (Internal server)")
        print("2. Generate code from together.ai API")
        user_choice = input("Enter the number of your choice: ")

        generated_binding, execution_time = self.generate_binding(user_choice, class_definition)
        if generated_binding and execution_time:
            print(f" Model code generation time: {execution_time}")
            self.write_data(generated_binding, os.path.join(new_dir, f"GenAi_{selected_class}_binding.cpp"))

if __name__ == "__main__":
    proj_dir = 'external_proj/simdjson'
    generator = CodeGenerator(proj_dir, "output_folder")
    generator.run()
