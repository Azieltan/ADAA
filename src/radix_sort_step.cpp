#// *********************************************************
// Program: radix_sort_step.cpp
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

// Extracts the d-th digit of a 10-digit number
inline int getDigit(long long key, int d) {
    long long place_value = 1;
    for (int i = 0; i < 10 - d; ++i) {
        place_value *= 10;
    }
    return (key / place_value) % 10;
}

// Formats the array state as: [key1/val1, key2/val2, ...]
std::string formatState(const std::vector<Record>& A) {
    std::string result = "[";
    for (size_t i = 0; i < A.size(); ++i) {
        result += std::to_string(A[i].key) + "/" + A[i].value;
        if (i < A.size() - 1) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

int main(int argc, char* argv[]) {
    // Expected arguments: <dataset_csv> <start_row> <end_row>
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <dataset_csv> <start_row> <end_row>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int startRow = std::stoi(argv[2]);
    int endRow = std::stoi(argv[3]);

    std::vector<Record> A;
    if (!readCSVRange(filename, A, startRow, endRow)) {
        return 1;
    }

    if (A.empty()) {
        std::cerr << "Error: No records loaded from the specified range." << std::endl;
        return 1;
    }

    // Determine total size of dataset n from the filename if possible, otherwise use input count
    // The spec outputs: dataset_<n>_radix_sorted_step_<startrow>_<endrow>.txt
    // We can extract n from the filename (e.g. "dataset_1000.csv" -> 1000)
    std::string sizeStr = "1000"; // default fallback
    size_t lastUnderscore = filename.find_last_of('_');
    size_t lastDot = filename.find_last_of('.');
    if (lastUnderscore != std::string::npos && lastDot != std::string::npos && lastDot > lastUnderscore + 1) {
        sizeStr = filename.substr(lastUnderscore + 1, lastDot - lastUnderscore - 1);
    }

    std::string outFilename = "dataset_" + sizeStr + "_radix_sorted_step_" + std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";
    std::ofstream outFile(outFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << outFilename << std::endl;
        return 1;
    }

    outFile << "Sample radix_sort_step_" << startRow << "_" << endRow << ".txt\n";
    outFile << "(processing from the rightmost character)\n";

    // Print original array state
    outFile << formatState(A) << " original\n";

    // Perform Radix Sort digit by digit and log each step
    for (int d = 10; d >= 1; --d) {
        // Counting sort on d-th digit
        int n = A.size();
        std::vector<Record> B(n);
        int C[10] = {0};

        for (int i = 0; i < n; ++i) {
            C[getDigit(A[i].key, d)]++;
        }
        for (int i = 1; i < 10; ++i) {
            C[i] += C[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int digit = getDigit(A[i].key, d);
            B[C[digit] - 1] = A[i];
            C[digit]--;
        }
        A = B;

        // Write the step state
        outFile << formatState(A) << " d=" << d << "\n";
    }

    outFile.close();
    std::cout << "Successfully logged radix sort steps to " << outFilename << std::endl;

    return 0;
}
