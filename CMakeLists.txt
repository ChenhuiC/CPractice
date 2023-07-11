cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(demo)

include_directories(include)

# 获取目录下所有的.C文件存入files里
file(GLOB files *.c)


add_executable(demo ${files})


# 遍历files把它们添加成可执行程序
# foreach (file ${files})
#     get_filename_component(name ${file} NAME)
#     add_executable(${name} ${file})
# endforeach ()