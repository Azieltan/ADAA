# CCP6214 Algorithm Design and Analysis (2610)
# Assignment Report Template

**Assignment Weightage:** 40%  
**Lecture Section:** TC4L  
**Tutorial Section:** T13L  
**Group Number:** G04  
**Group ID:** T13L_G04  
**Group Leader Name:** [Insert group leader name]  
**Submission Deadline:** 22 June 2026, 11:59 PM  
**OneDrive Big Files Folder:** [Optional: Insert OneDrive link if you choose to upload all 10 datasets, though only one input/output is required for proof]

---

## Group Member Information

> Replace placeholders with real student details. Names must be in alphabetical order. Label the group leader with `(Leader)`. Every member should have task percentage `100%`.

| No. | Student ID | Student Name and Phone Number | Task Percentage | Task Descriptions |
|---:|---|---|---:|---|
| 1 | 261UC240LY | Aziel Tan Zheng Chuan | 100% | Dataset generator, benchmark execution, evidence collection, final verification |
| 2 | 261UC240PJ | See Wing Kit | 100% | Radix sort implementation, radix step output, sorting analysis, demo explanation |
| 3 | 261UC26145 | Soo Kian Rong | 100% | Heap sort implementation, heap step output, complexity analysis, demo explanation |
| 4 | 261UC2406W | Vincent Lock Chun Kit | 100% | Hash table search implementation, benchmark verification, AVL/list comparison, APA references |

Every student is responsible for 100% of this group assignment work and must understand all submitted answers.

---

## Marksheet Checklist

| Question | Criteria | Weight | Status | Evidence |
|---|---|---:|---|---|
| Q1 | Dataset generation | 5 | Mostly complete | `src/dataset_generator.cpp`, generated `dataset_n.csv`, Section Q1 |
| Q2 | Radix sort from rightmost character | 5 | Mostly complete | `src/radix_sort.cpp`, `src/radix_sort_step.cpp`, Section Q2 |
| Q3 | Heap sort using max heap | 5 | Mostly complete | `src/heap_sort.cpp`, `src/heap_sort_step.cpp`, Section Q3 |
| Q4 | Hash table search | 5 | Mostly complete | `src/hash_table.h`, `src/hash_table_search.cpp`, `src/hash_table_search_step.cpp`, Section Q4 |
| Q5 | Conclusion and AVL comparison | 5 | Complete draft | Section Q5 |
| Q6 | Document clarity and completeness | 5 | Needs final evidence | DOCX, screenshots, TOC, page numbers, OneDrive link |
| Q7 | Experiments | 5 per member | Needs screenshots and member runs | `doc/benchmark_results.csv`, charts, runtime screenshots |
| Q8 | Interview, demo and Q&A | 5 per member | Prepare using this report | Section Q8 |

---

## Table of Contents

> In Microsoft Word: References -> Table of Contents -> Automatic Table. Update the page numbers before final submission.

1. Group Member Information  
2. Marksheet Checklist  
3. Q1 Dataset Generation  
4. Q2 Radix Sort  
5. Q3 Heap Sort  
6. Q4 Hash Table Search  
7. Q5 Conclusion and AVL Comparison  
8. Q6 Documentation Evidence  
9. Q7 Experiment Results  
10. Q8 Interview, Demo, and Q&A Preparation  
11. References  
12. Appendices  

---

## Evidence Placement Guide

Use the slots below to place screenshots, terminal captures, and file excerpts directly inside the matching section. Keep each item close to the related explanation so the marker can verify it quickly.

