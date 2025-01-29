# CondorEngine

## Libraries
Library | Version | Description
--------|---------|------------
Assimp | v5.4.3 | Mesh Loader
GLEW | | OpenGL Extensions
GLFW | v3.4 | Window Handler
GLM | v1.0.1 | OpenGL Math
STB | | Image Loader

---

## Installation

### `Method A` Download Source (Recommended)
1. Go to [CondorHalcon/CondorEngine/releases](https://github.com/CondorHalcon/CondorEngine/releases) and download the source code.
2. Extract the source to your project directory.
3. To your `CMakeLists.txt` file add:
    ```cmake
    add_subdirectory(CondorEngine)
    ```

### `Method B` Git Submodule
1. In terminal run the command 
    ```bash
    git submodule add -b master https://github.com/CondorHalcon/CondorEngine.git CondorEngine
    ```
2. Add `add_subdirectory(CondorEngine)` to your `CMakeLists.txt` file.

### `Method C` CMake FetchContent
1. Add the following to your `CMakeLists.txt` file:
    ```cmake
    FetchContent_Declare(
        CondorEngine
        GIT_REPOSITORY https://github.com/CondorHalcon/CondorEngine.git
        GIT_TAG        v0.2.0 # release-0.2.0
    )
    ```
2. After all the `Declare` commands in your `CMakeLists.txt` file add:
    ```cmake
    FetchContent_MakeAvailable(CondorEngine)
    ```

---

Once the engine has been added to your project with your preferred method, you can link it in your `CMakeLists.txt` file with:
```cmake
target_link_libraries(MyProject PUBLIC CondorEngine)
```
