# CCP6214 ADAA Assignment

This repository contains the C++ implementations, benchmark scripts, and report material for the CCP6214 Algorithm Design & Analysis assignment.

## Requirements Covered

- Dataset generator for randomized unique `(10-digit integer, 5-letter lowercase string)` records.
- Radix sort from the rightmost digit.
- Heap sort using a max heap.
- Hash table search using linked-list chaining and AVL-tree chaining.
- Step-output programs for demo requirements.
- Benchmark results for 10 input sizes and an 80M sorting comparison showing a runtime gap greater than 60 seconds.

## Run

From the repository root:

```powershell
.\scripts\run_benchmarks.ps1
.\scripts\generate_charts.ps1
```

For the 80M benchmark, place `dataset_80000000.csv` in the repository root, compile the programs with `run_benchmarks.ps1`, then run:

```powershell
.\scripts\run_sorting_comparison_80m.ps1
```

Generated large datasets and output files are intentionally ignored by Git. Submit them through the required OneDrive folder link if the zip file exceeds the assignment size limit.
