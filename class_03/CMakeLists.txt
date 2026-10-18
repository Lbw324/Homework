cmake_minimum_required(VERSION 3.10)
project(class_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(class_03
    main.cpp
    src/MarkerManager.cpp
)

target_include_directories(class_03 PRIVATE include)