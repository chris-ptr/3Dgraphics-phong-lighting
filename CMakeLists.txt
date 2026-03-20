cmake_minimum_required(VERSION 3.10)
project(PhongLighting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/glad.c
    src/Sphere.cpp
    src/stb_image.cpp
)

# Headers
include_directories(headers)
include_directories(libheadfiles/include)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
# If glfw3 CONFIG is not found, try searching for it manually or using pkg-config
if(NOT glfw3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
endif()

# Assimp
find_package(assimp REQUIRED)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Linking
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    OpenGL::GL 
    ${GLFW_LIBRARIES}
    assimp::assimp
)

# Ensure shaders and assets are in the build directory or handle paths
# For now, let's copy them or set the working directory in the README
