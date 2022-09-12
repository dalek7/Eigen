clc; clear;
a = [-0.03, -0.3, 0.5];
a = a / norm(a)
b = [0, 0, 1]

% r = vrrotvec(a,b) calculates a rotation needed to transform the 3D vector a to the 3D vector b.
r = vrrotvec(a,b) % r — Axis angle rotation vector : row vector

% Convert rotation from axis-angle to matrix representation
m = vrrotvec2mat(r)

a_transformed = m * a'


%%
disp('----------')
a = [0, 1, 0];
a = a / norm(a)
b = [-0.110224,  0.739443,  0.664134];
b = b / norm(b)

% r = vrrotvec(a,b) calculates a rotation needed to transform the 3D vector a to the 3D vector b.
r = vrrotvec(a,b) % r — Axis angle rotation vector : row vector

% Convert rotation from axis-angle to matrix representation
m = vrrotvec2mat(r)

a_transformed = m * a'


%%

n=  [ -0.11932,0.774991,0.620606];
norm(n)
%n = n / norm(n)
up= [ 0,1,0]
v=  [ 0.620606,-0,0.11932] ;

%v = v/ norm(v)
sa = norm(v)
ca = dot(up, n)

% from vs
%sa=     0.631973        ca=     0.774991        ang = atan2(sa, ca)=    0.684096

r = vrrotvec(up,v)
% Convert rotation from axis-angle to matrix representation
m = vrrotvec2mat(r)

m_from_vs = [0.49151379, -0.13827512, -0.85982215;
 -0.50310147, 0.76080984, -0.40994802;
 0.71084678, 0.6340729, 0.30438215];

%[0.49151379, -0.13827512, -0.85982215, 0.1360108;
% -0.50310147, 0.76080984, -0.40994802, -0.028067304;
% 0.71084678, 0.6340729, 0.30438215, 1.0718673;

x = [1, 0, 0];
cross(up, x )
cross(up, up)
