#Version of cmake
cmake_minimum_required(VERSION 2.8)

# Get project name from folder name and set it
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# Specify c++ version
set(CMAKE_CXX_STANDARD 14)

# All .cpp-files
#set(SOURCES src/main.cpp src/Window.cpp src/Application.cpp)
file(GLOB SOURCES src/*.cpp)
set(IMGUI_SOURCES deps/imgui/imgui.cpp deps/imgui/imgui_widgets.cpp deps/imgui/imgui_draw.cpp deps/imgui/imgui_demo.cpp deps/imgui-sfml/imgui-SFML.cpp)
#set(TRACY_SOURCES deps/tracy/TracyClient.cpp)
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES})


# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

#folder with your header (.h) files
include_directories(src)

# Additional resources like images and fonts
# configure_file(res/OpenSans-Regular.ttf OpenSans-Regular.ttf COPYONLY)
configure_file(res/worldmap.png worldmap.png COPYONLY)

# Find sfml and link it
# if you want to move sfml folder into another folder 
# edit line "include_directories(other_folder/SFML/include)"
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cmake")
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(deps/SFML/include) #edit set this line according to where ur sfml folder is
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