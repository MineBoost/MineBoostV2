<div align="center">
  <img src=".github/logo.png" alt="MineBoostV2 Logo" width="400"/>

  # MineBoostV2

  **PvP client for [Luanti](https://www.luanti.org/) (formerly Minetest). Optimized to run on more devices.**

  [![Build Status](https://github.com/minetest/minetest/workflows/build/badge.svg)](https://github.com/minetest/minetest/workflows/build/badge.svg)
  [![License](https://img.shields.io/badge/license-LGPL--2.1-blue.svg)](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html)
  [![Stars](https://img.shields.io/github/stars/MineBoost/MineBoostV2?style=flat)](https://github.com/MineBoost/MineBoostV2/stargazers)
  [![Forks](https://img.shields.io/github/forks/MineBoost/MineBoostV2?style=flat)](https://github.com/MineBoost/MineBoostV2/forks)

</div>

---

## About

**MineBoostV2** is a fork of [Luanti](https://www.luanti.org/) (formerly Minetest) built for PvP: lower system requirements, better performance on weak hardware and mobile devices, and extra quality-of-life features for combat.

## Table of Contents

1. [Features](#features)
2. [Further Documentation](#further-documentation)
3. [Default Controls](#default-controls)
4. [Paths](#paths)
5. [Configuration File](#configuration-file)
6. [Command-line Options](#command-line-options)
7. [Compiling](#compiling)
8. [Docker](#docker)
9. [Version Scheme](#version-scheme)

## Features

- 🚀 Optimized for low-end and mobile devices
- ⚔️ PvP-focused improvements
- 🧩 Compatible with mods and games built on the Luanti engine

## Further documentation

- Website: <https://www.luanti.org/>
- Wiki: <https://wiki.luanti.org/>
- Forum: <https://forum.luanti.org/>
- Upstream engine: <https://github.com/minetest/minetest/>
- [Developer documentation](doc/developing)
- [doc/](doc) directory of source distribution

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
| 0-9                        | Select item                                                                                                |
| Z                          | Zoom (needs zoom privilege)                                                                                |
| T                          | Chat                                                                                                       |
| /                          | Command                                                                                                    |
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
| F1                         | Hide/show HUD                                                                                              |
| F2                         | Hide/show chat                                                                                             |
| F3                         | Disable/enable fog                                                                                         |
| F4                         | Disable/enable camera update (Mapblocks are not updated anymore when disabled, disabled in release builds) |
| F5                         | Cycle through debug information screens                                                                    |
| F6                         | Cycle through profiler info screens                                                                        |
| F10                        | Show/hide console                                                                                          |
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

This project is distributed under the [LGPL-2.1](LICENSE.txt) license, as a fork of [Luanti](https://github.com/minetest/minetest) — Copyright (C) 2010-2024 Perttu Ahola and contributors.

---

<div align="center">
  <sub>Made with ❤️ by the MineBoost team</sub>
</div>
