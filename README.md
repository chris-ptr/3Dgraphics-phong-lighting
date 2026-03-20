# 3D Graphics - Phong Lighting Project

## Student: Christos Petropoulos (AM: 1115202100156)
### Course: Computer Graphics I 2024-2025

This project demonstrates a 3D scene with dynamic Phong lighting implemented in OpenGL. It features a moving light source (represented by a rotating sphere) orbiting a 3D model.

## Features

- **Phong Lighting Model**: Implementation of ambient, diffuse, and specular lighting.
- **3D Model Loading**: Uses Assimp to load complex 3D models (e.g., `woman1.obj`).
- **Dynamic Light Source**: A white sphere that orbits the model, acting as a point light source.
- **Interactive Camera**: Fly-through camera system using W, A, S, D and Mouse.
- **Adjustable Light Speed**: Control the rotation speed of the light source.

## Controls

| Key | Action |
| :---: | :--- |
| **W** | Move Forward |
| **S** | Move Backward |
| **A** | Move Left |
| **D** | Move Right |
| **H** | Increase Light Rotation Speed |
| **J** | Decrease Light Rotation Speed |
| **ESC** | Exit Application |
| **Mouse** | Look Around |

## Video Demonstration
![Phong Lighting Project](video/3d_phong.gif)

## Project Structure

- `src/`: Source code files (`.cpp`, `.c`).
- `headers/`: Header files (`.h`).
- `shaders/`: GLSL vertex and fragment shaders.
- `assets/`: 3D models and textures.
- `libheadfiles/`: External library headers (GLFW, GLM, Assimp, GLAD, stb).
- `CMakeLists.txt`: Modern CMake build configuration.

## How to Build

### Linux (Ubuntu/Debian)

1.  **Install Dependencies**:
    ```bash
    sudo apt-get update
    sudo apt-get install build-essential cmake libgl1-mesa-dev libglfw3-dev libassimp-dev libglm-dev
    ```

2.  **Build**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  **Run**:
    ```bash
    ./PhongLighting
    ```

### Windows (Visual Studio)

The repository still contains the project structure compatible with Visual Studio. You can open the project and ensure that the library paths in `libheadfiles/libs` are correctly linked. Alternatively, use CMake for Windows:

1.  Open the folder in Visual Studio (it has built-in CMake support).
2.  Or use CMake GUI to generate a `.sln` file.

## Acknowledgments

Based on custom implementations and concepts from [LearnOpenGL](https://learnopengl.com/).
