cmake_minimum_required(VERSION 3.11)


# see https://docs.hunter.sh/en/latest/quick-start/boost-components.html

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.16.tar.gz"
    SHA1 "dbe5b1c966414c4a055983c11d5251a2d8f2f16d"
)

project(gurgle VERSION 0.0.1)


hunter_add_package(glfw)
find_package(glfw3 CONFIG REQUIRED)

hunter_add_package(glew)
find_package(glew CONFIG REQUIRED)

hunter_add_package(stb)
find_package(stb CONFIG REQUIRED)

hunter_add_package(glm)
find_package(glm REQUIRED)


add_subdirectory(gurgle-lib)
add_subdirectory(gurgle-test)
add_subdirectory(gurgle-game)

enable_testing()
add_test(NAME testgurgle COMMAND gurgle-test)