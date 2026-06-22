#// *********************************************************
// Program: radix_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC5L
// Tutorial Class: T20L
// Trimester: 2610
// Member_1: 261UC240LY | Aziel Tan Zheng Chuan | AZIEL.TAN.ZHENG1.STUDENT.MMU.EDU.MY | PHONE
// Member_2: 261UC240PJ | See Wing Kit | SEE.WING.KIT1.STUDENT.MMU.EDU.MY | PHONE
// Member_3: 261UC26145 | Soo Kian Rong | SOO.KIAN.RONG1.STUDENT.MMU.EDU.MY | PHONE
// Member_4: 261UC2406W | Vincent Lock Chun Kit | VINCENT.LOCK.CHUN1@STUDENT.MMU.EDU.MY | PHONE
// *********************************************************
// Task Distribution
// Aziel Tan Zheng Chuan: Dataset generator, benchmark execution, evidence collection, final verification
// See Wing Kit: Radix sort implementation, radix step output, sorting analysis, demo explanation
// Soo Kian Rong: Heap sort implementation, heap step output, complexity analysis, demo explanation
// Vincent Lock Chun Kit: Hash table search implementation, benchmark verification, AVL/list comparison, APA references
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
