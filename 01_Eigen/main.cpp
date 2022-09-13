#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Dense> // for eig solver
#include <Eigen/Geometry>


#include "eigen_util.h"

using namespace Eigen;
using namespace std;
void quattest();
void helloeig();
void makeRotateTest();
void makeRotateTest2();
void helloQuat();

int main(int, char**) {

    //helloeig(); 
    //makeRotateTest();
    //helloQuat();
    makeRotateTest2();
   

    return 0;
}

void makeRotateTest2()
{
    Vector3f v1, v2;
    v1 << 0, 1, 0;
    //v2 << -0.106925,0.76072,0.640212;
    //v2 << -0.107438,  0.768901,  0.630277;
    v2 << -0.105058,  0.745211,  0.658501;
    
    v1.normalize();
    v2.normalize();

    cout << v1.transpose() <<endl;
    cout << "--->" <<endl;
    cout << v2.transpose() <<endl;

    Eigen::Quaternionf q2 = makeRotate(v1, v2);
    cout << "quat=" <<endl << q2 << endl<< endl;
    cout << q2.matrix() << endl<< endl;

    Eigen::Matrix3f q2m = q2.matrix(); // column-wise
    //cout << q2m(0) << ", " <<q2m(1)<< ", " <<q2m(2) << ", " <<q2m(3)<< endl; 
    cout << q2m(0) << ", " <<q2m(3)<< ", " <<q2m(6) << endl; 
    cout << q2m(1) << ", " <<q2m(4)<< ", " <<q2m(7) << endl; 
    cout << q2m(2) << ", " <<q2m(5)<< ", " <<q2m(8) << endl; 



}


void helloQuat()
{
    // https://www.cc.gatech.edu/classes/AY2015/cs4496_spring/Eigen.html
    Eigen::Quaterniond q(2, 0, 1, -3); 
    cout <<"Eigen::Quaterniond q(2, 0, 1, -3) " <<endl;
    cout << "q(w, x, y, z)" << endl;
    cout << "This quaternion consists of a scalar " << q.w() << " and a vector " << endl << q.vec() << endl;

    q.normalize();
    cout << "To represent rotation, we need to normalize it such that its length is " << q.norm() << endl;
    cout << "q = [w x y z]"<<endl;
    cout << q.w() << ", " << q.x() << ", "<< q.y() << ", " << q.z() <<endl;
    cout << q <<endl; //operator test
}

#include <Eigen/Geometry>
void makeRotateTest()
{
    Vector3f v1, v2;
    v1 <<-0.03, -0.3, 0.5;
    v2 <<0, 0, 1;
    
    v1 << -0.106925,0.76072,0.640212;
    v2 << 0, 1, 0;

    v1.normalize();
    v2.normalize();
    //cout<<  v1.x() <<endl;
    cout << v1.transpose() <<endl;
    cout << v2.transpose() <<endl;

    Eigen::Quaternionf q2 = makeRotate(v1, v2);
    //cout << printQuat(q2) <<endl;
    cout << "q = [ w x y z]"<<endl;
    cout << q2.w() << ", " << q2.x() << ", "<< q2.y() << ", " << q2.z() <<endl;
    cout <<endl;
    cout << q2.toRotationMatrix() <<endl;
    cout << endl;
    Vector3f v1_transformed = q2*v1;
    cout <<"transformed : \n" << v1_transformed <<endl;
}

// based on https://github.com/gaoxiang12/slambook2/blob/master/ch3/useEigen/eigenMatrix.cpp
void helloeig()
{
    Matrix3f m;
    m = Matrix3f::Identity();
    cout << m;
    cout << "\n\n";

    m << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    cout << m;
    cout << "\n\n";

    // typedef Matrix< double , Dynamic , Dynamic > Eigen::MatrixXd
    MatrixXd m2(2,2);
    m2(0,0) = 3;
    m2(1,0) = 2.5;
    m2(0,1) = -1;
    m2(1,1) = m2(1,0) + m2(0,1);
    std::cout << m2 ;
    cout << "\n\n";


    Matrix<float, 2, 3> matrix_23;
    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << "matrix 2x3 from 1 to 6: \n" << matrix_23 << endl<< endl;

    cout << "print matrix 2x3: " << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) cout << matrix_23(i, j) << "\t";
        cout << endl;
    }
    
    cout << endl;
    Vector3d v_3d;
    Matrix<float, 3, 1> vd_3d;

    Matrix3d matrix_33 = Matrix3d::Zero();
    cout<< matrix_33<< endl;

    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    MatrixXd matrix_x;


    //// Multiply matrix and vector (actually still matrix and matrix)
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;

    // but in Eigen you can't mix two different types of matrices, something like this is wrong
    // Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    // should be converted explicitly
    Matrix< double , 2 , 1 > result = matrix_23.cast< double >() * v_3d ;
    cout << " [1,2,3;4,5,6]*[3,2,1]= " << result.transpose() << endl;
    
    Matrix< float , 2 , 1 > result2 = matrix_23 * vd_3d;
    cout << " [1,2,3;4,5,6]*[4,5,6]= " << result2.transpose( ) << endl << endl;

    // some matrix operations
    // The four arithmetic operations will not be demonstrated, just use +-*/ directly.
    matrix_33 = Matrix3d::Random();       // Random number matrix
    cout << " random matrix: \n " << matrix_33 << endl;
    cout << " transpose: \n " << matrix_33.transpose () << endl;       // transpose
    cout << " sum: " << matrix_33.sum() << endl;             // The sum of each element
    cout << " trace: " << matrix_33.trace() << endl;           // trace
    cout << " times 10: \n " << 10 * matrix_33 << endl;                // multiplication
    cout << " inverse: \n " << matrix_33.inverse() << endl;         // inverse
    cout << " det: " << matrix_33.determinant() << endl;     // determinant
    cout << endl;

    // feature value
    // Real symmetric matrix can guarantee successful diagonalization
    cout << "Eigen analysis of Real symmetric matrix" << endl;
    Matrix3d ata = matrix_33. transpose () * matrix_33;
    cout <<ata <<endl;
    SelfAdjointEigenSolver<Matrix3d> eigen_solver (ata);
    cout << " Eigen values ​​= \n " << eigen_solver.eigenvalues() << endl;
    cout << " Eigen vectors = \n " << eigen_solver.eigenvectors() << endl <<endl;
    //cout <<eigen_solver.eigenvectors() << endl;
    cout <<eigen_solver.eigenvectors().col(0) << endl << "================" << endl;
    cout <<eigen_solver.eigenvectors().col(1) << endl;

}


// https://github.com/gaoxiang12/slambook2/blob/master/ch3/examples/coordinateTransform.cpp
void quattest()
{
    Quaterniond q1(0.35, 0.2, 0.3, 0.1), q2(-0.5, 0.4, -0.1, 0.2);

    q1.normalize();
    q2.normalize();
    Vector3d t1(0.3, 0.1, 0.1), t2(-0.1, 0.5, 0.3);
    Vector3d p1(0.5, 0, 0.2);

    Isometry3d T1w(q1), T2w(q2);
    T1w.pretranslate(t1);
    T2w.pretranslate(t2);

    Vector3d p2 = T2w * T1w.inverse() * p1;
    cout << endl << p2.transpose() << endl;
}