| Evidence Item | Where to Insert | What to Include |
|---|---|---|
| Dataset generator screenshot | Q1, under the evidence checklist | Terminal window showing `dataset_generator.exe` running and the generated dataset filename |
| Generated dataset excerpt | Q1, under the evidence checklist | 5 to 10 sample rows from `dataset_1000.csv` or the required sample size |
| Radix step screenshot | Q2, under the evidence checklist | Terminal window showing `radix_sort_step.exe` and the row range used |
| Radix full-sort screenshot | Q2, under the evidence checklist | Terminal window showing `radix_sort.exe` for each required input size |
| Radix step output excerpt | Q2, under the evidence checklist | A visible excerpt from `dataset_1000_radix_sorted_step_1_7.txt` |
| Radix sorted CSV excerpt | Q2, under the evidence checklist | A visible excerpt from `radix_sorted_dataset_1000.csv` |
| Heap step screenshot | Q3, under the evidence checklist | Terminal window showing `heap_sort_step.exe` and the row range used |
| Heap full-sort screenshot | Q3, under the evidence checklist | Terminal window showing `heap_sort.exe` for each required input size |
| Heap step output excerpt | Q3, under the evidence checklist | A visible excerpt from `dataset_1000_heap_sorted_step_1_7.txt` |
| Heap sorted CSV excerpt | Q3, under the evidence checklist | A visible excerpt from `heap_sort_dataset_1000.csv` |
| Hash benchmark screenshots | Q4, under the evidence checklist | Tree benchmark, list benchmark, found-target step, and not-found-target step |
| Hash output excerpts | Q4, under the evidence checklist | Visible excerpts from the generated `.txt` output files |
| Hardware screenshots | Q6, in the hardware table | One screenshot per member showing CPU and RAM details |
| Runtime screenshots | Q7, below the timing tables | Terminal screenshots for every dataset size and algorithm run |
| OneDrive link (Optional) | Cover page and Appendix A | Link to large input/output files if they are not inside the zip |

For each screenshot, add a short caption directly underneath it that states the program name, dataset size, and what the screenshot proves.

---

## Source Code Header Required in Each Source File

```cpp
// *********************************************************
// Program: YOUR_FILENAME.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2:
// Member_3:
// Member_4:
// *********************************************************
```

Current repository source files already contain this header structure with `REPLACE_WITH_*` placeholders. Replace those placeholders with real member details before final submission if your tutor checks the headers literally.

---

## Q1 [5] Dataset Generation

### Question Tasks

Generate datasets similar to the sample dataset in the assignment brief:

- each row has two fields: integer key and lowercase string value;
- integer keys are unique, random, positive, and 10 digits long;
- integer range is `1,000,000,000` to `9,999,999,999`;
- string values contain 5 lowercase alphabet letters;
- rows are randomized before sorting;
- the group leader student ID is used as the seed after mapping letters to digits.

### Implementation Summary

The dataset generator is implemented in `src/dataset_generator.cpp`. It accepts a dataset size `n` and an optional student ID:

```powershell
.\bin\dataset_generator.exe 1000 243UC247CT
```

For the sample student ID `243UC247CT`, the letter mapping produces seed `2431324730`. The program uses `mt19937_64` with this seed and a custom `SimpleHashSet` to ensure uniqueness without relying on sorting/searching library data structures.

### Output

The output file is named:

```text
dataset_n.csv
```

Example row format:

```text
8617903570,pqvfp
```

### Complexity

Dataset generation is expected `O(N)` time for `N` records, assuming low collision frequency in the uniqueness hash set. Space complexity is `O(N)` because generated records and uniqueness-tracking nodes are stored.

### Required Evidence to Insert

- [ ] Screenshot of `dataset_generator.exe` running.
- [ ] Screenshot or excerpt of generated `dataset_1000.csv`.
- [ ] OneDrive link if generated CSV files are too large for the zip submission.

Insert the screenshots and dataset excerpt directly below this checklist.

Place 1 screenshot of the generator run, followed by 1 small data excerpt from the generated CSV.

---

## Q2 [5] Radix Sort from Rightmost Character

### Question Tasks

Implement radix sort processing from the rightmost digit. The program must sort by the integer key and output `(integer,string)` rows.

### Implementation Summary

Radix sort is implemented in:

- `src/radix_sort.cpp`
- `src/radix_sort_step.cpp`

The implementation uses stable counting sort for each digit from `d = 10` down to `d = 1`, where `d = 10` is the least significant digit.

### Commands

Full sort:

```powershell
.\bin\radix_sort.exe dataset_1000.csv
```

Step output:

```powershell
.\bin\radix_sort_step.exe dataset_1000.csv 1 7
```

### Output Files

```text
radix_sorted_dataset_n.csv
dataset_n.radix_sorted_dataset_n.csv
dataset_n_radix_sorted_step_startrow_endrow.txt
```

### Time Complexity

For `N` records, `d` digits, and radix base `K = 10`, radix sort takes:

```text
Best case:    O(d * (N + K))
Average case: O(d * (N + K))
Worst case:   O(d * (N + K))
```

