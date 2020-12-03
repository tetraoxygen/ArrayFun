cmake_minimum_required(VERSION 3.16)

project(arrayfun)

add_executable(arrayfun arrayfun.cpp)

install(TARGETS arrayfun)

enable_testing()
add_test(NAME arrayfun COMMAND arrayfun)


IF (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_libraries(arrayfun -static)
ENDIF()