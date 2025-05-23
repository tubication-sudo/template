import random
import pathlib
import platform
import subprocess

lib_path = pathlib.Path(__file__).parent

number_of_testcase = {
    "random": 50
}

# Arguments for compiling C++ files
args = ['g++', '-std=c++17', '-I', str(lib_path)]

# Define paths for generator, solution file, and test case folder
gen_bin = pathlib.Path(__file__).parent / 'generator'
solution_file = pathlib.Path(__file__).parent / 'solution.cpp'
testcase_folder = pathlib.Path(__file__).parent / 'testcase'

testcase_folder.mkdir(exist_ok=True)

# Compile the solution file
solution_binary = solution_file.with_suffix('.exe' if platform.system() == 'Windows' else '')
print(f"Compiling solution: {solution_file} to {solution_binary}")
subprocess.run(args + [str(solution_file), '-o', str(solution_binary)], check=True)

if not solution_binary.exists():
    print(f"Error: Failed to compile solution from {solution_file}")
    exit(1)

# Compile and run C++ test case generators
for gen in gen_bin.glob('*.cpp'):
    binary = gen.with_suffix('.exe' if platform.system() == 'Windows' else '')

    print(f"Compiling generator file: {gen} to {binary}")
    subprocess.run(args + [str(gen), '-o', str(binary)], check=True)

    # Check if the compiled generator binary exists
    if not binary.exists():
        print(f"Error: Failed to compile generator file {gen}")
        continue

    name_test = gen.stem
    num_tests = number_of_testcase.get(name_test, 0)

    for i in range(num_tests):
        seed = random.randint(0, 1000000)

        input_file = testcase_folder / f'{name_test}_{i:02d}.inp'
        output_file = testcase_folder / f'{name_test}_{i:02d}.out'

        with input_file.open('w') as infile:
            subprocess.run([str(binary), str(seed)], stdout=infile, check=True)

        with input_file.open('r') as infile, output_file.open('w') as outfile:
            subprocess.run([str(solution_binary)], stdin=infile, stdout=outfile, check=True)

# Process Python-based generators
for gen in gen_bin.glob('*.py'):
    name_test = gen.stem + "_py"
    num_tests = number_of_testcase.get(name_test, 0)

    for i in range(num_tests):
        seed = random.randint(0, 1000000)

        input_file = testcase_folder / f'{name_test}_{i:02d}.inp'
        output_file = testcase_folder / f'{name_test}_{i:02d}.out'

        with input_file.open('w') as infile:
            subprocess.run(['python3', str(gen), str(seed)], stdout=infile, check=True)

        with input_file.open('r') as infile, output_file.open('w') as outfile:
            subprocess.run([str(solution_binary)], stdin=infile, stdout=outfile, check=True)

print("Test case generation complete.")
