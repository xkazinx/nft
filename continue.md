# continue.md (nft, master)

## Repos

| Repo | Commit | State |
|---|---|---|
| nft | master: the kazilib / SFML 3.1 / web / deploy commit (this file's) on `23b549e` (2022) | pushed |
| kazilib (`src/dep/kazilib`, new submodule) | master `a28bf1b` (ImGui in a browser, the yips port's), unchanged here | on origin |

## Last work (2026-11-08)

- **README and GitHub description:** the project's story on top (a good time with friends,
  random avatars from hand-drawn pieces posted as NFTs with bots). No code changed.

## Earlier (2026-11-06)

- **Native port:** kazilib submodule (ml version), SFML 2.5 → 3.1 x86, FASTBuild through
  kazilib (`src\fastbuild.json`), v145, C++latest, `/MD`, 64-bit-hosted tools. The old
  kazin lib (`$(LIBPATH)\kazin`), the vendored ImGui and magic_enum are gone: kazilib's
  scene manager, ImGui / ImGui-SFML, log, magic_enum, `lib::Rand`, initflags, json.
  UTF-16 sources rewritten as UTF-8. `src\nft.sln` (root `nft.sln` removed).
- **Behaviour kept**, with these changes: a key hint line at the bottom of each scene;
  `scene=` startup flag; `N` = next scene on the web (browsers keep Ctrl+S); the
  `while(!eof)` map read (an extra tile from an empty word, flags read past the string's
  end) and the empty-sprite case fixed; noisy debug logs dropped; Ctrl from the key event
  (either Ctrl key, was left Ctrl only); categories sorted (same order on every system).
- **Web:** `build_web.ps1`, `src\client\CMakeLists.txt`; the ImGui panel on the web too
  (kazilib `kazilib_web_imgui()`, `imgui.ini` packed so it has the native size). libc++
  fix: kazilib ml `stlx.h` defines `_NOEXCEPT` empty, `pch.h` restores it under
  `_LIBCPP_VERSION`.
- **Deployed:** https://kazin.dev/projects/nft/ (`deploy_ubuntu.ps1`, `/opt/nft/web`,
  Caddy `kazin.dev.d/nft.caddy`).
- **Showcase:** `docs\showcase\*.png`, `docs\screenshot.png` (four live cogollos),
  `docs\showcase\kazin\nft.jpg`, `nft-1.jpg` .. `nft-4.jpg` (1024x768, for kazin.dev; the
  portfolio repo not touched).

## Tested

| Test | Result |
|---|---|
| `build.ps1` Release x86 (FASTBuild, distributed), kazilib `a28bf1b` | built, 0 errors |
| native `client.exe`: generator (`C`), map (`scene=pacman`, arrows, `B`, `A` / `W`), ImGui panel; PrintWindow shots read | as the 2022 code draws them |
| `src\tests\web\run_web_test.ps1` (local build, headless Edge): gen (4 cogollos, `N` twice), tiled | passed |
| same, `-Url https://kazin.dev/projects/nft/` | passed |

Known gaps: Ctrl+S natively and Right Shift anywhere not driven by a test; the ImGui
File menu not clicked; only Edge; no phone.

## Next steps

- `to-resolve.md`: the manual checks and the questions (unused first pictures, red tint,
  the corner sprite, font licences).

## The user's prompts (this work)

1. "now I want you standarize the work and do the same with the githubs of yip, yips, tileship, tiled, nft, use various agents if well scoped"
2. "all the process we've done with tictactoe"
