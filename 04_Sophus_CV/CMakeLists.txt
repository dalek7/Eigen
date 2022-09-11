cmake_minimum_required(VERSION 3.0.0)
project(SophusCVTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(SophusCVTest main.cpp)
if (UNIX)
    set(EIGEN3_INCLUDE_DIR /usr/local/include/eigen3)
else(WIN32)
    set(EIGEN3_INCLUDE_DIR E:/FL/eigen3)
endif (UNIX)


find_package(OpenCV REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR} 
                    ${OpenCV_INCLUDE_DIR}
                    ../common/Thirdparty/Sophus
                    ../common/include)

set(EXT_LIBS opencv_core opencv_imgcodecs opencv_highgui opencv_imgproc opencv_calib3d opencv_features2d )

target_link_libraries(SophusCVTest PRIVATE ${EXT_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
