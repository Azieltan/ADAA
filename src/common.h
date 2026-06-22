#// *********************************************************
// Program: common.h
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

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>

// Record structure holding a 10-digit key and a 5-letter value
struct Record {
    long long key;
    std::string value;

    Record() : key(0), value("") {}
    Record(long long k, const std::string& v) : key(k), value(v) {}
};

// Parses a Student ID into a numeric seed according to the mapping:
// Letters: mapping to (1-based position in alphabet) % 10
// Digits: mapped to themselves
inline unsigned long long parseStudentIdToSeed(const std::string& studentId) {
    unsigned long long seed = 0;
    for (char c : studentId) {
        if (std::isdigit(c)) {
            seed = seed * 10 + (c - '0');
        } else if (std::isalpha(c)) {
            int digit = (std::toupper(c) - 'A' + 1) % 10;
            seed = seed * 10 + digit;
        }
    }
    return seed;
}

// Reads records from a CSV file
inline bool readCSV(const std::string& filename, std::vector<Record>& records) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string keyStr, valStr;
        if (std::getline(ss, keyStr, ',') && std::getline(ss, valStr)) {
            try {
                long long key = std::stoll(keyStr);
                // Strip possible carriage return
                if (!valStr.empty() && valStr.back() == '\r') {
                    valStr.pop_back();
                }
                records.push_back(Record(key, valStr));
            } catch (const std::exception& e) {
                std::cerr << "Warning: Failed to parse line: " << line << " (" << e.what() << ")" << std::endl;
            }
        }
    }
    file.close();
    return true;
}

// Reads records from a CSV file within a specific row range (1-indexed, inclusive)
inline bool readCSVRange(const std::string& filename, std::vector<Record>& records, int startRow, int endRow) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    int currentRow = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        currentRow++;
        if (currentRow >= startRow && currentRow <= endRow) {
            std::stringstream ss(line);
            std::string keyStr, valStr;
            if (std::getline(ss, keyStr, ',') && std::getline(ss, valStr)) {
                try {
                    long long key = std::stoll(keyStr);
                    if (!valStr.empty() && valStr.back() == '\r') {
                        valStr.pop_back();
                    }
                    records.push_back(Record(key, valStr));
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Failed to parse line: " << line << " (" << e.what() << ")" << std::endl;
                }
            }
        }
        if (currentRow > endRow) break;
    }
    file.close();
    return true;
}

// Writes records to a CSV file
inline bool writeCSV(const std::string& filename, const std::vector<Record>& records) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing " << filename << std::endl;
        return false;
    }

    for (const auto& rec : records) {
        file << rec.key << "," << rec.value << "\n";
    }
    file.close();
    return true;
}

#endif // COMMON_H
