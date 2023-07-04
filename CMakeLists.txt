cmake_minimum_required(VERSION 3.0.0)
project(linux_jit VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
aux_source_directory(src source)

include(CTest)
enable_testing()

add_executable(linux_jit main.cpp ${source})
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
