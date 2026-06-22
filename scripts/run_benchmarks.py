import os
import subprocess
import time
import sys

# Paths
WORKSPACE = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
COMPILER = r"C:\Program Files\GNU Octave\Octave-11.1.0\mingw64\bin\g++.exe"
SRC_DIR = os.path.join(WORKSPACE, "src")
BIN_DIR = os.path.join(WORKSPACE, "bin")
SCRIPTS_DIR = os.path.join(WORKSPACE, "scripts")
DOC_DIR = os.path.join(WORKSPACE, "doc")

# Create directories if they don't exist
os.makedirs(BIN_DIR, exist_ok=True)

# List of files to compile
COMPILATION_TASKS = [
    ("dataset_generator.cpp", "dataset_generator.exe"),
    ("radix_sort.cpp", "radix_sort.exe"),
    ("radix_sort_step.cpp", "radix_sort_step.exe"),
    ("heap_sort.cpp", "heap_sort.exe"),
    ("heap_sort_step.cpp", "heap_sort_step.exe"),
    ("hash_table_search.cpp", "hash_table_search.exe"),
    ("hash_table_search_step.cpp", "hash_table_search_step.exe"),
]

def compile_all():
    print("=== Compiling C++ Source Files ===")
    for src_file, out_exe in COMPILATION_TASKS:
        src_path = os.path.join(SRC_DIR, src_file)
        out_path = os.path.join(BIN_DIR, out_exe)
        cmd = [COMPILER, "-O3", "-std=c++17", src_path, "-o", out_path]
        print(f"Compiling {src_file} -> {out_exe}...")
        res = subprocess.run(cmd, capture_output=True, text=True)
        if res.returncode != 0:
            print(f"Error compiling {src_file}:")
            print(res.stderr)
            sys.exit(1)
    print("All compiled successfully!\n")

def check_dataset_uniqueness(filename):
    keys = set()
    with open(filename, 'r') as f:
        for line in f:
            if not line.strip(): continue
            parts = line.strip().split(',')
            if len(parts) != 2:
                return False, "Malformed line: " + line
            key = parts[0]
            if key in keys:
                return False, f"Duplicate key found: {key}"
            keys.add(key)
    return True, f"Verified unique: {len(keys)} elements."

def verify_sorted(filename):
    prev_key = -1
    count = 0
    with open(filename, 'r') as f:
        for line in f:
            if not line.strip(): continue
            parts = line.strip().split(',')
            key = int(parts[0])
            if key < prev_key:
                return False, f"Out of order at key {key} after {prev_key}"
            prev_key = key
            count += 1
    return True, f"Verified sorted: {count} elements."

def run_tests():
    print("=== Running Verification Tests ===")
    
    # 1. Generate sample dataset size 1000
    print("Generating dataset_1000.csv...")
    gen_path = os.path.join(BIN_DIR, "dataset_generator.exe")
    res = subprocess.run([gen_path, "1000", "243UC247CT"], capture_output=True, text=True, cwd=WORKSPACE)
    print(res.stdout)
    if res.returncode != 0:
        print("Dataset generator failed.")
        sys.exit(1)

    # Verify uniqueness of generated file
    csv_file = os.path.join(WORKSPACE, "dataset_1000.csv")
    ok, msg = check_dataset_uniqueness(csv_file)
    print(msg)
    if not ok: sys.exit(1)

    # 2. Run radix sort step on rows 1 to 7
    print("Running radix_sort_step...")
    step_path = os.path.join(BIN_DIR, "radix_sort_step.exe")
    subprocess.run([step_path, "dataset_1000.csv", "1", "7"], cwd=WORKSPACE)

    # 3. Run heap sort step on rows 1 to 7
    print("Running heap_sort_step...")
    hstep_path = os.path.join(BIN_DIR, "heap_sort_step.exe")
    subprocess.run([hstep_path, "dataset_1000.csv", "1", "7"], cwd=WORKSPACE)

    # 4. Run hash table search step on a found target and not-found target
    # Let's find the first key in the CSV to search for
    first_key = ""
    with open(csv_file, 'r') as f:
        first_key = f.readline().split(',')[0]
    
    print(f"Running hash_table_search_step for found target: {first_key}...")
    htstep_path = os.path.join(BIN_DIR, "hash_table_search_step.exe")
    subprocess.run([htstep_path, "dataset_1000.csv", first_key, "tree"], cwd=WORKSPACE)
    
    print("Running hash_table_search_step for not-found target: 123456789...")
    subprocess.run([htstep_path, "dataset_1000.csv", "123456789", "tree"], cwd=WORKSPACE)

    # 5. Run full radix sort on dataset_1000.csv
    print("Running radix_sort...")
    rs_path = os.path.join(BIN_DIR, "radix_sort.exe")
    subprocess.run([rs_path, "dataset_1000.csv"], cwd=WORKSPACE)
    sorted_rs = os.path.join(WORKSPACE, "radix_sorted_dataset_1000.csv")
    ok, msg = verify_sorted(sorted_rs)
    print("Radix Sort:", msg)
    if not ok: sys.exit(1)

    # 6. Run full heap sort on dataset_1000.csv
    print("Running heap_sort...")
    hs_path = os.path.join(BIN_DIR, "heap_sort.exe")
    subprocess.run([hs_path, "dataset_1000.csv"], cwd=WORKSPACE)
    sorted_hs = os.path.join(WORKSPACE, "heap_sort_dataset_1000.csv")
    ok, msg = verify_sorted(sorted_hs)
    print("Heap Sort:", msg)
    if not ok: sys.exit(1)

    # 7. Run hash table search benchmark
    print("Running hash_table_search...")
    ht_path = os.path.join(BIN_DIR, "hash_table_search.exe")
    subprocess.run([ht_path, "dataset_1000.csv", "tree"], cwd=WORKSPACE)
    subprocess.run([ht_path, "dataset_1000.csv", "list"], cwd=WORKSPACE)
    print("Verification tests completed successfully!\n")

