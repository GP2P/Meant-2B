cmake_minimum_required(VERSION 3.21)
project(Meant_2B_df)

set(CMAKE_CXX_STANDARD 23)

# Meant 2B

file(GLOB_RECURSE MEANT2B_SRC game/src/*.cpp)

add_executable(Meant_2B_df game/src/game.cpp ${MEANT2B_SRC})

find_package(SFML REQUIRED COMPONENTS graphics audio)

include_directories(/opt/homebrew/Cellar/sfml/2.5.1_1/include)

target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-arm64-mac.a)

target_include_directories(Meant_2B_df PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> dragonfly/include)

# SaucerShoot

file(GLOB_RECURSE SAUCERSHOOT_SRC SaucerShoot/*.cpp)

add_executable(SaucerShoot SaucerShoot/game.cpp ${SAUCERSHOOT_SRC})

find_package(SFML REQUIRED COMPONENTS graphics audio)

include_directories(/opt/homebrew/Cellar/sfml/2.5.1_1/include)

target_link_libraries(Meant_2B_df PUBLIC sfml-graphics sfml-audio ${CMAKE_CURRENT_SOURCE_DIR}/dragonfly/lib/libdragonfly-arm64-mac.a)

target_include_directories(SaucerShoot PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> dragonfly/include)