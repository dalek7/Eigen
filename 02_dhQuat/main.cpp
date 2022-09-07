#include <iostream>

#include "3d/dhVector.h"
#include "3d/dhQuat.h"
using namespace std;

// TODO : use another v2
// https://github.com/dalek7/Project-GL-TouchObj-TC/tree/main/data
// TODO: use Eigen
int main(int, char**) {
    dhVector v1(0,0,1);
    dhVector v2(0,1,1);
    v2 = v2.Unit();
    
    dhQuat q1;
    q1.makeRotate(v1, v2);

    cout << v1.x << ", " << v1.y << ", " <<  v1.z << endl;
    cout << v2.x << ", " << v2.y << ", " <<  v2.z << endl;

    dhVector4 qv = q1.asVec4();
    cout << qv.x << ", " << qv.y << ", " <<  qv.z <<", " <<qv.w<< endl;
    q1.normalize();

    qv = q1.asVec4();
    cout << qv.x << ", " << qv.y << ", " <<  qv.z <<", " <<qv.w<< endl;
    cout << q1 <<endl;
    cout << endl;

    dhMat H = q1.asMatrix();
    cout << H << endl<<endl;

    cout << "Another example" << endl;
    v1 = dhVector(-0.03, -0.3, 0.5);
    v2 = dhVector(0, 0, 1);

    v1 = v1.Unit();
    
    q1.makeRotate(v1, v2);
    cout << q1 <<endl;
    cout << q1.asMatrix() << endl;
    H = q1.asMatrix();
    
    dhVector4 v1h = dhVector4(v1.x, v1.y, v1.z, 1);
    cout <<"Initial : "<<  v1 << endl;
    cout <<"Target : "<<  v2 << endl;
    cout <<"Transform H : \n"<<  H << endl;
    //dhVector4 v1h_tr = H * v1h; // needs to be done
    dhVector v1h_tr = H * v1;
    cout <<"transformed : " << v1h_tr <<endl;

}
