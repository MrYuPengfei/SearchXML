cmake_minimum_required(VERSION 3.15)
project(SearchEngin VERSION 4.1.1)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
# 添加子目录
add_subdirectory(3rd)
add_subdirectory(common)
add_subdirectory(prepare)
add_subdirectory(server)
add_subdirectory(client)
