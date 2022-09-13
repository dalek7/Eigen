#include <iostream>
using namespace std;


#include "sophus/sim3.hpp"
#include "sophus/se3.hpp"
#include "eigen_util.h"

typedef Sophus::SO3d::Point Point;
typedef Sophus::SO3d::Tangent Tangent;
using namespace Sophus;
using namespace Eigen;

void test1();
void test2();

int main(int, char**) {
    test1();
}


void test2() 
{
    // SLAMBOOK2 Ch3. Lie Group and Lie Algebra
    // The first half introduces the operation on SO(3), and the second half is SE(3). 
    // We demonstrate how to construct SO(3), SE(3) objects as well as the exponential/logarithm mapping. 
    // And then, we update the lie group elements when we know the updated amount.

    //// Rotation matrix with 90 degrees along Z axis
    Matrix3d R = AngleAxisd(M_PI / 2, Vector3d(0, 0, 1)).toRotationMatrix();
    cout <<"R=" <<endl << R <<endl;

    //// or quaternion
    Quaterniond q(R);
    cout << "Quaternion from R" <<endl;
    cout << q << endl;

    Sophus::SO3d SO3_R(R);          // Sophus::SO3d can be constructed from rotation matrix
    Sophus::SO3d SO3_q(q);          // or quaternion

    // they are equivalent of course
    cout << "SO(3) from matrix:\n" << SO3_R.matrix() << endl;
    cout << "SO(3) from quaternion:\n" << SO3_q.matrix() << endl;
    cout << "they are equal" << endl;


    // Use logarithmic map to get the Lie algebra
    Vector3d so3 = SO3_R.log();
    cout << "so3 = " << so3.transpose() << endl;
    // hat is from vector to skew−symmetric matrix
    cout << "so3 hat=\n" << Sophus::SO3d::hat(so3) << endl;
    // inversely from matrix to vector
    cout << "so3 hat vee= " << Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose() << endl<< endl;


    // update by perturbation model
    Vector3d update_so3(1e-4, 0, 0); //// this is a small update
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R;
    cout << SO3_R.matrix() <<endl;
    cout << "-->" <<endl;
    cout << "SO3 updated = \n" << SO3_updated.matrix() << endl;
    cout << "*******************************" << endl;


    // Similar for SE(3)

    Vector3d t(1, 0, 0);          // translation 1 along X
    Sophus::SE3d SE3_Rt(R, t);           // construction SE3 from R,t
    Sophus::SE3d SE3_qt(q, t);           // or q, t
    cout << "SE3 from R,t= \n" << SE3_Rt.matrix() << endl;
    cout << "SE3 from q,t= \n" << SE3_qt.matrix() << endl;

    // Lie Algebra is 6d vector, we give a typedef
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = " << se3.transpose() << endl;
    // The output shows Sophus puts the translation at first in se(3), then rotation.

    cout << "se3 hat = \n" << Sophus::SE3d::hat(se3) << endl;
    cout << "se3 hat vee = " << Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose() << endl;

    //// Finally the update
    Vector6d update_se3;
    update_se3.setZero();
    update_se3(0, 0) = 1e-4;
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    cout << "SE3 updated = " << endl << SE3_updated.matrix() << endl;

    SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_updated;
    cout << "SE3 updated = " << endl << SE3_updated.matrix() << endl;

    SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_updated;
    cout << "SE3 updated = " << endl << SE3_updated.matrix() << endl;

}

void test1()
{
    // https://github.com/dalek7/Algorithms/blob/master/Sophus/SophusTest/SophusTest/SimpleTest.h
    //SO3 disturbance = SO3::exp(Sophus::Vector3d(0.05,0,0));
    Point omega0 = Point(0.0,0.0,0.0);
    SO3 disturbance0 = SO3::exp(omega0);
    cout <<"Point omega0 = Point(0.0,0.0,0.0)" << endl;
    cout << disturbance0.matrix() << endl;
    cout << endl; 

    omega0 = Point(0.0, M_PI * 1.0, 0.0);
    disturbance0 = SO3::exp(omega0);
    cout <<"Point omega0 = Point(0.0, M_PI * 1.0, 0.0)" << endl;
    cout << disturbance0.matrix() << endl;
    cout << endl; 

    Matrix3d R = AngleAxisd(M_PI , Vector3d(0, 1, 0)).toRotationMatrix(); //Y축을 기준으로 180도 (=pi) 만큼 회전
    cout <<"R= AngleAxisd(M_PI , Vector3d(0, 1, 0)) = " <<endl << R <<endl;
    cout <<" These two are equivalent. "<<endl;

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