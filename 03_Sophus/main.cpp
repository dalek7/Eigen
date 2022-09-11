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
    //SO3 disturbance = SO3::exp(Sophus::Vector3d(0.05,0,0));
    Point omega1 = Point(0.05,0,0);
    SO3 disturbance = SO3::exp(omega1);

    cout << omega1.transpose() << endl;
    cout << endl; 
    cout << disturbance.matrix() << endl;
    cout << endl; 
    cout << disturbance.log().transpose() << endl;
    
    cout << "==============================" << endl;

    Tangent omega2 = Tangent(0.05,0,0);
    disturbance = SO3::exp(omega2);
    
    cout << omega2.transpose() << endl;
    cout << endl; 
    cout << disturbance.matrix() << endl;
    cout << endl; 
    cout << disturbance.log().transpose() << endl;
    cout << "==============================" << endl;

}