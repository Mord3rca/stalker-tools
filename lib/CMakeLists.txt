FILE(GLOB sources *.c)
FILE(GLOB includes include/*.h)

add_library(${PROJECT_NAME} OBJECT)
target_include_directories(${PROJECT_NAME} PUBLIC include/)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_options(
    ${PROJECT_NAME} BEFORE PRIVATE
    -Wall
    $<$<CONFIG:BEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_sources(
    ${PROJECT_NAME} PUBLIC FILE_SET HEADERS
    BASE_DIRS include/
    FILES ${includes}
)

add_library(${PROJECT_NAME}_shared SHARED)
target_link_libraries(${PROJECT_NAME}_shared PUBLIC ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}_shared)

add_library(${PROJECT_NAME}_static STATIC)
target_link_libraries(${PROJECT_NAME}_static PUBLIC ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}_static)

install(TARGETS ${PROJECT_NAME} FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
