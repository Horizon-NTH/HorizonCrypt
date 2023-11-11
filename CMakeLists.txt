cmake_minimum_required(VERSION 3.12)

project(horizoncrypt VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(GMP REQUIRED)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/hcrypt/*.h ${CMAKE_SOURCE_DIR}/include/hcrypt/*.hpp)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
include_directories(C:/msys64/clang64/include)
target_include_directories(${PROJECT_NAME} PRIVATE include ${GMP_INCLUDE_DIR})
link_directories(C:/msys64/clang64/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GMP_LIBRARY})
