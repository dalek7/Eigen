clc; clear;
a = [-0.03, -0.3, 0.5];
b = [0, 0, 1];

% r = vrrotvec(a,b) calculates a rotation needed to transform the 3D vector a to the 3D vector b.
r = vrrotvec(a,b) % r — Axis angle rotation vector : row vector

% Convert rotation from axis-angle to matrix representation
m = vrrotvec2mat(r)