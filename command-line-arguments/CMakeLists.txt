add_library(command-line-arguments command-line-arguments.cpp)
target_include_directories(command-line-arguments PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
                                                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
set_target_properties(command-line-arguments PROPERTIES INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/lib)

install(TARGETS command-line-arguments
        EXPORT command-line-arguments
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES command-line-arguments.hpp
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/command-line-arguments)
