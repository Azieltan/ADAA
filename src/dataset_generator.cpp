#include "common.h"
#include <random>
#include <ctime>

// A custom lightweight hash set for checking key uniqueness
class SimpleHashSet {
private:
    struct Node {
        long long key;
        Node* next;
        Node(long long k, Node* n) : key(k), next(n) {}
    };

    std::vector<Node*> table;
    size_t tableSize;

    size_t hash(long long key) const {
        return (size_t)(key % tableSize);
    }

public:
    SimpleHashSet(size_t size) {
        // Use a table size about twice the expected element count to reduce collisions
        tableSize = size * 2;
        if (tableSize < 100) tableSize = 100;
        table.assign(tableSize, nullptr);
    }

    ~SimpleHashSet() {
        for (size_t i = 0; i < tableSize; ++i) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    // Returns true if key is inserted successfully (was not present), false if key already existed
    bool insert(long long key) {
        size_t h = hash(key);
        Node* curr = table[h];
        while (curr != nullptr) {
            if (curr->key == key) {
                return false; // Already exists
            }
            curr = curr->next;
        }
        table[h] = new Node(key, table[h]);
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <size_n> [student_id]" << std::endl;
        std::cerr << "Example: " << argv[0] << " 1000 243UC247CT" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Error: size_n must be positive." << std::endl;
        return 1;
    }

    std::string studentId = "243UC247CT"; // Default student ID from spec
    if (argc >= 3) {
        studentId = argv[2];
    }

    unsigned long long seed = parseStudentIdToSeed(studentId);
    std::cout << "Student ID: " << studentId << " -> Random Seed: " << seed << std::endl;

    std::mt19937_64 rng(seed);
    SimpleHashSet uniqueKeys(n);
    std::vector<Record> dataset;
    dataset.reserve(n);

    unsigned long long range = 9999999999ULL - 1000000000ULL + 1;

    for (int i = 0; i < n; ++i) {
        long long key;
        do {
            key = 1000000000ULL + (rng() % range);
        } while (!uniqueKeys.insert(key)); // Keep generating until a unique key is found

        std::string value = "";
        for (int j = 0; j < 5; ++j) {
            value += (char)('a' + (rng() % 26));
        }

        dataset.push_back(Record(key, value));
    }

    std::string filename = "dataset_" + std::to_string(n) + ".csv";
    if (writeCSV(filename, dataset)) {
        std::cout << "Successfully generated " << n << " unique records in " << filename << std::endl;
    } else {
        std::cerr << "Error writing CSV file." << std::endl;
        return 1;
    }

    return 0;
}