def run_benchmarks():
    print("=== Running Timing Benchmarks (10 input sizes) ===")
    
    # 10 input sizes
    sizes = [1000, 5000, 10000, 50000, 100000, 500000, 1000000, 3000000, 5000000, 10000000]
    
    benchmark_results = []
    
    gen_path = os.path.join(BIN_DIR, "dataset_generator.exe")
    rs_path = os.path.join(BIN_DIR, "radix_sort.exe")
    hs_path = os.path.join(BIN_DIR, "heap_sort.exe")
    ht_path = os.path.join(BIN_DIR, "hash_table_search.exe")

    for size in sizes:
        print(f"\n--- Running Benchmark for Size: {size} ---")
        
        # Generate dataset
        csv_filename = f"dataset_{size}.csv"
        csv_path = os.path.join(WORKSPACE, csv_filename)
        if not os.path.exists(csv_path):
            print(f"Generating {csv_filename}...")
            subprocess.run([gen_path, str(size), "243UC247CT"], cwd=WORKSPACE)
        
        # Radix Sort timing
        print("Running Radix Sort...")
        start = time.time()
        res = subprocess.run([rs_path, csv_path], capture_output=True, text=True, cwd=WORKSPACE)
        radix_time = 0.0
        for line in res.stdout.split('\n'):
            if "Radix Sort completed in" in line:
                radix_time = float(line.split()[-2])
        print(f"Radix Sort Time: {radix_time} s")

        # Heap Sort timing
        print("Running Heap Sort...")
        res = subprocess.run([hs_path, csv_path], capture_output=True, text=True, cwd=WORKSPACE)
        heap_time = 0.0
        for line in res.stdout.split('\n'):
            if "Heap Sort completed in" in line:
                heap_time = float(line.split()[-2])
        print(f"Heap Sort Time: {heap_time} s")

        # Hash Table Search timing (Tree/AVL)
        print("Running Hash Table (AVL Tree) Search...")
        subprocess.run([ht_path, csv_path, "tree"], cwd=WORKSPACE)
        best_tree_t, avg_tree_t, worst_tree_t = 0.0, 0.0, 0.0
        txt_path = os.path.join(WORKSPACE, f"hash_table_search_dataset_{size}.txt")
        with open(txt_path, 'r') as f:
            for line in f:
                if "Best case time:" in line:
                    best_tree_t = float(line.split()[-2])
                elif "Average case time:" in line:
                    avg_tree_t = float(line.split()[-2])
                elif "Worst case time:" in line:
                    worst_tree_t = float(line.split()[-2])
        
        # Hash Table Search timing (List)
        print("Running Hash Table (Linked List) Search...")
        subprocess.run([ht_path, csv_path, "list"], cwd=WORKSPACE)
        best_list_t, avg_list_t, worst_list_t = 0.0, 0.0, 0.0
        list_txt_path = os.path.join(WORKSPACE, f"hash_table_search_direct_dataset_{size}.txt")
        with open(list_txt_path, 'r') as f:
            for line in f:
                if "Best case time:" in line:
                    best_list_t = float(line.split()[-2])
                elif "Average case time:" in line:
                    avg_list_t = float(line.split()[-2])
                elif "Worst case time:" in line:
                    worst_list_t = float(line.split()[-2])

        result_row = {
            "size": size,
            "radix_time": radix_time,
            "heap_time": heap_time,
            "best_tree": best_tree_t,
            "avg_tree": avg_tree_t,
            "worst_tree": worst_tree_t,
            "best_list": best_list_t,
            "avg_list": avg_list_t,
            "worst_list": worst_list_t
        }
        benchmark_results.append(result_row)
        print(f"Summary for {size}: Radix={radix_time}s, Heap={heap_time}s, HashTreeAvg={avg_tree_t}s, HashListAvg={avg_list_t}s")

    # Save results to a CSV file in doc
    results_csv = os.path.join(DOC_DIR, "benchmark_results.csv")
    with open(results_csv, 'w') as f:
        f.write("size,radix_time,heap_time,best_tree,avg_tree,worst_tree,best_list,avg_list,worst_list\n")
        for row in benchmark_results:
            f.write(f"{row['size']},{row['radix_time']},{row['heap_time']},{row['best_tree']},{row['avg_tree']},{row['worst_tree']},{row['best_list']},{row['avg_list']},{row['worst_list']}\n")
    print(f"Benchmark results written to {results_csv}\n")

if __name__ == "__main__":
    compile_all()
    run_tests()
    run_benchmarks()
