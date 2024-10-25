cmake_minimum_required(VERSION 3.0)
project(main)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置头文件的搜索路径
#inlcude_directories()

#配置库文件搜索路径
#link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#设置可执行文件最终存储路径,PROJECT_SOURCE_DIR表示工程的根目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#把.指定路径下的所有.cpp文件添加到SRC_LIST
#aux_source_directory(. SRC_LIST)


#表示生成可执行文件server，由SRC_LIST中的源文件编译而来
add_executable(server ${SRC_LIST})

#server这个目标程序需要链接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread) 
