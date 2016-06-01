#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>




int SST_Math_Mat33f_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat33f X; /* 3 x 3 matrix */
SST_Mat33f Y; /* 3 x 3 matrix */
SST_Mat33f A; /* 3 x 3 matrix */
SST_Mat33f B; /* 3 x 3 matrix */
SST_Vec3f v; /* 3 vector */
SST_Vec3f w; /* 3 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = -15.000000f;
    v.v[1] = 15.000000f;
    v.v[2] = -9.000000f;
    X.v[0] = 8.000000f;
    X.v[1] = -19.000000f;
    X.v[2] = 0.000000f;
    X.v[3] = 16.000000f;
    X.v[4] = -17.000000f;
    X.v[5] = -12.000000f;
    X.v[6] = 6.000000f;
    X.v[7] = 4.000000f;
    X.v[8] = -18.000000f;
    Y.v[0] = -6.000000f;
    Y.v[1] = -16.000000f;
    Y.v[2] = 1.000000f;
    Y.v[3] = 7.000000f;
    Y.v[4] = 1.000000f;
    Y.v[5] = 9.000000f;
    Y.v[6] = -12.000000f;
    Y.v[7] = 10.000000f;
    Y.v[8] = 19.000000f;
SST_Math_Mat33fAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat33fAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[  8.  16.   6.]
 [-19. -17.   4.]
 [  0. -12. -18.]]
[[ -6.   7. -12.]
 [-16.   1.  10.]
 [  1.   9.  19.]]
[[  2.  23.  -6.]
 [-35. -16.  14.]
 [  1.  -3.   1.]]
*/
assert(fabsf((A.v[0])-(2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(23.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-35.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[  8.  16.   6.]
 [-19. -17.   4.]
 [  0. -12. -18.]]
[[ -6.   7. -12.]
 [-16.   1.  10.]
 [  1.   9.  19.]]
[[  2.  23.  -6.]
 [-35. -16.  14.]
 [  1.  -3.   1.]]
*/
fprintf(stdout,"SST_Math_Mat33fAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fAddLocal(&X,&Y); /* for accuracy */
assert(fabsf((X.v[0])-(2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(23.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-35.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 9.000000f;
    v.v[1] = 1.000000f;
    v.v[2] = 19.000000f;
    X.v[0] = 7.000000f;
    X.v[1] = 13.000000f;
    X.v[2] = -20.000000f;
    X.v[3] = -19.000000f;
    X.v[4] = 19.000000f;
    X.v[5] = 8.000000f;
    X.v[6] = 8.000000f;
    X.v[7] = -16.000000f;
    X.v[8] = -8.000000f;
    Y.v[0] = -7.000000f;
    Y.v[1] = -8.000000f;
    Y.v[2] = 4.000000f;
    Y.v[3] = -12.000000f;
    Y.v[4] = 5.000000f;
    Y.v[5] = -17.000000f;
    Y.v[6] = 17.000000f;
    Y.v[7] = 14.000000f;
    Y.v[8] = -11.000000f;
/*
[[  7. -19.   8.]
 [ 13.  19. -16.]
 [-20.   8.  -8.]]
[[ 14. -38.  16.]
 [ 26.  38. -32.]
 [-40.  16. -16.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyScalar(&X,2.000000f,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-32.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-40.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[  7. -19.   8.]
 [ 13.  19. -16.]
 [-20.   8.  -8.]]
[[ 14. -38.  16.]
 [ 26.  38. -32.]
 [-40.  16. -16.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyScalarLocal(&A,2.000000f);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fMultiplyScalarLocal(&X,2.000000f);
assert(fabsf((X.v[0])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-32.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-40.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -9.000000f;
    v.v[1] = -2.000000f;
    v.v[2] = -8.000000f;
    X.v[0] = -5.000000f;
    X.v[1] = -14.000000f;
    X.v[2] = -6.000000f;
    X.v[3] = 1.000000f;
    X.v[4] = -9.000000f;
    X.v[5] = 7.000000f;
    X.v[6] = 18.000000f;
    X.v[7] = 10.000000f;
    X.v[8] = -19.000000f;
    Y.v[0] = -8.000000f;
    Y.v[1] = -6.000000f;
    Y.v[2] = -2.000000f;
    Y.v[3] = -12.000000f;
    Y.v[4] = -6.000000f;
    Y.v[5] = 8.000000f;
    Y.v[6] = -5.000000f;
    Y.v[7] = -16.000000f;
    Y.v[8] = -16.000000f;
/*
[[ -5.   1.  18.]
 [-14.  -9.  10.]
 [ -6.   7. -19.]]
[[ -8. -12.  -5.]
 [ -6.  -6. -16.]
 [ -2.   8. -16.]]
[[  40.  -12.  -90.]
 [  84.   54. -160.]
 [  12.   56.  304.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(40.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-90.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(84.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(54.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-160.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(56.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(304.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[ -5.   1.  18.]
 [-14.  -9.  10.]
 [ -6.   7. -19.]]
[[ -8. -12.  -5.]
 [ -6.  -6. -16.]
 [ -2.   8. -16.]]
[[  40.  -12.  -90.]
 [  84.   54. -160.]
 [  12.   56.  304.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fMultiplyElementwiseLocal(&X,&Y);
assert(fabsf((X.v[0])-(40.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-90.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(84.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(54.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-160.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(56.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(304.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -7.000000f;
    v.v[1] = -15.000000f;
    v.v[2] = -19.000000f;
    X.v[0] = -16.000000f;
    X.v[1] = -15.000000f;
    X.v[2] = 10.000000f;
    X.v[3] = 0.000000f;
    X.v[4] = 0.000000f;
    X.v[5] = 6.000000f;
    X.v[6] = 1.000000f;
    X.v[7] = 3.000000f;
    X.v[8] = -18.000000f;
    Y.v[0] = -5.000000f;
    Y.v[1] = -12.000000f;
    Y.v[2] = -15.000000f;
    Y.v[3] = 6.000000f;
    Y.v[4] = 7.000000f;
    Y.v[5] = -7.000000f;
    Y.v[6] = 14.000000f;
    Y.v[7] = 6.000000f;
    Y.v[8] = -18.000000f;
/*
X
[[-16.   0.   1.]
 [-15.   0.   3.]
 [ 10.   6. -18.]]
Y
[[ -5.   6.  14.]
 [-12.   7.   6.]
 [-15.  -7. -18.]]
[[  65. -103. -242.]
 [  30. -111. -264.]
 [ 148.  228.  500.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(65.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-103.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-242.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(30.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(-111.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-264.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(148.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(228.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(500.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[-16.   0.   1.]
 [-15.   0.   3.]
 [ 10.   6. -18.]]
Y
[[ -5.   6.  14.]
 [-12.   7.   6.]
 [-15.  -7. -18.]]
X
[[  65. -103. -242.]
 [  30. -111. -264.]
 [ 148.  228.  500.]]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fMultiplyMatrixLocal(&X,&Y);
assert(fabsf((X.v[0])-(65.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-103.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-242.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(30.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-111.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-264.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(148.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(228.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(500.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -13.000000f;
    v.v[1] = -19.000000f;
    v.v[2] = 5.000000f;
    X.v[0] = 17.000000f;
    X.v[1] = -19.000000f;
    X.v[2] = -15.000000f;
    X.v[3] = 16.000000f;
    X.v[4] = -10.000000f;
    X.v[5] = 15.000000f;
    X.v[6] = -12.000000f;
    X.v[7] = 7.000000f;
    X.v[8] = -15.000000f;
    Y.v[0] = -5.000000f;
    Y.v[1] = -4.000000f;
    Y.v[2] = 5.000000f;
    Y.v[3] = 19.000000f;
    Y.v[4] = 19.000000f;
    Y.v[5] = 10.000000f;
    Y.v[6] = 19.000000f;
    Y.v[7] = 1.000000f;
    Y.v[8] = 17.000000f;
/*
X
[[ 17.  16. -12.]
 [-19. -10.   7.]
 [-15.  15. -15.]]
v
[-13. -19.   5.]
w
[-585.  472. -165.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat33fMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((w.v[0])-(-585.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[1])-(472.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[2])-(-165.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[ 17.  16. -12.]
 [-19. -10.   7.]
 [-15.  15. -15.]]
v
[-13. -19.   5.]
v
[-585.  472. -165.]
*/
fprintf(stdout,"SST_Math_Mat33fMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fMultiplyVectorLocal(&X,&v);
assert(fabsf((v.v[0])-(-585.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[1])-(472.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[2])-(-165.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 10.000000f;
    v.v[1] = 12.000000f;
    v.v[2] = -16.000000f;
    X.v[0] = 3.000000f;
    X.v[1] = -2.000000f;
    X.v[2] = 13.000000f;
    X.v[3] = -5.000000f;
    X.v[4] = 19.000000f;
    X.v[5] = 18.000000f;
    X.v[6] = -4.000000f;
    X.v[7] = -20.000000f;
    X.v[8] = -6.000000f;
    Y.v[0] = -1.000000f;
    Y.v[1] = -19.000000f;
    Y.v[2] = -8.000000f;
    Y.v[3] = 10.000000f;
    Y.v[4] = 19.000000f;
    Y.v[5] = -5.000000f;
    Y.v[6] = 6.000000f;
    Y.v[7] = 5.000000f;
    Y.v[8] = 7.000000f;
fprintf(stdout,"SST_Math_Mat33fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(13.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-5.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(19.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat33fTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33fTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33fTransposeLocal(&X);
assert(fabsf((X.v[0])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(13.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-5.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(19.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[-0.2223748   0.34678361 -0.91120285]
 [ 0.14824986 -0.91170913 -0.38315597]
 [-0.96362412 -0.22028992  0.1513305 ]]
[[  1.00000000e+00  -1.49011612e-08   1.49011612e-08]
 [ -1.49011612e-08   1.00000000e+00  -3.72529030e-09]
 [  1.49011612e-08  -3.72529030e-09   1.00000000e+00]]
*/
X.v[0] = (float)-0.222375f;
X.v[3] = (float)0.346784f;
X.v[6] = (float)-0.911203f;
X.v[1] = (float)0.148250f;
X.v[4] = (float)-0.911709f;
X.v[7] = (float)-0.383156f;
X.v[2] = (float)-0.963624f;
X.v[5] = (float)-0.220290f;
X.v[8] = (float)0.151331f;
fprintf(stdout,"SST_Math_Mat33fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat33fMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat33fMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat33fCheckOrthonormal(&X));
X.v[0] = (float)1.000000f;
X.v[3] = (float)0.000000f;
X.v[6] = (float)0.000000f;
X.v[1] = (float)0.000000f;
X.v[4] = (float)1.000000f;
X.v[7] = (float)0.000000f;
X.v[2] = (float)0.000000f;
X.v[5] = (float)0.000000f;
X.v[8] = (float)1.000000f;
/* Check Positive Test */
assert(SST_Math_Mat33fCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] = 16.000000f;
    v.v[1] = 12.000000f;
    v.v[2] = 16.000000f;
    X.v[0] = -2.000000f;
    X.v[1] = -2.000000f;
    X.v[2] = 10.000000f;
    X.v[3] = 6.000000f;
    X.v[4] = -14.000000f;
    X.v[5] = -7.000000f;
    X.v[6] = -8.000000f;
    X.v[7] = -6.000000f;
    X.v[8] = -9.000000f;
    Y.v[0] = -9.000000f;
    Y.v[1] = 12.000000f;
    Y.v[2] = -10.000000f;
    Y.v[3] = 1.000000f;
    Y.v[4] = 3.000000f;
    Y.v[5] = 13.000000f;
    Y.v[6] = -8.000000f;
    Y.v[7] = -16.000000f;
    Y.v[8] = -11.000000f;
/*
[[-0.04496788 -0.05888651  0.07922912]
 [ 0.04175589 -0.05246253 -0.00214133]
 [-0.08244111 -0.02462527 -0.02141328]]
*/
fprintf(stdout,"SST_Math_Mat33fInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat33fInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %ff\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,2,B.v[2]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,0,B.v[3]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,1,B.v[4]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,2,B.v[5]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,0,B.v[6]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,1,B.v[7]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,2,B.v[8]);
assert(fabsf((B.v[0])-(-0.044968f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[3])-(-0.058887f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[6])-(0.079229f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[1])-(0.041756f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[4])-(-0.052463f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[7])-(-0.002141f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[2])-(-0.082441f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[5])-(-0.024625f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[8])-(-0.021413f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 9.000000f;
    v.v[1] = 0.000000f;
    v.v[2] = -2.000000f;
    X.v[0] = -11.000000f;
    X.v[1] = -3.000000f;
    X.v[2] = 19.000000f;
    X.v[3] = 15.000000f;
    X.v[4] = -19.000000f;
    X.v[5] = 10.000000f;
    X.v[6] = -3.000000f;
    X.v[7] = 0.000000f;
    X.v[8] = -20.000000f;
    Y.v[0] = 12.000000f;
    Y.v[1] = -17.000000f;
    Y.v[2] = 4.000000f;
    Y.v[3] = -7.000000f;
    Y.v[4] = -20.000000f;
    Y.v[5] = 10.000000f;
    Y.v[6] = 18.000000f;
    Y.v[7] = 4.000000f;
    Y.v[8] = 5.000000f;
/*
[[-0.06257204 -0.04445908  0.00938581]
 [ 0.0098798  -0.04561172 -0.00148197]
 [-0.05450354 -0.06504199 -0.04182447]]
*/
fprintf(stdout,"SST_Math_Mat33fInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat33fInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat33fInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabsf((X.v[0])-(-0.062572f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-0.044459f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(0.009386f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(0.009880f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-0.045612f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-0.001482f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-0.054504f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-0.065042f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-0.041824f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat33ftest_fxn COMPLETE ====\n");
return 0;
}
