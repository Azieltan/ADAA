# PowerShell script to generate beautiful SVG charts from benchmark_results.csv
$ErrorActionPreference = "Stop"

$Workspace = "c:\Users\aziel\OneDrive\Desktop\ALGORITHM DESIGN AND ANALYSIS"
$DocDir = "$Workspace\doc"
$CsvPath = "$DocDir\benchmark_results.csv"

if (!(Test-Path $CsvPath)) {
    Write-Error "CSV results file not found at $CsvPath"
}

# Read and parse CSV
$lines = Get-Content $CsvPath
$headers = $lines[0].Split(',')
$data = @()
for ($i = 1; $i -lt $lines.Count; $i++) {
    if ([string]::IsNullOrWhiteSpace($lines[$i])) { continue }
    $cols = $lines[$i].Split(',')
    $row = [ordered]@{}
    for ($j = 0; $j -lt $headers.Count; $j++) {
        $row[$headers[$j]] = [double]$cols[$j]
    }
    $data += [PSCustomObject]$row
}

# SVG dimensions
$width = 800
$height = 500
$paddingLeft = 80
$paddingRight = 40
$paddingTop = 50
$paddingBottom = 60

$plotWidth = $width - $paddingLeft - $paddingRight
$plotHeight = $height - $paddingTop - $paddingBottom

