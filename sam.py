import os

proj_dir = "filepattern"
output_fname = proj_dir.split("/")[-1]
output_folder = "parsed_output"
output_file_path = os.path.join(output_folder, f"parsed_{output_fname}")

# Create the output folder if it doesn't exist
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# Now, you can use output_file_path to write your file
print(output_file_path)
