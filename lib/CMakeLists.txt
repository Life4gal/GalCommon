project(
		library_impl
		LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(
		${PROJECT_NAME}
		INTERFACE
		${PROJECT_SOURCE_DIR}/include
)
