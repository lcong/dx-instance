set(CMAKE_CXX_STANDARD 17)
add_definitions(-std=c++11)

add_compile_definitions(UNICODE _UNICODE)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/01_sole_feature/cliping_feature/01_case_clipping_with_culldistance/)
endif(WIN32)

include_directories("../../../../3rdparty/include/")
include_directories("../../../../common_class")
#link_directories("${CMAKE_BINARY_DIR}/lib")

aux_source_directory(../../../../common_class/ COMMON_CLASS)

add_executable(01_case_clipping_with_culldistance WIN32 "CaseApp.cpp" "CaseApp.h" "01_case_clipping_with_culldistance.cpp" ${COMMON_CLASS})
#target_link_libraries(01_case_clear_windows glad)
#target_link_libraries(01_case_clear_windows glfw3)