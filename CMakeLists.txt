cmake_minimum_required(VERSION 3.16)
project(MonProjet LANGUAGES CXX)

# ------------------------
# C++20
# ------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------
# Options de compilation
# ------------------------
# Warnings généraux
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------
# Build types
# ------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ------------------------
# Include directories
# ------------------------
include_directories(include)

# ------------------------
# Sources
# ------------------------
set(SOURCES
    main.cpp
    src/DataSample.cpp
    src/DataSet.cpp
    src/Dendrite.cpp
    src/Perceptron.cpp
    src/Graphic.cpp
    src/Network.cpp
)
# Trouver SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Créer l'exécutable
add_executable(MonProjet ${SOURCES})

# Lier SFML
target_link_libraries(MonProjet PRIVATE sfml-graphics sfml-window sfml-system)

