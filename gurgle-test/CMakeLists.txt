
add_executable(
    gurgle-test
    test-main.cpp
)

target_link_libraries(gurgle-test gurgle-lib)

set_target_properties(gurgle-test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")