#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>




int SST_Math_Mat22f_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat22f X; /* 2 x 2 matrix */
SST_Mat22f Y; /* 2 x 2 matrix */
SST_Mat22f A; /* 2 x 2 matrix */
SST_Mat22f B; /* 2 x 2 matrix */
SST_Vec2f v; /* 2 vector */
SST_Vec2f w; /* 2 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = -11.000000f;
    v.v[1] = -4.000000f;
    X.v[0] = -5.000000f;
    X.v[1] = -2.000000f;
    X.v[2] = -20.000000f;
    X.v[3] = -13.000000f;
    Y.v[0] = -13.000000f;
    Y.v[1] = -18.000000f;
    Y.v[2] = 13.000000f;
    Y.v[3] = -4.000000f;
SST_Math_Mat22fAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat22fAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ -5. -20.]
 [ -2. -13.]]
[[-13.  13.]
 [-18.  -4.]]
[[-18.  -7.]
 [-20. -17.]]
*/
assert(fabsf((A.v[0])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-7.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-17.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[ -5. -20.]
 [ -2. -13.]]
[[-13.  13.]
 [-18.  -4.]]
[[-18.  -7.]
 [-20. -17.]]
*/
fprintf(stdout,"SST_Math_Mat22fAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fAddLocal(&X,&Y); /* for accuracy */
assert(fabsf((X.v[0])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-7.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-17.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -12.000000f;
    v.v[1] = 8.000000f;
    X.v[0] = -2.000000f;
    X.v[1] = 17.000000f;
    X.v[2] = -18.000000f;
    X.v[3] = -7.000000f;
    Y.v[0] = -1.000000f;
    Y.v[1] = 0.000000f;
    Y.v[2] = -12.000000f;
    Y.v[3] = 15.000000f;
/*
[[ -2. -18.]
 [ 17.  -7.]]
[[ -4. -36.]
 [ 34. -14.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyScalar(&X,2.000000f,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-36.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(34.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[ -2. -18.]
 [ 17.  -7.]]
[[ -4. -36.]
 [ 34. -14.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyScalarLocal(&A,2.000000f);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fMultiplyScalarLocal(&X,2.000000f);
assert(fabsf((X.v[0])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-36.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(34.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -18.000000f;
    v.v[1] = 2.000000f;
    X.v[0] = -19.000000f;
    X.v[1] = 1.000000f;
    X.v[2] = 14.000000f;
    X.v[3] = 16.000000f;
    Y.v[0] = -13.000000f;
    Y.v[1] = -1.000000f;
    Y.v[2] = -13.000000f;
    Y.v[3] = -14.000000f;
/*
[[-19.  14.]
 [  1.  16.]]
[[-13. -13.]
 [ -1. -14.]]
[[ 247. -182.]
 [  -1. -224.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(247.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-182.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-224.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[-19.  14.]
 [  1.  16.]]
[[-13. -13.]
 [ -1. -14.]]
[[ 247. -182.]
 [  -1. -224.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fMultiplyElementwiseLocal(&X,&Y);
assert(fabsf((X.v[0])-(247.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-182.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-224.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -13.000000f;
    v.v[1] = -18.000000f;
    X.v[0] = -17.000000f;
    X.v[1] = 16.000000f;
    X.v[2] = -2.000000f;
    X.v[3] = -18.000000f;
    Y.v[0] = 7.000000f;
    Y.v[1] = -6.000000f;
    Y.v[2] = 10.000000f;
    Y.v[3] = 11.000000f;
/*
X
[[-17.  -2.]
 [ 16. -18.]]
Y
[[  7.  10.]
 [ -6.  11.]]
[[-107. -192.]
 [ 220.  -38.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(-107.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-192.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(220.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[-17.  -2.]
 [ 16. -18.]]
Y
[[  7.  10.]
 [ -6.  11.]]
X
[[-107. -192.]
 [ 220.  -38.]]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fMultiplyMatrixLocal(&X,&Y);
assert(fabsf((X.v[0])-(-107.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-192.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(220.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 19.000000f;
    v.v[1] = -14.000000f;
    X.v[0] = 17.000000f;
    X.v[1] = -17.000000f;
    X.v[2] = 11.000000f;
    X.v[3] = -13.000000f;
    Y.v[0] = -7.000000f;
    Y.v[1] = 11.000000f;
    Y.v[2] = 6.000000f;
    Y.v[3] = 12.000000f;
/*
X
[[ 17.  11.]
 [-17. -13.]]
v
[ 19. -14.]
w
[ 169. -141.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat22fMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((w.v[0])-(169.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[1])-(-141.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[ 17.  11.]
 [-17. -13.]]
v
[ 19. -14.]
v
[ 169. -141.]
*/
fprintf(stdout,"SST_Math_Mat22fMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fMultiplyVectorLocal(&X,&v);
assert(fabsf((v.v[0])-(169.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[1])-(-141.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -15.000000f;
    v.v[1] = -6.000000f;
    X.v[0] = 6.000000f;
    X.v[1] = -18.000000f;
    X.v[2] = -16.000000f;
    X.v[3] = -19.000000f;
    Y.v[0] = 9.000000f;
    Y.v[1] = -16.000000f;
    Y.v[2] = 17.000000f;
    Y.v[3] = -18.000000f;
fprintf(stdout,"SST_Math_Mat22fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-19.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat22fTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22fTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22fTransposeLocal(&X);
assert(fabsf((X.v[0])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-19.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[ 0.31622776 -0.94868332]
 [-0.94868332 -0.31622776]]
[[ 1.  0.]
 [ 0.  1.]]
*/
X.v[0] = (float)0.316228f;
X.v[2] = (float)-0.948683f;
X.v[1] = (float)-0.948683f;
X.v[3] = (float)-0.316228f;
fprintf(stdout,"SST_Math_Mat22fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat22fMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat22fMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat22fCheckOrthonormal(&X));
X.v[0] = (float)1.000000f;
X.v[2] = (float)0.000000f;
X.v[1] = (float)0.000000f;
X.v[3] = (float)1.000000f;
/* Check Positive Test */
assert(SST_Math_Mat22fCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] = 10.000000f;
    v.v[1] = 15.000000f;
    X.v[0] = 16.000000f;
    X.v[1] = -18.000000f;
    X.v[2] = -13.000000f;
    X.v[3] = 14.000000f;
    Y.v[0] = -9.000000f;
    Y.v[1] = 6.000000f;
    Y.v[2] = -11.000000f;
    Y.v[3] = 1.000000f;
/*
[[-1.39999998 -1.29999995]
 [-1.79999995 -1.60000002]]
*/
fprintf(stdout,"SST_Math_Mat22fInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat22fInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %ff\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,0,B.v[2]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,1,B.v[3]);
assert(fabsf((B.v[0])-(-1.400000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[2])-(-1.300000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[1])-(-1.800000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[3])-(-1.600000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -3.000000f;
    v.v[1] = 6.000000f;
    X.v[0] = -17.000000f;
    X.v[1] = 14.000000f;
    X.v[2] = -9.000000f;
    X.v[3] = -20.000000f;
    Y.v[0] = 1.000000f;
    Y.v[1] = 12.000000f;
    Y.v[2] = -12.000000f;
    Y.v[3] = 14.000000f;
/*
[[-0.04291845  0.01931331]
 [-0.03004292 -0.03648069]]
*/
fprintf(stdout,"SST_Math_Mat22fInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat22fInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat22fInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabsf((X.v[0])-(-0.042918f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(0.019313f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-0.030043f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-0.036481f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat22ftest_fxn COMPLETE ====\n");
return 0;
}
