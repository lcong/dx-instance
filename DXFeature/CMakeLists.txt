# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)
project ("d3d_test_case")
# 包含子项目。
message("d3d_test_case_start")

configure_file(./3rdparty/root_directory.h.in ${CMAKE_SOURCE_DIR}/3rdparty/include/root_directory.h)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

#add_subdirectory ("lib_build")
add_subdirectory ("case_src")