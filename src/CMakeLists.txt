cmake_minimum_required (VERSION 2.8.11)
project(csvtotex)
set (csvtotex_VERSION 1.0.1)
add_definitions(-DCMAKE_BUILD)
configure_file (
	"${PROJECT_SOURCE_DIR}/csvtotex_config.h.in"
	"${PROJECT_BINARY_DIR}/csvtotex_config.h"
)
add_executable(csvtotex csvtotex.c)
set_property(TARGET csvtotex PROPERTY C_STANDARD 99)
set_property(TARGET csvtotex PROPERTY C_STANDARD_REQUIRED ON)
target_include_directories (csvtotex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${PROJECT_BINARY_DIR}")