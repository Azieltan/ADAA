#// *********************************************************
// Program: radix_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC5L
// Tutorial Class: T20L
// Trimester: 2610
// Member_1: ID | VINCENT LOCK CHUN KIT | VINCENT.LOCK.CHUN1@STUDENT.MMU.EDU.MY | 0182771488
// Member_2: ID | AZIEL TAN ZHENG CHUAN | AZIEL.TAN.ZHENG1.STUDENT.MMU.EDU.MY | PHONE
// Member_3: ID | SEE WING KIT | SEE.WING.KIT1.STUDENT.MMU.EDU.MY | PHONE
// Member_4: ID | SOO KIAN RONG | SOO.KIAN.RONG1.STUDENT.MMU.EDU.MY | PHONE
// *********************************************************
// Task Distribution
// VINCENT LOCK CHUN KIT: Dataset generator, AVL tree implementation, benchmark orchestration, evidence collection
// AZIEL TAN ZHENG CHUAN: Radix sort implementation and charts, report writing (sorting sections)
// SEE WING KIT: Heap sort implementation and step outputs, script portability fixes, testing and verification
// SOO KIAN RONG: Hash table (linked-list and AVL) implementation, search benchmarks, APA citations
// *********************************************************

#include "common.h"
#include <chrono>

// Extracts the d-th digit of a 10-digit number (d=1 is most significant, d=10 is least significant)
inline int getDigit(long long key, int d) {
    long long place_value = 1;
    for (int i = 0; i < 10 - d; ++i) {
        place_value *= 10;
    }
    return (key / place_value) % 10;
}

// Stable counting sort on the d-th digit
void countingSortForRadix(std::vector<Record>& A, int d) {
    int n = A.size();
    std::vector<Record> B(n);
    int C[10] = {0};

    // Count occurrences
    for (int i = 0; i < n; ++i) {
        int digit = getDigit(A[i].key, d);
        C[digit]++;
    }

    // Cumulative sum
    for (int i = 1; i < 10; ++i) {
        C[i] += C[i - 1];
    }

    // Place elements in sorted order (stable, from right to left)
    for (int i = n - 1; i >= 0; --i) {
        int digit = getDigit(A[i].key, d);
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    // Copy back
    A = B;
}

// Full Radix Sort from d=10 down to d=1
void radixSort(std::vector<Record>& A) {
    for (int d = 10; d >= 1; --d) {
        countingSortForRadix(A, d);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <dataset_csv>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Record> records;
    if (!readCSV(filename, records)) {
        return 1;
    }

    int n = records.size();
    std::cout << "Loaded " << n << " records." << std::endl;

    // Perform sort and measure time
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(records);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    std::cout << "Radix Sort completed in " << seconds << " seconds." << std::endl;

    // Output to files to satisfy both naming styles in specification
    std::string out1 = "radix_sorted_dataset_" + std::to_string(n) + ".csv";
    std::string out2 = "dataset_" + std::to_string(n) + ".radix_sorted_dataset_" + std::to_string(n) + ".csv";

    writeCSV(out1, records);
    writeCSV(out2, records);

    return 0;
}
