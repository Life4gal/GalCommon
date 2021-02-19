cmake_minimum_required(VERSION 3.9.6...3.17 FATAL_ERROR)

project(galTest LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
		NAME cxxopts
		GITHUB_REPOSITORY jarro2783/cxxopts
		VERSION 2.2.0
		OPTIONS "CXXOPTS_BUILD_EXAMPLES Off" "CXXOPTS_BUILD_TESTS Off"
)

CPMAddPackage(NAME galLibrary SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create test executable ----
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp")

add_executable(
		${PROJECT_NAME}
		${sources}
		main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "galTest")

target_link_libraries(${PROJECT_NAME} galLibrary::galLibrary cxxopts)
