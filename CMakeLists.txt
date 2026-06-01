cmake_minimum_required(VERSION 3.5)

set(GLOBAL_NAME "stalker-tools")
set(GLOBAL_VERSION "0.0.1")

project(
    ${GLOBAL_NAME} LANGUAGES C VERSION ${GLOBAL_VERSION}
    DESCRIPTION "A collection of tools to manipulate/parse STALKER assets"
)

set(ENABLE_DLTX_TRACE OFF CACHE BOOL "Enable Trace capability for DLTX parsing")

include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

if (${ENABLE_DLTX_TRACE})
    add_definitions( -DDLTX_TRACE )
endif()

add_subdirectory("lib/stcore")
add_subdirectory("src/")
