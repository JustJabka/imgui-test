cmake_minimum_required(VERSION 3.10)
project(imgui_test)

# C++ version
set(CMAKE_CXX_STANDARD 17)

# headers
include_directories(include)
include_directories(include/glad)
include_directories(include/imgui)
include_directories(include/KHR)
include_directories(include/stb)

# src and lib
file(GLOB LIBS lib/*.cpp)
file(GLOB SOURCES src/*.c)

# Create executable
add_executable(imgui_test main.cpp ${SOURCES} ${LIBS})

# Add all required libraries (OpenGL, GLFW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(imgui_test OpenGL::GL glfw)