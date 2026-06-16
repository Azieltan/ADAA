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
- [ ] Add command prompt running-time screenshots for every input size and algorithm run.
- [ ] Add a Microsoft OneDrive folder link for big input/output files.
- [ ] Include required files in the final zip:
  - DOCX report
  - `.cpp` source files
  - required `.csv` input files or OneDrive folder link
  - required `.txt` output files or OneDrive folder link
- [ ] Name the final zip using the required format, for example `T13L_G04.zip`.

## Compliance Notes

- The repository cannot truthfully complete personal/group fields, hardware screenshots, running-time screenshots, or OneDrive links without the real evidence from each member.
- Generated datasets and large outputs are ignored by `.gitignore` to keep the repository small. This is acceptable only if the final DOCX provides the OneDrive folder link required by the assignment.
