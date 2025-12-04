# Str: 目标字符串
# CurrentNumber: 当前选好的数字
# UnselectedCount: 剩余未选择的数字个数
# LastPos: 上一次选择的数字位置
function SelectNumber {
  param (
    [string]$Str,
    [long]$CurrentNumber,
    [int]$UnselectedCount,
    [int]$LastPos
  )

  if ($UnselectedCount -eq 0) {
    return $CurrentNumber
  }

  $currentPos = $LastPos + 1

  # 找满足条件的最大数
  for ($i = $LastPos + 1; $i -lt $Str.Length; $i ++) {
    # 如果从 i 后字符串长度已经不够选择了，则跳出循环
    if ($i + $UnselectedCount -gt $Str.Length) {
      break
    }
    $number = [int]::Parse($Str[$i])
    if ([int]::Parse($Str[$currentPos]) -lt $number) {
      $currentPos = $i
    }
  }

  $CurrentNumber = $CurrentNumber * 10 + [int]::Parse($Str[$currentPos])

  return SelectNumber $Str $CurrentNumber ($UnselectedCount - 1) $currentPos
}

function Solve {
  param (
    [int]$SelectCount
  )

  $total = 0

  Get-Content -Path "input.in" | ForEach-Object {
    if ($_ -eq "") {
      return
    }
    $number = SelectNumber $_ 0 $SelectCount -1
    $total += $number
  }

  return $total
}

function Part01 {
  return Solve 2
}

function Part02 {
  return Solve 12
}

if ($args[0] -eq "part01" -or $args.Count -eq 0) {
  Write-Host $(Part01)
}
else {
  Write-Host $(Part02)
}