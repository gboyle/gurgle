cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.21.tar.gz"
    SHA1 "15e27f2fe47d4f162b5cab1e6dfecc699ebaa304"
)

project(gurgle VERSION 0.0.1)


hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)

hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

hunter_add_package(stb)
find_package(stb CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm CONFIG REQUIRED)

hunter_add_package(imgui)
find_package(imgui CONFIG REQUIRED)

add_subdirectory(gurgle-lib)
add_subdirectory(gurgle-test)
add_subdirectory(gurgle-game)

set_property(PROPERTY VS_STARTUP_PROJECT gurgle-game)

enable_testing()
add_test(NAME testgurgle COMMAND gurgle-test)