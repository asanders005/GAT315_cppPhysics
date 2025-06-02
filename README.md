# Physics Simulator

A 2D physics simulator with a graphical user interface, built using C++17 and [raylib](https://www.raylib.com/). The simulator allows you to interactively create, modify, and simulate physical bodies and springs in real time.

## Features

- **Interactive GUI:** Adjust body properties (mass, size, gravity scale, damping, restitution) and world parameters (gravity, gravitation, spring stiffness) using sliders and toggles.
- **Body Types:** Switch between Dynamic, Kinematic, and Static body types.
- **Spring Simulation:** Tune spring damping and stiffness.
- **Real-Time Simulation:** Start, pause, and reset the simulation at any time.
- **Camera Controls:** Pan and zoom the scene for better visualization.

## Getting Started

### Prerequisites

- C++17 compatible compiler (e.g., MSVC, GCC, Clang)
- [raylib](https://www.raylib.com/) library
- [raygui](https://github.com/raysan5/raygui) for GUI components

### Controls

- **TAB:** Toggle the physics properties window.
- **Mouse:** Interact with GUI sliders, buttons, and dropdowns.
- **Reset:** Click the "Reset World" button or use backspace to restart the simulation.

## File Structure

- `src/GUI/Gui.cpp` — Handles all GUI rendering and user interaction.
- `src/Physics/` — Core physics logic (bodies, forces, springs).
- `src/Main.cpp` — Application entry point and main loop.

## Customization

- **Styles:** GUI style can be changed by modifying the style file path in `Gui.cpp`.
- **Physics Parameters:** Extend or modify the available parameters in the GUI as needed.

## Acknowledgments

- [raylib](https://www.raylib.com/) — Simple and easy-to-use library to enjoy videogames programming.
- [raygui](https://github.com/raysan5/raygui) — Immediate-mode GUI for raylib.
