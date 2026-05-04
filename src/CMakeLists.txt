project(dltx-reader)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${GLOBAL_NAME})

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE dltx-reader.c)

install(TARGETS ${PROJECT_NAME})

project(xdb)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${GLOBAL_NAME})

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE xdb.c)

install(TARGETS ${PROJECT_NAME})
