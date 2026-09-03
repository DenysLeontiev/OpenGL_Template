# OpenGL Template

A lightweight, ready-to-use C++ OpenGL template project utilizing Premake for build configuration.

## Included Libraries

This project comes pre-configured with the following libraries:
- **OpenGL**: Core graphics API
- **GLFW**: Window creation and input handling
- **GLEW**: OpenGL extension wrangler
- **GLM**: Mathematics library for graphics
- **Dear ImGui**: Immediate mode GUI for debugging and interfaces
- **stb_image**: Image loading library
- **Assimp**: 3D model importer

## How to Build and Run

1. **Generate the Project Files**:
   Double-click `GenerateProject.bat` in the root directory. This uses Premake5 to generate a Visual Studio 2022 solution (`.sln`) file.

2. **Open the Project**:
   Open the newly generated `OpenGLTemplate.sln` in Visual Studio 2022.

3. **Build and Run**:
   - Set the build configuration to **Debug** and the platform to **x86** (or Win32).
   - Press **F5** (or click "Local Windows Debugger") to build and run the application.

*Note: Required DLLs and resources are automatically copied to the output folder as a post-build step.*
