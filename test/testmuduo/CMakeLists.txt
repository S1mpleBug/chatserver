# cmake_minimum_required(VERSION 3.0)
# project(main) # 工程名字 而非可执行文件名字

# # 配置编译选项
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)  # 在原始的编译选项基础上再加一个-g选项
set (CMAKE_CXX_STANDARD 11)                 # 设置C++11标准
# 配置头文件搜索路径
# include_directories()
# 配置库文件搜索路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 设置cmake的全局变量
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 把.制定的路径下的所有源文件名字放入变量名SRC_LIST里面
# aux_source_directory(. SRC_LIST)

# 表示生成可执行文件server 由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})
# 表示server这个目标程序 需要连接muduo_net muduo_base pthread三个库文件
target_link_libraries(server muduo_net muduo_base pthread)