Because the keys are fixed 10-digit integers and base 10 is used, the practical runtime scales linearly with `N`.

### Space Complexity

```text
O(N + K)
```

The extra space is required for the counting sort output buffer and digit counts.

### Required Evidence to Insert

- [x] Screenshot of `radix_sort_step.exe`.
- [x] Screenshot of `radix_sort.exe` running for each input size.
- [x] Excerpt of `dataset_1000_radix_sorted_step_1_7.txt`.
- [x] Excerpt of `radix_sorted_dataset_1000.csv`.

**Screenshot of `radix_sort_step.exe`**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\radix_sort_step.exe dataset_1000.csv 1 7
Successfully logged radix sort steps to dataset_1000_radix_sorted_step_1_7.txt
```
*Caption: Terminal window showing `radix_sort_step.exe` and the row range 1 to 7.*

**Screenshot of `radix_sort.exe`**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\radix_sort.exe dataset_1000.csv
Loaded 1000 records.
Radix Sort completed in 0.000306 seconds.

PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\radix_sort.exe dataset_5000.csv
Loaded 5000 records.
Radix Sort completed in 0.000786 seconds.

PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\radix_sort.exe dataset_10000.csv
Loaded 10000 records.
Radix Sort completed in 0.001656 seconds.
```
*Caption: Terminal window showing `radix_sort.exe` running for input sizes 1000, 5000, and 10000.*

**Excerpt of `dataset_1000_radix_sorted_step_1_7.txt`**
```text
Sample radix_sort_step_1_7.txt
(processing from the rightmost character)
[8617903570/nzjak, 8076568198/btlzy, 8991682790/zihhz, 5981322282/uojzk, 4721475084/yskdr, 6356042608/iqygo, 8780928345/nhhcm] original
[8617903570/nzjak, 8991682790/zihhz, 5981322282/uojzk, 4721475084/yskdr, 8780928345/nhhcm, 8076568198/btlzy, 6356042608/iqygo] d=10
[6356042608/iqygo, 8780928345/nhhcm, 8617903570/nzjak, 5981322282/uojzk, 4721475084/yskdr, 8991682790/zihhz, 8076568198/btlzy] d=9
[4721475084/yskdr, 8076568198/btlzy, 5981322282/uojzk, 8780928345/nhhcm, 8617903570/nzjak, 6356042608/iqygo, 8991682790/zihhz] d=8
[5981322282/uojzk, 6356042608/iqygo, 8991682790/zihhz, 8617903570/nzjak, 4721475084/yskdr, 8076568198/btlzy, 8780928345/nhhcm] d=7
[8617903570/nzjak, 5981322282/uojzk, 8780928345/nhhcm, 6356042608/iqygo, 8076568198/btlzy, 4721475084/yskdr, 8991682790/zihhz] d=6
[6356042608/iqygo, 5981322282/uojzk, 4721475084/yskdr, 8076568198/btlzy, 8991682790/zihhz, 8617903570/nzjak, 8780928345/nhhcm] d=5
[8780928345/nhhcm, 5981322282/uojzk, 4721475084/yskdr, 8991682790/zihhz, 6356042608/iqygo, 8076568198/btlzy, 8617903570/nzjak] d=4
[8617903570/nzjak, 4721475084/yskdr, 6356042608/iqygo, 8076568198/btlzy, 8780928345/nhhcm, 5981322282/uojzk, 8991682790/zihhz] d=3
[8076568198/btlzy, 6356042608/iqygo, 8617903570/nzjak, 4721475084/yskdr, 8780928345/nhhcm, 5981322282/uojzk, 8991682790/zihhz] d=2
[4721475084/yskdr, 5981322282/uojzk, 6356042608/iqygo, 8076568198/btlzy, 8617903570/nzjak, 8780928345/nhhcm, 8991682790/zihhz] d=1
```

**Excerpt of `radix_sorted_dataset_1000.csv`**
```csv
1002732732,mlmww
1016713099,gotoe
1016995594,kplnb
1021413932,shgpa
1022280656,bdkgt
1025594805,riywo
1032079290,xrzpe
1032834713,vjxai
1054771608,qwujn
1055813357,pvhse
```

---

## Q3 [5] Heap Sort Using Max Heap

