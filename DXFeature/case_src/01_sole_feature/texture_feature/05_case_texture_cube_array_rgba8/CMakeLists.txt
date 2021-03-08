set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++11)

add_compile_definitions(UNICODE _UNICODE)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/01_sole_feature/texture_feature/05_case_texture_cube_array_rgba8/)
endif(WIN32)

include_directories("../../../../3rdparty/include/")
include_directories("../../../../common_class")


aux_source_directory(../../../../common_class/ COMMON_CLASS)

add_executable(05_case_texture_cube_array_rgba8 WIN32 "CaseApp.cpp" "CaseApp.h" "05_case_texture_cube_array_rgba8.cpp" ${COMMON_CLASS})
#target_link_libraries(01_case_clear_windows glad)
#target_link_libraries(01_case_clear_windows glfw3)