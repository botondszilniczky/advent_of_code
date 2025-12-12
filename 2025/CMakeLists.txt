# ./2025/CMakeLists.txt

cmake_minimum_required(VERSION 3.16)

project(AoC2025 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_compile_options(-Wall -Wextra -Wpedantic)


add_custom_target(copy_resources_2025
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_SOURCE_DIR}/input/*.in
    ${PROJECT_BINARY_DIR}/
    COMMENT "Copying resources into binary directory"
)

set(executables "01;02;03;04;05;06;07")

foreach(exe ${executables})
    add_executable(2025_${exe} src/${exe}.cpp)
    add_dependencies(2025_${exe} copy_resources_2025)
    
endforeach(exe ${executables})
