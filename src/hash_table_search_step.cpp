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
