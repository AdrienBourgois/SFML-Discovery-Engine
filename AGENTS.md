# AGENTS.md — Guidance for AI coding agents

Purpose: give an AI (or new contributor) the minimum, practical knowledge to be immediately productive in this repository.

Quick plan (what this file contains)
- One-line project summary and big-picture architecture
- Concrete build / run / debug commands for Windows (Visual Studio / msbuild)
- Project-specific conventions and patterns with exact file references
- Integration points, bundled libs, and common pitfalls

Quickstart (developer flow)
- Open the solution: `SFML Discovery Engine.slnx` in Visual Studio (recommended). Set `Game` as the startup project and build Debug/x64.
- Command-line build (PowerShell):
  msbuild "E:\Gaming Campus\Templates\SFML Discovery Engine\SFML Discovery Engine.slnx" /p:Configuration=Debug /p:Platform=x64
- Run the game binary:
  `E:\Gaming Campus\Templates\SFML Discovery Engine\x64\Debug\Game.exe`
- Logs: `Logs/EngineLog.txt`. Build artifacts: `x64/Debug/` contains `Game.exe`, `Engine.lib`, `*.pdb`.

Big-picture architecture
- Engine (Engine/) — the reusable core implemented as a static library. Public API headers live in `Engine/include/` and implementation in `Engine/src/`.
- Game (Game/) — an executable project that references `Engine` as a project dependency and uses Engine public headers.
- include/ — third-party headers (ImGui, SFML headers shipped here for convenience).
- lib/ — vendored static libraries (SFML, freetype, FLAC/ogg/vorbis, etc.). Examples: `lib/sfml-graphics-s-d.lib`, `lib/freetype.lib`, `lib/FLAC.lib`.

How components interact (key files)
- Engine public API: `Engine/include/Engine.h`, `Engine/include/EngineConfig.h`.
- Module system (Engine provides a Module base + ModuleManager): `Engine/include/Module.h`, `Engine/include/ModuleManager.h`, `Engine/include/ModuleManager.inl` and `Engine/src/ModuleManager.cpp`.
- Game entry: `Game/main.cpp` uses `Engine::Init(argc, argv)` and `Engine::Run()`.

Module pattern & lifecycle (how to add features)
- Modules subclass `Module` and register/instantiate via `ModuleManager`. Look at `Engine/include/Modules/ImGuiModule.h` and `Engine/src/Modules/ImGuiModule.cpp` for an example.
- Typical lifecycle methods are declared/used in ModuleManager — initialization, update, render, shutdown. Put public APIs for modules in `Engine/include/Modules/`.

Technical stack (concise)
- IDE / build: Visual Studio, solution file `SFML Discovery Engine.slnx` (uses x64 platform by default).
- Language: C++ (minimum C++20). The codebase uses modern features and aims for C++23/C++26 where appropriate.
- Rendering & windowing: SFML (static libraries bundled in `lib/`, headers in `include/SFML/`).
- UI/Debug: ImGui + ImGui-SFML (sources compiled directly into `Engine/ImGui/`).
- Physics: Box2D is planned but not yet integrated.

Notable implementation details (exact references)
- Engine is implemented as a singleton that owns a `ModuleManager` (`Engine/include/Engine.h`).
- Module lifecycle is extensive: Awake / Start / Update / PreRender / Render / OnGUI / PostRender / Present / OnDebug / OnDebugSelected / Destroy / Finalize. See module headers under `Engine/include/Modules/` and `ModuleManager.inl`.
- `ModuleManager` stores modules in a `std::vector<Module*>` and provides `CreateModule<T>()` and `GetModule<T>()` helpers using concepts + `dynamic_cast`. See `Engine/include/ModuleManager.inl` and `Engine/src/ModuleManager.cpp`.
- Gameplay structure: `Scene` contains `GameObject[]`, each holding `Component[]`. Creation and lookup use `dynamic_cast`-based helpers. See `Engine/include/Scene.h`, `GameObject.h`, `Component.h`.
- Math utilities: a custom templated `Vector2<T>` exists under `Engine/include/Maths/`.
- Command-line parsing: `Engine/src/EngineConfig.cpp` populates a map of args; use `EngineConfig::ArgExists` / `GetArg`.
- Logging: simple in-repo logger; default output file is `Logs/EngineLog.txt` (see `Engine/include/Utils/Logger/*`).
- Memory model: code currently uses raw pointers for ownership in many places; a progressive migration to `std::unique_ptr` is under consideration. Be careful when changing ownership semantics.
- Known filename mismatch: `RessourcesModule.cpp` (typo) vs expected `ResourcesModule` naming — be cautious when searching by exact name.

