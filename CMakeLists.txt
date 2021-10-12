# Shoutout to CMake guide: https://eliasdaler.github.io/using-cmake/
cmake_minimum_required(VERSION 3.1)

IF (WIN32)
    set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe)
    # this makes sure that .dll-files are build into build/ folder
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSEIF (APPLE)
    # run 'where clang' and 'where clang++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
ELSEIF (UNIX AND NOT APPLE)
    # run 'which gcc' and 'which g++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
ENDIF()
    
# Get project name from folder name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Use c++ 17
set(CMAKE_CXX_STANDARD 17)
# Enable additional warnings and debug mode
# https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

# All .cpp-files
file(GLOB SOURCES src/*.cpp)
file(GLOB CORE src/core/*.cpp)
file(GLOB UTILS src/util/*.cpp)
file(GLOB TRAFFICSIM src/trafficsim/*.cpp)
# folder with .h files, e.g. include/
include_directories(src)

# 3rd party dependencies
add_subdirectory(lib)

# Here the .c/.cpp files get linked
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES} ${TRAFFICSIM} ${CORE} ${UTILS})

# Here we link 3rd party library ImGui-SFML
# No need to link SFML implicitly as ImGui-SFML does it for you!
# Refer to https://eliasdaler.github.io/using-cmake/
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)

# Additional resources like images and fonts
# We want the to copy from permanent folder "res" to temporary folder "build"
configure_file(res/texture_list.txt texture_list.txt COPYONLY)
configure_file(res/car/blue_car.png blue_car.png COPYONLY)
configure_file(res/car/brown_car.png brown_car.png COPYONLY)
configure_file(res/car/green_car.png green_car.png COPYONLY)
configure_file(res/car/grey_car.png grey_car.png COPYONLY)
configure_file(res/car/red_car.png red_car.png COPYONLY)
configure_file(res/car/teal_car.png teal_car.png COPYONLY)
configure_file(res/car/white_car.png white_car.png COPYONLY)
configure_file(res/home_building.png home_building.png COPYONLY)
configure_file(res/office_building.png office_building.png COPYONLY)
configure_file(res/home_road.png home_road.png COPYONLY)
configure_file(res/straight_road.png straight_road.png COPYONLY)
configure_file(res/right_turn.png right_turn.png COPYONLY)
configure_file(res/left_turn.png left_turn.png COPYONLY)
configure_file(res/right_intersection.png right_intersection.png COPYONLY)
configure_file(res/left_intersection.png left_intersection.png COPYONLY)
configure_file(res/right_trisection.png right_trisection.png COPYONLY)
configure_file(res/left_trisection.png left_trisection.png COPYONLY)
configure_file(res/right_junction.png right_junction.png COPYONLY)
configure_file(res/left_junction.png left_junction.png COPYONLY)
configure_file(res/map1.csv map1.csv COPYONLY)

# Set "a" to be the output filename, does not really matter, shorter is quicker to type...
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")