
# **Fairlight CMI IIx (MAME)** #

This repository was created to publish a working implementation of the famous Fairlight CMI IIx (Computer Music Instrument) machine emulated by the MAME software. In the beginning, we did a lot of research on the Internet to find out a publicly available working implementation, but without success. The only references we found were some YouTube channels presenting basic guides and showing some preset examples. In particular the ones of:

- __SergioFrias__ (https://www.youtube.com/@SergioFrias);
- __Mog's Emulation Station__ (https://www.youtube.com/@mogemulation);
- __B. ART__ (https://www.youtube.com/@B.ART-electro)

Although they haven't published their working MAME setup, their suggestions in the comments section under their videos were useful in building up this work. So definitely we thank them for all their suggestions. We hope this work will be useful for everyone who wants to try/work with this beautiful CMI IIx and at the same time that it could be a starting point to improve its performance and implement missing features.

## Missing Features
In this section, we want to list all the known features that are missing from the original Fairlight CMI IIx machine.

- Emulation of the Curtis SSM2045 filter is completely missing so the samples are pretty rough around the edges (Mog's Emulation Station).
- The second MIDI keyboard is not implemented (Mog's Emulation Station).
- The Analog Card used for sampling is not implemented (Mog's Emulation Station).

## Execute the CMI

This section will walk through the steps to get the CMI machine running on the MAME emulator:
1. Get the last compiled version for Windows from https://github.com/davide-ciraolo/mame-cmi2x-fairlight/releases/tag/v1 or compile the source code following the steps from MAME documentation (https://www.mamedev.org/tools/). To compile the code for our first release we used the following command: `` make SUBTARGET=cmi SOURCES=src\mame\fairlight\cmi.cpp ARCHOPTS="-fuse-ld=lld" -jX `` where X is the number of CPU cores you want to use. This command will compile only the files required to run the CMI, instead of all the MAME drivers;
2. Get the needed ROMs (cmi2x.zip, cmi_ankbd.zip, cmi_mkbd.zip) from the Internet (i.e. https://gist.github.com/vmartins/c8c3aebce8936402bdf99a30ce1a43e9) and put them inside the "roms" folder;
3. Get a working System Disk (i.e. SYSV19.IMD) and one or more presets disks (i.e. VOICES.IMD, STRINGS4.IMD, etc..) from the Internet (i.e. https://dbwbp.com/synthbin/Fairlight%20CMI%20IIx%20Disks%20Image.zip) and put them inside a folder with read/write permissions like the Windows Public folder (i.e. C:\Users\Public), this will allow MAME to read them and you to change presets at any time;
4. Launch the emulator with the command: `` .\cmi.exe cmi2x -mouse -flop1 "<path-to-SYSV19.IMD>" -flop2 "<path-to-your-PRESET.IMD>" -midiin1 "<name of MIDI device>" `` (refer to the next section to know how to retrieve MIDI device name).
5. Enjoy :)

## Compile for MacOS
Here we explain how to compile the source code for MacOS (keep in mind that we tested the compilation process only on an Intel Mac running MacOS Sonoma):

1. ARM64 builds will not work on Intel Macs, but Intel builds will work on ARM Macs (https://sdlmame.lngn.net);

2. Follow the steps from [MAME documentation](https://docs.mamedev.org/initialsetup/compilingmame.html#apple-macos) and [RetroGamesUltra](https://retrogamesultra.com/2019/02/24/running-the-mame-arcade-emulator-on-mac-os-x/) as a general guideline;

3. You can download SDL [here](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.3);

4. Be careful when installing SDL, as it should be placed in '/Library/Frameworks';

5. Start the compilation process with: ``sudo make SUBTARGET=cmi SOURCES=src/mame/fairlight/cmi.cpp -jX NOWERROR=1 REGENIE=1``, where X is the number of CPU cores you want to use. This command will compile only the files required to run the CMI, instead of all the MAME drivers;

6. After finishing the compilation process, follow the steps 2, 3 and 4 of "Execute the CMI" section;

7. Enjoy :)

## Compiler optimization
You can use the ``ARCHOPTS="-march=native"`` flag to optimize the code for your CPU. E.g. ``make SUBTARGET=cmi SOURCES=src/mame/fairlight/cmi.cpp -jX ARCHOPTS="-march=native"``

If you need to compile the code for a different CPU, you can check a list of other x86 options for the GNU C++ compiler [here](https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html) (i.e., -march=skylake)

## MIDI Setup

1. Connect your MIDI device to your computer.
2. Command to list MIDI devices:
  - Windows: `` .\cmi.exe --listmidi `` This will show the list of MIDI devices connected to the computer.
3. To start the CMI with a specific MIDI device you have to add the flag `` --midiin1 "<name of MIDI device>" `` To the execution command of the CMI.

## Keyboard Configuration

Currently, this is the default setup for the Alphanumeric Keyboard Key binding:
| Key Code              | Character   | + Shift     | + LShift + Ctrl |
|-----------------------|-------------|-------------|-----------------|
| KEYCODE_1             | 1           | !           |                 |
| KEYCODE_2             | 2           | "           |                 |
| KEYCODE_3             | 3           | #           |                 |
| KEYCODE_4             | 4           | $           |                 |
| KEYCODE_5             | 5           | %           |                 |
| KEYCODE_6             | 6           | &           |                 |
| KEYCODE_7             | 7           | '           |                 |
| KEYCODE_8             | 8           | (           |                 |
| KEYCODE_9             | 9           | )           |                 |
| KEYCODE_0             | 0           |             |                 |
| KEYCODE_A             | A           |             |                 |
| KEYCODE_B             | B           |             |                 |
| KEYCODE_C             | C           |             |                 |
| KEYCODE_D             | D           |             |                 |
| KEYCODE_E             | E           |             |                 |
| KEYCODE_F             | F           |             |                 |
| KEYCODE_G             | G           |             |                 |
| KEYCODE_H             | H           |             |                 |
| KEYCODE_I             | I           |             |                 |
| KEYCODE_J             | J           |             |                 |
| KEYCODE_K             | K           | [           | {               |
| KEYCODE_L             | L           | \\          | \|              |
| KEYCODE_M             | M           | ]           | }               |
| KEYCODE_N             | N           | ^           | ~               |
| KEYCODE_O	            | O           |	_           |                 |
| KEYCODE_P             | P           | @           | '               |
| KEYCODE_Q             | Q           |             |                 |
| KEYCODE_R             | R           |             |                 |
| KEYCODE_S             | S           |             |                 |
| KEYCODE_T             | T           |             |                 |
| KEYCODE_U             | U           |             |                 |
| KEYCODE_V             | V           |             |                 |
| KEYCODE_W             | W           |             |                 |
| KEYCODE_X             | X           |             |                 |
| KEYCODE_Y             | Y           |             |                 |
| KEYCODE_Z             | Z           |             |                 |
| KEYCODE_UP            | Up          |             |                 |
| KEYCODE_DOWN          | Down        |             |                 |
| KEYCODE_LEFT          | Left        |             |                 |
| KEYCODE_RIGHT         | Right       |             |                 |
| KEYCODE_ESC           | ESC         |             |                 |
| KEYCODE_F1            | Home        |             |                 |
| KEYCODE_F2            | Set         |             |                 |
| KEYCODE_F3            | Add         |             |                 |
| KEYCODE_F4            | Sub         |             |                 |
| KEYCODE_F5            | Clear       |             |                 |
| KEYCODE_BACKSPACE     | Backspace   |             |                 |
| KEYCODE_ENTER         | Return (a)  |             |                 |
| KEYCODE_ENTER         | Return (b)  |             |                 |
| KEYCODE_LCONTROL      | Ctrl        |             |                 |
| KEYCODE_LSHIFT        | LShift      |             |                 |
| KEYCODE_RSHIFT        | RShift      |             |                 |
| KEYCODE_SPACE         | Space       |             |                 |
| KEYCODE_STOP          | .           | >           |                 |
| KEYCODE_COMMA         | ,           | <           |                 |
| KEYCODE_COLON         | :           | *           |                 |
| KEYCODE_SLASH         | /           | ?           |                 |
| KEYCODE_CLOSEBRACE    | ;           | +           |                 |
| KEYCODE_EQUALS        | =           |             |                 |
| KEYCODE_MINUS         | -           |             |                 |
| KEYCODE_PLUS_PAD      | +           |             |                 |
| KEYCODE_MINUS_PAD     | -           |             |                 |

We decided to create this table, because we found the keyboard configuration a little foggy, as a modern keyboard layout differs from the one of the original CMI. In addition, some key bindings were not set by default: Home, Set, Add, Sub and Clear. So we configured them as F1, F2, F3, F4 and F5, respectively. We also spent some time trying to understand how to type the ";". It ended up being another unset key named "WTF" (fair enough...). So we changed the name to "; & +" as it can also be used to type "+", and we bound it to the KEYCODE_CLOSEBRACE, which on our keyboard layout was the most "natural" key to type for it.

You can change these bindings, as you prefer, at any time through the [MAME input settings](https://docs.mamedev.org/usingmame/mamemenus.html#input-settings-menu)

## For any questions

For questions about the MAME emulator, how to compile the source code, and how to adjust the settings refer to the [MAME documentation](https://docs.mamedev.org/whatis.html).

Feel free to contact us for any other questions.

**MAME**
=============

[![Join the chat at https://gitter.im/mamedev/mame](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/mamedev/mame?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Build status:

| OS/Compiler   | Status        | 
| ------------- |:-------------:| 
| Linux/GCC and clang | ![CI (Linux)](https://github.com/mamedev/mame/workflows/CI%20(Linux)/badge.svg) |
| Windows/MinGW GCC | ![CI (Windows)](https://github.com/mamedev/mame/workflows/CI%20(Windows)/badge.svg) |
| macOS/clang | ![CI (macOS)](https://github.com/mamedev/mame/workflows/CI%20(macOS)/badge.svg) |
| UI Translations | ![Compile UI translations](https://github.com/mamedev/mame/workflows/Compile%20UI%20translations/badge.svg) |
| Documentation | ![Build documentation](https://github.com/mamedev/mame/workflows/Build%20documentation/badge.svg) |

Static analysis status for entire build (except for third-party parts of project):

[![Coverity Scan Status](https://scan.coverity.com/projects/5727/badge.svg?flat=1)](https://scan.coverity.com/projects/mame-emulator)

What is MAME?
=============

MAME is a multi-purpose emulation framework.

MAME's purpose is to preserve decades of software history. As electronic technology continues to rush forward, MAME prevents this important "vintage" software from being lost and forgotten. This is achieved by documenting the hardware and how it functions. The source code to MAME serves as this documentation. The fact that the software is usable serves primarily to validate the accuracy of the documentation (how else can you prove that you have recreated the hardware faithfully?). Over time, MAME (originally stood for Multiple Arcade Machine Emulator) absorbed the sister-project MESS (Multi Emulator Super System), so MAME now documents a wide variety of (mostly vintage) computers, video game consoles and calculators, in addition to the arcade video games that were its initial focus.

How to compile?
===============

If you're on a UNIX-like system (including Linux and macOS), it could be as easy as typing

```
make
```

for a MAME build,

```
make SUBTARGET=arcade
```

for an arcade-only build, or

```
make SUBTARGET=mess
```

for a MESS build.

See the [Compiling MAME](http://docs.mamedev.org/initialsetup/compilingmame.html) page on our documentation site for more information, including prerequisites for macOS and popular Linux distributions.

For recent versions of macOS you need to install [Xcode](https://developer.apple.com/xcode/) including command-line tools and [SDL 2.0](https://www.libsdl.org/download-2.0.php).

For Windows users, we provide a ready-made [build environment](http://mamedev.org/tools/) based on MinGW-w64.

Visual Studio builds are also possible, but you still need [build environment](http://mamedev.org/tools/) based on MinGW-w64.
In order to generate solution and project files just run:

```
make vs2019
```
or use this command to build it directly using msbuild

```
make vs2019 MSBUILD=1
```


Where can I find out more?
=============

* [Official MAME Development Team Site](http://mamedev.org/) (includes binary downloads, wiki, forums, and more)
* [Official MESS Wiki](http://mess.redump.net/)
* [MAME Testers](http://mametesters.org/) (official bug tracker for MAME and MESS)


Contributing
=============

## Coding standard

MAME source code should be viewed and edited with your editor set to use four spaces per tab. Tabs are used for initial indentation of lines, with one tab used per indentation level. Spaces are used for other alignment within a line.

Some parts of the code follow [Allman style](https://en.wikipedia.org/wiki/Indent_style#Allman_style); some parts of the code follow [K&R style](https://en.wikipedia.org/wiki/Indent_style#K.26R_style) -- mostly depending on who wrote the original version. **Above all else, be consistent with what you modify, and keep whitespace changes to a minimum when modifying existing source.** For new code, the majority tends to prefer Allman style, so if you don't care much, use that.

All contributors need to either add a standard header for license info (on new files) or inform us of their wishes regarding which of the following licenses they would like their code to be made available under: the [BSD-3-Clause](http://opensource.org/licenses/BSD-3-Clause) license, the [LGPL-2.1](http://opensource.org/licenses/LGPL-2.1), or the [GPL-2.0](http://opensource.org/licenses/GPL-2.0).

License
=======
The MAME project as a whole is made available under the terms of the
[GNU General Public License, version 2](http://opensource.org/licenses/GPL-2.0)
or later (GPL-2.0+), since it contains code made available under multiple
GPL-compatible licenses.  A great majority of the source files (over 90%
including core files) are made available under the terms of the
[3-clause BSD License](http://opensource.org/licenses/BSD-3-Clause), and we
would encourage new contributors to make their contributions available under the
terms of this license.

Please note that MAME is a registered trademark of Gregory Ember, and permission
is required to use the "MAME" name, logo, or wordmark.

<a href="http://opensource.org/licenses/GPL-2.0" target="_blank">
<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">
</a>

    Copyright (C) 1997-2021  MAMEDev and contributors

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License version 2, as provided in
    docs/legal/GPL-2.0.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details.

Please see COPYING for more details.