### Question Tasks

Implement heap sort using a max heap. The program must sort by the integer key and output `(integer,string)` rows.

### Implementation Summary

Heap sort is implemented in:

- `src/heap_sort.cpp`
- `src/heap_sort_step.cpp`

The program builds a max heap, swaps the maximum element at the heap root with the final heap element, reduces the heap size, and restores the max-heap property using `maxHeapify`.

### Commands

Full sort:

```powershell
.\bin\heap_sort.exe dataset_1000.csv
```

Step output:

```powershell
.\bin\heap_sort_step.exe dataset_1000.csv 1 7
```

### Output Files

```text
heap_sort_dataset_n.csv
dataset_n.heap_sorted_dataset_n.csv
dataset_n_heap_sorted_step_startrow_endrow.txt
```

### Time Complexity

```text
Best case:    O(N log N)
Average case: O(N log N)
Worst case:   O(N log N)
```

Building the heap takes `O(N)`, and the repeated extraction and heapify operations dominate the runtime.

### Space Complexity

```text
O(1)
```

Heap sort is in-place apart from small constant variables.

### Required Evidence to Insert

- [x] Screenshot of `heap_sort_step.exe`.
- [x] Screenshot of `heap_sort.exe` running for each input size.
- [x] Excerpt of `dataset_1000_heap_sorted_step_1_7.txt`.
- [x] Excerpt of `heap_sort_dataset_1000.csv`.

**Screenshot of `heap_sort_step.exe`**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\heap_sort_step.exe dataset_1000.csv 1 7
Successfully logged heap sort steps to dataset_1000_heap_sorted_step_1_7.txt
```
*Caption: Terminal window showing `heap_sort_step.exe` and the row range 1 to 7.*

**Screenshot of `heap_sort.exe`**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\heap_sort.exe dataset_1000.csv
Loaded 1000 records.
Heap Sort completed in 0.000143 seconds.

PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\heap_sort.exe dataset_5000.csv
Loaded 5000 records.
Heap Sort completed in 0.000998 seconds.

PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\heap_sort.exe dataset_10000.csv
Loaded 10000 records.
Heap Sort completed in 0.002743 seconds.
```
*Caption: Terminal window showing `heap_sort.exe` running for input sizes 1000, 5000, and 10000.*

**Excerpt of `dataset_1000_heap_sorted_step_1_7.txt`**
```text
Sample heap_sort_step_1_7.txt
(using maxheap)
[8991682790/zihhz, 8076568198/btlzy, 8780928345/nhhcm, 5981322282/uojzk, 4721475084/yskdr, 6356042608/iqygo, 8617903570/nzjak] initial
[8780928345/nhhcm, 8076568198/btlzy, 8617903570/nzjak, 5981322282/uojzk, 4721475084/yskdr, 6356042608/iqygo, 8991682790/zihhz] i = 6
[8617903570/nzjak, 8076568198/btlzy, 6356042608/iqygo, 5981322282/uojzk, 4721475084/yskdr, 8780928345/nhhcm, 8991682790/zihhz] i = 5
[8076568198/btlzy, 5981322282/uojzk, 6356042608/iqygo, 4721475084/yskdr, 8617903570/nzjak, 8780928345/nhhcm, 8991682790/zihhz] i = 4
[6356042608/iqygo, 5981322282/uojzk, 4721475084/yskdr, 8076568198/btlzy, 8617903570/nzjak, 8780928345/nhhcm, 8991682790/zihhz] i = 3
[5981322282/uojzk, 4721475084/yskdr, 6356042608/iqygo, 8076568198/btlzy, 8617903570/nzjak, 8780928345/nhhcm, 8991682790/zihhz] i = 2
[4721475084/yskdr, 5981322282/uojzk, 6356042608/iqygo, 8076568198/btlzy, 8617903570/nzjak, 8780928345/nhhcm, 8991682790/zihhz] i = 1
```

**Excerpt of `heap_sort_dataset_1000.csv`**
```csv
1002732732,mlmww
1016713099,gotoe
1016995594,kplnb
1021413932,shgpa
1022280656,bdkgt
1025594805,riywo
1032079290,xrzpe
1032834713,vjxai
1054771608,qwujn
1055813357,pvhse
```

---

## Q4 [5] Hash Table Search

