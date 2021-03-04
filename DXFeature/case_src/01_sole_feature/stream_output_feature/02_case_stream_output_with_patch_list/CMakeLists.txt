set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++11)

add_compile_definitions(UNICODE _UNICODE)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/)
endif(WIN32)

include_directories("../../../../3rdparty/include/")
include_directories("../../../../common_class")
#link_directories("${CMAKE_BINARY_DIR}/lib")

aux_source_directory(../../../../common_class/ COMMON_CLASS)

add_executable(02_case_stream_output_with_patch_list WIN32 "CaseApp.cpp" "CaseApp.h" "02_case_stream_output_with_patch_list.cpp" ${COMMON_CLASS})
