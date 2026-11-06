# Builds kazilib and the client (build\client\client.exe, next to its data): Release,
# x86, with the 64-bit-hosted tools, through kazilib's FASTBuild runner
# (src\dep\kazilib\fastbuild\build.ps1, src\fastbuild.json), distributed to the
# workers that answer. Runs setup.ps1 first for any library still missing. Arguments
# go to the runner: aliases (kazilib, client; all by default), -Configuration Debug
# (only when asked), -Regen, -Clean, -Local.
$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot

& (Join-Path $root 'setup.ps1')

# A running client holds its exe: stop this checkout's
Get-Process client, client_d -ErrorAction SilentlyContinue |
    Where-Object { $_.Path -like (Join-Path $root 'build\client\*') } | Stop-Process -Force

& (Join-Path $root 'src\dep\kazilib\fastbuild\build.ps1') -Config (Join-Path $root 'src\fastbuild.json') @args
exit $LASTEXITCODE