### Question Tasks

Perform theoretical and experimental running time analysis for hash table search. Cover best, average, and worst cases. Compare linked-list chaining and AVL-tree chaining.

### Implementation Summary

Hash table search is implemented in:

- `src/hash_table.h`
- `src/hash_table_search.cpp`
- `src/hash_table_search_step.cpp`

Two collision-resolution strategies are implemented:

1. linked-list chaining;
2. AVL-tree chaining.

The hash table size is selected as the next prime number greater than or equal to `N`, giving a load factor close to 1 under uniform distribution.

### Commands

Tree chaining benchmark:

```powershell
.\bin\hash_table_search.exe dataset_1000.csv tree
```

Linked-list chaining benchmark:

```powershell
.\bin\hash_table_search.exe dataset_1000.csv list
```

Step output for a found key:

```powershell
.\bin\hash_table_search_step.exe dataset_1000.csv FOUND_TARGET tree
```

Step output for a not-found key:

```powershell
.\bin\hash_table_search_step.exe dataset_1000.csv 123456789 tree
```

### Output Files

```text
hash_table_search_dataset_n.txt
hash_table_search_direct_dataset_n.txt
dataset_n_hash_table_search_step_target.txt
```

### Linked-List Chaining Complexity

```text
Best case:    O(1)
Average case: O(1 + alpha)
Worst case:   O(k), where k is the longest chain length
Space:        O(N)
```

### AVL-Tree Chaining Complexity

```text
Best case:    O(1)
Average case: O(1 + log alpha)
Worst case:   O(log k), where k is the bucket tree size
Space:        O(N)
```

### Required Evidence to Insert

- [x] Screenshot of tree-chaining benchmark.
- [x] Screenshot of linked-list-chaining benchmark.
- [x] Screenshot of found-target step output.
- [x] Screenshot of not-found-target step output.
- [x] Excerpts from the generated `.txt` output files.

**Screenshot of tree-chaining benchmark**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\hash_table_search.exe dataset_1000.csv tree
Loaded 1000 records.
Building AVL Tree Chaining Hash Table...
Worst case height: 3 key: 3507583688
AVL Tree Chaining Hashing Benchmarks logged to hash_table_search_dataset_1000.txt
```
*Caption: Terminal window showing AVL tree-chaining benchmark on dataset size 1000.*

**Screenshot of linked-list-chaining benchmark**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\hash_table_search.exe dataset_1000.csv list
Loaded 1000 records.
Building Linked List Chaining Hash Table...
Worst case chain length: 6 key: 7777208853
Linked List Chaining Hashing Benchmarks logged to hash_table_search_direct_dataset_1000.txt
```
*Caption: Terminal window showing linked-list-chaining benchmark on dataset size 1000.*

**Screenshot of found-target step output**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\hash_table_search_step.exe dataset_1000.csv 1002732732 tree
Successfully logged hash table search path (tree) to dataset_1000_hash_table_search_step_1002732732.txt
```
*Caption: Terminal window showing successful search step output for a found target (1002732732) in an AVL tree hash table.*

**Screenshot of not-found-target step output**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\bin\hash_table_search_step.exe dataset_1000.csv 123456789 tree
Successfully logged hash table search path (tree) to dataset_1000_hash_table_search_step_123456789.txt
```
*Caption: Terminal window showing unsuccessful search step output for a not-found target (123456789) in an AVL tree hash table.*

**Excerpt of `hash_table_search_dataset_1000.txt`**
```text
Best case time: 1e-06 seconds
Average case time: 1e-06 seconds
Worst case time: 2e-06 seconds
```

**Excerpt of `hash_table_search_direct_dataset_1000.txt`**
```text
Best case time: 1e-06 seconds
Average case time: 1e-06 seconds
Worst case time: 1e-06 seconds
```

**Excerpt of `dataset_1000_hash_table_search_step_1002732732.txt`**
```text
9050357310 != 1002732732
1002732732 = 1002732732/mlmww
```

**Excerpt of `dataset_1000_hash_table_search_step_123456789.txt`**
```text
3639416171 != 123456789
-1 != 123456789
```

---

## Q5 [5] Conclusion and AVL Comparison

### Sorting Findings on the Same Hardware

