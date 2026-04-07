cmake_minimum_required(VERSION 3.10)

project(BalatroScoringSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB ALL_SOURCES "*.cpp")

add_executable(MainApp ${ALL_SOURCES})