#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>




int SST_Math_Mat44d_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat44d X; /* 4 x 4 matrix */
SST_Mat44d Y; /* 4 x 4 matrix */
SST_Mat44d A; /* 4 x 4 matrix */
SST_Mat44d B; /* 4 x 4 matrix */
SST_Vec4d v; /* 4 vector */
SST_Vec4d w; /* 4 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] =        9.000000000000000;
    v.v[1] =       -6.000000000000000;
    v.v[2] =      -18.000000000000000;
    v.v[3] =      -13.000000000000000;
    X.v[0] =      -10.000000000000000;
    X.v[1] =       17.000000000000000;
    X.v[2] =       15.000000000000000;
    X.v[3] =       -1.000000000000000;
    X.v[4] =      -19.000000000000000;
    X.v[5] =        4.000000000000000;
    X.v[6] =       -5.000000000000000;
    X.v[7] =       -4.000000000000000;
    X.v[8] =      -17.000000000000000;
    X.v[9] =       16.000000000000000;
    X.v[10] =        5.000000000000000;
    X.v[11] =       -4.000000000000000;
    X.v[12] =      -18.000000000000000;
    X.v[13] =       -4.000000000000000;
    X.v[14] =       13.000000000000000;
    X.v[15] =      -16.000000000000000;
    Y.v[0] =        9.000000000000000;
    Y.v[1] =        8.000000000000000;
    Y.v[2] =      -10.000000000000000;
    Y.v[3] =      -16.000000000000000;
    Y.v[4] =        0.000000000000000;
    Y.v[5] =      -19.000000000000000;
    Y.v[6] =      -11.000000000000000;
    Y.v[7] =       18.000000000000000;
    Y.v[8] =       16.000000000000000;
    Y.v[9] =       13.000000000000000;
    Y.v[10] =      -12.000000000000000;
    Y.v[11] =      -14.000000000000000;
    Y.v[12] =        9.000000000000000;
    Y.v[13] =        5.000000000000000;
    Y.v[14] =       13.000000000000000;
    Y.v[15] =      -10.000000000000000;
SST_Math_Mat44dAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat44dAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[-10. -19. -17. -18.]
 [ 17.   4.  16.  -4.]
 [ 15.  -5.   5.  13.]
 [ -1.  -4.  -4. -16.]]
[[  9.   0.  16.   9.]
 [  8. -19.  13.   5.]
 [-10. -11. -12.  13.]
 [-16.  18. -14. -10.]]
[[ -1. -19.  -1.  -9.]
 [ 25. -15.  29.   1.]
 [  5. -16.  -7.  26.]
 [-17.  14. -18. -26.]]
*/
assert(fabs((A.v[0])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(     -19.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[12])-(      -9.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      25.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[9])-(      29.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[13])-(       1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(       5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[10])-(      -7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[14])-(      26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(      14.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[11])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[15])-(     -26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-10. -19. -17. -18.]
 [ 17.   4.  16.  -4.]
 [ 15.  -5.   5.  13.]
 [ -1.  -4.  -4. -16.]]
[[  9.   0.  16.   9.]
 [  8. -19.  13.   5.]
 [-10. -11. -12.  13.]
 [-16.  18. -14. -10.]]
[[ -1. -19.  -1.  -9.]
 [ 25. -15.  29.   1.]
 [  5. -16.  -7.  26.]
 [-17.  14. -18. -26.]]
*/
fprintf(stdout,"SST_Math_Mat44dAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dAddLocal(&X,&Y); /* for accuracy */
assert(fabs((X.v[0])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(     -19.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(      -9.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      25.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(      29.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(       1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(      -7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(      26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(      14.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(     -26.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       -8.000000000000000;
    v.v[1] =      -10.000000000000000;
    v.v[2] =       -7.000000000000000;
    v.v[3] =        7.000000000000000;
    X.v[0] =        3.000000000000000;
    X.v[1] =        6.000000000000000;
    X.v[2] =        0.000000000000000;
    X.v[3] =       19.000000000000000;
    X.v[4] =       14.000000000000000;
    X.v[5] =       -9.000000000000000;
    X.v[6] =      -17.000000000000000;
    X.v[7] =      -20.000000000000000;
    X.v[8] =       18.000000000000000;
    X.v[9] =      -18.000000000000000;
    X.v[10] =       -4.000000000000000;
    X.v[11] =       12.000000000000000;
    X.v[12] =        8.000000000000000;
    X.v[13] =      -11.000000000000000;
    X.v[14] =       12.000000000000000;
    X.v[15] =       -6.000000000000000;
    Y.v[0] =      -20.000000000000000;
    Y.v[1] =      -11.000000000000000;
    Y.v[2] =      -13.000000000000000;
    Y.v[3] =       19.000000000000000;
    Y.v[4] =       19.000000000000000;
    Y.v[5] =       14.000000000000000;
    Y.v[6] =       19.000000000000000;
    Y.v[7] =      -16.000000000000000;
    Y.v[8] =      -20.000000000000000;
    Y.v[9] =       12.000000000000000;
    Y.v[10] =      -12.000000000000000;
    Y.v[11] =        8.000000000000000;
    Y.v[12] =        0.000000000000000;
    Y.v[13] =        9.000000000000000;
    Y.v[14] =       18.000000000000000;
    Y.v[15] =        9.000000000000000;
/*
[[  3.  14.  18.   8.]
 [  6.  -9. -18. -11.]
 [  0. -17.  -4.  12.]
 [ 19. -20.  12.  -6.]]
[[  6.  28.  36.  16.]
 [ 12. -18. -36. -22.]
 [  0. -34.  -8.  24.]
 [ 38. -40.  24. -12.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyScalar(&X,       2.000000000000000,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(       6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(      28.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[12])-(      16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[9])-(     -36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[13])-(     -22.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     -34.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[10])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[14])-(      24.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      38.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     -40.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[11])-(      24.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[15])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[  3.  14.  18.   8.]
 [  6.  -9. -18. -11.]
 [  0. -17.  -4.  12.]
 [ 19. -20.  12.  -6.]]
[[  6.  28.  36.  16.]
 [ 12. -18. -36. -22.]
 [  0. -34.  -8.  24.]
 [ 38. -40.  24. -12.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyScalarLocal(&A,       2.000000000000000);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dMultiplyScalarLocal(&X,       2.000000000000000);
assert(fabs((X.v[0])-(       6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(      28.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(      16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(     -36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(     -22.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     -34.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(      24.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      38.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     -40.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(      24.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       -1.000000000000000;
    v.v[1] =      -12.000000000000000;
    v.v[2] =       11.000000000000000;
    v.v[3] =       -3.000000000000000;
    X.v[0] =       -5.000000000000000;
    X.v[1] =      -12.000000000000000;
    X.v[2] =       16.000000000000000;
    X.v[3] =        0.000000000000000;
    X.v[4] =       10.000000000000000;
    X.v[5] =      -20.000000000000000;
    X.v[6] =      -15.000000000000000;
    X.v[7] =        6.000000000000000;
    X.v[8] =        0.000000000000000;
    X.v[9] =        8.000000000000000;
    X.v[10] =      -14.000000000000000;
    X.v[11] =      -18.000000000000000;
    X.v[12] =       -1.000000000000000;
    X.v[13] =       17.000000000000000;
    X.v[14] =       15.000000000000000;
    X.v[15] =       17.000000000000000;
    Y.v[0] =       10.000000000000000;
    Y.v[1] =        0.000000000000000;
    Y.v[2] =       12.000000000000000;
    Y.v[3] =       -1.000000000000000;
    Y.v[4] =       19.000000000000000;
    Y.v[5] =      -11.000000000000000;
    Y.v[6] =       -5.000000000000000;
    Y.v[7] =       -9.000000000000000;
    Y.v[8] =        6.000000000000000;
    Y.v[9] =       -1.000000000000000;
    Y.v[10] =        5.000000000000000;
    Y.v[11] =       -3.000000000000000;
    Y.v[12] =      -15.000000000000000;
    Y.v[13] =       -8.000000000000000;
    Y.v[14] =       13.000000000000000;
    Y.v[15] =       -8.000000000000000;
/*
[[ -5.  10.   0.  -1.]
 [-12. -20.   8.  17.]
 [ 16. -15. -14.  15.]
 [  0.   6. -18.  17.]]
[[ 10.  19.   6. -15.]
 [  0. -11.  -1.  -8.]
 [ 12.  -5.   5.  13.]
 [ -1.  -9.  -3.  -8.]]
[[ -50.  190.    0.   15.]
 [  -0.  220.   -8. -136.]
 [ 192.   75.  -70.  195.]
 [  -0.  -54.   54. -136.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -50.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(     190.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[12])-(      15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(     220.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[9])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[13])-(    -136.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(     192.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(      75.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[10])-(     -70.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[14])-(     195.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     -54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[11])-(      54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[15])-(    -136.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[ -5.  10.   0.  -1.]
 [-12. -20.   8.  17.]
 [ 16. -15. -14.  15.]
 [  0.   6. -18.  17.]]
[[ 10.  19.   6. -15.]
 [  0. -11.  -1.  -8.]
 [ 12.  -5.   5.  13.]
 [ -1.  -9.  -3.  -8.]]
[[ -50.  190.    0.   15.]
 [  -0.  220.   -8. -136.]
 [ 192.   75.  -70.  195.]
 [  -0.  -54.   54. -136.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dMultiplyElementwiseLocal(&X,&Y);
assert(fabs((X.v[0])-(     -50.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(     190.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(      15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(     220.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(    -136.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(     192.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(      75.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(     -70.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(     195.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      -0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     -54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(      54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(    -136.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       14.000000000000000;
    v.v[1] =       10.000000000000000;
    v.v[2] =        0.000000000000000;
    v.v[3] =      -19.000000000000000;
    X.v[0] =        9.000000000000000;
    X.v[1] =      -15.000000000000000;
    X.v[2] =        1.000000000000000;
    X.v[3] =       -6.000000000000000;
    X.v[4] =        0.000000000000000;
    X.v[5] =       -2.000000000000000;
    X.v[6] =      -14.000000000000000;
    X.v[7] =      -14.000000000000000;
    X.v[8] =        4.000000000000000;
    X.v[9] =      -14.000000000000000;
    X.v[10] =       14.000000000000000;
    X.v[11] =      -11.000000000000000;
    X.v[12] =       16.000000000000000;
    X.v[13] =       15.000000000000000;
    X.v[14] =        8.000000000000000;
    X.v[15] =       -7.000000000000000;
    Y.v[0] =       -9.000000000000000;
    Y.v[1] =       -5.000000000000000;
    Y.v[2] =        3.000000000000000;
    Y.v[3] =        2.000000000000000;
    Y.v[4] =       -3.000000000000000;
    Y.v[5] =       -6.000000000000000;
    Y.v[6] =       15.000000000000000;
    Y.v[7] =       -2.000000000000000;
    Y.v[8] =       15.000000000000000;
    Y.v[9] =      -15.000000000000000;
    Y.v[10] =       -5.000000000000000;
    Y.v[11] =       -4.000000000000000;
    Y.v[12] =        1.000000000000000;
    Y.v[13] =       -9.000000000000000;
    Y.v[14] =      -19.000000000000000;
    Y.v[15] =        0.000000000000000;
/*
X
[[  9.   0.   4.  16.]
 [-15.  -2. -14.  15.]
 [  1. -14.  14.   8.]
 [ -6. -14. -11.  -7.]]
Y
[[ -9.  -3.  15.   1.]
 [ -5.  -6. -15.  -9.]
 [  3.  15.  -5. -19.]
 [  2.  -2.  -4.   0.]]
[[ -37.    1.   51.  -67.]
 [ 133. -183. -185.  269.]
 [ 119.  275.  123. -139.]
 [  77.  -49.  203.  329.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -37.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(       1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      51.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[12])-(     -67.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     133.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(    -183.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[9])-(    -185.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[13])-(     269.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(     119.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     275.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[10])-(     123.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[14])-(    -139.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      77.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     -49.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[11])-(     203.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[15])-(     329.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[  9.   0.   4.  16.]
 [-15.  -2. -14.  15.]
 [  1. -14.  14.   8.]
 [ -6. -14. -11.  -7.]]
Y
[[ -9.  -3.  15.   1.]
 [ -5.  -6. -15.  -9.]
 [  3.  15.  -5. -19.]
 [  2.  -2.  -4.   0.]]
X
[[ -37.    1.   51.  -67.]
 [ 133. -183. -185.  269.]
 [ 119.  275.  123. -139.]
 [  77.  -49.  203.  329.]]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dMultiplyMatrixLocal(&X,&Y);
assert(fabs((X.v[0])-(     -37.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(       1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      51.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(     -67.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     133.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(    -183.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(    -185.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(     269.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(     119.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     275.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(     123.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(    -139.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      77.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     -49.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(     203.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(     329.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =        8.000000000000000;
    v.v[1] =        8.000000000000000;
    v.v[2] =       -5.000000000000000;
    v.v[3] =      -18.000000000000000;
    X.v[0] =       10.000000000000000;
    X.v[1] =       -7.000000000000000;
    X.v[2] =        1.000000000000000;
    X.v[3] =        1.000000000000000;
    X.v[4] =       -6.000000000000000;
    X.v[5] =      -15.000000000000000;
    X.v[6] =       -3.000000000000000;
    X.v[7] =       -5.000000000000000;
    X.v[8] =      -15.000000000000000;
    X.v[9] =       -2.000000000000000;
    X.v[10] =       -5.000000000000000;
    X.v[11] =       -6.000000000000000;
    X.v[12] =       -1.000000000000000;
    X.v[13] =       -9.000000000000000;
    X.v[14] =       -3.000000000000000;
    X.v[15] =       -5.000000000000000;
    Y.v[0] =        6.000000000000000;
    Y.v[1] =       17.000000000000000;
    Y.v[2] =      -16.000000000000000;
    Y.v[3] =       -8.000000000000000;
    Y.v[4] =       -1.000000000000000;
    Y.v[5] =       14.000000000000000;
    Y.v[6] =       -7.000000000000000;
    Y.v[7] =        8.000000000000000;
    Y.v[8] =        9.000000000000000;
    Y.v[9] =       -1.000000000000000;
    Y.v[10] =       11.000000000000000;
    Y.v[11] =      -17.000000000000000;
    Y.v[12] =        6.000000000000000;
    Y.v[13] =        5.000000000000000;
    Y.v[14] =       11.000000000000000;
    Y.v[15] =        8.000000000000000;
/*
X
[[ 10.  -6. -15.  -1.]
 [ -7. -15.  -2.  -9.]
 [  1.  -3.  -5.  -3.]
 [  1.  -5.  -6.  -5.]]
v
[  8.   8.  -5. -18.]
w
[ 125.   -4.   63.   88.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat44dMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((w.v[0])-(     125.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[1])-(      -4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[2])-(      63.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[3])-(      88.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[ 10.  -6. -15.  -1.]
 [ -7. -15.  -2.  -9.]
 [  1.  -3.  -5.  -3.]
 [  1.  -5.  -6.  -5.]]
v
[  8.   8.  -5. -18.]
v
[ 125.   -4.   63.   88.]
*/
fprintf(stdout,"SST_Math_Mat44dMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dMultiplyVectorLocal(&X,&v);
assert(fabs((v.v[0])-(     125.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[1])-(      -4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[2])-(      63.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[3])-(      88.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =       18.000000000000000;
    v.v[1] =       -8.000000000000000;
    v.v[2] =      -11.000000000000000;
    v.v[3] =       10.000000000000000;
    X.v[0] =      -15.000000000000000;
    X.v[1] =       -6.000000000000000;
    X.v[2] =      -13.000000000000000;
    X.v[3] =      -17.000000000000000;
    X.v[4] =        0.000000000000000;
    X.v[5] =        8.000000000000000;
    X.v[6] =       -6.000000000000000;
    X.v[7] =      -18.000000000000000;
    X.v[8] =       -5.000000000000000;
    X.v[9] =        8.000000000000000;
    X.v[10] =       -8.000000000000000;
    X.v[11] =      -12.000000000000000;
    X.v[12] =       -8.000000000000000;
    X.v[13] =      -17.000000000000000;
    X.v[14] =       16.000000000000000;
    X.v[15] =       -1.000000000000000;
    Y.v[0] =       16.000000000000000;
    Y.v[1] =       -8.000000000000000;
    Y.v[2] =       13.000000000000000;
    Y.v[3] =       -2.000000000000000;
    Y.v[4] =        8.000000000000000;
    Y.v[5] =        9.000000000000000;
    Y.v[6] =       -1.000000000000000;
    Y.v[7] =      -20.000000000000000;
    Y.v[8] =      -14.000000000000000;
    Y.v[9] =       11.000000000000000;
    Y.v[10] =      -12.000000000000000;
    Y.v[11] =       -4.000000000000000;
    Y.v[12] =       -3.000000000000000;
    Y.v[13] =      -12.000000000000000;
    Y.v[14] =      -10.000000000000000;
    Y.v[15] =       18.000000000000000;
fprintf(stdout,"SST_Math_Mat44dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(     -13.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[12])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[9])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[13])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(      -5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[10])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[14])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[11])-(      16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[15])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat44dTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44dTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44dTransposeLocal(&X);
assert(fabs((X.v[0])-(     -15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(     -13.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(     -18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      -5.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     -17.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(      16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(      -1.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-0.55940561 -0.42900339 -0.45263254 -0.54602678]
 [-0.22376224 -0.66120998  0.69491745  0.17268919]
 [-0.48481819 -0.00459646 -0.35870509  0.79765961]
 [-0.63399302  0.61541557  0.42842056 -0.18913578]]
[[  1.00000000e+00  -5.55111512e-17   0.00000000e+00   2.77555756e-17]
 [ -5.55111512e-17   1.00000000e+00  -1.66533454e-16  -6.93889390e-17]
 [  0.00000000e+00  -1.66533454e-16   1.00000000e+00   2.22044605e-16]
 [  2.77555756e-17  -6.93889390e-17   2.22044605e-16   1.00000000e+00]]
*/
X.v[0] = (double)      -0.559405605471151;
X.v[4] = (double)      -0.429003386656450;
X.v[8] = (double)      -0.452632538505463;
X.v[12] = (double)      -0.546026783125930;
X.v[1] = (double)      -0.223762242188460;
X.v[5] = (double)      -0.661209981656212;
X.v[9] = (double)       0.694917449479891;
X.v[13] = (double)       0.172689193458502;
X.v[2] = (double)      -0.484818191408331;
X.v[6] = (double)      -0.004596464857033;
X.v[10] = (double)      -0.358705093004686;
X.v[14] = (double)       0.797659607879747;
X.v[3] = (double)      -0.633993019533971;
X.v[7] = (double)       0.615415572525027;
X.v[11] = (double)       0.428420564103736;
X.v[15] = (double)      -0.189135783311693;
fprintf(stdout,"SST_Math_Mat44dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat44dMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat44dMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat44dCheckOrthonormal(&X));
X.v[0] = (double)       1.000000000000000;
X.v[4] = (double)       0.000000000000000;
X.v[8] = (double)       0.000000000000000;
X.v[12] = (double)       0.000000000000000;
X.v[1] = (double)       0.000000000000000;
X.v[5] = (double)       1.000000000000000;
X.v[9] = (double)       0.000000000000000;
X.v[13] = (double)       0.000000000000000;
X.v[2] = (double)       0.000000000000000;
X.v[6] = (double)       0.000000000000000;
X.v[10] = (double)       1.000000000000000;
X.v[14] = (double)       0.000000000000000;
X.v[3] = (double)       0.000000000000000;
X.v[7] = (double)       0.000000000000000;
X.v[11] = (double)       0.000000000000000;
X.v[15] = (double)       1.000000000000000;
/* Check Positive Test */
assert(SST_Math_Mat44dCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] =      -12.000000000000000;
    v.v[1] =      -12.000000000000000;
    v.v[2] =       15.000000000000000;
    v.v[3] =      -12.000000000000000;
    X.v[0] =       15.000000000000000;
    X.v[1] =        8.000000000000000;
    X.v[2] =       15.000000000000000;
    X.v[3] =      -17.000000000000000;
    X.v[4] =       10.000000000000000;
    X.v[5] =       10.000000000000000;
    X.v[6] =       -5.000000000000000;
    X.v[7] =      -10.000000000000000;
    X.v[8] =        8.000000000000000;
    X.v[9] =        3.000000000000000;
    X.v[10] =       19.000000000000000;
    X.v[11] =       19.000000000000000;
    X.v[12] =        4.000000000000000;
    X.v[13] =        9.000000000000000;
    X.v[14] =       15.000000000000000;
    X.v[15] =       11.000000000000000;
    Y.v[0] =        1.000000000000000;
    Y.v[1] =      -17.000000000000000;
    Y.v[2] =       -3.000000000000000;
    Y.v[3] =        2.000000000000000;
    Y.v[4] =       15.000000000000000;
    Y.v[5] =        8.000000000000000;
    Y.v[6] =        3.000000000000000;
    Y.v[7] =       -6.000000000000000;
    Y.v[8] =       -7.000000000000000;
    Y.v[9] =       -6.000000000000000;
    Y.v[10] =      -15.000000000000000;
    Y.v[11] =        1.000000000000000;
    Y.v[12] =      -18.000000000000000;
    Y.v[13] =        6.000000000000000;
    Y.v[14] =       11.000000000000000;
    Y.v[15] =       18.000000000000000;
/*
[[ 0.00320783 -0.019247    0.03545501 -0.03376667]
 [ 0.06084754  0.03491474 -0.05379031  0.02265744]
 [ 0.09378693 -0.06272159 -0.01603917  0.03908492]
 [-0.1017221   0.1103326   0.03359784 -0.00818842]]
*/
fprintf(stdout,"SST_Math_Mat44dInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat44dInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,2,B.v[2]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,3,B.v[3]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,0,B.v[4]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,1,B.v[5]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,2,B.v[6]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,3,B.v[7]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,0,B.v[8]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,1,B.v[9]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,2,B.v[10]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,3,B.v[11]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",3,0,B.v[12]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",3,1,B.v[13]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",3,2,B.v[14]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",3,3,B.v[15]);
assert(fabs((B.v[0])-(       0.003207833867972)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[4])-(      -0.019247003207834)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[8])-(       0.035455005909168)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[12])-(      -0.033766672294445)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[1])-(       0.060847543474591)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[5])-(       0.034914739152457)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[9])-(      -0.053790308965051)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[13])-(       0.022657437109573)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[2])-(       0.093786932297822)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[6])-(      -0.062721593786932)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[10])-(      -0.016039169339862)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[14])-(       0.039084923180821)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[3])-(      -0.101722100287017)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[7])-(       0.110332601722100)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[11])-(       0.033597838932973)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[15])-(      -0.008188418031403)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =        5.000000000000000;
    v.v[1] =      -17.000000000000000;
    v.v[2] =      -17.000000000000000;
    v.v[3] =       10.000000000000000;
    X.v[0] =       16.000000000000000;
    X.v[1] =      -11.000000000000000;
    X.v[2] =      -11.000000000000000;
    X.v[3] =       14.000000000000000;
    X.v[4] =        3.000000000000000;
    X.v[5] =      -10.000000000000000;
    X.v[6] =       15.000000000000000;
    X.v[7] =       -3.000000000000000;
    X.v[8] =        7.000000000000000;
    X.v[9] =      -14.000000000000000;
    X.v[10] =       17.000000000000000;
    X.v[11] =       -4.000000000000000;
    X.v[12] =        8.000000000000000;
    X.v[13] =        1.000000000000000;
    X.v[14] =       -1.000000000000000;
    X.v[15] =      -10.000000000000000;
    Y.v[0] =       -1.000000000000000;
    Y.v[1] =       19.000000000000000;
    Y.v[2] =      -19.000000000000000;
    Y.v[3] =      -12.000000000000000;
    Y.v[4] =       -5.000000000000000;
    Y.v[5] =       16.000000000000000;
    Y.v[6] =       11.000000000000000;
    Y.v[7] =        1.000000000000000;
    Y.v[8] =        2.000000000000000;
    Y.v[9] =       13.000000000000000;
    Y.v[10] =        5.000000000000000;
    Y.v[11] =       17.000000000000000;
    Y.v[12] =       11.000000000000000;
    Y.v[13] =       14.000000000000000;
    Y.v[14] =        3.000000000000000;
    Y.v[15] =      -17.000000000000000;
/*
[[ 0.14584812  0.16926899  0.10823279  0.12278211]
 [ 1.2264017   1.84669979  1.26046842  1.0397445 ]
 [-0.97444996 -1.50319375 -0.97374024 -0.83250532]
 [ 0.22604684  0.28424414  0.16288148  0.09297374]]
*/
fprintf(stdout,"SST_Math_Mat44dInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat44dInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat44dInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabs((X.v[0])-(       0.145848119233499)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(       0.169268985095813)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(       0.108232789212207)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[12])-(       0.122782114975160)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(       1.226401703335700)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(       1.846699787083038)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[9])-(       1.260468417317247)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[13])-(       1.039744499645138)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      -0.974449964513840)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(      -1.503193754435770)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[10])-(      -0.973740241305891)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[14])-(      -0.832505322924060)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(       0.226046841731725)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(       0.284244144783534)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[11])-(       0.162881476224273)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[15])-(       0.092973740241306)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat44dtest_fxn COMPLETE ====\n");
return 0;
}
