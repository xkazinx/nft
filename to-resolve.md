# to-resolve.md (nft)

## Onto kazilib, SFML 3.1, the web, kazin.dev (2026-11-06; continue.md)

Manual checks:

- **Native window by hand**: `build\client\client.exe`, press `C` a few times, Ctrl+S
  through the scenes, walk both cogollos on the map (arrows + `B`, `WASD` + Right Shift),
  Ctrl+arrows, File menu of the ImGui panel. Why: the native run was checked with keys
  posted to the window (no Ctrl, no Right Shift: posted messages don't set the key
  state); the web test covers `C`, arrows, `B`, `WASD`.
- **Right Shift and the ImGui panel's File menu in a browser**: on
  https://kazin.dev/projects/nft/ drop a bomb with the second cogollo (Right Shift), open
  File, close the panel. Why: the headless driver has a left Shift only, and the test
  shoots the panel without clicking it. (Ctrl+S is the browser's "save page": `N` is the
  next scene on the web, tested.)
- **Firefox, Safari, a phone**: the page loads 10 MB (`index.data`: the 2048x2048 PNGs,
  the fonts) and needs a keyboard. Why: only Edge (SwiftShader) was tested.

Open questions:

- **A category's first picture is never used** (as in 2022, `Sprite::Initialize`): the
  first file of each folder only makes the category, so `arm\1.png`, `body\0.png`,
  `face\1.png`, `feet\1.png` never appear. Kept. `body\0.png` is opaque (white
  background), so maybe on purpose for the body; fix for the others?
- **Both cogollos on the map are tinted red** (`TiledUnit::OnHotpatch` runs before `_self`
  is set), and **a full-size `full\1.png` sits in the map's corner** (`TiledMap::AddUnit`
  adds an unscaled sprite per unit). Kept as the prototype drew them. Fix?
- **Licences**: the Arial fonts (`build\client\arial*.ttf`, Microsoft's) and the cogollo
  art are now public on kazin.dev. Free to publish, or replace the fonts (e.g. Liberation
  Sans)?
- **The name**: the README calls it "nft" (the repo's name); the window says NFTGEN.
