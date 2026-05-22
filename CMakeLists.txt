cmake_minimum_required(VERSION 4.2)
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
        Match.h)
