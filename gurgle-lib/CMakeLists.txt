
add_library(
    gurgle-lib
    lib-main.cpp
    lib-main.hpp
)

target_include_directories(gurgle-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gurgle-lib glfw)