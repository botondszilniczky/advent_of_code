add_custom_target(copy_resources
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_SOURCE_DIR}/2015/*/input*.txt
    ${PROJECT_BINARY_DIR}/2015/
    COMMENT "Copying resources into binary directory"
)

set(directories "01;02;03;05;06")

foreach(dir ${directories})
    add_executable(${dir} ${dir}/solution.cpp)
    target_include_directories(${dir} PUBLIC ${PROJECT_BINARY_DIR}/processing)
    target_link_libraries(${dir} PUBLIC InputProcessor FileReader)
    add_dependencies(${dir} copy_resources)
endforeach() 
