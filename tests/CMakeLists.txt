enable_testing()

project(stcoretests)

FILE(GLOB testssrc *.c)

add_executable(${PROJECT_NAME})

pkg_search_module(CUNIT REQUIRED IMPORTED_TARGET cunit)

target_link_libraries(${PROJECT_NAME} stcore_shared PkgConfig::CUNIT)

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE ${testssrc})

add_test(NAME stcoretests COMMAND ./${PROJECT_NAME})
