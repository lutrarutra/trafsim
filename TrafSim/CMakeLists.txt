# Get project name from folder name and set it
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

#Version of cmake
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14) #c++14

file(GLOB SOURCES src/*.cpp)
file(GLOB CORE src/core/*.cpp)
file(GLOB UTILS src/util/*.cpp)
file(GLOB TRAFFICSIM src/trafficsim/*.cpp)
set(IMGUI_SOURCES deps/imgui/imgui.cpp deps/imgui/imgui_widgets.cpp deps/imgui/imgui_draw.cpp deps/imgui/imgui_demo.cpp deps/imgui-sfml/imgui-SFML.cpp)


if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if (${APPLE})
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cmake")
    find_package(SFML 2.5.1 REQUIRED network audio graphics window system)
    if(SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
    endif()
    add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES} ${TRAFFICSIM} ${CORE} ${UTILS})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()
if(LINUX)
    set(SFML_INCLUDE_DIR "deps/SFML/include")
    set(SFML_LIBRARY_DIR "deps/SFML/lib")
    set(SFML_DIR "deps/SFML/lib/cmake/SFML")

    link_directories(SFML_LIBRARY_DIR)
    include_directories(SFML_INCLUDE_DIR)

    # .cpp files
    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

    if(SFML_FOUND)
        message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
        message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
        message(STATUS "SFML_VERSION: ${SFML_VERSION}")
    endif()
    add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES} ${TRAFFICSIM} ${CORE} ${UTILS})
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
endif ()

include_directories(deps/imgui)
include_directories(deps/imgui-sfml)
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


find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(WARNING "OpenGL not found!\n")
endif()
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

# Enable additional warnings and debug mode
set (CMAKE_CXX_FLAGS "-g -W -pedantic")

#folder with your header (.h) files
include_directories(src)


# Set "a" as output's name
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "a")