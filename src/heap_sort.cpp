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
