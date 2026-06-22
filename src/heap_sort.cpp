#// *********************************************************
// Program: heap_sort.cpp
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
#include <utility>

// Restores the max-heap property for a subtree rooted at node i
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

// Full Heap Sort
void heapSort(std::vector<Record>& A) {
    int n = A.size();
    buildMaxHeap(A);
    for (int i = n - 1; i >= 1; --i) {
        std::swap(A[0], A[i]);
        maxHeapify(A, i, 0);
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
    heapSort(records);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double seconds = duration.count();

    std::cout << "Heap Sort completed in " << seconds << " seconds." << std::endl;

    // Output to files
    std::string out1 = "heap_sort_dataset_" + std::to_string(n) + ".csv";
    std::string out2 = "dataset_" + std::to_string(n) + ".heap_sorted_dataset_" + std::to_string(n) + ".csv";

    writeCSV(out1, records);
    writeCSV(out2, records);

    return 0;
}
