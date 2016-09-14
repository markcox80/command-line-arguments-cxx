add_executable(command-line-arguments-tests tests.cpp)
target_include_directories(command-line-arguments-tests
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/catch)
target_link_libraries(command-line-arguments-tests command-line-arguments)

add_custom_target(tests
                  COMMAND command-line-arguments-tests
                  DEPENDS command-line-arguments-tests
                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
