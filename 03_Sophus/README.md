

```bash
0.05 0 0

         1          0          0
         0    0.99875 -0.0499792
         0  0.0499792    0.99875

0.05 0 0
==============================  
0.05 0 0

         1          0          0
         0    0.99875 -0.0499792
         0  0.0499792    0.99875

0.05 0 0
==============================
0.07 0 0
SO3::exp(omega1+omega2)
         1          0          0
         0   0.997551 -0.0699428
         0  0.0699428   0.997551

SO3::exp(omega1) * SO3::exp(omega2)
         1          0          0
         0   0.997551 -0.0699428
         0  0.0699428   0.997551

0.07 0 0
0.07 0 0
```


```
R=
6.12323e-17          -1           0
          1 6.12323e-17           0
          0           0           1
Quaternion from R
0.707107, 0, 0, 0.707107
SO(3) from matrix:
2.22045e-16          -1           0
          1 2.22045e-16           0
          0           0           1
SO(3) from quaternion:
2.22045e-16          -1           0
          1 2.22045e-16           0
          0           0           1
they are equal

so3 =      0      0 1.5708
so3 hat=
      0 -1.5708       0
 1.5708       0      -0
     -0       0       0
so3 hat vee=      0      0 1.5708

2.22045e-16          -1           0
          1 2.22045e-16           0
          0           0           1
-->
SO3 updated =
          0          -1           0
          1           0     -0.0001
     0.0001 2.03288e-20           1
*******************************
SE3 from R,t=
2.22045e-16          -1           0           1
          1 2.22045e-16           0           0
          0           0           1           0
          0           0           0           1
SE3 from q,t=
2.22045e-16          -1           0           1
          1 2.22045e-16           0           0
          0           0           1           0
          0           0           0           1
se3 =  0.785398 -0.785398         0         0         0    1.5708
se3 hat =
        0   -1.5708         0  0.785398
   1.5708         0        -0 -0.785398
       -0         0         0         0
        0         0         0         0
se3 hat vee =  0.785398 -0.785398         0         0         0    1.5708
SE3 updated =
2.22045e-16          -1           0      1.0001
          1 2.22045e-16           0           0
          0           0           1           0
          0           0           0           1
SE3 updated =
2.22045e-16          -1           0      1.0002
          1 2.22045e-16           0           0
          0           0           1           0
          0           0           0           1
SE3 updated =
2.22045e-16          -1           0      1.0003
          1 2.22045e-16           0           0
          0           0           1           0
          0           0           0           1
```