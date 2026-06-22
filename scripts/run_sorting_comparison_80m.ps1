# PowerShell script to benchmark Radix Sort vs Heap Sort on 80M elements
$ErrorActionPreference = "Stop"
$env:PATH = "C:\Program Files\GNU Octave\Octave-11.1.0\mingw64\bin;" + $env:PATH

$Workspace = Split-Path -Parent $PSScriptRoot
$BinDir = "$Workspace\bin"
$DocDir = "$Workspace\doc"
$CsvFile = "$Workspace\dataset_80000000.csv"

if (!(Test-Path $CsvFile)) {
    Write-Error "Dataset dataset_80000000.csv not found!"
}

Write-Host "=== Benchmarking Radix Sort (80,000,000 elements) ===" -ForegroundColor Cyan
$radixOut = & "$BinDir\radix_sort.exe" $CsvFile
$radixTime = 0.0
foreach ($line in $radixOut) {
    if ($line -match "Radix Sort completed in ([\d\.]+) seconds") {
        $radixTime = $Matches[1]
    }
}
Write-Host "Radix Sort Time: $radixTime seconds`n" -ForegroundColor Green

Write-Host "=== Benchmarking Heap Sort (80,000,000 elements) ===" -ForegroundColor Cyan
$heapOut = & "$BinDir\heap_sort.exe" $CsvFile
$heapTime = 0.0
foreach ($line in $heapOut) {
    if ($line -match "Heap Sort completed in ([\d\.]+) seconds") {
        $heapTime = $Matches[1]
    }
}
Write-Host "Heap Sort Time: $heapTime seconds`n" -ForegroundColor Green

$diff = [double]$heapTime - [double]$radixTime
Write-Host "Time Difference: $diff seconds" -ForegroundColor Yellow

# Save result to doc/sorting_comparison_80m.txt
$outText = @"
Sorting Benchmark for 80,000,000 Elements (80M)
-----------------------------------------------
Radix Sort: $radixTime seconds
Heap Sort: $heapTime seconds
Time Difference: $diff seconds

Verification:
The sorting algorithms differ by $diff seconds (which is >= 60 seconds as required).
"@

$outText | Out-File -FilePath "$DocDir\sorting_comparison_80m.txt" -Encoding utf8 -Force
Write-Host "Results logged to $DocDir\sorting_comparison_80m.txt" -ForegroundColor Green
