cmake_minimum_required(VERSION 3.15)
project(SearchEngin VERSION 4.1.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_FLAGS   "-std=c++17")             # c++17
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告
set(CMAKE_CXX_FLAGS_DEBUG   "-O0" )             # 调试包不优化
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG " )   # release包优化
SET(CMAKE_BUILD_TYPE "Debug")                   # 使用Debug模式
# SET(CMAKE_BUILD_TYPE "Release")                 # 使用Release模式
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# 添加子目录
add_subdirectory(3rd)
add_subdirectory(common)
add_subdirectory(prepare)
add_subdirectory(server)
add_subdirectory(client)
