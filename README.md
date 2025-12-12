# Polar

![polar library title](/images/cubes.png)

**Polar** is an open-source C++ framework for realtime interactive simulation.

It provides a core foundation for developing games, applications, and simulation-oriented projects.

## Supported platforms

Polar supports Linux and Windows; macOS has not been tested.

## External libraries

- SDL3 — windowing, input, and platform abstraction.
- EnTT — entity-component-system architecture.

All required dependencies are bundled within the repository.

## Build Instructions
CMake is used as the build system.

```bash
git clone https://github.com/telesleo/polar.git
cd polar
cmake -B build
cmake --build build
```

To include it in your own project:

```cmake
add_subdirectory("polar")
target_link_libraries(myproject PRIVATE polar)
```

## Roadmap
- Rendering system (OpenGL)
  - Render passes
  - 2D Lighting
- Input handling
- Audio support
- GUI

## Contributing
Contributions are welcome! Feel free to open issues or submit pull requests. :)
