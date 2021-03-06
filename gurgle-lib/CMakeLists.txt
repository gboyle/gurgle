
add_library(
    gurgle-lib
    imgui_impl_glfw_gl3.cpp
    imgui_impl_glfw_gl3.h    
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
    texture.cpp
    texture.hpp
    tests/test.cpp
    tests/test.hpp
    tests/test-menu.cpp
    tests/test-menu.hpp    
    tests/test-clear-color.cpp
    tests/test-clear-color.hpp
    tests/test-original.cpp
    tests/test-original.hpp
    tests/test-cube.cpp
    tests/test-cube.hpp
    tests/test-texture-2d.cpp
    tests/test-texture-2d.hpp
)

target_include_directories(gurgle-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/tests)

target_link_libraries(gurgle-lib PUBLIC glfw)
target_link_libraries(gurgle-lib PUBLIC glew::glew)
target_link_libraries(gurgle-lib PUBLIC stb::stb)
target_link_libraries(gurgle-lib PUBLIC glm)
target_link_libraries(gurgle-lib PUBLIC imgui::imgui)