# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & run

Dependencies (cmake, gcc, glfw, glm, libGL, X11 libs) come from `shell.nix`, so run everything inside `nix-shell`.

```bash
nix-shell
cmake -S . -B build -G Ninja      # build/ is already configured with Ninja
cmake --build build
cd build && ./smgcRunner          # must run from build/ (see below)
```

- **Working directory matters.** Shaders are loaded by the relative path `SMGC/default.vert` / `SMGC/default.frag`, and `Config` reads `core.config` from the CWD. `build/` contains a symlink `SMGC -> ../SMGC` and its own `core.config` for this reason. Shader edits need no rebuild, just a restart.
- `build/compile_commands.json` is generated for clangd.
- There are no tests and no linter.

## Repository layout quirks

- `Core/` is a **symlink to `../smpb/Core`**, a separate git repo (the "smpb" engine core). Changes there affect other projects and are committed in that repo, not this one.
- `third_party/glad` is vendored and built as a static lib. GLM comes from the system via `find_package`.
- Every new `.cpp`/`.h` must be added to the explicit source list in `CMakeLists.txt` (no globbing).
- Code comments and log messages are often in Russian. Keep the existing language of the surrounding code.

## Architecture

### Core: component + task system (from `Core/`)
- `Core` owns a list of `BaseComponent`s. `main.cpp` builds it: `Config` → `SMGC` (→ `Scene`, currently commented out). Then it calls `core.init()` and `core.cycle()`.
- `cycle()` runs a fixed-rate loop. The TPS (ticks per second) comes from `core.config` `SET_TPS`, and each tick calls `tick(tickCounter)` on every component in order. A component that returns non-zero from `init`/`tick` gets its `death()` called and is removed.
- Components talk only through **tasks**: `sendTask(std::make_unique<SomeTask>(...), "ComponentName")` delivers synchronously to the target's `proccessTask` (note the spelling). Tasks are subclasses of `BaseTask` identified by a numeric `taskIdx`. Receivers check the idx and `static_cast` to the concrete type.
- Components reach core settings through the `Core_*` helpers on `BaseComponent` (`Core_getTPS()`, `Core_isDebugModeEnabled()`, `Core_stop()`).

### SMGC: the OpenGL renderer component (`SMGC/`)
- Creates the GLFW window and a GL 4.4 core context, loads glad, owns the shader/VAO/VBO/EBO and an SSBO (`ObjectsBuffer`, binding 0). Each tick it does keyboard camera control and the draw.
- Task protocol is defined in `SMGC/taskDefinitions.*`: `task_SmgcClearObjects` (idx 1), `task_SmgcPushObject` (idx 2), `task_SmgcSwapObjects` (idx 0). Objects use **double buffering**. Producers clear and push into `Objects_B`, then swap, and `draw()` uploads `Objects_A` to the SSBO. A new task needs a new unique idx plus a `taskIs_*` helper and a branch in `SMGC::proccessTask`.
- `Object` is 4×`vec4` (64 bytes, std430). Field meaning per object type is documented in `SMGC/разметка.txt`: type and position, size/angle params, RGBA color, and rotation. The C++ struct and the GLSL `Object` struct must stay in sync.
- Geometry is built on the CPU by `ObjectsGenerator` (`Quad`, `Cube`, `AntiCube`) into `std::vector<Vertex>`/indices. `Vertex` = `vec3 pos` plus `float attached`, where 0 means a world-space vertex and 1 means camera-attached. The vertex shader blends between `aPos - iCameraPos` and `aPos` based on this value.
- The vertex shader builds its own projection by hand: there is no MVP matrix, rotation is done from Euler degrees in `iCameraRot`, w = view z, and near/far are 0.01/1000. Each frame is drawn twice, first filled with polygon offset and then as an orange wireframe with `iOutline = 1`.
- Uniforms set every frame: `iTime`, `iResolution`, `iCameraPos`, `iCameraRot`, `iMaxDist`, `iOutline`.
- The project is moving from an earlier **SDF ray-marching** renderer to rasterization. `SMGC/default copy.frag` is the old full-screen ray-marcher: it reads objects from the SSBO and has the Menger sponge, Mandelbulb, capsule and other shapes. The SSBO/task pipeline exists for that path.

### Scene (`Scene/`)
- Example producer component. Every tick it sends Clear → several PushObject → Swap to `"SMGC"`, with colors from `PaletteCosinka` (`SMGC/paletts.*`). It is disabled in `main.cpp`.

## Controls (for manual testing)
Arrow keys rotate the camera, WASD moves, Q/E halve or double the speed, and C snaps the angles to 45° and the position to the grid. With debug mode on, the camera pos/rot and per-tick timing are logged to stderr every tick.
