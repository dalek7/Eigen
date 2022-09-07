cmake_minimum_required(VERSION 3.0.0)
project(Hello VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories( ./3d )
add_executable(Hello    main.cpp 
                        3d/dhVector.cpp
                        3d/dhVector4.cpp
                        3d/dhMat.cpp
                        
                        3d/dhQuat.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
