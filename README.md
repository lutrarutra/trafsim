# Traffic Simulator

Traffic simulator implemented in C++

![] (https://media.giphy.com/media/ifXVEva4ksUVCz5vRn/giphy.gif)


## Dependencies

* CMake (to generate makefile)
* GNU make (to build)
* OpenGL (dependency in SFML and ImGui)

## Working enviroments

* Unix including Mac OS


## How to build?

1. Clone `git clone --recursive https://github.com/lutrarutra/trafsim`
2. Create build directory inside of the project folder: `mkdir build`
3. Open navigate into new "build" folder with terminal: `cd build`
4. Generate makefile with CMake: `cmake ..`
5. Build generated makefile: `make`
6. Run it: `./a`


## Libraries used

* SFML - Simple and Fast Multimedia Library
  - https://github.com/SFML/SFML
  
* ImGui - Immediate Mode Graphical User interface for C++
  - https://github.com/ocornut/imgui

* ImGui - Library which allows you to use ImGui with SFML
  - https://github.com/eliasdaler/imgui-sfml
 
 