The benchmark results show that radix sort becomes faster than heap sort as dataset size grows. This is expected because radix sort has fixed-digit linear behavior for 10-digit integer keys, while heap sort scales as `O(N log N)`.

For the largest documented 80M sorting benchmark:

| Dataset Size | Radix Sort Time | Heap Sort Time | Difference |
|---:|---:|---:|---:|
| 80,000,000 | 29.6604 seconds | 160.782 seconds | 131.1216 seconds |

The difference is greater than 60 seconds, satisfying the assignment requirement.

### Best Sorting Algorithm for Array-Based Implementation

Radix sort is the better sorting algorithm for this dataset and array-based implementation because:

- the integer keys have fixed length;
- the radix base is small and constant;
- the algorithm avoids `log N` comparison cost;
- it scales close to linearly in the benchmark results.

Heap sort remains useful when constant extra memory is required, but it is slower for this assignment dataset at large input sizes.

### Theoretical Comparison: Array-Based AVL Tree vs Linked-List-Based AVL Tree

| Factor | Linked-List-Based AVL Tree | Array-Based AVL Tree |
|---|---|---|
| Storage layout | Nodes allocated separately and linked with pointers | Nodes stored contiguously in an array/vector |
| Cache locality | Weaker due to pointer chasing | Stronger due to contiguous memory |
| Pointer/index overhead | Stores left/right pointers | Can store smaller child indices |
| Allocation overhead | Many dynamic allocations | Fewer allocations if preallocated |
| Deletion handling | Direct node deletion is simple | Requires free-list or reusable index tracking |
| Practical performance | More flexible but less cache-friendly | Usually faster for large data due to locality |

The array-based AVL implementation is theoretically more efficient in memory locality and may use less structural memory if integer indices replace 64-bit pointers. The linked-list-based AVL tree is simpler to implement and manage dynamically, but may suffer from heap fragmentation and cache misses.

---

## Q6 [5] Documentation Evidence

### Required Items

- [ ] Final report in DOCX format.
- [ ] Cover page with lecture section, tutorial section, group number, group ID, leader name, member IDs, names, phone numbers, task percentage, and task descriptions.
- [ ] Table of contents with page numbers and links.
- [ ] Marksheet checklist.
- [ ] Inputs, outputs, screenshots, explanations, tables, and charts.
- [ ] APA 7 citations and references.
- [ ] One Microsoft OneDrive folder link for large files.
- [ ] Hardware specification screenshots for each member.
- [ ] Command prompt running-time screenshots for every input size.

### Hardware Specification Screenshots

Insert screenshots here:

| Member | Hardware Screenshot |
|---|---|
| [Student Name 1] | [Insert screenshot showing CPU and RAM details] |
| [Student Name 2] | [Insert screenshot showing CPU and RAM details] |
| [Student Name 3] | [Insert screenshot showing CPU and RAM details] |
| [Student Name 4] | [Insert screenshot showing CPU and RAM details] |

---

## Q7 [5 per Member] Experiment Results

### Benchmark Environment

| Item | Value |
|---|---|
| Operating System | Windows 11 64-bit |
| Processor | 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz |
| Memory | 8.00 GB |
| Compiler | GCC/MinGW `g++` with `-O3 -std=c++17` |
| Timing Rule | Running time excludes CSV input reading and output printing |

### 10-Input-Size Results

| Dataset Size (N) | Radix Sort (s) | Heap Sort (s) | AVL Tree Best (s) | AVL Tree Avg (s) | AVL Tree Worst (s) | Linked List Best (s) | Linked List Avg (s) | Linked List Worst (s) |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 1,000 | 0.000306 | 0.000143 | 0.000001 | 0.000001 | 0.000002 | 0.000001 | 0.000001 | 0.000001 |
| 5,000 | 0.000786 | 0.000998 | 0 | 0 | 0 | 0 | 0 | 0 |
| 10,000 | 0.001656 | 0.002743 | 0 | 0 | 0 | 0 | 0 | 0 |
| 50,000 | 0.028918 | 0.016433 | 0 | 0 | 0 | 0 | 0 | 0 |
| 100,000 | 0.055312 | 0.030529 | 0 | 0.000169 | 0.000183 | 0 | 0.000304 | 0.000216 |
| 500,000 | 0.391244 | 0.199570 | 0.000343 | 0.001029 | 0.000918 | 0.001755 | 0.002726 | 0.002099 |
| 1,000,000 | 0.421608 | 0.472718 | 0.000338 | 0.001300 | 0.001261 | 0.000318 | 0.001797 | 0.001518 |
| 2,000,000 | 0.797085 | 1.316610 | 0.000694 | 0.002367 | 0.002349 | 0.001349 | 0.003190 | 0.005680 |
| 5,000,000 | 2.128100 | 3.744500 | 0.001618 | 0.006774 | 0.006470 | 0.001818 | 0.007109 | 0.007272 |
| 10,000,000 | 5.972160 | 7.822690 | 0.004468 | 0.012400 | 0.011984 | 0.004729 | 0.012920 | 0.012373 |

