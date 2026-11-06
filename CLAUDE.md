# CLAUDE.md (nft)

- **Build:** `powershell -ExecutionPolicy Bypass -File build.ps1` (`setup.ps1`: kazilib submodule, junction `src\dep\SFML-3.1.0` → `src\dep\kazilib\SFML-3.1.0`; then kazilib FASTBuild on `src\fastbuild.json`: kazilib, client). `build.ps1 client`, `-Regen`, `-Clean`, `-Local`, `-Jobs <n>`; `-Configuration Debug` only if asked. Output `build\client\client.exe` beside its data (run from there). `setup.ps1`'s `submodule update` resets kazilib to the recorded pointer: stage a moved pointer first (`git add src/dep/kazilib`).
- **Web:** `build_web.ps1` (Emscripten `D:\code\tools\emsdk`, SFML web `D:\code\tools\kazilib-web`) → `src\build\web\client-build\`; `src\client\CMakeLists.txt` is the web build only (data from `build\client` via `--preload-file`). Code that differs: `#ifdef __EMSCRIPTEN__` (the loop's sleep, frame limit, GL context version, `N` = next scene: browsers keep Ctrl shortcuts); ImGui behind `NFT_IMGUI` (web: with kazilib's `kazilib_web_imgui()`; textures in ImGui by `ImGui::SFML::toTextureID`, never GL names).
- **Deploy:** `deploy_ubuntu.ps1` → box `kazin-music`, `/opt/nft/web`, Caddy `kazin.dev/projects/nft` (`deploy\ubuntu\`); static, no service. Touch only nft's files there.
- **Tests:** `src\tests\web\run_web_test.ps1` (local build; `-Url https://kazin.dev/projects/nft/` live), 0 failed, outside the command sandbox; read the shots in `testerino\web\`.
- **Kazilib first:** scenes (`scene/manager.h`), ImGui, log, enums, random, flags from kazilib; reusable code goes there.
- **Behaviour:** the 2022 prototype's; known oddities kept are in `to-resolve.md`.
- **README:** 2022 original stays at its end (`## Original README`).
- **Names:** members `_name`, functions / types `PascalCase`, `struct` (full rules: `D:\code\hb\hbmillennium\CLAUDE.md`).
