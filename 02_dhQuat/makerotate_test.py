
# https://github.com/dalek7/umbrella/blob/6901d2774349f46aec566f200d8844c76c40ccc9/MFC/OFMathTest/lib/ofQuaternion.cpp#L68-L142
# https://github.com/jinyunp/rotation_with_quaternion
def makeRotation(v1, v2):
    from scipy.spatial.transform import Rotation as R
    import numpy as np
    import math

    v1 = v1 / np.linalg.norm(v1)
    v2 = v2 / np.linalg.norm(v2)

    dot_product = 1.0 + np.dot(v1, v2)

    s = math.sqrt(0.5 * dot_product)
    tmp = np.cross(v1, v2) / (2.0 * s)

    # q = np.quaternion()
    # q.x = tmp[0]
    # q.y = tmp[1]
    # q.z = tmp[2]
    # q.w = s

    r = R.from_quat([tmp[0], tmp[1], tmp[2], s])
    # r = R.from_quat([q.x, q.y, q.z, q.w])

    return r.as_matrix()


# v1 as an arbitrary axis which is rotated to unit vector of z-axis
v1 = [-0.03, -0.3, 0.5]
v2 = [0, 0, 1]

R = makeRotation(v1, v2)
print(R)
print()
import numpy as np

v1_norm = v1 / np.linalg.norm(v1)
v1_transformed = R.dot(np.transpose(v1_norm))
print(v1_transformed)
'''
[[ 0.99857782 -0.01422176  0.05138162]
 [-0.01422176  0.85778243  0.51381615]
 [-0.05138162 -0.51381615  0.85636026]]
'''