cmake_minimum_required(VERSION 3.20)
project(3DEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_executable(3DEngine main.cpp
        Line.h
        Line.cpp
        Window.h
        Window.cpp
        Mesh.h
        Mesh.cpp
        ImportManager.cpp
        ImportManager.h
        BaseShapes.cpp
        BaseShapes.h
        UpdateManager.cpp
        UpdateManager.h
        UpdateManager.h)

target_link_libraries(3DEngine PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        assimp
)
