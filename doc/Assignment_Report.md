# CCP6214 - Algorithm Design & Analysis (2610)
## Assignment Report: Sorting and Searching Algorithms Comparative Analysis

**Lecture Section:** TC4L  
**Tutorial Section:** T13L  
**Group Number:** G04  
**Group ID:** T13L_G04  
**Group Leader:** [Group Leader Name]  

---

### Group Member Information & Task Distribution
| No. | Student ID | Student Name (Alphabetical) | Phone Number | Task Percentage | Task Descriptions |
|---|---|---|---|---|---|
| 1 | [Leader ID] | **[Leader Name] (Leader)** | [Phone] | 100% | Dataset generator, AVL tree implementation, benchmarks execution |
| 2 | [Member ID 2] | [Member Name 2] | [Phone] | 100% | Radix sort implementation, step logic, report writing |
| 3 | [Member ID 3] | [Member Name 3] | [Phone] | 100% | Heap sort implementation, step logic, theoretical analysis |
| 4 | [Member ID 4] | [Member Name 4] | [Phone] | 100% | Hash table implementation, benchmarks verification, APA citations |

---

## 1. Introduction and Objectives
This assignment performs a comparative study of key computer science algorithms:
1. **Sorting**: Radix Sort (least-significant digit first) vs. Heap Sort (using a Max-Heap).
2. **Searching**: Hash Table Search with collision resolution using Linked List Chaining vs. AVL Balanced Binary Search Tree Chaining.

All algorithms are implemented from scratch in C++ without using language-specific sorting or searching libraries to understand their lower-level performance characteristics, memory layout, and compiler optimization effects.

---

## 2. Theoretical Complexity Analysis

### 2.1 Sorting Algorithms

#### Radix Sort
- **Time Complexity**: 
  - **Best, Average, and Worst Cases**: $O(d \cdot (N + K))$, where $N$ is the number of elements, $d$ is the number of digits/characters, and $K$ is the radix base.
  - Since keys are $10$-digit integers, $d = 10$. We use base-10 counting sort, so $K = 10$. Thus, the time complexity scales strictly linearly as $O(10 \cdot (N + 10)) \approx O(N)$.
- **Space Complexity**: $O(N + K)$ auxiliary memory for the counting sort output buffer and frequency buckets.
- **Stability**: Stable. The relative order of duplicate elements is preserved, which is a mathematical requirement for Radix Sort to work when sorting digit-by-digit.

#### Heap Sort
- **Time Complexity**: 
  - **Best, Average, and Worst Cases**: $O(N \log N)$. Building the initial Max-Heap takes $O(N)$ time. Each of the $N-1$ extractions performs a swap and a `maxHeapify` operation which takes $O(\log N)$ time.
- **Space Complexity**: $O(1)$ auxiliary memory. Heap sort is an **in-place** sorting algorithm, requiring no extra buffers.
- **Stability**: Unstable. Swapping elements during heapification violates stable ordering.

---

### 2.2 Searching Algorithms (Hash Table Collision Resolution)

We analyze a hash table of size $M$ where $M$ is chosen as the next prime number larger than or equal to $N$. Under a uniform hashing function ($h(k) = k \pmod M$), the load factor $\alpha = N/M \approx 1$.

#### Linked List Chaining (Direct Chaining)
- **Time Complexity**:
  - **Best Case**: $O(1)$ - The element is found at the head of the bucket list.
  - **Average Case**: $O(1 + \alpha) = O(1)$ - Assuming uniform distribution.
  - **Worst Case**: $O(k)$ where $k$ is the length of the longest chain. If all elements collide in one bucket, searching behaves like a linear search, scaling as $O(N)$.
- **Space Complexity**: $O(N)$ for the chain nodes.

#### AVL Tree Chaining (Tree Chaining)
- **Time Complexity**:
  - **Best Case**: $O(1)$ - The element is at the root of the bucket's AVL tree.
  - **Average Case**: $O(1 + \log \alpha) = O(1)$ - Assuming uniform distribution.
  - **Worst Case**: $O(\log k)$ where $k$ is the size of the bucket tree. Even under severe collisions, the height-balanced tree guarantees logarithmic search time.
- **Space Complexity**: $O(N)$ for the AVL tree nodes (each node requires extra space for height/balance factor indicators).

---

## 3. Experimental Results & Analysis

### 3.1 Experimental Hardware Specifications
- **Operating System**: Windows 11 (64-bit)
- **Processor**: 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40GHz
- **Memory**: 8.00 GB
- **Compiler**: GCC 15.2.0 (MinGW64 via GNU Octave) compiled with `-O3 -std=c++17`

### 3.2 Benchmark Running Times
Below is the compiled timing data from the experiment runs:

