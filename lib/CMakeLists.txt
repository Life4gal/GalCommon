project(library LANGUAGES CXX)

file(GLOB_RECURSE HEADERS "include/*.hpp")

add_library(${PROJECT_NAME} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
