#ifndef __Eigen_Utils__
#define __Eigen_Utils__

// based on the ofQuaternion 

#ifndef PI
	#define PI       3.14159265358979323846
#endif

#ifndef DEG_TO_RAD
	#define DEG_TO_RAD (PI/180.0)
#endif

static inline 
float DegToRad(float degrees) {
    return degrees * DEG_TO_RAD;
}


#include <Eigen/Geometry>
using namespace Eigen;

/// \brief Make a rotation Quat which will rotate vec1 to vec2.
/// Generally take a dot product to get the angle between these
/// and then use a cross product to get the rotation axis
/// Watch out for the two special cases when the vectors
/// are co-incident or opposite in direction.
//Eigen::Quaternionf makeRotate(const Vector3f& vec1, const Vector3f& vec2);

/** Make a rotation Quat which will rotate vec1 to vec2

 This routine uses only fast geometric transforms, without costly acos/sin computations.
 It's exact, fast, and with less degenerate cases than the acos/sin method.

 For an explanation of the math used, you may see for example:
 http://logiciels.cnes.fr/MARMOTTES/marmottes-mathematique.pdf

 @note This is the rotation with shortest angle, which is the one equivalent to the
 acos/sin transform method. Other rotations exists, for example to additionally keep
 a local horizontal attitude.

 @author Nicolas Brodu
 */

static inline 
Eigen::Quaternionf  makeRotate( const Vector3f& from, const Vector3f& to ) {

	// This routine takes any vector as argument but normalized
	// vectors are necessary, if only for computing the dot product.
	// Too bad the API is that generic, it leads to performance loss.
	// Even in the case the 2 vectors are not normalized but same length,
	// the sqrt could be shared, but we have no way to know beforehand
	// at this point, while the caller may know.
	// So, we have to test... in the hope of saving at least a sqrt
	Vector3f sourceVector = from;
	Vector3f targetVector = to;

	float fromLen2 = from.norm()*  from.norm();
	float fromLen;
	// normalize only when necessary, epsilon test
	if ((fromLen2 < 1.0 - 1e-7) || (fromLen2 > 1.0 + 1e-7)) {
		fromLen = sqrt(fromLen2);
		sourceVector /= fromLen;
	} else fromLen = 1.0;

	float toLen2 = to.norm()*  to.norm();
	// normalize only when necessary, epsilon test
	if ((toLen2 < 1.0 - 1e-7) || (toLen2 > 1.0 + 1e-7)) {
		float toLen;
		// re-use fromLen for case of mapping 2 vectors of the same length
		if ((toLen2 > fromLen2 - 1e-7) && (toLen2 < fromLen2 + 1e-7)) {
			toLen = fromLen;
		} else toLen = sqrt(toLen2);
		targetVector /= toLen;
	}


	// Now let's get into the real stuff
	// Use "dot product plus one" as test as it can be re-used later on
	double dotProdPlus1 = 1.0 + sourceVector.dot(targetVector);
    float _vx, _vy, _vz, _vw;
	// Check for degenerate case of full u-turn. Use epsilon for detection
	if (dotProdPlus1 < 1e-7) {

		// Get an orthogonal vector of the given vector
		// in a plane with maximum vector coordinates.
		// Then use it as quaternion axis with pi angle
		// Trick is to realize one value at least is >0.6 for a normalized vector.

        
		if (fabs(sourceVector.x()) < 0.6) {
			const double norm = sqrt(1.0 - sourceVector.x() * sourceVector.x());
			_vx = 0.0;
			_vy = sourceVector.z() / norm;
			_vz = -sourceVector.y() / norm;
			_vw = 0.0;
		} else if (fabs(sourceVector.y()) < 0.6) {
			const double norm = sqrt(1.0 - sourceVector.y() * sourceVector.y());
			_vx = -sourceVector.z() / norm;
			_vy = 0.0;
			_vz = sourceVector.x() / norm;
			_vw = 0.0;
		} else {
			const double norm = sqrt(1.0 - sourceVector.z() * sourceVector.z());
			_vx = sourceVector.y() / norm;
			_vy = -sourceVector.x() / norm;
			_vz = 0.0;
			_vw = 0.0;
		}

	}

	else {
		// Find the shortest angle quaternion that transforms normalized vectors
		// into one other. Formula is still valid when vectors are colinear
		const double s = sqrt(0.5 * dotProdPlus1);
		const Vector3f tmp = sourceVector.cross(targetVector) / (2.0 * s);
		_vx = tmp.x();
		_vy = tmp.y();
		_vz = tmp.z();
		_vw = s;
	}

    Eigen::Quaternionf q;
    q.x() = _vx;
    q.y() = _vy;
    q.z() = _vz;
    q.w() = _vw;
    

    //Vector4f ret = Vector4f(_vw, _vx, _vy, _vz);
    return q;

}


/// \briefSet a quaternion which will perform a rotation of an
/// angle around the axis given by the vector(x,y,z).
///
/// Define Spherical Linear interpolation method also
//Vector4f makeRotate(float angle, float x, float y, float z);


/// Set the elements of the Quat to represent a rotation of angle
/// (degrees) around the axis (x,y,z)

/*
TODO: check this function 
Vector4f q1 = makeRotate(0.1, 1, 0, 0);
cout << q1 <<endl;
*/
static inline 
Eigen::Vector4f makeRotate( float angle, float x, float y, float z ) {
	angle = DegToRad(angle);
	
	const float epsilon = 0.0000001f;

	float length = sqrtf( x * x + y * y + z * z );
	if (length < epsilon) {
		// ~zero length axis, so reset rotation to zero.
		//*this = ofQuaternion();
		return Vector4f(0,0,0,1); //  _v.set(0, 0, 0, 1);
	}

	float inversenorm  = 1.0f / length;
	float coshalfangle = cosf( 0.5f * angle );
	float sinhalfangle = sinf( 0.5f * angle );


	float x_ = x * sinhalfangle * inversenorm;
	float y_ = y * sinhalfangle * inversenorm;
	float z_ = z * sinhalfangle * inversenorm;
	float w_ = coshalfangle;
    
    Vector4f v;

    v << x_, y_, z_, w_;

    return v;
}




#endif
