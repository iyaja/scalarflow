cmake_minimum_required(VERSION 3.0.0)
project(ScalarFlow VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(./src ./include ./lib ./tests)

# add_library(ScalarFlow ScalarFlow.cpp)
# add_library(scalarflow )

add_executable(main ./src/main.cpp)
# add_executable(catch ./tests/test_graph.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
