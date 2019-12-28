#Version of cmake
cmake_minimum_required(VERSION 2.8)

# Get project name from folder name and set it
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Specify c++ version
set(CMAKE_CXX_STANDARD 14)

# if (NOT MSVC)
#     target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined,address)
#     target_link_libraries(${PROJECT_NAME} asan ubsan)
# endif()

# All .cpp-files
#set(SOURCES src/main.cpp src/Window.cpp src/Application.cpp)
file(GLOB SOURCES src/*.cpp)
file(GLOB CORE src/core/*.cpp)
file(GLOB UTILS src/util/*.cpp)
file(GLOB TRAFSIM src/trafficsim/*.cpp)
set(IMGUI_SOURCES deps/imgui/imgui.cpp deps/imgui/imgui_widgets.cpp deps/imgui/imgui_draw.cpp deps/imgui/imgui_demo.cpp deps/imgui-sfml/imgui-SFML.cpp)
#set(TRACY_SOURCES deps/tracy/TracyClient.cpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${TRAFSIM} ${CORE} ${UTILS} ${IMGUI_SOURCES})


# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

#folder with your header (.h) files
include_directories(src)
include_directories(src/core)
include_directories(src/util)
include_directories(src/trafficsim)

# Additional resources like images and fonts
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

# Find sfml and link it
# if you want to move sfml folder into another folder 
# edit line "include_directories(other_folder/SFML/include)"
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cmake")
find_package(SFML 2.5 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


#Osmium deps libraries
target_link_libraries(${PROJECT_NAME} bz2) #bz2lib
target_link_libraries(${PROJECT_NAME} expat) #expatlib
target_link_libraries(${PROJECT_NAME} z) #zlib

#tracy dep libraries
#target_link_libraries(${PROJECT_NAME} pthread) #libpthread
#target_link_libraries(${PROJECT_NAME} dl) #libdl

#OpenGL for ImGui
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(WARNING "OpenGL not found!\n")
endif()
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})


include_directories(deps/imgui)
include_directories(deps/imgui-sfml)

#include_directories(deps/tracy)

#Osmium library
find_package(Osmium REQUIRED)
if(NOT OSMIUM_FOUND)
    message(WARNING "Libosmium not found!\n")
endif()
include_directories(${OSMIUM_INCLUDE_DIRS})

#Protozero
find_package(Protozero REQUIRED)
if(NOT PROTOZERO_FOUND)
    message(WARNING "Protozero not found!\n")
endif()
include_directories(${PROTOZERO_INCLUDE_DIRS})

# Set "a" as output's name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")