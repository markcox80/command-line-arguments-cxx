add_library(command-line-arguments command-line-arguments.cpp)
target_include_directories(command-line-arguments PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
set_target_properties(command-line-arguments PROPERTIES INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib)

install(TARGETS command-line-arguments
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES command-line-arguments.hpp
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/command-line-arguments)
