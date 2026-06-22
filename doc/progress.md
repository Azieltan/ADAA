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
- **阶段七：Git集成与GitHub同步** (Complete)
  - 创建了 `.gitignore` 文件，成功过滤了 1.44GB 的超大测试数据集及临时文件。
  - 初始化本地 Git 仓库，并绑定了 GitHub 远程仓库 `https://github.com/Azieltan/ADAA.git`。
  - 将所有核心源码、脚本及报告推送到 GitHub 上的 `main` 分支。
- **阶段八：拉取并同步云端最新变更** (Complete)
  - 执行 `git pull` 同步了云端最新的修改，包括 `README.md`、Word 报告模板 `doc/CCP6214_Report_Template.md`/`.docx` 以及提交合规清单 `doc/Submission_Compliance_Checklist.md`。
- **阶段九：依据提交要求澄清更新报告模板与合规清单** (Complete)
  - 根据 Mr Shaari 关于数据存储限制的最新澄清，修改了 `doc/Submission_Compliance_Checklist.md`、`doc/CCP6214_Report_Template.md` 和 `README.md`。
  - 明确了仅需提交一个输入数据集和每个算法的一个输出文件作为正确性证明以规避 99MB 存储限制，同时成员仍需本地运行 10 个数据集以完成性能时间记录。
  - 所有更改已在本地完成，且按指示暂不推送到 Git 远程仓库。

- **阶段十：添加标识文件** (Complete)
  - 在根目录创建了 `aziel_version_ADAA` 文件，备注 "update lecturer requirment"。

## 历史进展 (History)
- **2026-06-15 21:53**: 初始化进展文档与实施计划，定位系统 C++ 编译器。
- **2026-06-15 22:04**: 完成 C++ 实现与 10 个基准测试集的测试；发起 80M 超大数据集的生成。
- **2026-06-15 22:11**: 80M 测试运行成功，差值达 131 秒。渲染了 SVG 图表并生成了最终作业报告文档。
- **2026-06-16 14:43**: 配置 `.gitignore`，初始化 Git 仓库，并推送代码至 GitHub (ADAA)。
- **2026-06-22 18:19**: 执行 `git pull` 同步拉取云端的最新更新。
- **2026-06-22 18:31**: 按照 Mr Shaari 的最新指引，更新了合规清单与报告模板，使 OneDrive 提交包可选，只包含单一输入/输出作为证明。
- **2026-06-22 18:55**: 在根目录创建了 `aziel_version_ADAA` 标识文件。
