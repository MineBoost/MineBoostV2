<div align="center">
  <img src=".github/logo.png" alt="MineBoostV2 Logo" width="400"/>

  # MineBoostV2

  **PvP client built on the Luanti (formerly Minetest) engine. Optimized to run on more devices.**

  [![License](https://img.shields.io/badge/license-LGPL--2.1-blue.svg)](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html)
  [![Stars](https://img.shields.io/github/stars/MineBoost/MineBoostV2?style=flat)](https://github.com/MineBoost/MineBoostV2/stargazers)
  [![Forks](https://img.shields.io/github/forks/MineBoost/MineBoostV2?style=flat)](https://github.com/MineBoost/MineBoostV2/forks)

</div>

---

## About

**MineBoostV2** is a fork of the Luanti (formerly Minetest) engine built for PvP: lower system requirements, better performance on low-end hardware, and extra quality-of-life features for combat.

> **Note:** MineBoostV2 targets **desktop only** (Windows/Linux/macOS). Mobile/Android is not supported.

## Table of Contents

1. [MineBoost Features](#mineboost-features)
2. [Default Controls](#default-controls)
3. [Paths](#paths)
4. [Configuration File](#configuration-file)
5. [Command-line Options](#command-line-options)
6. [Compiling](#compiling)
7. [Docker](#docker)
8. [Version Scheme](#version-scheme)

## MineBoost Features

MineBoostV2's own settings menu groups everything under four sections — **GUI**, **Render**, **Movement**, and **Scrollbars**. The lists below mirror that same grouping, plus two extra sections for the chat-driven systems (Friend List, Macro Wheel) and outside integrations that don't live in a settings toggle.

### GUI
On-screen HUD elements, each with its own toggle, and — where noted — its own position/color/size settings.
- **KeyStroker** — shows which keys/mouse buttons you're currently pressing
- **CPS Counter** — live clicks-per-second counter
- **Coordinates** — on-screen X/Y/Z position
- **FPS Counter**
- **Ping**
- **Now Playing (Music HUD)** — track title + thumbnail while audio plays
- **Inventory HUD**
- **Craft HUD**
- **Target HUD** — name, skin avatar, and live HP bar of whoever's in your crosshair
- **Photo HUD** — decorative image shown behind open menus

### Render
- **Fullbright** — removes darkness/shadow so everything is fully lit
- **Water Effect** — toggle the underwater post-processing tint
- **Node Illumination**
- **Display Sunrise**
- **Disable Stars**
- **Custom Fog Color**
- **Custom Sky Color**
- **Particles** — master toggle for particle effects
- **Target ESP** — draws highlight particles on whoever you're currently targeting
- **Hand View** — toggle visibility of your own first-person hand/arm model

### Movement
- **Fast Place** — place blocks faster than the default rate
- **No Friend Damage** — disable damage dealt to players on your Friend List

### Scrollbars
Fine-tuning sliders for the features above:
- **FPS Limit**
- **Hit Particle Amount**
- **Target Particle Amount** — density of the Target ESP effect
- **HUD Size** — global scale for all of MineBoost's custom HUD elements

### Friend List & Macro Wheel (chat commands)
Two systems driven by chat commands rather than menu toggles, each keeping its own list per server:

**Friend List** — feeds both `No Friend Damage` and Friend ESP highlighting.
- `.friend add <Nickname>` — add a player
- `.friend del <Nickname>` — remove a player
- `.friend list` — show your current list

**Macro Wheel** — hold the wheel key (**Tab** by default) to pop up a radial menu of saved commands, scroll to pick one, release to run it — works for server commands, chat messages, or other `.` client commands.
- `.macro add <command>` — add an entry
- `.macro del <number>` — remove an entry by its number
- `.macro list` — list all saved macros
- `.macro clear` — wipe the whole wheel

### Other integrations
- **MineBoostV2 Presence Badges** — small badge next to the nametag of other players also running MineBoostV2, detected via mod-channel heartbeat or an optional custom presence server URL
- **Discord Rich Presence** — shows your current server/activity on your Discord profile

## Default controls

All controls are re-bindable using settings.
Some can be changed in the key config dialog in the settings tab.

| Button                     | Action                                                                                                     |
| -------------------------- | ---------------------------------------------------------------------------------------------------------- |
| Move mouse                 | Look around                                                                                                |
| W, A, S, D                 | Move                                                                                                       |
| Space                      | Jump/move up                                                                                               |
| Shift                      | Sneak/move down                                                                                            |
| Q                          | Drop itemstack                                                                                             |
| Shift + Q                  | Drop single item                                                                                           |
| Left mouse button          | Dig/punch/use                                                                                              |
| Right mouse button         | Place/use                                                                                                  |
| Shift + right mouse button | Build (without using)                                                                                      |
| I                          | Inventory menu                                                                                             |
| Mouse wheel                | Select item                                                                                                |
| 1-9, 0                     | Select item (slots 1-9, then 0 for slot 10) — each has its own individual keybind, rebindable separately  |
| N                          | Next hotbar slot                                                                                           |
| B                          | Previous hotbar slot                                                                                       |
| Z                          | Zoom (needs zoom privilege)                                                                                |
| T                          | Chat                                                                                                       |
| /                          | Open chat with `/` pre-filled (server command)                                                             |
| .                          | Open chat with `.` pre-filled — used for MineBoost's local `.friend` / `.macro` commands                   |
| Esc                        | Pause menu/abort/exit (pauses only singleplayer game)                                                      |
| +                          | Increase view range                                                                                        |
| -                          | Decrease view range                                                                                        |
| K                          | Enable/disable fly mode (needs fly privilege)                                                              |
| J                          | Enable/disable fast mode (needs fast privilege)                                                            |
| H                          | Enable/disable noclip mode (needs noclip privilege)                                                        |
| E                          | Aux1 (Move fast in fast mode. Games may add special features)                                              |
| C                          | Cycle through camera modes                                                                                 |
| V                          | Cycle through minimap modes                                                                                |
| Shift + V                  | Change minimap orientation                                                                                 |
| F                          | Toggle left-handed mode                                                                                    |
| M                          | Mute/unmute sound                                                                                          |
| Tab                        | Hold to open the MineBoost Macro Wheel                                                                     |
| Right Shift                | Open the MineBoost settings menu (GUI / Render / Movement / Scrollbars)                                    |
| F1                         | Hide/show HUD                                                                                              |
| F2                         | Hide/show chat                                                                                             |
| F3                         | Disable/enable fog                                                                                         |
| F4                         | Disable/enable camera update (Mapblocks are not updated anymore when disabled, disabled in release builds) |
| F5                         | Cycle through debug information screens                                                                    |
| F6                         | Cycle through profiler info screens                                                                        |
| F10                        | Show/hide console                                                                                          |
| F11                        | Toggle fullscreen                                                                                          |
| F12                        | Take screenshot                                                                                            |

## Paths

Locations:

- `bin` - Compiled binaries
- `share` - Distributed read-only data
- `user` - User-created modifiable data

Where each location is on each platform:

- Windows .zip / RUN_IN_PLACE source:
  - `bin` = `bin`
  - `share` = `.`
  - `user` = `.`
- Windows installed:
  - `bin` = `C:\Program Files\MineBoostV2\bin` (Depends on the install location)
  - `share` = `C:\Program Files\MineBoostV2` (Depends on the install location)
  - `user` = `%APPDATA%\MineBoostV2` or `%MINETEST_USER_PATH%`
- Linux installed:
  - `bin` = `/usr/bin`
  - `share` = `/usr/share/minetest`
  - `user` = `~/.minetest` or `$MINETEST_USER_PATH`
- macOS:
  - `bin` = `Contents/MacOS`
  - `share` = `Contents/Resources`
  - `user` = `Contents/User` or `~/Library/Application Support/minetest` or `$MINETEST_USER_PATH`

Worlds can be found as separate folders in: `user/worlds/`

## Configuration file

- Default location:
`user/minetest.conf`
- This file is created by closing the client for the first time.
- A specific file can be specified on the command line:
`--config <path-to-file>`
- A run-in-place build will look for the configuration file in
`location_of_exe/../minetest.conf` and also `location_of_exe/../../minetest.conf`

## Command-line options

- Use `--help`

## Compiling

- [Compiling - common information](doc/compiling/README.md)
- [Compiling on GNU/Linux](doc/compiling/linux.md)
- [Compiling on Windows](doc/compiling/windows.md)
- [Compiling on MacOS](doc/compiling/macos.md)

## Docker

- [Developing minetestserver with Docker](doc/developing/docker.md)
- [Running a server with Docker](doc/docker_server.md)

## Version scheme

We use `major.minor.patch` since 5.0.0-dev. Prior to that we used `0.major.minor`.

- Major is incremented when the release contains breaking changes, all other
numbers are set to 0.
- Minor is incremented when the release contains new non-breaking features,
patch is set to 0.
- Patch is incremented when the release only contains bugfixes and very
minor/trivial features considered necessary.

Since 5.0.0-dev and 0.4.17-dev, the dev notation refers to the next release,
i.e.: 5.0.0-dev is the development version leading to 5.0.0.
Prior to that we used `previous_version-dev`.

## License

This project is distributed under the [LGPL-2.1](LICENSE.txt) license, as a fork of the Luanti engine — Copyright (C) 2010-2024 Perttu Ahola and contributors.

---

<div align="center">
  <sub>Made with ❤️ by the MineBoost team</sub>
</div>
