#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>




int SST_Math_Mat22i_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat22i X; /* 2 x 2 matrix */
SST_Mat22i Y; /* 2 x 2 matrix */
SST_Mat22i A; /* 2 x 2 matrix */
SST_Mat22i B; /* 2 x 2 matrix */
SST_Vec2i v; /* 2 vector */
SST_Vec2i w; /* 2 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = -13;
    v.v[1] = -2;
    X.v[0] = 18;
    X.v[1] = 5;
    X.v[2] = -10;
    X.v[3] = -16;
    Y.v[0] = -3;
    Y.v[1] = 16;
    Y.v[2] = 3;
    Y.v[3] = 7;
SST_Math_Mat22iAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat22iAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ 18 -10]
 [  5 -16]]
[[-3  3]
 [16  7]]
[[15 -7]
 [21 -9]]
*/
assert((A.v[0])==(15));
assert((A.v[2])==(-7));
assert((A.v[1])==(21));
assert((A.v[3])==(-9));
/*
[[ 18 -10]
 [  5 -16]]
[[-3  3]
 [16  7]]
[[15 -7]
 [21 -9]]
*/
fprintf(stdout,"SST_Math_Mat22iAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(15));
assert((X.v[2])==(-7));
assert((X.v[1])==(21));
assert((X.v[3])==(-9));
/* Resetting test vectors / mats */
    v.v[0] = 2;
    v.v[1] = 8;
    X.v[0] = 2;
    X.v[1] = 16;
    X.v[2] = -9;
    X.v[3] = 4;
    Y.v[0] = 17;
    Y.v[1] = -20;
    Y.v[2] = 15;
    Y.v[3] = 17;
/*
[[ 2 -9]
 [16  4]]
[[  4 -18]
 [ 32   8]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(4));
assert((A.v[2])==(-18));
assert((A.v[1])==(32));
assert((A.v[3])==(8));
/*
[[ 2 -9]
 [16  4]]
[[  4 -18]
 [ 32   8]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iMultiplyScalarLocal(&X,2);
assert((X.v[0])==(4));
assert((X.v[2])==(-18));
assert((X.v[1])==(32));
assert((X.v[3])==(8));
/* Resetting test vectors / mats */
    v.v[0] = -16;
    v.v[1] = -18;
    X.v[0] = -19;
    X.v[1] = -14;
    X.v[2] = -11;
    X.v[3] = 7;
    Y.v[0] = -18;
    Y.v[1] = 3;
    Y.v[2] = -14;
    Y.v[3] = -13;
/*
[[-19 -11]
 [-14   7]]
[[-18 -14]
 [  3 -13]]
[[342 154]
 [-42 -91]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(342));
assert((A.v[2])==(154));
assert((A.v[1])==(-42));
assert((A.v[3])==(-91));
/*
[[-19 -11]
 [-14   7]]
[[-18 -14]
 [  3 -13]]
[[342 154]
 [-42 -91]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(342));
assert((X.v[2])==(154));
assert((X.v[1])==(-42));
assert((X.v[3])==(-91));
/* Resetting test vectors / mats */
    v.v[0] = 11;
    v.v[1] = 8;
    X.v[0] = -4;
    X.v[1] = -2;
    X.v[2] = 2;
    X.v[3] = -11;
    Y.v[0] = 10;
    Y.v[1] = -2;
    Y.v[2] = -10;
    Y.v[3] = 7;
/*
X
[[ -4   2]
 [ -2 -11]]
Y
[[ 10 -10]
 [ -2   7]]
[[-44  54]
 [  2 -57]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-44));
assert((A.v[2])==(54));
assert((A.v[1])==(2));
assert((A.v[3])==(-57));
/*
X
[[ -4   2]
 [ -2 -11]]
Y
[[ 10 -10]
 [ -2   7]]
X
[[-44  54]
 [  2 -57]]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(-44));
assert((X.v[2])==(54));
assert((X.v[1])==(2));
assert((X.v[3])==(-57));
/* Resetting test vectors / mats */
    v.v[0] = 0;
    v.v[1] = -7;
    X.v[0] = 2;
    X.v[1] = 14;
    X.v[2] = 2;
    X.v[3] = -17;
    Y.v[0] = 15;
    Y.v[1] = -7;
    Y.v[2] = 4;
    Y.v[3] = 11;
/*
X
[[  2   2]
 [ 14 -17]]
v
[ 0 -7]
w
[-14 119]
*/
i=0;
fprintf(stdout,"SST_Math_Mat22iMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(-14));
assert((w.v[1])==(119));
/*
X
[[  2   2]
 [ 14 -17]]
v
[ 0 -7]
v
[-14 119]
*/
fprintf(stdout,"SST_Math_Mat22iMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(-14));
assert((v.v[1])==(119));
/* Resetting test vectors / mats */
    v.v[0] = 14;
    v.v[1] = -18;
    X.v[0] = 11;
    X.v[1] = -8;
    X.v[2] = -5;
    X.v[3] = 8;
    Y.v[0] = 4;
    Y.v[1] = 6;
    Y.v[2] = -6;
    Y.v[3] = -9;
fprintf(stdout,"SST_Math_Mat22iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(11));
assert((A.v[2])==(-8));
assert((A.v[1])==(-5));
assert((A.v[3])==(8));
fprintf(stdout,"SST_Math_Mat22iTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22iTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22iTransposeLocal(&X);
assert((X.v[0])==(11));
assert((X.v[2])==(-8));
assert((X.v[1])==(-5));
assert((X.v[3])==(8));
/*
[[-0.80873608  0.5881717 ]
 [ 0.5881717   0.80873608]]
[[ 1.  0.]
 [ 0.  1.]]
*/
X.v[0] = (int)0;
X.v[2] = (int)0;
X.v[1] = (int)0;
X.v[3] = (int)0;
fprintf(stdout,"SST_Math_Mat22iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat22iMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat22iMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Positive Test */
assert(SST_Math_Mat22iCheckOrthonormal(&X));
/* Check Negative Test */
assert(!SST_Math_Mat22iCheckOrthonormal(&Y));
fprintf(stdout,"\n==== SST_Math_Mat22itest_fxn COMPLETE ====\n");
return 0;
}
