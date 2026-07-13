# =========================
# ===== dltx-resolver =====
# =========================

project(dltx-resolver)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} stcore_shared)

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE dltx-resolver.c)

install(TARGETS ${PROJECT_NAME})

# =========================
# ========= stfsmount =========
# =========================

if (!MSYS)

project(stfsmount)

add_executable(${PROJECT_NAME})

pkg_search_module(FUSE REQUIRED IMPORTED_TARGET fuse3)

target_link_libraries(${PROJECT_NAME} stcore_shared PkgConfig::FUSE)

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE stfsmount.c)

install(TARGETS ${PROJECT_NAME})

endif()

# =========================
# ========== xdb ==========
# =========================

project(xdb)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} stcore_shared)

add_compile_options(
    -Wall
    $<$<CONFIG:DEBUG>:-g>
)

target_sources(${PROJECT_NAME} PRIVATE xdb.c)

install(TARGETS ${PROJECT_NAME})
