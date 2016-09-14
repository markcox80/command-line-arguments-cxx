cmake_minimum_required(VERSION 3.4.2)
cmake_policy(SET CMP0054 NEW)

add_subdirectory(command-line-arguments)
add_subdirectory(tests)

# Export the library
set(P_EXPORTS_PREFIX ${CMAKE_INSTALL_PREFIX}/share/command-line-arguments)
install(EXPORT command-line-arguments
        DESTINATION ${P_EXPORTS_PREFIX})

# Create the CMake Config file
configure_file(command-line-arguments-config.cmake.in command-line-arguments-config.cmake)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/command-line-arguments-config.cmake
        DESTINATION ${P_EXPORTS_PREFIX})
