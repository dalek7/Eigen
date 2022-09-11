cmake_minimum_required(VERSION 3.0.0)
project(EigenTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(EigenTest main.cpp)

#https://stackoverflow.com/a/9160449
if (UNIX)
    set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)
else(WIN32)
    set(EIGEN3_INCLUDE_DIR E:/FL/eigen3)
endif (UNIX)


include_directories(${EIGEN3_INCLUDE_DIR} 
                    ../common/include)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
