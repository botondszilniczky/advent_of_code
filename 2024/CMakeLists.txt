#add_executable(01 src/01.cpp)

add_custom_target(copy_resources_2024
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_SOURCE_DIR}/2024/*/*input.txt
    ${PROJECT_BINARY_DIR}/2024/
    COMMENT "Copying resources into binary directory"
)


set(executables "01;02")

foreach(exe ${executables})
    add_executable(2024_${exe} src/${exe}.cpp)
    add_dependencies(2024_${exe} copy_resources_2024)
endforeach()