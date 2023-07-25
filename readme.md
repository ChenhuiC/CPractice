## 使用cmake构建编译
1. 进入build文件夹
2. cmake .. -G "MinGW Makefiles"
3. cmake --build .

## 清理工程
没有找到cmake clean相关的  
所有生成的文件都在build中。要清理这些文件，只需删除目录rm -rf build