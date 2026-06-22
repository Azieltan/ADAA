# CCP6214 Assignment Compliance Checklist

Generated against `CCP6214_Assigment.pdf` on 2026-06-16.

## Completed in this repository

- [x] Standard C++ implementations are present in `src/`.
- [x] Dataset generator creates unique randomized 10-digit positive integer keys and 5-letter lowercase strings.
- [x] Radix sort processes digits from rightmost to leftmost and outputs sorted `(integer,string)` rows.
- [x] Heap sort uses a max-heap and outputs sorted `(integer,string)` rows.
- [x] Hash table search benchmarks best, average, and worst cases for AVL-tree chaining and linked-list chaining.
- [x] At least 10 benchmark input sizes are documented in `doc/benchmark_results.csv`.
- [x] The 80M sorting comparison in `doc/sorting_comparison_80m.txt` reports a 131.1216 second difference, satisfying the >= 60 second requirement.
- [x] Complexity analysis, experiment table, charts, conclusion, and APA-style references are included in `doc/Assignment_Report.md`.
- [x] Scripts now use the current repository path instead of a hard-coded user folder.

## Must be completed with real group evidence before submission

- [ ] Replace all placeholder group details in `doc/Assignment_Report.md`:
  - group leader name
  - each student ID
  - each student name in alphabetical order
  - each phone number
  - each member's concrete task descriptions
- [ ] Replace placeholder member details in the source-code header blocks if required by your tutor.
- [ ] Export the final report as DOCX. The PDF states zero mark may apply if the group fails to submit documentation in DOCX format.
- [ ] Add the marksheet checklist, table of contents with page numbers/links, and question sections in the final DOCX format.
- [ ] Add hardware specification screenshots for each member.
- [ ] Add command prompt running-time screenshots for every input size and algorithm run (all 10 sizes must still be run by members, as per instructions).
- [ ] Add a Microsoft OneDrive folder link for big input/output files (Optional now, since data storage requirements are reduced).
- [ ] Include required files in the final zip (updated per Mr Shaari's clarification):
  - DOCX report.
  - `.cpp` source files.
  - Exactly ONE sample `.csv` dataset file (e.g., `dataset_1000.csv`) as proof.
  - Exactly ONE corresponding output file for each algorithm as proof (e.g., `radix_sorted_dataset_1000.csv`, `heap_sort_dataset_1000.csv`, `hash_table_search_dataset_1000.txt`).
- [ ] Name the final zip using the required format, for example `T13L_G04.zip`.

## Compliance Notes

- The repository cannot truthfully complete personal/group fields, hardware screenshots, running-time screenshots, or OneDrive links without the real evidence from each member.
- **Clarification Update**: As confirmed by Mr Shaari, only one input dataset and one output file per algorithm are required as proof of correctness in the submission zip to resolve data storage limitations. However, all 10 datasets must still be run by members to fill out the timing tables and charts in the report.
- Generated datasets and large outputs are ignored by `.gitignore` to keep the repository small.
