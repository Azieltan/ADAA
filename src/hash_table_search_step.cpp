#// *********************************************************
// Program: hash_table_search_step.cpp
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

int main(int argc, char* argv[]) {
    // Expected arguments: <dataset_csv> <target_key> [mode (tree|list)]
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <dataset_csv> <target_key> [mode (tree|list)]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    long long targetKey = std::stoll(argv[2]);

    std::string mode = "tree"; // default is AVL tree chaining
    if (argc >= 4) {
        mode = argv[3];
    }

    std::vector<Record> records;
    if (!readCSV(filename, records)) {
        return 1;
    }

    int n = records.size();

    // Determine total size of dataset n from the filename if possible, otherwise use input count
    std::string sizeStr = std::to_string(n);
    size_t lastUnderscore = filename.find_last_of('_');
    size_t lastDot = filename.find_last_of('.');
    if (lastUnderscore != std::string::npos && lastDot != std::string::npos && lastDot > lastUnderscore + 1) {
        sizeStr = filename.substr(lastUnderscore + 1, lastDot - lastUnderscore - 1);
    }

    std::string outFilename = "dataset_" + sizeStr + "_hash_table_search_step_" + std::to_string(targetKey) + ".txt";
    std::ofstream outFile(outFilename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open output file: " << outFilename << std::endl;
        return 1;
    }

    std::vector<std::string> path;

    if (mode == "tree") {
        AVLTreeHashTable ht(n);
        for (const auto& rec : records) {
            ht.insert(rec);
        }
        ht.search(targetKey, path);
    } else {
        LinkedListHashTable ht(n);
        for (const auto& rec : records) {
            ht.insert(rec);
        }
        ht.search(targetKey, path);
    }

    // Write path to file
    for (const auto& step : path) {
        outFile << step << "\n";
    }

    outFile.close();
    std::cout << "Successfully logged hash table search path (" << mode << ") to " << outFilename << std::endl;

    return 0;
}
