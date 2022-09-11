#include <iostream>
#include <opencv2/opencv.hpp>

#include "eigen_util.h"
#include "sophus/sim3.hpp"

using namespace cv;
using namespace Sophus;

const float eps = 1e-4;

cv::Mat ExpSO3(const float &x, const float &y, const float &z)
{
    cv::Mat I = cv::Mat::eye(3,3,CV_32F);
    const float d2 = x*x+y*y+z*z;
    const float d = sqrt(d2);
    cv::Mat W = (cv::Mat_<float>(3,3) << 0, -z, y,
                 z, 0, -x,
                 -y,  x, 0);
    if(d<eps)
        return (I + W + 0.5f*W*W);
    else
        return (I + W*sin(d)/d + W*W*(1.0f-cos(d))/d2);
}

cv::Mat ExpSO3(const cv::Mat &v)
{
    return ExpSO3(v.at<float>(0),v.at<float>(1),v.at<float>(2));
}


//typedef Sophus::SO3d::Point Point;

int main(int, char**) {
    
    float deg =  M_PI/2;
    Mat m= ExpSO3(0, 0, deg);
    cout << m <<endl;
    cout <<endl;

    Sophus::SO3d::Point point1 = Sophus::SO3d::Point(0, 0, deg);
    SO3 rot = SO3::exp(point1);
    cout << rot.matrix() <<endl;   

    deg = 0.1;
    m= ExpSO3(0, 0, deg);
    cout << m <<endl;
    cout <<endl;

    point1 = Sophus::SO3d::Point(0, 0, deg);
    rot = SO3::exp(point1);
    cout << rot.matrix() <<endl;   

    return 0;
}
