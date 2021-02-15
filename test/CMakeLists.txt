cmake_minimum_required(VERSION 3.9.6...3.17)

project(galTest LANGUAGES CXX)

add_executable(
		${PROJECT_NAME}
		main.cpp
)

target_compile_features(galTest PRIVATE cxx_std_17)

target_link_libraries(galTest PRIVATE library)



