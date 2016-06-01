#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>




int SST_Math_Mat33d_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat33d X; /* 3 x 3 matrix */
SST_Mat33d Y; /* 3 x 3 matrix */
SST_Mat33d A; /* 3 x 3 matrix */
SST_Mat33d B; /* 3 x 3 matrix */
SST_Vec3d v; /* 3 vector */
SST_Vec3d w; /* 3 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] =       14.000000000000000;
    v.v[1] =      -16.000000000000000;
    v.v[2] =       13.000000000000000;
    X.v[0] =       -4.000000000000000;
    X.v[1] =      -18.000000000000000;
    X.v[2] =       12.000000000000000;
    X.v[3] =       11.000000000000000;
    X.v[4] =      -14.000000000000000;
    X.v[5] =       19.000000000000000;
    X.v[6] =       -6.000000000000000;
    X.v[7] =        0.000000000000000;
    X.v[8] =       11.000000000000000;
    Y.v[0] =      -17.000000000000000;
    Y.v[1] =        9.000000000000000;
    Y.v[2] =       17.000000000000000;
    Y.v[3] =       -7.000000000000000;
    Y.v[4] =        8.000000000000000;
    Y.v[5] =      -11.000000000000000;
    Y.v[6] =      -14.000000000000000;
    Y.v[7] =        8.000000000000000;
    Y.v[8] =       -8.000000000000000;
SST_Math_Mat33dAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat33dAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ -4.  11.  -6.]
 [-18. -14.   0.]
 [ 12.  19.  11.]]
[[-17.  -7. -14.]
 [  9.   8.   8.]
 [ 17. -11.  -8.]]
[[-21.   4. -20.]
 [ -9.  -6.   8.]
 [ 29.   8.   3.]]
*/
assert(fabs((A.v[0])-(     -21.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(       4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     -20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      -9.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(      29.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(       3.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[ -4.  11.  -6.]
 [-18. -14.   0.]
 [ 12.  19.  11.]]
[[-17.  -7. -14.]
 [  9.   8.   8.]
 [ 17. -11.  -8.]]
[[-21.   4. -20.]
 [ -9.  -6.   8.]
 [ 29.   8.   3.]]
*/
fprintf(stdout,"SST_Math_Mat33dAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dAddLocal(&X,&Y); /* for accuracy */
assert(fabs((X.v[0])-(     -21.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(       4.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     -20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -9.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      29.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(       8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(       3.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =      -17.000000000000000;
    v.v[1] =       -8.000000000000000;
    v.v[2] =       16.000000000000000;
    X.v[0] =      -18.000000000000000;
    X.v[1] =       19.000000000000000;
    X.v[2] =        0.000000000000000;
    X.v[3] =       -4.000000000000000;
    X.v[4] =      -10.000000000000000;
    X.v[5] =       -4.000000000000000;
    X.v[6] =        9.000000000000000;
    X.v[7] =       -8.000000000000000;
    X.v[8] =       14.000000000000000;
    Y.v[0] =       11.000000000000000;
    Y.v[1] =      -10.000000000000000;
    Y.v[2] =      -20.000000000000000;
    Y.v[3] =        9.000000000000000;
    Y.v[4] =      -14.000000000000000;
    Y.v[5] =      -10.000000000000000;
    Y.v[6] =        9.000000000000000;
    Y.v[7] =       11.000000000000000;
    Y.v[8] =      -20.000000000000000;
/*
[[-18.  -4.   9.]
 [ 19. -10.  -8.]
 [  0.  -4.  14.]]
[[-36.  -8.  18.]
 [ 38. -20. -16.]
 [  0.  -8.  28.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyScalar(&X,       2.000000000000000,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(     -36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(      18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      38.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(     -20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      28.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-18.  -4.   9.]
 [ 19. -10.  -8.]
 [  0.  -4.  14.]]
[[-36.  -8.  18.]
 [ 38. -20. -16.]
 [  0.  -8.  28.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyScalarLocal(&A,       2.000000000000000);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dMultiplyScalarLocal(&X,       2.000000000000000);
assert(fabs((X.v[0])-(     -36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(      18.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      38.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(     -20.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       0.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(      -8.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      28.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =      -17.000000000000000;
    v.v[1] =       -4.000000000000000;
    v.v[2] =      -18.000000000000000;
    X.v[0] =       -3.000000000000000;
    X.v[1] =      -18.000000000000000;
    X.v[2] =       -9.000000000000000;
    X.v[3] =       -6.000000000000000;
    X.v[4] =        2.000000000000000;
    X.v[5] =      -13.000000000000000;
    X.v[6] =       15.000000000000000;
    X.v[7] =       10.000000000000000;
    X.v[8] =        9.000000000000000;
    Y.v[0] =      -20.000000000000000;
    Y.v[1] =        3.000000000000000;
    Y.v[2] =      -16.000000000000000;
    Y.v[3] =      -14.000000000000000;
    Y.v[4] =       18.000000000000000;
    Y.v[5] =      -11.000000000000000;
    Y.v[6] =       -2.000000000000000;
    Y.v[7] =       11.000000000000000;
    Y.v[8] =        7.000000000000000;
/*
[[ -3.  -6.  15.]
 [-18.   2.  10.]
 [ -9. -13.   9.]]
[[-20. -14.  -2.]
 [  3.  18.  11.]
 [-16. -11.   7.]]
[[  60.   84.  -30.]
 [ -54.   36.  110.]
 [ 144.  143.   63.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(      60.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(      84.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     -30.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     -54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(      36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     110.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(     144.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(     143.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      63.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[ -3.  -6.  15.]
 [-18.   2.  10.]
 [ -9. -13.   9.]]
[[-20. -14.  -2.]
 [  3.  18.  11.]
 [-16. -11.   7.]]
[[  60.   84.  -30.]
 [ -54.   36.  110.]
 [ 144.  143.   63.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dMultiplyElementwiseLocal(&X,&Y);
assert(fabs((X.v[0])-(      60.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      84.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     -30.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     -54.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(      36.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     110.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(     144.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(     143.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      63.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =      -12.000000000000000;
    v.v[1] =        4.000000000000000;
    v.v[2] =      -13.000000000000000;
    X.v[0] =      -17.000000000000000;
    X.v[1] =       17.000000000000000;
    X.v[2] =      -10.000000000000000;
    X.v[3] =        0.000000000000000;
    X.v[4] =       12.000000000000000;
    X.v[5] =       16.000000000000000;
    X.v[6] =       -3.000000000000000;
    X.v[7] =       -7.000000000000000;
    X.v[8] =        4.000000000000000;
    Y.v[0] =       15.000000000000000;
    Y.v[1] =        2.000000000000000;
    Y.v[2] =       -7.000000000000000;
    Y.v[3] =       16.000000000000000;
    Y.v[4] =       -2.000000000000000;
    Y.v[5] =       11.000000000000000;
    Y.v[6] =       12.000000000000000;
    Y.v[7] =       14.000000000000000;
    Y.v[8] =      -12.000000000000000;
/*
X
[[-17.   0.  -3.]
 [ 17.  12.  -7.]
 [-10.  16.   4.]]
Y
[[ 15.  16.  12.]
 [  2.  -2.  14.]
 [ -7.  11. -12.]]
[[-234. -305. -168.]
 [ 328.  171.  456.]
 [-146. -148.   56.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(    -234.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(    -305.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(    -168.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(     328.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(     171.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(     456.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(    -146.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(    -148.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(      56.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[-17.   0.  -3.]
 [ 17.  12.  -7.]
 [-10.  16.   4.]]
Y
[[ 15.  16.  12.]
 [  2.  -2.  14.]
 [ -7.  11. -12.]]
X
[[-234. -305. -168.]
 [ 328.  171.  456.]
 [-146. -148.   56.]]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dMultiplyMatrixLocal(&X,&Y);
assert(fabs((X.v[0])-(    -234.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(    -305.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(    -168.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(     328.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(     171.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(     456.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(    -146.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(    -148.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(      56.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =      -15.000000000000000;
    v.v[1] =      -14.000000000000000;
    v.v[2] =       10.000000000000000;
    X.v[0] =       19.000000000000000;
    X.v[1] =        7.000000000000000;
    X.v[2] =       17.000000000000000;
    X.v[3] =       15.000000000000000;
    X.v[4] =        0.000000000000000;
    X.v[5] =       12.000000000000000;
    X.v[6] =       -5.000000000000000;
    X.v[7] =       17.000000000000000;
    X.v[8] =      -19.000000000000000;
    Y.v[0] =        6.000000000000000;
    Y.v[1] =       16.000000000000000;
    Y.v[2] =      -19.000000000000000;
    Y.v[3] =        0.000000000000000;
    Y.v[4] =       15.000000000000000;
    Y.v[5] =       -7.000000000000000;
    Y.v[6] =        0.000000000000000;
    Y.v[7] =       17.000000000000000;
    Y.v[8] =        7.000000000000000;
/*
X
[[ 19.  15.  -5.]
 [  7.   0.  17.]
 [ 17.  12. -19.]]
v
[-15. -14.  10.]
w
[-545.   65. -613.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat33dMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((w.v[0])-(    -545.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[1])-(      65.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((w.v[2])-(    -613.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
X
[[ 19.  15.  -5.]
 [  7.   0.  17.]
 [ 17.  12. -19.]]
v
[-15. -14.  10.]
v
[-545.   65. -613.]
*/
fprintf(stdout,"SST_Math_Mat33dMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dMultiplyVectorLocal(&X,&v);
assert(fabs((v.v[0])-(    -545.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[1])-(      65.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((v.v[2])-(    -613.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =        2.000000000000000;
    v.v[1] =        9.000000000000000;
    v.v[2] =       11.000000000000000;
    X.v[0] =       15.000000000000000;
    X.v[1] =      -12.000000000000000;
    X.v[2] =      -14.000000000000000;
    X.v[3] =       -6.000000000000000;
    X.v[4] =       -7.000000000000000;
    X.v[5] =       -6.000000000000000;
    X.v[6] =        6.000000000000000;
    X.v[7] =      -16.000000000000000;
    X.v[8] =        7.000000000000000;
    Y.v[0] =       12.000000000000000;
    Y.v[1] =       18.000000000000000;
    Y.v[2] =        2.000000000000000;
    Y.v[3] =       10.000000000000000;
    Y.v[4] =      -12.000000000000000;
    Y.v[5] =       18.000000000000000;
    Y.v[6] =       11.000000000000000;
    Y.v[7] =       -3.000000000000000;
    Y.v[8] =       13.000000000000000;
fprintf(stdout,"SST_Math_Mat33dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabs((A.v[0])-(      15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[3])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[6])-(     -14.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[1])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[4])-(      -7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[7])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[2])-(       6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[5])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((A.v[8])-(       7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat33dTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33dTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33dTransposeLocal(&X);
assert(fabs((X.v[0])-(      15.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(     -12.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(     -14.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(      -7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(      -6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(       6.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(     -16.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(       7.000000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
/*
[[-0.63105474 -0.76871053  0.10418269]
 [ 0.50484379 -0.50893357 -0.69722261]
 [ 0.58898443 -0.38738965  0.70924369]]
[[  1.00000000e+00  -1.11022302e-16  -5.55111512e-17]
 [ -1.11022302e-16   1.00000000e+00  -1.66533454e-16]
 [ -5.55111512e-17  -1.66533454e-16   1.00000000e+00]]
*/
X.v[0] = (double)      -0.631054742867507;
X.v[3] = (double)      -0.768710530027031;
X.v[6] = (double)       0.104182688245145;
X.v[1] = (double)       0.504843794294005;
X.v[4] = (double)      -0.508933572401668;
X.v[7] = (double)      -0.697222605948278;
X.v[2] = (double)       0.588984426676340;
X.v[5] = (double)      -0.387389648684675;
X.v[8] = (double)       0.709243685361179;
fprintf(stdout,"SST_Math_Mat33dTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33dTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat33dMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat33dMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat33dCheckOrthonormal(&X));
X.v[0] = (double)       1.000000000000000;
X.v[3] = (double)       0.000000000000000;
X.v[6] = (double)       0.000000000000000;
X.v[1] = (double)       0.000000000000000;
X.v[4] = (double)       1.000000000000000;
X.v[7] = (double)       0.000000000000000;
X.v[2] = (double)       0.000000000000000;
X.v[5] = (double)       0.000000000000000;
X.v[8] = (double)       1.000000000000000;
/* Check Positive Test */
assert(SST_Math_Mat33dCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] =      -12.000000000000000;
    v.v[1] =       18.000000000000000;
    v.v[2] =      -14.000000000000000;
    X.v[0] =        9.000000000000000;
    X.v[1] =       14.000000000000000;
    X.v[2] =       12.000000000000000;
    X.v[3] =       -7.000000000000000;
    X.v[4] =        1.000000000000000;
    X.v[5] =      -15.000000000000000;
    X.v[6] =       12.000000000000000;
    X.v[7] =      -10.000000000000000;
    X.v[8] =      -18.000000000000000;
    Y.v[0] =       -3.000000000000000;
    Y.v[1] =       -5.000000000000000;
    Y.v[2] =       -4.000000000000000;
    Y.v[3] =      -14.000000000000000;
    Y.v[4] =       14.000000000000000;
    Y.v[5] =      -12.000000000000000;
    Y.v[6] =        4.000000000000000;
    Y.v[7] =        8.000000000000000;
    Y.v[8] =       11.000000000000000;
/*
[[ 0.03294118  0.06       -0.01137255]
 [-0.02588235  0.06       -0.05058824]
 [ 0.04352941 -0.01       -0.02098039]]
*/
fprintf(stdout,"SST_Math_Mat33dInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat33dInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",0,2,B.v[2]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,0,B.v[3]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,1,B.v[4]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",1,2,B.v[5]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,0,B.v[6]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,1,B.v[7]);
fprintf(stdout,"B[%d][%d] = %24.15lf\n",2,2,B.v[8]);
assert(fabs((B.v[0])-(       0.032941176470588)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[3])-(       0.060000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[6])-(      -0.011372549019608)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[1])-(      -0.025882352941176)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[4])-(       0.060000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[7])-(      -0.050588235294118)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[2])-(       0.043529411764706)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[5])-(      -0.010000000000000)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((B.v[8])-(      -0.020980392156863)) <=100*DBL_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] =        8.000000000000000;
    v.v[1] =      -14.000000000000000;
    v.v[2] =       -3.000000000000000;
    X.v[0] =       12.000000000000000;
    X.v[1] =        3.000000000000000;
    X.v[2] =       12.000000000000000;
    X.v[3] =        9.000000000000000;
    X.v[4] =       17.000000000000000;
    X.v[5] =       10.000000000000000;
    X.v[6] =      -13.000000000000000;
    X.v[7] =        0.000000000000000;
    X.v[8] =        7.000000000000000;
    Y.v[0] =       13.000000000000000;
    Y.v[1] =      -12.000000000000000;
    Y.v[2] =       11.000000000000000;
    Y.v[3] =        1.000000000000000;
    Y.v[4] =       -3.000000000000000;
    Y.v[5] =       -2.000000000000000;
    Y.v[6] =       -2.000000000000000;
    Y.v[7] =       -7.000000000000000;
    Y.v[8] =       16.000000000000000;
/*
[[ 0.03399029 -0.05512711  0.06312482]
 [-0.00599829  0.06855184 -0.01113967]
 [-0.04970009 -0.00342759  0.05055698]]
*/
fprintf(stdout,"SST_Math_Mat33dInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat33dInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat33dInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabs((X.v[0])-(       0.033990288489003)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[3])-(      -0.055127106540988)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[6])-(       0.063124821479577)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[1])-(      -0.005998286203942)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[4])-(       0.068551842330763)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[7])-(      -0.011139674378749)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[2])-(      -0.049700085689803)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[5])-(      -0.003427592116538)) <=100*DBL_EPSILON /* yes this is bad */);
assert(fabs((X.v[8])-(       0.050556983718937)) <=100*DBL_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat33dtest_fxn COMPLETE ====\n");
return 0;
}