### 80M Sorting Requirement

| Dataset Size (N) | Radix Sort (s) | Heap Sort (s) | Difference (s) | Requirement Met |
|---:|---:|---:|---:|---|
| 80,000,000 | 29.6604 | 160.782 | 131.1216 | Yes, difference >= 60 seconds |

### Charts

Insert or embed these chart files:

- [doc/sorting_benchmark.svg](doc/sorting_benchmark.svg)
- [doc/hash_table_benchmark.svg](doc/hash_table_benchmark.svg)

### Running-Time Screenshots

**Screenshot of Automated Benchmark Script for all 10 Dataset Sizes**
```powershell
PS C:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS> .\scripts\run_benchmarks.ps1
=== Running Timing Benchmarks (10 input sizes) ===

--- Running Benchmark for Size: 1000 ---
Running Radix Sort...
Radix Sort Time: 0.000333 s
Running Heap Sort...
Heap Sort Time: 0.00026 s
Summary for 1000: Radix=0.000333 s, Heap=0.00026 s, HashTreeAvg=0 s, HashListAvg=0 s

--- Running Benchmark for Size: 5000 ---
Running Radix Sort...
Radix Sort Time: 0.001104 s
Running Heap Sort...
Heap Sort Time: 0.00082 s
Summary for 5000: Radix=0.001104 s, Heap=0.00082 s, HashTreeAvg=0 s, HashListAvg=0 s

--- Running Benchmark for Size: 10000 ---
Running Radix Sort...
Radix Sort Time: 0.002688 s
Running Heap Sort...
Heap Sort Time: 0.001834 s
Summary for 10000: Radix=0.002688 s, Heap=0.001834 s, HashTreeAvg=0 s, HashListAvg=0 s

--- Running Benchmark for Size: 50000 ---
Running Radix Sort...
Radix Sort Time: 0.028918 s
Running Heap Sort...
Heap Sort Time: 0.016433 s
Summary for 50000: Radix=0.028918 s, Heap=0.016433 s, HashTreeAvg=0 s, HashListAvg=0 s

--- Running Benchmark for Size: 100000 ---
Running Radix Sort...
Radix Sort Time: 0.055312 s
Running Heap Sort...
Heap Sort Time: 0.030529 s
Summary for 100000: Radix=0.055312 s, Heap=0.030529 s, HashTreeAvg=0.000169 s, HashListAvg=0.000304 s

--- Running Benchmark for Size: 500000 ---
Running Radix Sort...
Radix Sort Time: 0.391244 s
Running Heap Sort...
Heap Sort Time: 0.19957 s
Summary for 500000: Radix=0.391244 s, Heap=0.19957 s, HashTreeAvg=0.001029 s, HashListAvg=0.002726 s

--- Running Benchmark for Size: 1000000 ---
Running Radix Sort...
Radix Sort Time: 0.421608 s
Running Heap Sort...
Heap Sort Time: 0.472718 s
Summary for 1000000: Radix=0.421608 s, Heap=0.472718 s, HashTreeAvg=0.0013 s, HashListAvg=0.001797 s

--- Running Benchmark for Size: 2000000 ---
Running Radix Sort...
Radix Sort Time: 0.797085 s
Running Heap Sort...
Heap Sort Time: 1.31661 s
Summary for 2000000: Radix=0.797085 s, Heap=1.31661 s, HashTreeAvg=0.002367 s, HashListAvg=0.00319 s

--- Running Benchmark for Size: 5000000 ---
Running Radix Sort...
Radix Sort Time: 2.1281 s
Running Heap Sort...
Heap Sort Time: 3.7445 s
Summary for 5000000: Radix=2.1281 s, Heap=3.7445 s, HashTreeAvg=0.006774 s, HashListAvg=0.007109 s

--- Running Benchmark for Size: 10000000 ---
Running Radix Sort...
Radix Sort Time: 5.97216 s
Running Heap Sort...
Heap Sort Time: 7.82269 s
Summary for 10000000: Radix=5.97216 s, Heap=7.82269 s, HashTreeAvg=0.0124 s, HashListAvg=0.01292 s

All benchmarks completed successfully!
```
*Caption: Terminal window showing the automated benchmark script executing all 10 dataset sizes and logging their respective Radix Sort, Heap Sort, and Hash Table Search timings.*

