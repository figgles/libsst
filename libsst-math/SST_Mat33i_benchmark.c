#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>




int SST_Math_Mat33i_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat33i X; /* 3 x 3 matrix */
SST_Mat33i Y; /* 3 x 3 matrix */
SST_Mat33i A; /* 3 x 3 matrix */
SST_Mat33i B; /* 3 x 3 matrix */
SST_Vec3i v; /* 3 vector */
SST_Vec3i w; /* 3 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = -8;
    v.v[1] = 0;
    v.v[2] = -2;
    X.v[0] = -3;
    X.v[1] = -20;
    X.v[2] = 10;
    X.v[3] = -9;
    X.v[4] = 4;
    X.v[5] = 11;
    X.v[6] = 2;
    X.v[7] = 16;
    X.v[8] = -11;
    Y.v[0] = -7;
    Y.v[1] = -13;
    Y.v[2] = 15;
    Y.v[3] = -2;
    Y.v[4] = 0;
    Y.v[5] = -2;
    Y.v[6] = 2;
    Y.v[7] = 5;
    Y.v[8] = -16;
SST_Math_Mat33iAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat33iAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ -3  -9   2]
 [-20   4  16]
 [ 10  11 -11]]
[[ -7  -2   2]
 [-13   0   5]
 [ 15  -2 -16]]
[[-10 -11   4]
 [-33   4  21]
 [ 25   9 -27]]
*/
assert((A.v[0])==(-10));
assert((A.v[3])==(-11));
assert((A.v[6])==(4));
assert((A.v[1])==(-33));
assert((A.v[4])==(4));
assert((A.v[7])==(21));
assert((A.v[2])==(25));
assert((A.v[5])==(9));
assert((A.v[8])==(-27));
/*
[[ -3  -9   2]
 [-20   4  16]
 [ 10  11 -11]]
[[ -7  -2   2]
 [-13   0   5]
 [ 15  -2 -16]]
[[-10 -11   4]
 [-33   4  21]
 [ 25   9 -27]]
*/
fprintf(stdout,"SST_Math_Mat33iAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(-10));
assert((X.v[3])==(-11));
assert((X.v[6])==(4));
assert((X.v[1])==(-33));
assert((X.v[4])==(4));
assert((X.v[7])==(21));
assert((X.v[2])==(25));
assert((X.v[5])==(9));
assert((X.v[8])==(-27));
/* Resetting test vectors / mats */
    v.v[0] = -17;
    v.v[1] = 18;
    v.v[2] = -14;
    X.v[0] = -14;
    X.v[1] = 12;
    X.v[2] = -13;
    X.v[3] = -2;
    X.v[4] = -16;
    X.v[5] = -20;
    X.v[6] = 6;
    X.v[7] = 15;
    X.v[8] = 1;
    Y.v[0] = 14;
    Y.v[1] = 4;
    Y.v[2] = 17;
    Y.v[3] = -19;
    Y.v[4] = -13;
    Y.v[5] = -16;
    Y.v[6] = -20;
    Y.v[7] = 9;
    Y.v[8] = -16;
/*
[[-14  -2   6]
 [ 12 -16  15]
 [-13 -20   1]]
[[-28  -4  12]
 [ 24 -32  30]
 [-26 -40   2]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-28));
assert((A.v[3])==(-4));
assert((A.v[6])==(12));
assert((A.v[1])==(24));
assert((A.v[4])==(-32));
assert((A.v[7])==(30));
assert((A.v[2])==(-26));
assert((A.v[5])==(-40));
assert((A.v[8])==(2));
/*
[[-14  -2   6]
 [ 12 -16  15]
 [-13 -20   1]]
[[-28  -4  12]
 [ 24 -32  30]
 [-26 -40   2]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iMultiplyScalarLocal(&X,2);
assert((X.v[0])==(-28));
assert((X.v[3])==(-4));
assert((X.v[6])==(12));
assert((X.v[1])==(24));
assert((X.v[4])==(-32));
assert((X.v[7])==(30));
assert((X.v[2])==(-26));
assert((X.v[5])==(-40));
assert((X.v[8])==(2));
/* Resetting test vectors / mats */
    v.v[0] = -8;
    v.v[1] = 1;
    v.v[2] = 13;
    X.v[0] = -7;
    X.v[1] = 14;
    X.v[2] = 9;
    X.v[3] = 12;
    X.v[4] = -5;
    X.v[5] = -11;
    X.v[6] = -1;
    X.v[7] = -13;
    X.v[8] = 0;
    Y.v[0] = 12;
    Y.v[1] = -3;
    Y.v[2] = 15;
    Y.v[3] = 16;
    Y.v[4] = 7;
    Y.v[5] = -9;
    Y.v[6] = -11;
    Y.v[7] = 16;
    Y.v[8] = 7;
/*
[[ -7  12  -1]
 [ 14  -5 -13]
 [  9 -11   0]]
[[ 12  16 -11]
 [ -3   7  16]
 [ 15  -9   7]]
[[ -84  192   11]
 [ -42  -35 -208]
 [ 135   99    0]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-84));
assert((A.v[3])==(192));
assert((A.v[6])==(11));
assert((A.v[1])==(-42));
assert((A.v[4])==(-35));
assert((A.v[7])==(-208));
assert((A.v[2])==(135));
assert((A.v[5])==(99));
assert((A.v[8])==(0));
/*
[[ -7  12  -1]
 [ 14  -5 -13]
 [  9 -11   0]]
[[ 12  16 -11]
 [ -3   7  16]
 [ 15  -9   7]]
[[ -84  192   11]
 [ -42  -35 -208]
 [ 135   99    0]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(-84));
assert((X.v[3])==(192));
assert((X.v[6])==(11));
assert((X.v[1])==(-42));
assert((X.v[4])==(-35));
assert((X.v[7])==(-208));
assert((X.v[2])==(135));
assert((X.v[5])==(99));
assert((X.v[8])==(0));
/* Resetting test vectors / mats */
    v.v[0] = -5;
    v.v[1] = -6;
    v.v[2] = -12;
    X.v[0] = -14;
    X.v[1] = 15;
    X.v[2] = -10;
    X.v[3] = -14;
    X.v[4] = -20;
    X.v[5] = -9;
    X.v[6] = -11;
    X.v[7] = -1;
    X.v[8] = 18;
    Y.v[0] = -18;
    Y.v[1] = 19;
    Y.v[2] = 3;
    Y.v[3] = -8;
    Y.v[4] = 16;
    Y.v[5] = 12;
    Y.v[6] = 19;
    Y.v[7] = -10;
    Y.v[8] = -3;
/*
X
[[-14 -14 -11]
 [ 15 -20  -1]
 [-10  -9  18]]
Y
[[-18  -8  19]
 [ 19  16 -10]
 [  3  12  -3]]
[[ -47 -244  -93]
 [-653 -452  488]
 [  63  152 -154]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-47));
assert((A.v[3])==(-244));
assert((A.v[6])==(-93));
assert((A.v[1])==(-653));
assert((A.v[4])==(-452));
assert((A.v[7])==(488));
assert((A.v[2])==(63));
assert((A.v[5])==(152));
assert((A.v[8])==(-154));
/*
X
[[-14 -14 -11]
 [ 15 -20  -1]
 [-10  -9  18]]
Y
[[-18  -8  19]
 [ 19  16 -10]
 [  3  12  -3]]
X
[[ -47 -244  -93]
 [-653 -452  488]
 [  63  152 -154]]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(-47));
assert((X.v[3])==(-244));
assert((X.v[6])==(-93));
assert((X.v[1])==(-653));
assert((X.v[4])==(-452));
assert((X.v[7])==(488));
assert((X.v[2])==(63));
assert((X.v[5])==(152));
assert((X.v[8])==(-154));
/* Resetting test vectors / mats */
    v.v[0] = 9;
    v.v[1] = 13;
    v.v[2] = -11;
    X.v[0] = 2;
    X.v[1] = -4;
    X.v[2] = 13;
    X.v[3] = -1;
    X.v[4] = 13;
    X.v[5] = 1;
    X.v[6] = -7;
    X.v[7] = 3;
    X.v[8] = 11;
    Y.v[0] = -9;
    Y.v[1] = -8;
    Y.v[2] = 3;
    Y.v[3] = -1;
    Y.v[4] = -4;
    Y.v[5] = 9;
    Y.v[6] = 15;
    Y.v[7] = 9;
    Y.v[8] = -16;
/*
X
[[ 2 -1 -7]
 [-4 13  3]
 [13  1 11]]
v
[  9  13 -11]
w
[ 82 100   9]
*/
i=0;
fprintf(stdout,"SST_Math_Mat33iMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(82));
assert((w.v[1])==(100));
assert((w.v[2])==(9));
/*
X
[[ 2 -1 -7]
 [-4 13  3]
 [13  1 11]]
v
[  9  13 -11]
v
[ 82 100   9]
*/
fprintf(stdout,"SST_Math_Mat33iMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(82));
assert((v.v[1])==(100));
assert((v.v[2])==(9));
/* Resetting test vectors / mats */
    v.v[0] = 17;
    v.v[1] = 3;
    v.v[2] = 4;
    X.v[0] = -9;
    X.v[1] = 17;
    X.v[2] = 2;
    X.v[3] = -14;
    X.v[4] = -12;
    X.v[5] = 16;
    X.v[6] = -3;
    X.v[7] = -2;
    X.v[8] = -20;
    Y.v[0] = 5;
    Y.v[1] = 17;
    Y.v[2] = 7;
    Y.v[3] = -12;
    Y.v[4] = -16;
    Y.v[5] = 0;
    Y.v[6] = 13;
    Y.v[7] = 16;
    Y.v[8] = -17;
fprintf(stdout,"SST_Math_Mat33iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-9));
assert((A.v[3])==(17));
assert((A.v[6])==(2));
assert((A.v[1])==(-14));
assert((A.v[4])==(-12));
assert((A.v[7])==(16));
assert((A.v[2])==(-3));
assert((A.v[5])==(-2));
assert((A.v[8])==(-20));
fprintf(stdout,"SST_Math_Mat33iTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33iTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33iTransposeLocal(&X);
assert((X.v[0])==(-9));
assert((X.v[3])==(17));
assert((X.v[6])==(2));
assert((X.v[1])==(-14));
assert((X.v[4])==(-12));
assert((X.v[7])==(16));
assert((X.v[2])==(-3));
assert((X.v[5])==(-2));
assert((X.v[8])==(-20));
/*
[[-0.46537892 -0.62176306  0.62994695]
 [ 0.87904907 -0.40783255  0.2468711 ]
 [ 0.10341754  0.66864289  0.73635691]]
[[  1.00000000e+00   8.32667268e-17  -1.11022302e-16]
 [  8.32667268e-17   1.00000000e+00  -5.55111512e-17]
 [ -1.11022302e-16  -5.55111512e-17   1.00000000e+00]]
*/
X.v[0] = (int)0;
X.v[3] = (int)0;
X.v[6] = (int)0;
X.v[1] = (int)0;
X.v[4] = (int)0;
X.v[7] = (int)0;
X.v[2] = (int)0;
X.v[5] = (int)0;
X.v[8] = (int)0;
fprintf(stdout,"SST_Math_Mat33iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat33iMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat33iMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Positive Test */
assert(SST_Math_Mat33iCheckOrthonormal(&X));
/* Check Negative Test */
assert(!SST_Math_Mat33iCheckOrthonormal(&Y));
fprintf(stdout,"\n==== SST_Math_Mat33itest_fxn COMPLETE ====\n");
return 0;
}
