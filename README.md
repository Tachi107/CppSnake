# CppSnake

CppSnake is a simple Snake game made with OpenGL and C++

## Build

To build this project, you'll need [Meson](https://mesonbuild.com).
If you're on Windows, you'll also need to install [git](https://git-scm.com) in order to clone the repository.

After installing the required tools, open your terminal/command prompt and clone this repository using `git clone https://github.com/Tachi107/CppSnake.git --recurse-submodules`.
Then, enter the CppSnake folder and use `meson` to generate build files.
Last, compile the project with `meson compile`.

```sh
git clone https://github.com/Tachi107/CppSnake.git --recurse-submodules
cd CppSnake
meson setup build
meson compile -C build
```
