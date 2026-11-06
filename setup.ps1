# The libraries the client builds against, x86 (Win32):
#   kazilib  src\dep\kazilib  (submodule: std names, startup flags, scenes, ImGui and
#            ImGui-SFML, magic_enum, json, the random generator, the web port)
#   SFML     src\dep\SFML-3.1.0: a junction to kazilib's own SFML 3.1.0 x86
#            (src\dep\kazilib\SFML-3.1.0, in kazilib's git)
# Every build uses the 64-bit-hosted tools (host=x64) and the v145 toolset.
$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
$dep = Join-Path $root 'src\dep'

git -C $root submodule update --init src/dep/kazilib
if ($LASTEXITCODE) { throw 'submodule update failed' }

$sfml = Join-Path $dep 'SFML-3.1.0'
if (-not (Test-Path (Join-Path $sfml 'include\SFML\Graphics.hpp'))) {
    $kaziSfml = Join-Path $dep 'kazilib\SFML-3.1.0'
    if (-not (Test-Path (Join-Path $kaziSfml 'include\SFML\Graphics.hpp'))) { throw "no SFML in $kaziSfml" }
    if (Test-Path $sfml) { Remove-Item $sfml -Force -Recurse }
    New-Item -ItemType Junction -Path $sfml -Target $kaziSfml | Out-Null
    Write-Host "SFML: linked to $kaziSfml"
}

Write-Host 'Dependencies ready'
