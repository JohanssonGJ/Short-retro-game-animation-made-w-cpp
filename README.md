# Short-retro-game-animation-made-w-cpp
Retro Space Animation (C++ / Visual Studio 2022)

A tiny retro scene made in C++. The sequence plays through with motion, power-ups, a boss moment, and chiptune-style SFX/BGM.

## Features
- Scripted sequence with power-ups and a boss moment
- PNG rendering via a lightweight loader
- Sound effects and looping background music
- Compact single-file utilities for windowing, PNG, and audio

## Build & Run (Windows, VS2022)
1. Install **Visual Studio 2022** with **Desktop development with C++**.
2. Open **`demo.sln`**.
3. Build → **Build Solution** (Ctrl+Shift+B).
4. Run (Ctrl+F5). Close the window to exit.

_All helper sources are bundled—no external dependencies._

## How it works (high level)
- Uses a standard **update → draw → present** frame loop.  
- Sprites move based on simple velocities and timing.  
- **Collisions** use axis-aligned bounding boxes (AABB) for quick overlap checks.  
- Events (e.g., collecting a power-up or hitting the boss) trigger one-shot SFX; background music loops.

## Project layout
Assets remain in the project root to match file paths used in code.

## Credits
- Helper libs: `fssimplewindow`, `yspng`, `yssimplesound`
