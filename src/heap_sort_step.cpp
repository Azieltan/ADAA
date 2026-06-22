#// *********************************************************
// Program: heap_sort_step.cpp
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
#include <utility>

// Restores the max-heap property
void maxHeapify(std::vector<Record>& A, int heapSize, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && A[left].key > A[largest].key) {
        largest = left;
    }
    if (right < heapSize && A[right].key > A[largest].key) {
        largest = right;
    }

    if (largest != i) {
        std::swap(A[i], A[largest]);
        maxHeapify(A, heapSize, largest);
    }
}

// Builds a max-heap from the array
void buildMaxHeap(std::vector<Record>& A) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        maxHeapify(A, n, i);
    }
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
    std::string sizeStr = "1000"; // default fallback
    size_t lastUnderscore = filename.find_last_of('_');
    size_t lastDot = filename.find_last_of('.');
    if (lastUnderscore != std::string::npos && lastDot != std::string::npos && lastDot > lastUnderscore + 1) {
        sizeStr = filename.substr(lastUnderscore + 1, lastDot - lastUnderscore - 1);
    }

    std::string outFilename = "dataset_" + sizeStr + "_heap_sorted_step_" + std::to_string(startRow) + "_" + std::to_string(endRow) + ".txt";
    std::ofstream outFile(outFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << outFilename << std::endl;
        return 1;
    }

    outFile << "Sample heap_sort_step_" << startRow << "_" << endRow << ".txt\n";
    outFile << "(using maxheap)\n";

    // Build the initial max heap
    int n = A.size();
    buildMaxHeap(A);

    // Print initial heap state
    outFile << formatState(A) << " initial\n";

    // Perform heap sort, log each swap and heapify step
    for (int i = n - 1; i >= 1; --i) {
        std::swap(A[0], A[i]);
        maxHeapify(A, i, 0);

        // Write the step state after heapifying
        outFile << formatState(A) << " i = " << i << "\n";
    }

    outFile.close();
    std::cout << "Successfully logged heap sort steps to " << outFilename << std::endl;

    return 0;
}
