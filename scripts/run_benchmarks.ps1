# PowerShell script to compile, verify, and run benchmarks for the assignment
$ErrorActionPreference = "Stop"
$env:PATH = "C:\Program Files\GNU Octave\Octave-11.1.0\mingw64\bin;" + $env:PATH

$Workspace = "c:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS"
$Compiler = "C:\Program Files\GNU Octave\Octave-11.1.0\mingw64\bin\g++.exe"
$SrcDir = "$Workspace\src"
$BinDir = "$Workspace\bin"
$DocDir = "$Workspace\doc"

# Ensure directories exist
if (!(Test-Path $BinDir)) { New-Item -ItemType Directory -Path $BinDir | Out-Null }
if (!(Test-Path $DocDir)) { New-Item -ItemType Directory -Path $DocDir | Out-Null }

Write-Host "=== Compiling C++ Source Files ===" -ForegroundColor Green

$Compilations = @(
    @("dataset_generator.cpp", "dataset_generator.exe"),
    @("radix_sort.cpp", "radix_sort.exe"),
    @("radix_sort_step.cpp", "radix_sort_step.exe"),
    @("heap_sort.cpp", "heap_sort.exe"),
    @("heap_sort_step.cpp", "heap_sort_step.exe"),
    @("hash_table_search.cpp", "hash_table_search.exe"),
    @("hash_table_search_step.cpp", "hash_table_search_step.exe")
)

foreach ($comp in $Compilations) {
    $src = "$SrcDir\$($comp[0])"
    $out = "$BinDir\$($comp[1])"
    Write-Host "Compiling $($comp[0]) -> $($comp[1])..."
    & $Compiler -O3 -std=c++17 $src -o $out
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Compilation of $($comp[0]) failed!"
    }
}
Write-Host "All compiled successfully!`n" -ForegroundColor Green

Write-Host "=== Running Verification Tests ===" -ForegroundColor Green

# 1. Generate sample dataset size 1000
Write-Host "Generating dataset_1000.csv..."
& "$BinDir\dataset_generator.exe" 1000 "243UC247CT"
if ($LASTEXITCODE -ne 0) { Write-Error "Dataset generator failed." }

# 2. Run radix sort step on rows 1 to 7
Write-Host "Running radix_sort_step..."
& "$BinDir\radix_sort_step.exe" dataset_1000.csv 1 7

# 3. Run heap sort step on rows 1 to 7
Write-Host "Running heap_sort_step..."
& "$BinDir\heap_sort_step.exe" dataset_1000.csv 1 7

# 4. Run hash table search step on a found target and not-found target
$firstKey = (Get-Content dataset_1000.csv -Head 1).Split(',')[0]
Write-Host "Running hash_table_search_step for found target: $firstKey..."
& "$BinDir\hash_table_search_step.exe" dataset_1000.csv $firstKey tree

Write-Host "Running hash_table_search_step for not-found target: 123456789..."
& "$BinDir\hash_table_search_step.exe" dataset_1000.csv 123456789 tree

# 5. Run full radix sort on dataset_1000.csv
Write-Host "Running radix_sort..."
& "$BinDir\radix_sort.exe" dataset_1000.csv

# 6. Run full heap sort on dataset_1000.csv
Write-Host "Running heap_sort..."
& "$BinDir\heap_sort.exe" dataset_1000.csv

# 7. Run hash table search benchmark
Write-Host "Running hash_table_search..."
& "$BinDir\hash_table_search.exe" dataset_1000.csv tree
& "$BinDir\hash_table_search.exe" dataset_1000.csv list

Write-Host "Verification tests completed successfully!`n" -ForegroundColor Green

Write-Host "=== Running Timing Benchmarks (10 input sizes) ===" -ForegroundColor Green

$Sizes = @(1000, 5000, 10000, 50000, 100000, 500000, 1000000, 2000000, 5000000, 10000000)
$ResultsCsv = "$DocDir\benchmark_results.csv"

# Header of CSV
"size,radix_time,heap_time,best_tree,avg_tree,worst_tree,best_list,avg_list,worst_list" | Out-File -FilePath $ResultsCsv -Encoding utf8 -Force

foreach ($size in $Sizes) {
    Write-Host "`n--- Running Benchmark for Size: $size ---" -ForegroundColor Cyan
    
    $csvFile = "$Workspace\dataset_$size.csv"
    if (!(Test-Path $csvFile)) {
        Write-Host "Generating dataset_$size.csv..."
        & "$BinDir\dataset_generator.exe" $size "243UC247CT"
    }

    # Radix Sort timing
    Write-Host "Running Radix Sort..."
    $radixOut = & "$BinDir\radix_sort.exe" $csvFile
    $radixTime = 0.0
    foreach ($line in $radixOut) {
        if ($line -match "Radix Sort completed in ([\d\.]+) seconds") {
            $radixTime = $Matches[1]
        }
    }
    Write-Host "Radix Sort Time: $radixTime s"

    # Heap Sort timing
    Write-Host "Running Heap Sort..."
    $heapOut = & "$BinDir\heap_sort.exe" $csvFile
    $heapTime = 0.0
    foreach ($line in $heapOut) {
        if ($line -match "Heap Sort completed in ([\d\.]+) seconds") {
            $heapTime = $Matches[1]
        }
    }
    Write-Host "Heap Sort Time: $heapTime s"

    # Hash Table Search timing (Tree/AVL)
    Write-Host "Running Hash Table (AVL Tree) Search..."
    & "$BinDir\hash_table_search.exe" $csvFile tree
    $bestTree = 0.0; $avgTree = 0.0; $worstTree = 0.0
    $treeTxt = "$Workspace\hash_table_search_dataset_$size.txt"
    if (Test-Path $treeTxt) {
        $lines = Get-Content $treeTxt
        foreach ($line in $lines) {
            if ($line -match "Best case time: ([\d\.\-]+) seconds") { $bestTree = $Matches[1] }
            elseif ($line -match "Average case time: ([\d\.\-]+) seconds") { $avgTree = $Matches[1] }
            elseif ($line -match "Worst case time: ([\d\.\-]+) seconds") { $worstTree = $Matches[1] }
        }
    }

    # Hash Table Search timing (List)
    Write-Host "Running Hash Table (Linked List) Search..."
    & "$BinDir\hash_table_search.exe" $csvFile list
    $bestList = 0.0; $avgList = 0.0; $worstList = 0.0
    $listTxt = "$Workspace\hash_table_search_direct_dataset_$size.txt"
    if (Test-Path $listTxt) {
        $lines = Get-Content $listTxt
        foreach ($line in $lines) {
            if ($line -match "Best case time: ([\d\.\-]+) seconds") { $bestList = $Matches[1] }
            elseif ($line -match "Average case time: ([\d\.\-]+) seconds") { $avgList = $Matches[1] }
            elseif ($line -match "Worst case time: ([\d\.\-]+) seconds") { $worstList = $Matches[1] }
        }
    }

    # Write result to CSV
    "$size,$radixTime,$heapTime,$bestTree,$avgTree,$worstTree,$bestList,$avgList,$worstList" | Out-File -FilePath $ResultsCsv -Encoding utf8 -Append
    Write-Host "Summary for ${size}: Radix=$radixTime s, Heap=$heapTime s, HashTreeAvg=$avgTree s, HashListAvg=$avgList s" -ForegroundColor Cyan
}

Write-Host "`nAll benchmarks completed successfully! Results written to: $ResultsCsv" -ForegroundColor Green
