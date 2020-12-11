cmake_minimum_required(VERSION 3.0.0)
project(scalarflow VERSION 0.1.0)

# include(CTest)
# enable_testing()

# Compiler Flags
add_compile_options("-std=c++1y;-stdlib=libc++;-O0;-pedantic;-Wall;-Werror;-Wfatal-errors;-Wextra;-Wno-unused-parameter;-Wno-unused-variable;-Wno-unused-function;-MP;-g;-c")

# Linker Flags
add_link_options("-std=c++1y;-stdlib=libc++;-lc++abi")

# Import Catch2 framework
# add_subdirectory(lib/Catch2)
# list(APPEND CMAKE_MODULE_PATH lib/Catch2/contrib)
# include(Catch)

# Build and Install ScalarFlow Library
add_library(scalarflow src/scalarflow/graph.cpp src/scalarflow/sfg.cpp)
target_include_directories(scalarflow INTERFACE src)

# Static Binaries
add_executable(main src/main.cpp src/lexer.cpp)
target_link_libraries(main scalarflow)


# Tests
add_executable(test tests/test.cpp tests/test_graph.cpp tests/test_edge.cpp)
target_link_libraries(test scalarflow)

# target_link_libraries(catch Catch2::Catch2)
# catch_discover_tests(catch)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)