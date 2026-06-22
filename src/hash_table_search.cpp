#// *********************************************************
// Program: hash_table_search.cpp
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
#include "hash_table.h"
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <dataset_csv> [mode (tree|list)]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string mode = "tree"; // Default is AVL tree chaining
    if (argc >= 3) {
        mode = argv[2];
    }

    std::vector<Record> records;
    if (!readCSV(filename, records)) {
        return 1;
    }

    int n = records.size();
    std::cout << "Loaded " << n << " records." << std::endl;

    // Output filename
    std::string sizeStr = std::to_string(n);
    std::string outFilename = "hash_table_search_dataset_" + sizeStr + ".txt";
    if (mode == "list") {
        outFilename = "hash_table_search_direct_dataset_" + sizeStr + ".txt";
    }

    std::ofstream outFile(outFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << outFilename << std::endl;
        return 1;
    }

    if (mode == "tree") {
        std::cout << "Building AVL Tree Chaining Hash Table..." << std::endl;
        // Construct AVL Tree Chain table
        AVLTreeHashTable ht(n);
        for (const auto& rec : records) {
            ht.insert(rec);
        }

        // Find Best Case key (root of the first non-empty bucket)
        long long bestKey = ht.findBestCaseKey();
        if (bestKey == -1) {
            std::cerr << "Error: Table is empty." << std::endl;
            return 1;
        }

        // Find Worst Case key (deepest node in the deepest AVL tree)
        int worstHeight = 0;
        long long worstKey = ht.findWorstCaseKey(worstHeight);
        std::cout << "Worst case height: " << worstHeight << " key: " << worstKey << std::endl;

        // 1. Benchmarking Best Case (N searches for the root key)
        volatile bool dummy = false;
        auto startBest = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(bestKey);
        }
        auto endBest = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationBest = endBest - startBest;
        double bestSec = durationBest.count();

        // 2. Benchmarking Average Case (Search all N keys in the dataset)
        auto startAvg = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(records[i].key);
        }
        auto endAvg = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationAvg = endAvg - startAvg;
        double avgSec = durationAvg.count();

        // 3. Benchmarking Worst Case (N searches for the worst key)
        auto startWorst = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(worstKey);
        }
        auto endWorst = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationWorst = endWorst - startWorst;
        double worstSec = durationWorst.count();

        outFile << "Best case time: " << bestSec << " seconds\n";
        outFile << "Average case time: " << avgSec << " seconds\n";
        outFile << "Worst case time: " << worstSec << " seconds\n";

        std::cout << "AVL Tree Chaining Hashing Benchmarks logged to " << outFilename << std::endl;

    } else if (mode == "list") {
        std::cout << "Building Linked List Chaining Hash Table..." << std::endl;
        LinkedListHashTable ht(n);
        for (const auto& rec : records) {
            ht.insert(rec);
        }

        long long bestKey = ht.findBestCaseKey();
        if (bestKey == -1) {
            std::cerr << "Error: Table is empty." << std::endl;
            return 1;
        }

        int longestChain = 0;
        long long worstKey = ht.findWorstCaseKey(longestChain);
        std::cout << "Worst case chain length: " << longestChain << " key: " << worstKey << std::endl;

        // 1. Benchmarking Best Case
        volatile bool dummy = false;
        auto startBest = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(bestKey);
        }
        auto endBest = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationBest = endBest - startBest;
        double bestSec = durationBest.count();

        // 2. Benchmarking Average Case
        auto startAvg = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(records[i].key);
        }
        auto endAvg = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationAvg = endAvg - startAvg;
        double avgSec = durationAvg.count();

        // 3. Benchmarking Worst Case
        auto startWorst = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; ++i) {
            dummy = dummy || ht.searchFast(worstKey);
        }
        auto endWorst = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationWorst = endWorst - startWorst;
        double worstSec = durationWorst.count();

        outFile << "Best case time: " << bestSec << " seconds\n";
        outFile << "Average case time: " << avgSec << " seconds\n";
        outFile << "Worst case time: " << worstSec << " seconds\n";

        std::cout << "Linked List Chaining Hashing Benchmarks logged to " << outFilename << std::endl;
    }

    outFile.close();
    return 0;
}
