add_executable(command-line-arguments-tests tests.cpp)
target_link_libraries(command-line-arguments-tests command-line-arguments catch)

add_custom_target(tests
                  COMMAND command-line-arguments-tests
                  DEPENDS command-line-arguments-tests
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
