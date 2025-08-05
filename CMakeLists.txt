cmake_minimum_required(VERSION 3.10)
project(HungarianAlgorithm VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译选项
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# 添加包含目录
include_directories(include)

# 创建库
add_library(hungarian STATIC
    src/hungarian.cpp
)

target_include_directories(hungarian PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 创建示例程序
add_executable(hungarian_example
    examples/main.cpp
)

target_link_libraries(hungarian_example hungarian)

# 创建测试程序
add_executable(hungarian_test
    tests/test_hungarian.cpp
)

target_link_libraries(hungarian_test hungarian)

# 安装规则
install(TARGETS hungarian
    EXPORT HungarianAlgorithmTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES include/hungarian.h
    DESTINATION include
)