| Dataset Size (N) | Radix Sort (s) | Heap Sort (s) | AVL Tree Search (Best) (s) | AVL Tree Search (Avg) (s) | AVL Tree Search (Worst) (s) | Linked List Search (Best) (s) | Linked List Search (Avg) (s) | Linked List Search (Worst) (s) |
|---|---|---|---|---|---|---|---|---|
| **1,000** | 0.000198 | 0.000125 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 |
| **5,000** | 0.001503 | 0.001325 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 |
| **10,000** | 0.002059 | 0.002626 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 |
| **50,000** | 0.025947 | 0.020419 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 | < 0.0001 |
| **100,000** | 0.043528 | 0.031539 | < 0.0001 | 0.000165 | 0.000157 | < 0.0001 | 0.000153 | 0.000175 |
| **500,000** | 0.264035 | 0.286193 | 0.000255 | 0.000914 | 0.001000 | 0.000307 | 0.000958 | 0.001022 |
| **1,000,000** | 0.387753 | 0.629356 | 0.000490 | 0.001526 | 0.001593 | 0.000377 | 0.001530 | 0.001420 |
| **2,000,000** | 0.744502 | 1.334040 | 0.000676 | 0.002647 | 0.002635 | 0.000949 | 0.003045 | 0.003107 |
| **5,000,000** | 1.915280 | 3.929920 | 0.001847 | 0.006151 | 0.005882 | 0.001840 | 0.006100 | 0.005974 |
| **10,000,000** | 3.369070 | 8.413640 | 0.004859 | 0.013828 | 0.012223 | 0.004020 | 0.014100 | 0.014079 |

---

### 3.3 Performance Graphs
*(Double-click or open these files in your web browser to view them in interactive high-resolution)*

1. **Sorting Comparison**: [sorting_benchmark.svg](doc/sorting_benchmark.svg)
2. **Hashing Comparison**: [hash_table_benchmark.svg](doc/hash_table_benchmark.svg)

---

### 3.4 Sorting Analysis & Validation of >= 60s Difference
To satisfy the requirement that the maximum input size has a runtime difference of at least 60 seconds, we conducted a benchmark on **80,000,000 (80 Million)** records:
- **Radix Sort Time**: **29.6604 seconds**
- **Heap Sort Time**: **160.782 seconds**
- **Time Difference**: **131.1216 seconds** (Verified $\ge 60$ seconds)

#### Key Observations:
1. **Radix Sort** maintains a strict linear scale $O(N)$. At 10M size it takes 3.37s, and at 80M it scales 8x to 29.66s, confirming its $O(N)$ nature.
2. **Heap Sort** scales as $O(N \log N)$. As $N$ grows, heapify swaps become highly cache-unfriendly (jumping across an array representing a binary heap causes massive memory cache thrashing), leading to a steep, superlinear curve.
3. **Conclusion**: Radix Sort is significantly faster than Heap Sort for array-based implementations of large datasets of fixed-length integers.

---

### 3.5 Hash Table Search Analysis

#### Best vs. Average vs. Worst Cases:
1. **Best Case**: Extremely fast because the key is at the root/head of the bucket, requiring only $1$ key comparison.
2. **Worst Case**: The search goes to the deepest node of the AVL tree or the end of the linked list chain. In our uniform hashing setup, the maximum chain length was $10$ for $N=10,000,000$.
3. **Cache Effects**: In our benchmark, we conducted $N$ searches. When searching for the *same* worst-case key $N$ times, the CPU cache is extremely hot for that path, making `worst_tree` slightly faster than `avg_tree` (where we search for $N$ *different* keys, resulting in systematic L1/L2/L3 cache misses).

---

## 4. Theoretical Comparison: Array-Based vs. Linked List-Based AVL Trees

For Hash Table collision resolution using AVL trees, we can represent the AVL tree in two ways:
1. **Linked List-Based AVL Tree**: Dynamically allocated nodes via `new` linked by 64-bit pointers.
2. **Array-Based AVL Tree**: Nodes allocated contiguously inside a vector, referencing child nodes by integer indices.

| Metric | Linked List-Based AVL Tree | Array-Based AVL Tree |
|---|---|---|
| **Memory Allocation** | Frequent, expensive heap allocations (`new`/`delete`). | Single contiguous allocation (vector expansion is amortized). |
| **Pointer Size** | 64-bit pointers (8 bytes per pointer; 16 bytes total for left/right). | 32-bit indices (4 bytes per index; 8 bytes total for left/right). |
| **Cache Locality** | Bad. Dynamic nodes are scattered randomly across heap space (pointer chasing). | Excellent. Contiguous index accesses hit L1/L2 caches. |
| **Delete Management** | Easy. Standard memory free-ing. | Requires tracking deleted nodes via a free list/pool. |

**Recommendation**: The array-based AVL tree is highly superior for production systems because it eliminates heap fragmentation, halves structural pointer overhead, and exploits spatial locality for hardware-level caching.

---

## 5. References (APA 7th Edition)
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2022). *Introduction to Algorithms* (4th ed.). MIT Press.
- Knuth, D. E. (1998). *The Art of Computer Programming: Sorting and Searching* (2nd ed., Vol. 3). Addison-Wesley.
