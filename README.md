# MineBoostV2

A fork of [Luanti](https://www.luanti.org/) (formerly Minetest) with a built-in PvP/utility client layered on top of the engine — an in-game settings menu, movable/recolorable HUD elements, a friends list, and a chat macro wheel. Everything below is part of the client itself, so it works on any Luanti server without a server-side mod.

## In-game menu

Opens a tabbed settings panel with the following tiles:

**GUI**
- `KeyStroker` — on-screen WASD + mouse button indicator (`show_keys`)
- `ShowCPS` — left/right click-per-second counter (`show_cps`)
- `ShowCoords`, `ShowFPS`, `ShowPing` — bordered HUD panels for position, framerate and ping (`show_coords`, `show_fps`, `show_ping`)
- `NowPlaying` — currently-playing-media HUD widget (`music_hud`)
- `InventoryHUD`, `CraftHUD` — always-on inventory/crafting grids, independent of the normal inventory screen (`inventory_hud`, `craft_hud`)
- `TargetHUD` — info about whatever's under your crosshair (`target_hud`)
- `PhotoHUD` — displays a custom image as a HUD element (`photo_hud`), right-click for its own image/position settings

**Render**
- `Fullbright`, `Water Effect`, `Node illumination`, `Display sunrise`, `Disable stars`, `CustomFog`, `Sky color`, `Particles` — assorted rendering/visual toggles
- `TargedESP` — highlights players through terrain (`target_highlight_particles`)
- `HandView` — right-click for the first-person hand/wielditem panel: offset and scale sliders, swing-animation style (`Vanilla`, `Static`, `Fast`, `Sway`, `Chime`, `Old`, `Punch`, `Tilt`), `Left Hand` (render on the left side), `NoViewBob` (drop only the idle walking wobble, attack/use animations untouched)

**Movement**
- `Fast place` — faster block placement (`fast_place`)
- `NoFriend Damage` — hits on anyone in your [friends list](#friends-list) don't register (`no_friend_damage`)

**Scrollbars**
- `FOV`, `FPS` limit, `Target Particles`, `Hit Particles`, and a global `HUD Size` multiplier that scales every custom HUD element above at once

Every tile can be toggled by clicking it, or bound to a key/mouse button by middle-clicking it and pressing the key you want; hover a bound tile and press `` ` `` (above `Tab`) to clear the bind.

**Colors** panel recolors, independently: `Coords`, `FPS`, `Ping`, `NowPlaying`, `InventoryHUD`, `CraftHUD`, `TargetHUD`, `PhotoHUD`, plus separate outline colors for `KeyStroker Outline`, `CPS Outline`, and the `Preview Outline` used by drag boxes.

**Move HUD** puts the menu into an edit mode where every HUD element above shows a draggable, resizable preview box at its real on-screen position, so you can lay everything out by hand instead of editing `minetest.conf`.

## Friends list

Client-side and per-server: `.friend add <name>`, `.friend remove <name>`, names matched case-insensitively. Used by `NoFriend Damage` and by the target-ESP renderer to skip friends. Stored as `friends.txt` (or `friends_<server>.txt` once connected to a server) in your Luanti user folder — see [`src/client/friendlist.h`](src/client/friendlist.h).

## Macro wheel

Client-side, per-server saved chat commands: `.macro add <command>`, `.macro list`, `.macro remove <n>`. Hold the wheel key (default `Tab`) to pop the wheel up, scroll to pick an entry, release to send it exactly as if typed in chat — works for plain messages, `/server_commands`, or other `.` client-side commands. Stored as `macros.txt` (or `macros_<server>.txt`) — see [`src/client/macrolist.h`](src/client/macrolist.h).

## Presence badge

A small badge is drawn above the head of any other player also running MineBoostV2, detected through the engine's own mod-channel heartbeat. Optionally, `mineboost_presence_server_url` in `minetest.conf` can point at an HTTP presence server for detection independent of any one Luanti server; empty/off by default.

## Discord Rich Presence

Shows your current game/server as Discord Rich Presence, with buttons linking to the project's Discord and Telegram channel — see [`src/client/discordrpc.cpp`](src/client/discordrpc.cpp).

## Default controls

All controls are re-bindable using settings (`keymap_*` in `minetest.conf`, or from the key config dialog in the settings tab).

| Button | Action |
| --- | --- |
| Move mouse | Look around |
| W, A, S, D | Move |
| Space | Jump/move up |
| Shift | Sneak/move down |
| Q | Drop itemstack |
| Shift + Q | Drop single item |
| Left mouse button | Dig/punch/use |
| Right mouse button | Place/use |
| Shift + right mouse button | Build (without using) |
| I | Inventory menu |
| Mouse wheel | Select item |
| 0-9 | Select item |
| N / B | Next/previous hotbar page |
| Z | Zoom (needs zoom privilege) |
| T | Chat |
| / | Command |
| . | Client-side (`.`) command |
| Esc | Pause menu/abort/exit (pauses only singleplayer game) |
| + / - | Increase/decrease view range |
| K | Enable/disable fly mode (needs fly privilege) |
| J | Enable/disable fast mode (needs fast privilege) |
| H | Enable/disable noclip mode (needs noclip privilege) |
| E | Aux1 (move fast in fast mode; games may add special features) |
| C | Cycle through camera modes |
| V | Cycle through minimap modes |
| Shift + V | Change minimap orientation |
| M | Mute/unmute |
| **Right Shift** | **Open the MineBoostV2 menu** |
| **F** | **Toggle Left Hand directly**, without opening HandView's panel |
| **Tab** (hold) | **Pop up the [macro wheel](#macro-wheel)**; scroll to pick an entry, release to send it |
| **Middle-click** a menu tile | **Start binding** a key/mouse button to that tile |
| **`` ` ``** (above Tab) while hovering a bound tile | **Clear** that tile's bind |
| F1 | Hide/show HUD |
| F2 | Hide/show chat |
| F3 | Disable/enable fog |
| F4 | Disable/enable camera update (mapblocks stop updating while disabled; disabled in release builds) |
| F5 | Cycle through debug information screens |
| F6 | Cycle through profiler info screens |
| F10 | Show/hide console |
| F11 | Toggle fullscreen |
| F12 | Take screenshot |

## Repository layout

This is a full engine checkout, not a mod — the client features above live under `src/gui/custom_menu/` (menu/HUD-tile UI), `src/client/` (camera/wielditem, friend list, macro list, Discord RPC, presence badge), and `builtin/client/` (Lua-side KeyStroker/CPS HUD elements).

| Path | What's there |
| --- | --- |
| `src/` | Engine + client C++ source |
| `builtin/` | Built-in Lua (client and game) |
| `games/`, `mods/`, `clientmods/` | Bundled game(s) and client-side mods |
| `textures/`, `fonts/` | Bundled assets |
| `doc/` | Compiling/developer docs (inherited from upstream Luanti) |
| `android/` | Gradle project for the Android build |
| `po/`, `locale/` | Translations |
| `irr/` | Bundled IrrlichtMt (the rendering/windowing library Luanti is built on) |
| `lib/` | Bundled third-party libraries (gmp, jsoncpp, lua, sha256, catch2, ...) |
| `Dockerfile`, `shell.nix` | Container / Nix dev-shell build setups |
| `CMakeLists.txt`, `CMakePresets.json` | Build config (`Debug`/`Release`/`RelWithDebInfo` presets) |
| `friends.txt`, `macros.txt` | Default (empty) friends/macro files for a portable build — see above |
| `minetest.conf.example` | Template for `minetest.conf` |

## Compiling

Same build system as upstream Luanti:

- [Compiling — common information](doc/compiling/README.md)
- [Compiling on GNU/Linux](doc/compiling/linux.md)
- [Compiling on Windows](doc/compiling/windows.md)
- [Compiling on macOS](doc/compiling/macos.md)
- Android: `android/` (Gradle)
- Docker: `Dockerfile`
- Nix dev shell: `shell.nix`

## License

LGPL-2.1, inherited from Luanti — see `LICENSE.txt` / `COPYING.LESSER`.
