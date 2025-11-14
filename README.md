# OpenTetris

A (pretty mediocre, but fun) implementation of **Tetris** in **C++** using **OpenGL**, built for **Windows** and **Linux**.

Controls:
- Move: Left/Right arrow
- Rotate left: Z
- Rotate right: X

---

# 🛠️ Build Instructions

This project uses **CMake**, so it must be installed on all platforms.  
All build presets are defined in **CMakePresets.json** for both Debug and Release on Windows & Linux.
Running the project in WSL is possible as long as `wslg` is supported by your Windows version (requires Windows 11 or messing around with the wsl version in Windows 10).

---

# 🐧 Linux Build Guide

Most dependencies (GLFW, GLAD, etc.) are fetched by CMake automatically.  
However, **some low-level system libraries must be installed manually** because they come from your distro.

### 🧪 Full Ubuntu packages install

```bash
sudo apt install cmake ninja-build g++ pkg-config \
  libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
  libgl1-mesa-dev mesa-common-dev \
  libwayland-dev libxkbcommon-dev wayland-protocols
```

### 📦 Required System Packages explanation

The previous command installed the following packages:

### Build tools
- `cmake`
- `ninja` or `ninja-build`
- `g++`
- `pkg-config`

### Window system development libraries

GLFW requires either **X11** or **Wayland** headers to be installed.

```
libx11-dev
libxrandr-dev
libxinerama-dev
libxcursor-dev
libxi-dev
libgl1-mesa-dev
libwayland-dev
libxkbcommon-dev
wayland-protocols
```

### OpenGL development headers

These provide `<GL/gl.h>` and Mesa’s OpenGL implementation.

- Ubuntu/Debian → `mesa-common-dev`
- Arch → included in `mesa`
- Fedora → `mesa-libGL-devel`

## 🔨 Building the project

Run the following command from the root of the project:

```bash
cmake --preset=linux-debug
cd build/linux-debug
ninja
```

If anything is missing, **CMake will tell you** during configuration.

## ▶️ Running

Executable path:

```
{projectRoot}/bin/Linux64/Debug/OpenTetris
```

Run it:

```bash
cd bin/Linux64/Debug
./OpenTetris
```

---

# 🪟 Windows Build Guide

This project uses **MSVC** and was tested on:

- Visual Studio 2022
- Visual Studio 2026 Preview

### 📁 Opening the project

Use:

**File → Open → Folder…**

❌ *Do NOT use “Open Solution File”* — this is a pure CMake project.

Visual Studio will automatically detect the available presets (Debug/Release, x86/x64).  
You can then build and run directly from the IDE.
