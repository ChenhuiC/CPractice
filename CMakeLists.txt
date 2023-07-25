cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(demo)

include_directories(include)

# 获取当前目录及其子目录下的所有c文件存入files里
file(GLOB files ${CMAKE_SOURCE_DIR}/*.c ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/sort/*.c)

# 添加子目录
# add_subdirectory(src)

add_executable(demo ${files})
foreach (file ${files})
    message(${file})
endforeach ()

# 遍历files把它们添加成可执行程序
# foreach (file ${files})
#     get_filename_component(name ${file} NAME)
#     add_executable(${name} ${file})
# endforeach ()