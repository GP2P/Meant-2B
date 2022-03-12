cmake_minimum_required(VERSION 3.21)
project(Meant_2B_df)

set(CMAKE_CXX_STANDARD 23)

# Meant 2B

# must manually reload CMake Project after adding file
file(GLOB_RECURSE MEANT2B_SRC game/src/*.cpp)

add_executable(Meant_2B_df game/src/game.cpp ${MEANT2B_SRC})

find_package(SFML REQUIRED COMPONENTS graphics audio)

# change to your SFML install directory's include folder
include_directories(/opt/homebrew/Cellar/sfml/2.5.1_1/include)

# uncomment only the line corresponding with your platform and architecture

# Windows
# target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-x64-debug.lib)
# macOS - intel
# target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-x64-mac.a)
# macOS - arm
target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-arm64-mac.a)
# Linux
# target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-x64-linux.a)

target_include_directories(Meant_2B_df PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> dragonfly/include)
