cmake_minimum_required(VERSION 3.27.8)
project(speedway_mw_11_292745)

set(CMAKE_CXX_STANDARD 20)

add_executable(speedway_mw_11_292745 main.cpp
        Rider.cpp
        Rider.h
        Team.cpp
        Team.h
        Heat.cpp
        Heat.h
        Match.cpp
        Match.h
        Engine.cpp
        Engine.h
        Button.cpp
        Button.h)
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)
target_link_libraries(speedway_mw_11_292745 sfml-graphics sfml-window sfml-system)