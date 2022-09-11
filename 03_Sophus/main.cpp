#include <iostream>
using namespace std;


#include "sophus/sim3.hpp"
#include "sophus/se3.hpp"

typedef Sophus::SO3d::Point Point;
typedef Sophus::SO3d::Tangent Tangent;
using namespace Sophus;
using namespace Eigen;

void test1();

int main(int, char**) {
    test1();
}



void test1()
{
    // https://github.com/dalek7/Algorithms/blob/master/Sophus/SophusTest/SophusTest/SimpleTest.h
    //SO3 disturbance = SO3::exp(Sophus::Vector3d(0.05,0,0));
    Point omega1 = Point(0.05,0,0);
    SO3 disturbance1 = SO3::exp(omega1);

    cout << omega1.transpose() << endl;
    cout << endl; 
    cout << disturbance1.matrix() << endl;
    cout << endl; 
    cout << disturbance1.log().transpose() << endl;
    
    cout << "==============================" << endl;

    Tangent omega2 = Tangent(0.05,0,0);
    SO3 disturbance = SO3::exp(omega2);
    
    cout << omega2.transpose() << endl;
    cout << endl; 
    cout << disturbance.matrix() << endl;
    cout << endl; 
    cout << disturbance.log().transpose() << endl;
    cout << "==============================" << endl;

    omega2 =Point(0.02,0,0);
    SO3 disturbance2 = SO3::exp(omega2);
    SO3 disturbance12 = SO3::exp(omega1+omega2);
    SO3 disturbance1x2 = disturbance1 * disturbance2;

    cout << (omega1+omega2).transpose() << endl;;
    cout << "SO3::exp(omega1+omega2)" <<endl;
    cout << disturbance12.matrix() << endl;
    cout <<endl;
    cout << "SO3::exp(omega1) * SO3::exp(omega2)" <<endl;
    cout << disturbance1x2.matrix() << endl;
    cout <<endl;
    cout << disturbance12.log().transpose() << endl;
    cout << disturbance1x2.log().transpose() << endl;

}