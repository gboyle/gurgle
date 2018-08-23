
add_library(
    gurgle-lib
    game.cpp
    game.hpp
    renderer.cpp  
    renderer.hpp 
    vertex-buffer.cpp
    vertex-buffer.hpp
    index-buffer.cpp
    index-buffer.hpp
    vertex-array.cpp
    vertex-array.hpp
    vertex-layout.cpp
    vertex-layout.hpp
    shader.cpp
    shader.hpp
)

target_include_directories(gurgle-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gurgle-lib glfw)
target_link_libraries(gurgle-lib glew::glew)