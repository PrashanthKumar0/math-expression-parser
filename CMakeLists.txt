cmake_minimum_required(VERSION 3.3)
project(math-expression-parser)

file(GLOB src_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# file(GLOB internal_header_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
# message("SRC ${src_files}")

add_executable(math_exp_parser main.cpp ${src_files})
target_include_directories(math_exp_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
