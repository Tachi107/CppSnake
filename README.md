# CppSnake

CppSnake is a simple Snake game made with OpenGL and C++

---

## Build

To build this project, you'll need [CMake](https://cmake.org).
If you're on Windows, you'll also need to install [git](https://git-scm.com) in order to clone the repository.

---

### Linux

First, clone this repository using `git clone --recurse-submodules https://github.com/Tachi107/CppSnake.git`.
Then, create a build directory outside of the CppSnake one, and generate the build files with CMake.
Last, compile the project with make.

```bash
mkdir CppSnake-build
cd CppSnake-build
cmake <CppSnake-dir> (for example, cmake ../CppSnake)
make
```

---

### Windows

Open a git command promt, and run `git clone --recurse-submodules https://github.com/Tachi107/CppSnake.git`.
Then, open CMake-GUI and select the downloaded repository as the source folder, and another folder of choice as the build folder.
Then, click on Configure and select the compiler you prefer, and wait until CMake has finished loading. Then, click Conigure again and lastly click on Generate to build the project.
Now you need to build the project files. If you choose Visual Studio in CMake, you'll just need to open the solution and build it as any other VS project.
