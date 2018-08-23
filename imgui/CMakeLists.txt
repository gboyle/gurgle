

add_library(
    imgui

    imgui.cpp
    imgui_draw.cpp
    imgui_impl_glfw_gl3.cpp
    imgui_internal.h
    stb_rect_pack.h
    stb_truetype.h
    imconfig.h
    imgui_demo.cpp
    imgui.h
    imgui_impl_glfw_gl3.h
    # main.cpp
    stb_textedit.h
)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(imgui PUBLIC glew::glew)
# target_link_libraries(imgui PUBLIC stb::stb)
# target_link_libraries(imgui PUBLIC glm)

