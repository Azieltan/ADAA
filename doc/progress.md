# 进展文档 - CCP6214 Algorithm Design & Analysis Assignment

## 当前进展 (Current Progress)
- **阶段一：需求分析与规划** (Complete)
  - 规划完毕，制定实施方案。
- **阶段二：C++核心代码实现** (Complete)
  - 核心排序和哈希查找数据结构编写完毕。
- **阶段三：自动化基准测试与编译器优化修正** (Complete)
  - 基准测试脚本 `run_benchmarks.ps1` 运行成功，已捕捉所有测试数据。
- **阶段四：生成超大测试集以实现60秒运行时差** (Complete)
  - 后台成功生成 80,000,000 数据集。
- **阶段五：运行 80M 数据集排序测试** (Complete)
  - 运行结果：Radix Sort = 29.66s，Heap Sort = 160.78s。
  - 运行时差：**131.12秒**，完美超越规范中 60 秒的硬性要求。
  - 数据记录在 `doc/sorting_comparison_80m.txt`。
- **阶段六：图表渲染与最终 Word 报告模板生成** (Complete)
  - 图表脚本 `generate_charts.ps1` 渲染完成：
    - `doc/sorting_benchmark.svg` (排序对比图)
    - `doc/hash_table_benchmark.svg` (哈希表查找对比图)
  - 编写了详尽的高级排版报告文档：`doc/Assignment_Report.md`。

## 历史进展 (History)
- **2026-06-15 21:53**: 初始化进展文档与实施计划，定位系统 C++ 编译器。
- **2026-06-15 22:04**: 完成 C++ 实现与 10 个基准测试集的测试；发起 80M 超大数据集的生成。
- **2026-06-15 22:11**: 80M 测试运行成功，差值达 131 秒。渲染了 SVG 图表并生成了最终作业报告文档。
