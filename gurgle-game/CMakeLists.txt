
add_executable(
    gurgle-game
    game-main.cpp
)

target_link_libraries(gurgle-game gurgle-lib)

set_target_properties(gurgle-game PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

