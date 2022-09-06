cmake_minimum_required(VERSION 3.0.0)
project(EigenTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(EigenTest main.cpp)
set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)
include_directories(${EIGEN3_INCLUDE_DIR} )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
