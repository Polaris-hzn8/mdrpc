cmake_minimum_required(VERSION 3.0)
project(mdrpc)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 公共包含目录
include_directories(${PROJECT_SOURCE_DIR}/mdrpc/include)
include_directories(${PROJECT_SOURCE_DIR}/example)

# 公共库目录
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(/opt/protobuf3/lib)  # protobuf 库目录

# 添加子目录（注意顺序：先构建库，再构建使用库的程序）
add_subdirectory(mdrpc)      # 先构建 mdrpc 动态库
add_subdirectory(example)    # 再构建 example 中的可执行文件

