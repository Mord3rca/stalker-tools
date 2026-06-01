FILE(GLOB stfssources *.c syscalls/*.c)

project(stfs VERSION ${GLOBAL_VERSION})

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME} PRIVATE ${stfssources})

target_link_libraries(${PROJECT_NAME} PRIVATE stcore_shared)

target_compile_options(
    ${PROJECT_NAME} BEFORE PRIVATE
    -Wall
    $<$<CONFIG:BEBUG>:-g>
    -I${CMAKE_SOURCE_DIR}/lib/stcore  # Have to access private library
    -I${CMAKE_SOURCE_DIR}/lib/stcore/include
    -I${CMAKE_SOURCE_DIR}/lib/stfs
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS ${PROJECT_NAME})
