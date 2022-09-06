#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Dense> // for eig solver
#include <Eigen/Geometry>
using namespace Eigen;
using namespace std;
void quattest();
void helloeig();


int main(int, char**) {

    helloeig(); 

    return 0;
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