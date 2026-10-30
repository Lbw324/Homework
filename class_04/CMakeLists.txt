# 1. 指定最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 2. 定义项目名称和编程语言
project(class_04 LANGUAGES CXX)

# 3. 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 查找 OpenCV 库
find_package(OpenCV 4 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}) 

# 6. 创建可执行程序
add_executable(class_04 main.cpp)

# 7. 链接 OpenCV 库
target_link_libraries(class_04 PRIVATE ${OpenCV_LIBS})
