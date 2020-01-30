cmake_minimum_required(VERSION 3.15)
project(Assignment3_Bernardi_Buoso_Benetollo)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(Assignment3_Bernardi_Buoso_Benetollo mainTestLib.cc)