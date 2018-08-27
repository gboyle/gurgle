
#include "game.hpp"

#include "renderer.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "test-menu.hpp"
#include "test-clear-color.hpp"
#include "test-original.hpp"
#include "test-cube.hpp"

#include <iostream>
#include <string>

int gurgle()
{

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Gurgle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // must occur after we've created a valid OpenGL rendering context
    //glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Unable to initialize glew\n";
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    GLClearError();

    {
        // scope to deallocate OpenGL related locals before glfwTerminate

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glBlendEquation(GL_FUNC_ADD));

        Renderer renderer;

        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::Test *current_test = 0;
        test::TestMenu *test_menu = new test::TestMenu(current_test);
        current_test = test_menu;

        test_menu->registerTest<test::TestClearColor>("Clear Color");
        test_menu->registerTest<test::TestOriginal>("Original");
        test_menu->registerTest<test::TestCube>("Cube");

        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            ImGui_ImplGlfwGL3_NewFrame();

            if (current_test)
            {
                current_test->onUpdate(0.0f);
                current_test->onRender(renderer);

                ImGui::Begin("Test");
                if (current_test != test_menu && ImGui::Button("Back"))
                {
                    delete current_test;
                    current_test = test_menu;
                }
                current_test->onGuiRender();
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if (current_test != test_menu)
        {
            delete current_test;
        }

        delete test_menu;
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}