# Function to generate Sorting Chart
function Generate-Sorting-Chart {
    $maxSize = 0.0
    $maxTime = 0.0
    foreach ($r in $data) {
        if ($r.size -gt $maxSize) { $maxSize = $r.size }
        if ($r.radix_time -gt $maxTime) { $maxTime = $r.radix_time }
        if ($r.heap_time -gt $maxTime) { $maxTime = $r.heap_time }
    }
    # Round up maxTime to a clean value
    $maxTime = [Math]::Ceiling($maxTime)
    if ($maxTime -eq 0) { $maxTime = 1.0 }

    $svg = @"
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 $width $height" width="100%" height="100%" style="background-color: #121212; font-family: 'Outfit', 'Inter', sans-serif;">
  <!-- Grid Lines and Y-Axis ticks -->
"@

    # Gridlines
    $ticks = 5
    for ($i = 0; $i -le $ticks; $i++) {
        $yVal = $maxTime * ($i / $ticks)
        $yPos = $paddingTop + $plotHeight - ($plotHeight * ($i / $ticks))
        $svg += @"
  <line x1="$paddingLeft" y1="$yPos" x2="$($width - $paddingRight)" y2="$yPos" stroke="#2a2a2a" stroke-width="1" stroke-dasharray="4" />
  <text x="$($paddingLeft - 15)" y="$($yPos + 5)" fill="#aaaaaa" font-size="12" text-anchor="end">$($yVal.ToString("F1"))s</text>
"@
    }

    # X-Axis ticks
    $xTicks = 5
    for ($i = 0; $i -le $xTicks; $i++) {
        $xVal = $maxSize * ($i / $xTicks)
        $xPos = $paddingLeft + ($plotWidth * ($i / $xTicks))
        $xLabel = "$([Math]::Round($xVal / 1000000, 1))M"
        if ($xVal -lt 1000000) { $xLabel = "$([Math]::Round($xVal / 1000, 1))K" }
        if ($xVal -eq 0) { $xLabel = "0" }
        $svg += @"
  <line x1="$xPos" y1="$paddingTop" x2="$xPos" y2="$($paddingTop + $plotHeight)" stroke="#2a2a2a" stroke-width="1" stroke-dasharray="4" />
  <text x="$xPos" y="$($paddingTop + $plotHeight + 20)" fill="#aaaaaa" font-size="12" text-anchor="middle">$xLabel</text>
"@
    }

    # Axes
    $svg += @"
  <!-- Axes -->
  <line x1="$paddingLeft" y1="$paddingTop" x2="$paddingLeft" y2="$($paddingTop + $plotHeight)" stroke="#444444" stroke-width="2" />
  <line x1="$paddingLeft" y1="$($paddingTop + $plotHeight)" x2="$($width - $paddingRight)" y2="$($paddingTop + $plotHeight)" stroke="#444444" stroke-width="2" />
  <text x="$($paddingLeft + $plotWidth / 2)" y="$($height - 10)" fill="#ffffff" font-size="14" font-weight="bold" text-anchor="middle">Dataset Size (N)</text>
  <text x="25" y="$($paddingTop + $plotHeight / 2)" fill="#ffffff" font-size="14" font-weight="bold" text-anchor="middle" transform="rotate(-90 25 $($paddingTop + $plotHeight / 2))">Running Time (seconds)</text>
  <text x="$($width / 2)" y="30" fill="#ffffff" font-size="18" font-weight="bold" text-anchor="middle">Comparative Sorting Performance: Radix Sort vs Heap Sort</text>
"@

    # Plot lines
    $radixPoints = @()
    $heapPoints = @()
    foreach ($r in $data) {
        $x = $paddingLeft + ($plotWidth * ($r.size / $maxSize))
        $yRadix = $paddingTop + $plotHeight - ($plotHeight * ($r.radix_time / $maxTime))
        $yHeap = $paddingTop + $plotHeight - ($plotHeight * ($r.heap_time / $maxTime))
        
        $radixPoints += "$x,$yRadix"
        $heapPoints += "$x,$yHeap"
    }

    $radixStr = $radixPoints -join " "
    $heapStr = $heapPoints -join " "

    $svg += @"
  <!-- Radix Sort Line (Blue) -->
  <polyline points="$radixStr" fill="none" stroke="#4285F4" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" />
  <!-- Heap Sort Line (Red) -->
  <polyline points="$heapStr" fill="none" stroke="#EA4335" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" />
"@

    # Dots on data points
    foreach ($r in $data) {
        $x = $paddingLeft + ($plotWidth * ($r.size / $maxSize))
        $yRadix = $paddingTop + $plotHeight - ($plotHeight * ($r.radix_time / $maxTime))
        $yHeap = $paddingTop + $plotHeight - ($plotHeight * ($r.heap_time / $maxTime))
        
        $svg += @"
  <circle cx="$x" cy="$yRadix" r="4" fill="#4285F4" stroke="#ffffff" stroke-width="1" />
  <circle cx="$x" cy="$yHeap" r="4" fill="#EA4335" stroke="#ffffff" stroke-width="1" />
"@
    }

    # Legend
    $svg += @"
  <!-- Legend -->
  <rect x="$($width - 200)" y="60" width="150" height="60" rx="5" fill="#1e1e1e" stroke="#333333" stroke-width="1" />
  <line x1="$($width - 185)" y1="80" x2="$($width - 165)" y2="80" stroke="#4285F4" stroke-width="3" />
  <circle cx="$($width - 175)" cy="80" r="3" fill="#4285F4" />
  <text x="$($width - 155)" y="84" fill="#ffffff" font-size="12">Radix Sort (O(N))</text>

  <line x1="$($width - 185)" y1="100" x2="$($width - 165)" y2="100" stroke="#EA4335" stroke-width="3" />
  <circle cx="$($width - 175)" cy="100" r="3" fill="#EA4335" />
  <text x="$($width - 155)" y="104" fill="#ffffff" font-size="12">Heap Sort (O(N log N))</text>
</svg>
"@
    $svg | Out-File -FilePath "$DocDir\sorting_benchmark.svg" -Encoding utf8
    Write-Host "Sorting benchmark chart written to $DocDir\sorting_benchmark.svg"
}

