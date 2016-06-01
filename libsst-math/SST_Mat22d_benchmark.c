#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>




int SST_Math_Mat22d_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat22d X; /* 2 x 2 matrix */
SST_Mat22d Y; /* 2 x 2 matrix */
SST_Mat22d A; /* 2 x 2 matrix */
SST_Mat22d B; /* 2 x 2 matrix */
SST_Vec2d v; /* 2 vector */
SST_Vec2d w; /* 2 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] =      -10.000000000000000;
    v.v[1] =      -20.000000000000000;
    X.v[0] =       13.000000000000000;
    X.v[1] =      -18.000000000000000;
    X.v[2] =       -9.000000000000000;
    X.v[3] =       -2.000000000000000;
    Y.v[0] =       -9.000000000000000;
    Y.v[1] =        1.000000000000000;
    Y.v[2] =        1.000000000000000;
    Y.v[3] =        4.000000000000000;
SST_Math_Mat22dAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat22dAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ 13.  -9.]
 [-18.  -2.]]
[[-9.  1.]
 [ 1.  4.]]
[[  4.  -8.]
 [-17.   2.]]
*/
assert(fabs((A.v[0])-(       4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(       2.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[ 13.  -9.]
 [-18.  -2.]]
[[-9.  1.]
 [ 1.  4.]]
[[  4.  -8.]
 [-17.   2.]]
*/
fprintf(stdout,"SST_Math_Mat22dAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dAddLocal(&X,&Y); /* for accuracy */
assert(fabs((X.v[0])-(       4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(       2.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =      -11.000000000000000;
    v.v[1] =       -4.000000000000000;
    X.v[0] =      -13.000000000000000;
    X.v[1] =        5.000000000000000;
    X.v[2] =        6.000000000000000;
    X.v[3] =       10.000000000000000;
    Y.v[0] =      -18.000000000000000;
    Y.v[1] =        9.000000000000000;
    Y.v[2] =       -1.000000000000000;
    Y.v[3] =       17.000000000000000;
/*
[[-13.   6.]
 [  5.  10.]]
[[-26.  12.]
 [ 10.  20.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyScalar(&X,       2.000000000000000,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(      12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      10.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-13.   6.]
 [  5.  10.]]
[[-26.  12.]
 [ 10.  20.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyScalarLocal(&A,       2.000000000000000);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dMultiplyScalarLocal(&X,       2.000000000000000);
assert(fabs((X.v[0])-(     -26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      10.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       12.000000000000000;
    v.v[1] =       -7.000000000000000;
    X.v[0] =      -20.000000000000000;
    X.v[1] =       -2.000000000000000;
    X.v[2] =       -1.000000000000000;
    X.v[3] =      -20.000000000000000;
    Y.v[0] =       12.000000000000000;
    Y.v[1] =        0.000000000000000;
    Y.v[2] =        5.000000000000000;
    Y.v[3] =      -17.000000000000000;
/*
[[-20.  -1.]
 [ -2. -20.]]
[[ 12.   5.]
 [  0. -17.]]
[[-240.   -5.]
 [  -0.  340.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(    -240.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(      -5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(     340.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-20.  -1.]
 [ -2. -20.]]
[[ 12.   5.]
 [  0. -17.]]
[[-240.   -5.]
 [  -0.  340.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dMultiplyElementwiseLocal(&X,&Y);
assert(fabs((X.v[0])-(    -240.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      -5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(     340.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       -4.000000000000000;
    v.v[1] =       -5.000000000000000;
    X.v[0] =       18.000000000000000;
    X.v[1] =       18.000000000000000;
    X.v[2] =       10.000000000000000;
    X.v[3] =       -4.000000000000000;
    Y.v[0] =       -4.000000000000000;
    Y.v[1] =        5.000000000000000;
    Y.v[2] =       16.000000000000000;
    Y.v[3] =       16.000000000000000;
/*
X
[[ 18.  10.]
 [ 18.  -4.]]
Y
[[ -4.  16.]
 [  5.  16.]]
[[ -22.  448.]
 [ -92.  224.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -22.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(     448.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     -92.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(     224.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[ 18.  10.]
 [ 18.  -4.]]
Y
[[ -4.  16.]
 [  5.  16.]]
X
[[ -22.  448.]
 [ -92.  224.]]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dMultiplyMatrixLocal(&X,&Y);
assert(fabs((X.v[0])-(     -22.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(     448.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     -92.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(     224.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =        6.000000000000000;
    v.v[1] =      -13.000000000000000;
    X.v[0] =       -4.000000000000000;
    X.v[1] =        1.000000000000000;
    X.v[2] =      -20.000000000000000;
    X.v[3] =      -16.000000000000000;
    Y.v[0] =        0.000000000000000;
    Y.v[1] =       17.000000000000000;
    Y.v[2] =      -20.000000000000000;
    Y.v[3] =       14.000000000000000;
/*
X
[[ -4. -20.]
 [  1. -16.]]
v
[  6. -13.]
w
[ 236.  214.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat22dMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((w.v[0])-(     236.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[1])-(     214.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[ -4. -20.]
 [  1. -16.]]
v
[  6. -13.]
v
[ 236.  214.]
*/
fprintf(stdout,"SST_Math_Mat22dMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dMultiplyVectorLocal(&X,&v);
assert(fabs((v.v[0])-(     236.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[1])-(     214.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       -2.000000000000000;
    v.v[1] =       -6.000000000000000;
    X.v[0] =      -19.000000000000000;
    X.v[1] =        0.000000000000000;
    X.v[2] =      -15.000000000000000;
    X.v[3] =       -4.000000000000000;
    Y.v[0] =       -5.000000000000000;
    Y.v[1] =       16.000000000000000;
    Y.v[2] =       11.000000000000000;
    Y.v[3] =       -8.000000000000000;
fprintf(stdout,"SST_Math_Mat22dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -19.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      -4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat22dTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22dTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22dTransposeLocal(&X);
assert(fabs((X.v[0])-(     -19.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      -4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[ 1.  0.]
 [ 0.  1.]]
[[ 1.  0.]
 [ 0.  1.]]
*/
X.v[0] = (double)       1.000000000000000;
X.v[2] = (double)       0.000000000000000;
X.v[1] = (double)       0.000000000000000;
X.v[3] = (double)       1.000000000000000;
fprintf(stdout,"SST_Math_Mat22dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat22dMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat22dMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat22dCheckOrthonormal(&X));
X.v[0] = (double)       1.000000000000000;
X.v[2] = (double)       0.000000000000000;
X.v[1] = (double)       0.000000000000000;
X.v[3] = (double)       1.000000000000000;
/* Check Positive Test */
assert(SST_Math_Mat22dCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] =       11.000000000000000;
    v.v[1] =       18.000000000000000;
    X.v[0] =      -18.000000000000000;
    X.v[1] =      -13.000000000000000;
    X.v[2] =      -11.000000000000000;
    X.v[3] =        0.000000000000000;
    Y.v[0] =        6.000000000000000;
    Y.v[1] =        3.000000000000000;
    Y.v[2] =      -19.000000000000000;
    Y.v[3] =      -15.000000000000000;
/*
[[ -6.16790569e-18  -7.69230769e-02]
 [ -9.09090909e-02   1.25874126e-01]]
*/
fprintf(stdout,"SST_Math_Mat22dInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat22dInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,0,B.v[2]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,1,B.v[3]);
assert(fabs((B.v[0])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[2])-(      -0.076923076923077)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[1])-(      -0.090909090909091)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[3])-(       0.125874125874126)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       16.000000000000000;
    v.v[1] =        6.000000000000000;
    X.v[0] =       17.000000000000000;
    X.v[1] =       15.000000000000000;
    X.v[2] =       -1.000000000000000;
    X.v[3] =        6.000000000000000;
    Y.v[0] =       -1.000000000000000;
    Y.v[1] =       17.000000000000000;
    Y.v[2] =      -18.000000000000000;
    Y.v[3] =       -8.000000000000000;
/*
[[ 0.05128205  0.00854701]
 [-0.12820513  0.14529915]]
*/
fprintf(stdout,"SST_Math_Mat22dInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat22dInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat22dInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabs((X.v[0])-(       0.051282051282051)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       0.008547008547009)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -0.128205128205128)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(       0.145299145299145)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat22dtest_fxn COMPLETE ====\n");
return 0;
}
