FILE(GLOB execsources *.c)

foreach(source ${execsources})
    get_filename_component(pname ${source} NAME_WE)

    project(${pname})

    add_executable(${PROJECT_NAME})

    target_link_libraries(${PROJECT_NAME} ${GLOBAL_NAME})

    add_compile_options(
        -Wall
        $<$<CONFIG:DEBUG>:-g>
    )

    target_sources(${PROJECT_NAME} PRIVATE ${source})

    install(TARGETS ${PROJECT_NAME})
endforeach()