---

## Q8 [5 per Member] Interview, Demo, and Q&A Preparation

### Demo Steps

| Step | Program | Example Input | Expected Output |
|---:|---|---|---|
| 1 | `dataset_generator` | `1000000 243UC247CT` | `dataset_1000000.csv` |
| 2 | `radix_sort_step` | `dataset_1000.csv 1 7` | `dataset_1000_radix_sorted_step_1_7.txt` |
| 3 | `heap_sort_step` | `dataset_1000.csv 1 7` | `dataset_1000_heap_sorted_step_1_7.txt` |
| 4 | `hash_table_search_step` | `dataset_1000.csv FOUND_TARGET tree` | `dataset_1000_hash_table_search_step_FOUND_TARGET.txt` |
| 5 | `radix_sort` | `dataset_1000000.csv` | `radix_sorted_dataset_1000000.csv` and printed runtime |
| 6 | `heap_sort` | `dataset_1000000.csv` | `heap_sort_dataset_1000000.csv` and printed runtime |
| 7 | `hash_table_search` | `dataset_1000000.csv tree/list` | runtime files for best, average, and worst cases |

### Member Presentation Allocation

| Member | Algorithm/Area to Present |
|---|---|
| [Student Name 1] | Dataset generator and benchmark setup |
| [Student Name 2] | Radix sort and radix step output |
| [Student Name 3] | Heap sort and heap step output |
| [Student Name 4] | Hash table search and AVL/list comparison |

### Common Q&A Preparation

1. Why is radix sort faster for this dataset?
   - The keys are fixed-length 10-digit integers, so the number of digit passes is constant.

2. Why does heap sort use `O(1)` extra space?
   - It rearranges records in the same array and only uses constant temporary variables.

3. Why is CSV reading excluded from timing?
   - The assignment requires timing only the algorithm, not input/output overhead.

4. Why benchmark `N` searches for hash table search?
   - A single search is too fast to measure reliably, so the assignment requires repeated searches.

5. Why compare AVL-tree chaining against linked-list chaining?
   - They represent different collision-resolution strategies with different worst-case search guarantees.

---

## References

Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to algorithms* (4th ed.). MIT Press.

Knuth, D. E. (1998). *The art of computer programming: Sorting and searching* (2nd ed., Vol. 3). Addison-Wesley.

---

## Appendix A: Submission Package Checklist (Clarified by Mr Shaari)

- [ ] `T13L_G04.docx` (final report in Word format).
- [ ] `src/*.cpp` (source code files).
- [ ] Exactly ONE sample `.csv` input dataset file (e.g., `dataset_1000.csv`) as proof.
- [ ] Exactly ONE corresponding output file for each algorithm as proof (e.g., `radix_sorted_dataset_1000.csv`, `heap_sort_dataset_1000.csv`, `hash_table_search_dataset_1000.txt`).
- [ ] Runtime screenshots (all 10 sizes must still be run and screenshots placed in the report, but the actual files are omitted from the zip).
- [ ] Hardware screenshots (one per group member).
- [ ] Final zip named `T13L_G04.zip`.

Place the completed DOCX and evidence files in the final submission package. The OneDrive link is now optional since the required files easily fit within the submission size limit.

---

## Appendix B: Known Remaining Placeholders

The following cannot be completed truthfully without real group evidence:

- group leader name;
- student IDs, names, emails, and phone numbers;
- exact CPU/RAM/hardware screenshots for each member;
- command prompt running-time screenshots;
- Microsoft OneDrive folder link;
- final Word-generated table of contents and page numbers.
