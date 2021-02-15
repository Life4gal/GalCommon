cmake_minimum_required(VERSION 3.9.6...3.17 FATAL_ERROR)

project(
		galLibrary
		VERSION 0.0.1
		LANGUAGES CXX
		DESCRIPTION "empty for now"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)
add_subdirectory(test)