Design constraints & project philosophy (practical guidance for contributors and agents)
- Prioritize clarity and straightforward code over advanced abstractions. When non-obvious techniques are used (concepts, templates, `dynamic_cast`, ownership choices), prefer adding a short comment explaining the rationale.
- Introduce modern C++ features progressively and only when they improve readability or teachability (e.g., `unique_ptr`, `std::expected`, ranges, `[[nodiscard]]`, `constexpr`, `std::span`).
- Keep external dependencies minimal — this repo ships SFML and ImGui sources; avoid adding new libraries without pairing the change with clear reasons and update instructions for `include/` and `lib/`.
- Avoid over-engineering: prefer simple, explicit solutions unless a refactor is justified and documented.

Command-line args (project-specific behavior)
- Parser: `Engine/src/EngineConfig.cpp` — behavior summary:
  - Flags start with `-`, stored without the leading dash (`-example` → key `example`).
  - The token following a flag is treated as its value. Use `EngineConfig::GetArg("key")` and `ArgExists("key")`.
  - Note: the implementation inserts the current key/value pair on each loop iteration — review `SetCommandLineArgs` if you rely on strictly empty keys for positional args.

Third-party integration & lib handling
- Headers: `include/ImGui`, `include/ImGui-SFML`, and `include/SFML` provide headers used by Engine and Game.
- Static libraries are vendored in `lib/`. When editing vcxproj files, ensure `AdditionalLibraryDirectories` point to this folder and add the appropriate `*.lib` names to link lists.
- The projects use static SFML variants (filenames contain `-s`); be aware of `SFML_STATIC` defines and potential dependencies (opengl32, winmm, etc.).

Build & run gotchas
- Platform / configuration must match: the repo expects x64 builds. Mismatched platform leads to link errors.
- Post-build or packaging steps may copy `Assets/` into the output folder — assets should be next to the exe at runtime.
- If libs are missing, verify `lib/` contents and `AdditionalLibraryDirectories` in the `*.vcxproj` files.

Debugging tips
- Use Visual Studio with `Game` as startup project; PDBs are present in `x64/Debug/` for mixed debugging.
- Check `Logs/EngineLog.txt` for runtime engine messages.

Conventions & patterns to follow (for agents)
- Public vs private headers: put engine public headers in `Engine/include/`. Implementation files belong in `Engine/src/`.
- Inline/template implementations live in `.inl` files next to their headers (e.g., `ModuleManager.inl`) — update both header and .inl when changing templated behavior.
- Keep module APIs stable and expose them via `Engine/include/Modules/*`.

Where to change things safely
- To add a new module: add header to `Engine/include/Modules/`, implementation to `Engine/src/Modules/`, and register creation in `ModuleManager` (see `ModuleManager.inl` and existing `CreateDefaultModules`).
- To update a third-party lib: replace headers in `include/` and the `.lib` files in `lib/`, then update `*.vcxproj` link lists.

FAQ / common PR checks for agents
- Ensure builds succeed on x64/Debug before proposing API changes.
- If altering public headers, update `Engine.vcxproj` ClInclude entries and bump any dependent Game code.
- When changing command-line parsing or Engine startup behavior, include tested scenarios: no-arg runs, flags without values, and flag+value combinations.

References (exact files to inspect for examples)
- `Engine/include/Engine.h`
- `Engine/src/EngineConfig.cpp`
- `Engine/include/ModuleManager.inl`
- `Engine/src/Modules/ImGuiModule.cpp`
- `Game/main.cpp`
- `lib/` (all `*.lib` files)