# Function to generate Hashing Chart
function Generate-Hashing-Chart {
    $maxSize = 0.0
    $maxTime = 0.0
    foreach ($r in $data) {
        if ($r.size -gt $maxSize) { $maxSize = $r.size }
        if ($r.avg_tree -gt $maxTime) { $maxTime = $r.avg_tree }
        if ($r.avg_list -gt $maxTime) { $maxTime = $r.avg_list }
        if ($r.worst_tree -gt $maxTime) { $maxTime = $r.worst_tree }
        if ($r.worst_list -gt $maxTime) { $maxTime = $r.worst_list }
    }
    # Round up maxTime to a clean value in milliseconds
    $maxTimeMs = $maxTime * 1000.0
    $maxTimeMs = [Math]::Ceiling($maxTimeMs)
    if ($maxTimeMs -eq 0) { $maxTimeMs = 1.0 }

    $svg = @"
<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 $width $height" width="100%" height="100%" style="background-color: #121212; font-family: 'Outfit', 'Inter', sans-serif;">
  <!-- Grid Lines and Y-Axis ticks -->
"@

    # Gridlines
    $ticks = 5
    for ($i = 0; $i -le $ticks; $i++) {
        $yValMs = $maxTimeMs * ($i / $ticks)
        $yPos = $paddingTop + $plotHeight - ($plotHeight * ($i / $ticks))
        $svg += @"
  <line x1="$paddingLeft" y1="$yPos" x2="$($width - $paddingRight)" y2="$yPos" stroke="#2a2a2a" stroke-width="1" stroke-dasharray="4" />
  <text x="$($paddingLeft - 15)" y="$($yPos + 5)" fill="#aaaaaa" font-size="12" text-anchor="end">$($yValMs.ToString("F1")) ms</text>
"@
    }

    # X-Axis ticks
    $xTicks = 5
    for ($i = 0; $i -le $xTicks; $i++) {
        $xVal = $maxSize * ($i / $xTicks)
        $xPos = $paddingLeft + ($plotWidth * ($i / $xTicks))
        $xLabel = "$([Math]::Round($xVal / 1000000, 1))M"
        if ($xVal -lt 1000000) { $xLabel = "$([Math]::Round($xVal / 1000, 1))K" }
        if ($xVal -eq 0) { $xLabel = "0" }
        $svg += @"
  <line x1="$xPos" y1="$paddingTop" x2="$xPos" y2="$($paddingTop + $plotHeight)" stroke="#2a2a2a" stroke-width="1" stroke-dasharray="4" />
  <text x="$xPos" y="$($paddingTop + $plotHeight + 20)" fill="#aaaaaa" font-size="12" text-anchor="middle">$xLabel</text>
"@
    }

    # Axes
    $svg += @"
  <!-- Axes -->
  <line x1="$paddingLeft" y1="$paddingTop" x2="$paddingLeft" y2="$($paddingTop + $plotHeight)" stroke="#444444" stroke-width="2" />
  <line x1="$paddingLeft" y1="$($paddingTop + $plotHeight)" x2="$($width - $paddingRight)" y2="$($paddingTop + $plotHeight)" stroke="#444444" stroke-width="2" />
  <text x="$($paddingLeft + $plotWidth / 2)" y="$($height - 10)" fill="#ffffff" font-size="14" font-weight="bold" text-anchor="middle">Dataset Size (N)</text>
  <text x="25" y="$($paddingTop + $plotHeight / 2)" fill="#ffffff" font-size="14" font-weight="bold" text-anchor="middle" transform="rotate(-90 25 $($paddingTop + $plotHeight / 2))">Running Time for N Searches (ms)</text>
  <text x="$($width / 2)" y="30" fill="#ffffff" font-size="18" font-weight="bold" text-anchor="middle">Comparative Hashing Performance: AVL Tree vs Linked List Chains</text>
"@

    # Plot lines for Hashing
    $avgTreePts = @()
    $worstTreePts = @()
    $avgListPts = @()
    $worstListPts = @()
    
    foreach ($r in $data) {
        $x = $paddingLeft + ($plotWidth * ($r.size / $maxSize))
        # Map values to Milliseconds for readability
        $yAvgTree = $paddingTop + $plotHeight - ($plotHeight * (($r.avg_tree * 1000.0) / $maxTimeMs))
        $yWorstTree = $paddingTop + $plotHeight - ($plotHeight * (($r.worst_tree * 1000.0) / $maxTimeMs))
        $yAvgList = $paddingTop + $plotHeight - ($plotHeight * (($r.avg_list * 1000.0) / $maxTimeMs))
        $yWorstList = $paddingTop + $plotHeight - ($plotHeight * (($r.worst_list * 1000.0) / $maxTimeMs))
        
        $avgTreePts += "$x,$yAvgTree"
        $worstTreePts += "$x,$yWorstTree"
        $avgListPts += "$x,$yAvgList"
        $worstListPts += "$x,$yWorstList"
    }

    $avgTreeStr = $avgTreePts -join " "
    $worstTreeStr = $worstTreePts -join " "
    $avgListStr = $avgListPts -join " "
    $worstListStr = $worstListPts -join " "

    $svg += @"
  <!-- AVL Tree Avg Line (Green) -->
  <polyline points="$avgTreeStr" fill="none" stroke="#34A853" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" />
  <!-- AVL Tree Worst Line (Light Green dash) -->
  <polyline points="$worstTreeStr" fill="none" stroke="#34A853" stroke-width="2" stroke-dasharray="5,5" stroke-linecap="round" stroke-linejoin="round" />
  
  <!-- Linked List Avg Line (Yellow) -->
  <polyline points="$avgListStr" fill="none" stroke="#FBBC05" stroke-width="3" stroke-linecap="round" stroke-linejoin="round" />
  <!-- Linked List Worst Line (Yellow dash) -->
  <polyline points="$worstListStr" fill="none" stroke="#FBBC05" stroke-width="2" stroke-dasharray="5,5" stroke-linecap="round" stroke-linejoin="round" />
"@

    # Dots
    foreach ($r in $data) {
        $x = $paddingLeft + ($plotWidth * ($r.size / $maxSize))
        $yAvgTree = $paddingTop + $plotHeight - ($plotHeight * (($r.avg_tree * 1000.0) / $maxTimeMs))
        $yAvgList = $paddingTop + $plotHeight - ($plotHeight * (($r.avg_list * 1000.0) / $maxTimeMs))
        
        $svg += @"
  <circle cx="$x" cy="$yAvgTree" r="4" fill="#34A853" stroke="#ffffff" stroke-width="1" />
  <circle cx="$x" cy="$yAvgList" r="4" fill="#FBBC05" stroke="#ffffff" stroke-width="1" />
"@
    }

    # Legend
    $svg += @"
  <!-- Legend -->
  <rect x="$($width - 240)" y="60" width="190" height="90" rx="5" fill="#1e1e1e" stroke="#333333" stroke-width="1" />
  
  <line x1="$($width - 225)" y1="75" x2="$($width - 205)" y2="75" stroke="#34A853" stroke-width="3" />
  <circle cx="$($width - 215)" cy="75" r="3" fill="#34A853" />
  <text x="$($width - 195)" y="79" fill="#ffffff" font-size="11">AVL Tree Chaining (Avg)</text>

  <line x1="$($width - 225)" y1="95" x2="$($width - 205)" y2="95" stroke="#34A853" stroke-width="2" stroke-dasharray="3,3" />
  <text x="$($width - 195)" y="99" fill="#ffffff" font-size="11">AVL Tree Chaining (Worst)</text>

  <line x1="$($width - 225)" y1="115" x2="$($width - 205)" y2="115" stroke="#FBBC05" stroke-width="3" />
  <circle cx="$($width - 215)" cy="115" r="3" fill="#FBBC05" />
  <text x="$($width - 195)" y="119" fill="#ffffff" font-size="11">Linked List Chaining (Avg)</text>

  <line x1="$($width - 225)" y1="135" x2="$($width - 205)" y2="135" stroke="#FBBC05" stroke-width="2" stroke-dasharray="3,3" />
  <text x="$($width - 195)" y="139" fill="#ffffff" font-size="11">Linked List Chaining (Worst)</text>
</svg>
"@
    $svg | Out-File -FilePath "$DocDir\hash_table_benchmark.svg" -Encoding utf8
    Write-Host "Hashing benchmark chart written to $DocDir\hash_table_benchmark.svg"
}

Generate-Sorting-Chart
Generate-Hashing-Chart
