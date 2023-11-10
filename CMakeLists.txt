cmake_minimum_required(VERSION 3.24.0)
project(slowInterpreter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_executable(slowInterpreter 
	lox/Lox.cpp
)
