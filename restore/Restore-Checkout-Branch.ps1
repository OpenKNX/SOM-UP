# we assume, we start this script in projects "restore" directory
Set-Location ..
$currentDir = Get-Location
$subprojects = Get-Content dependencies.txt
foreach ($subproject in $subprojects) {
    $attr = $subproject.Split()
    if ($attr[0] -ne "-------") {
        # the following does not work as expected
        # git --git-dir "$($attr[2])/.git" checkout $attr[1]
        Write-Host ""
        Write-Host "Subproject $($attr[2])" -ForegroundColor Yellow
        Set-Location $attr[2]
        git fetch --all
        if (!$?) {
            Write-Host "  FAIL: fetch --all" -ForegroundColor Red
            Set-Location $currentDir
            Set-Location restore
            exit 1
        }
        git checkout $attr[1]
        if (!$?) {
            Write-Host "  FAIL: checkout" -ForegroundColor Red
            Set-Location $currentDir
            Set-Location restore
            exit 1
        }
        git pull --ff-only
        if (!$?) {
            Write-Host "  FAIL: pull --ff-only" -ForegroundColor Red
            Set-Location $currentDir
            Set-Location restore
            exit 1
        }
        Set-Location $currentDir
    }
}
Set-Location restore
timeout /T 20
