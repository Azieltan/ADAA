#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "common.h"
#include <utility>

// Prime number helpers
inline bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

inline int nextPrime(int num) {
    if (num <= 2) return 2;
    int prime = num;
    if (prime % 2 == 0) prime++;
    while (!isPrime(prime)) {
        prime += 2;
    }
    return prime;
}

// ==========================================
// 1. Linked List Chaining Hash Table (Direct)
// ==========================================
class LinkedListHashTable {
public:
    struct Node {
        Record data;
        Node* next;
        Node(const Record& rec, Node* n) : data(rec), next(n) {}
    };

private:
    std::vector<Node*> table;
    int M; // Table size

    int hash(long long key) const {
        return (int)(key % M);
    }

public:
    LinkedListHashTable(int size) {
        M = nextPrime(size);
        table.assign(M, nullptr);
    }

    ~LinkedListHashTable() {
        for (int i = 0; i < M; ++i) {
            Node* curr = table[i];
            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

    int getTableSize() const { return M; }

    void insert(const Record& rec) {
        int h = hash(rec.key);
        // Insert at the head of the list
        table[h] = new Node(rec, table[h]);
    }

    // Search and return pointer to node, logs search path
    Node* search(long long key, std::vector<std::string>& path) {
        int h = hash(key);
        Node* curr = table[h];
        while (curr != nullptr) {
            if (curr->data.key == key) {
                path.push_back(std::to_string(curr->data.key) + " = " + std::to_string(curr->data.key) + "/" + curr->data.value);
                return curr;
            } else {
                path.push_back(std::to_string(curr->data.key) + " != " + std::to_string(key));
            }
            curr = curr->next;
        }
        path.push_back("-1 != " + std::to_string(key));
        return nullptr;
    }

    // Faster search without path logging (for timing benchmarks)
    bool searchFast(long long key) const {
        int h = hash(key);
        Node* curr = table[h];
        while (curr != nullptr) {
            if (curr->data.key == key) return true;
            curr = curr->next;
        }
        return false;
    }

    // Finds a key that resides at the head of its chain (Best Case candidate)
    long long findBestCaseKey() const {
        for (int i = 0; i < M; ++i) {
            if (table[i] != nullptr) {
                return table[i]->data.key;
            }
        }
        return -1;
    }

    // Finds the key that sits at the tail of the longest chain (Worst Case candidate)
    long long findWorstCaseKey(int& longestChainLen) const {
        longestChainLen = 0;
        long long worstKey = -1;
        for (int i = 0; i < M; ++i) {
            int len = 0;
            Node* curr = table[i];
            Node* tail = nullptr;
            while (curr != nullptr) {
                len++;
                tail = curr;
                curr = curr->next;
            }
            if (len > longestChainLen && tail != nullptr) {
                longestChainLen = len;
                worstKey = tail->data.key;
            }
        }
        return worstKey;
    }
};

// ==========================================
// 2. AVL Tree Chaining Hash Table (Tree)
// ==========================================
class AVLTreeHashTable {
public:
    struct AVLNode {
        Record data;
        AVLNode* left;
        AVLNode* right;
        int height;
        AVLNode(const Record& rec) : data(rec), left(nullptr), right(nullptr), height(1) {}
    };

private:
    std::vector<AVLNode*> table;
    int M; // Table size

    int hash(long long key) const {
        return (int)(key % M);
    }

    int height(AVLNode* N) const {
        return N == nullptr ? 0 : N->height;
    }

    int getBalance(AVLNode* N) const {
        return N == nullptr ? 0 : height(N->left) - height(N->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, const Record& rec) {
        if (node == nullptr) {
            return new AVLNode(rec);
        }

        if (rec.key < node->data.key) {
            node->left = insertNode(node->left, rec);
        } else if (rec.key > node->data.key) {
            node->right = insertNode(node->right, rec);
        } else {
            return node; // Duplicate keys not allowed in standard set
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && rec.key < node->left->data.key) {
            return rightRotate(node);
        }
        // Right Right Case
        if (balance < -1 && rec.key > node->right->data.key) {
            return leftRotate(node);
        }
        // Left Right Case
        if (balance > 1 && rec.key > node->left->data.key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && rec.key < node->right->data.key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void destroyTree(AVLNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    AVLNode* searchNode(AVLNode* node, long long key, std::vector<std::string>& path) {
        if (node == nullptr) {
            path.push_back("-1 != " + std::to_string(key));
            return nullptr;
        }

        if (node->data.key == key) {
            path.push_back(std::to_string(node->data.key) + " = " + std::to_string(node->data.key) + "/" + node->data.value);
            return node;
        }

        path.push_back(std::to_string(node->data.key) + " != " + std::to_string(key));

        if (key < node->data.key) {
            return searchNode(node->left, key, path);
        } else {
            return searchNode(node->right, key, path);
        }
    }

    bool searchNodeFast(AVLNode* node, long long key) const {
        if (node == nullptr) return false;
        if (node->data.key == key) return true;
        if (key < node->data.key) return searchNodeFast(node->left, key);
        return searchNodeFast(node->right, key);
    }

    // Finds deep leaf in the tree
    void findDeepestNode(AVLNode* node, int depth, int& maxDepth, long long& deepestKey) const {
        if (node == nullptr) return;
        if (depth > maxDepth) {
            maxDepth = depth;
            deepestKey = node->data.key;
        }
        findDeepestNode(node->left, depth + 1, maxDepth, deepestKey);
        findDeepestNode(node->right, depth + 1, maxDepth, deepestKey);
    }

public:
    AVLTreeHashTable(int size) {
        M = nextPrime(size);
        table.assign(M, nullptr);
    }

    ~AVLTreeHashTable() {
        for (int i = 0; i < M; ++i) {
            destroyTree(table[i]);
        }
    }

    int getTableSize() const { return M; }

    void insert(const Record& rec) {
        int h = hash(rec.key);
        table[h] = insertNode(table[h], rec);
    }

    AVLNode* search(long long key, std::vector<std::string>& path) {
        int h = hash(key);
        return searchNode(table[h], key, path);
    }

    bool searchFast(long long key) const {
        int h = hash(key);
        return searchNodeFast(table[h], key);
    }

    long long findBestCaseKey() const {
        for (int i = 0; i < M; ++i) {
            if (table[i] != nullptr) {
                return table[i]->data.key; // Root of the AVL tree
            }
        }
        return -1;
    }

    long long findWorstCaseKey(int& worstHeight) const {
        worstHeight = 0;
        long long worstKey = -1;
        for (int i = 0; i < M; ++i) {
            if (table[i] != nullptr) {
                int h = table[i]->height;
                if (h > worstHeight) {
                    worstHeight = h;
                    int maxD = 0;
                    long long dKey = table[i]->data.key;
                    findDeepestNode(table[i], 1, maxD, dKey);
                    worstKey = dKey;
                }
            }
        }
        return worstKey;
    }
};

#endif // HASH_TABLE_H
