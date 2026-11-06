# The web client end to end in a headless browser (kazilib web\tools\browser.js:
# Edge, WebGL2 on SwiftShader), two runs: the generator (gen.json: four cogollos
# made with C) and the tiled map (tiled.json, ?scene=pacman: a cogollo walks and
# drops a bomb, the other one walks). Screenshots in testerino\web\<local | live>\
# (read them: the steps check that the page ran, not what it drew).
# Exit code = the runs that failed.
#   powershell -ExecutionPolicy Bypass -File src\tests\web\run_web_test.ps1 [-Url https://kazin.dev/projects/nft/]
# -Url  a deployed page instead of the local build (src\build\web\client-build, build_web.ps1)
param([string]$Url = '')
$ErrorActionPreference = 'Stop'
$root = Resolve-Path (Join-Path $PSScriptRoot '..\..\..')
$shots = Join-Path $root ('testerino\web\' + $(if ($Url) { 'live' } else { 'local' }))
New-Item -ItemType Directory -Force $shots | Out-Null
$browser = Join-Path $root 'src\dep\kazilib\web\tools\browser.js'
$build = Join-Path $root 'src\build\web\client-build'
if (-not $Url -and -not (Test-Path (Join-Path $build 'index.wasm'))) { throw 'no src\build\web\client-build\index.wasm: run build_web.ps1' }

$failed = 0
foreach ($run in @(@{ steps = 'gen.json'; page = 'index.html' }, @{ steps = 'tiled.json'; page = 'index.html?scene=pacman' })) {
	# Screenshot names in the steps land in the shots folder
	$steps = Join-Path $shots $run.steps
	(Get-Content (Join-Path $PSScriptRoot $run.steps) -Raw) -replace '"shot": "', ('"shot": "' + ($shots -replace '\\', '/') + '/') |
		Set-Content -Encoding utf8 $steps
	Write-Host "== $($run.steps)"
	if ($Url) {
		node $browser --url ($Url.TrimEnd('/') + '/' + $run.page) --steps $steps --timeout 60
	} else {
		node $browser --serve $build --port 8093 --page $run.page --steps $steps --timeout 60
	}
	if ($LASTEXITCODE) { $failed++ }
}
Write-Host $(if ($failed) { "$failed run(s) failed" } else { 'web test passed' })
exit $failed
