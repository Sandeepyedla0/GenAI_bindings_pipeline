from transformers import AutoTokenizer, LlamaForCausalLM
#from human_eval.data import write_jsonl, read_problems
import tqdm
import time
from pathlib import Path
import os

import sys
sys.path.append("/opt/conda/lib/python3.9/site-packages")
import together


def together_api(input_promt):
    code_llm_dict = {
    1: 'Phind/Phind-CodeLlama-34B-v2',
    2: 'Phind/Phind-CodeLlama-34B-Python-v1',
    3: 'WizardLM/WizardCoder-Python-34B-V1.0',
    4: 'WizardLM/WizardCoder-15B-V1.0',
    5: 'togethercomputer/CodeLlama-13b-Instruct',
    6: 'togethercomputer/CodeLlama-13b-Python',
    7: 'togethercomputer/CodeLlama-13b',
    8: 'togethercomputer/CodeLlama-34b-Instruct',
    9: 'togethercomputer/CodeLlama-34b-Python',
    10: 'togethercomputer/CodeLlama-34b',
    11: 'togethercomputer/CodeLlama-7b-Instruct',
    12: 'togethercomputer/CodeLlama-7b-Python',
    13: 'togethercomputer/CodeLlama-7b',
        }
    # Provide user options to select
    print("Available options:")
    for key, value in code_llm_dict.items():
        print(f"{key}: {value}")

    # Get user input
    selected_option = int(input("Select an option  "))

    # Check if the selected option is valid
    if selected_option in code_llm_dict:
        selected_LLM_model = code_llm_dict[selected_option]
        print(f"You selected: {selected_LLM_model}")
    else:
        print("Invalid option. Please select a valid option.")

    start_time = time.time()
    print(f"{selected_LLM_model}: generation in process")
    output = together.Complete.create(
    prompt = input_promt, 
    model = selected_LLM_model, 
    max_tokens = 1024,
    temperature = 0.1,
    top_k = 60,
    top_p = 0.75,
    repetition_penalty = 1.1
    #stop = ['<human>', '\n\n']
    )
    end_time = time.time()
    execution_time = end_time - start_time
    generated_code = output['output']['choices'][0]['text']

    # print generated text
    # print(output['prompt'][0]+output['output']['choices'][0]['text'])
    # print(output['output']['choices'][0]['text'])
    return generated_code, execution_time


def phind_LLM(model_path, prompt_template):

    tokenizer = AutoTokenizer.from_pretrained(model_path, padding_side='left')
    start_time =time.time()
    inputs = tokenizer.encode_plus(prompt_template, return_tensors="pt", truncation=True, max_length=1024, padding="max_length")

    # Input id and generation mask
    input_ids = inputs.input_ids
    attention_mask = inputs.attention_mask

    # output generation
    print("Phind-CodeLlama-34B-v2 generation in process")
    generate_ids = model.generate(input_ids, attention_mask=attention_mask, max_new_tokens=1024, do_sample=False, top_p=0.75, top_k=60, temperature=0.1)

    # Decoding output
    generated_code = tokenizer.decode(generate_ids[0], skip_special_tokens=True)
    generated_code = generated_code.replace(prompt_template, "").split("\n\n\n")[0]

    end_time = time.time()
    execution_time - end_time -start_time
    print(generated_code)
    return generated_code, execution_time

def promt_generation():
    # PolyCoder_Data_Collection/Code-LMs/Data/code_generation_script/axle_projects/filepattern/src/filepattern/cpp/include/filepattern.h
    # instruction = " Generate C++ bindings ('.cpp' file) with the Pybind11 module for a C++ class and provide only the output code without any explanation for :"
    instruction = """ Complete the cmake file library name is 'backend' and target_compile_definitions
    file_path = 'src/filepattern/cpp/bindings.cpp' :
    if(BUILD_PYTHON_LIB)
        find_package(pybind11 CONFIG REQUIRED) """

    # Initialize a dictionary to store file contents with filenames as keys
    file_contents = {}

    # Prompt the user for the number of file paths they want to input
    num_paths = int(input("Enter the number of file paths: "))

    # Loop to gather and read file contents into variables
    for i in range(num_paths):
        file_path = input(f"Enter the file path {i + 1}: ")
        file_path = Path(file_path)
        normalized_path = os.path.normpath(file_path)

    # Read the file content into a variable
    with open(normalized_path, 'r', encoding="utf-8") as source_file:
        file_contents[f'file_{i + 1}'] = source_file.read()

    # Create a prompt_template with the instruction and file contents
    prompt_template = instruction
    # for key in file_contents:
    #     prompt_template += f" {file_contents[key]}"

    # print(f"Generated Prompt Template: {prompt_template}")

    llm_promt = f'''{prompt_template}'''
    return llm_promt

def write_data(generated_binding,save_path):
    # Write the content to the .cpp file
    with open(save_path, 'w', encoding='utf-8') as cpp_file:
        cpp_file.write(generated_binding)

if __name__ == '__main__':

    model_path = "Phind/Phind-CodeLlama-34B-v2"
    model = LlamaForCausalLM.from_pretrained(model_path, device_map="auto")
    tokenizer = AutoTokenizer.from_pretrained(model_path, padding_side='left')

    together.api_key = "e03a7067bb512668df6dc48cffc1da1b04ff24b3639222546cffec115fd1e2fb"

    # see available models
    model_list = together.Models.list()

    # print(f"{len(model_list)} models available")

    # print the first 10 models on the menu
    model_names = [model_dict['name'] for model_dict in model_list]
    model_names


    print("Select an option:")
    print("1. Generate code from SCB NCAT LLM server (Internal server)")
    print("2. Generate code from together.ai API")

    # Get user input
    user_choice = input("Enter the number of your choice: ")
    generated_promt = promt_generation()
    # print(generated_promt)
    # save_path = 'bindings.cpp'
    save_path = 'cmake.txt'


    if user_choice == '1':
        print("Selected : SCB NCAT LLM server")
        generated_binding,execution_time = phind_LLM(model_path, generated_promt)

    elif user_choice == '2':
        # Option 2: Code generation from together.ai API
        print("Code generation from together.ai API")
        generated_binding, execution_time = together_api(generated_promt)

    else:
        print("Invalid option. Please select a valid option (1 or 2).")
    write_data (generated_binding,save_path)

    print(f" Model code generation time: {execution_time}")





    