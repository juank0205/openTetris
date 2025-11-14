# OpenTetris

This is a pretty mediocre implementation of Tetris in OpenGL for both Windows and Linux in C++.

## How to build

The build system used is CMake, therefore it must be available no matter the OS to build on.
A preset is defined in the CMakePresets.json file for debug and release modes on Windows and Linux.

### Linux

Even though most dependencies are fetched automatically by CMake (GLFW, GLAD, etc.), some system libraries must be installed manually because they come from your Linux distribution.

#### Required packages

- `cmake`
- `ninja`
- `g++`

#### OpenGL & window-system development libraries

GLFW requires X11 or Wayland development headers to be present. Install the ones matching your system:

##### X11 (default on most distros)

- `libx11-dev`
- `libxrandr-dev`
- `libxinerama-dev`
- `libxcursor-dev`
- `libxi-dev`
- `libgl1-mesa-dev`

##### Wayland

If you are using wayland, you will also need:

- `libwayland-dev`
- `libxkbcommon-dev`
- `wayland-protocols`

#### OpenGL development headers

These provide <GL/gl.h> and Mesa’s GL implementation:

- Ubuntu/Debian: `mesa-common-dev`
- Arch: included in `mesa`
- Fedora: `mesa-libGL-devel`

Full Ubuntu install example
```
sudo apt install cmake ninja-build g++ \
  libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
  libgl1-mesa-dev mesa-common-dev
```

#### Building
```
cmake --preset=linux-debug
cd build/linux-debug
ninja
```
If a system dependency is missing, CMake will print an error during configuration. Just install it via your package manager.

#### Running

The executable is located in: `{projectRoot}/bin/Linux64/Debug/OpenTetris`
Run it with:
```
cd bin/Linux/Debug
./OpenTetris

```

### Windows

This project is intended to be built with Visual Studio’s MSVC compiler.
Tested on Visual Studio 2022 and Visual Studio 2026 Preview.

Open the project using:

File → Open → Folder… (NOT “Open Solution”), since the project is CMake-based.

Visual Studio will automatically detect the Windows presets (Debug/Release, x86/x64) and allow building and running the executable directly.
