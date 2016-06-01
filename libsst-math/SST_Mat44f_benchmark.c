#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>




int SST_Math_Mat44f_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat44f X; /* 4 x 4 matrix */
SST_Mat44f Y; /* 4 x 4 matrix */
SST_Mat44f A; /* 4 x 4 matrix */
SST_Mat44f B; /* 4 x 4 matrix */
SST_Vec4f v; /* 4 vector */
SST_Vec4f w; /* 4 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = 8.000000f;
    v.v[1] = -5.000000f;
    v.v[2] = 18.000000f;
    v.v[3] = -10.000000f;
    X.v[0] = -12.000000f;
    X.v[1] = -15.000000f;
    X.v[2] = 4.000000f;
    X.v[3] = -15.000000f;
    X.v[4] = -8.000000f;
    X.v[5] = -19.000000f;
    X.v[6] = 18.000000f;
    X.v[7] = 13.000000f;
    X.v[8] = 0.000000f;
    X.v[9] = -16.000000f;
    X.v[10] = 5.000000f;
    X.v[11] = 19.000000f;
    X.v[12] = -18.000000f;
    X.v[13] = -15.000000f;
    X.v[14] = -11.000000f;
    X.v[15] = 14.000000f;
    Y.v[0] = 18.000000f;
    Y.v[1] = -20.000000f;
    Y.v[2] = 6.000000f;
    Y.v[3] = 18.000000f;
    Y.v[4] = -1.000000f;
    Y.v[5] = 7.000000f;
    Y.v[6] = 12.000000f;
    Y.v[7] = -7.000000f;
    Y.v[8] = -4.000000f;
    Y.v[9] = -2.000000f;
    Y.v[10] = 6.000000f;
    Y.v[11] = -17.000000f;
    Y.v[12] = 8.000000f;
    Y.v[13] = -5.000000f;
    Y.v[14] = -1.000000f;
    Y.v[15] = 14.000000f;
SST_Math_Mat44fAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat44fAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[-12.  -8.   0. -18.]
 [-15. -19. -16. -15.]
 [  4.  18.   5. -11.]
 [-15.  13.  19.  14.]]
[[ 18.  -1.  -4.   8.]
 [-20.   7.  -2.  -5.]
 [  6.  12.   6.  -1.]
 [ 18.  -7. -17.  14.]]
[[  6.  -9.  -4. -10.]
 [-35. -12. -18. -20.]
 [ 10.  30.  11. -12.]
 [  3.   6.   2.  28.]]
*/
assert(fabsf((A.v[0])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(-9.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[12])-(-10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(-35.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[9])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[13])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(30.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[10])-(11.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[14])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[11])-(2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[15])-(28.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[-12.  -8.   0. -18.]
 [-15. -19. -16. -15.]
 [  4.  18.   5. -11.]
 [-15.  13.  19.  14.]]
[[ 18.  -1.  -4.   8.]
 [-20.   7.  -2.  -5.]
 [  6.  12.   6.  -1.]
 [ 18.  -7. -17.  14.]]
[[  6.  -9.  -4. -10.]
 [-35. -12. -18. -20.]
 [ 10.  30.  11. -12.]
 [  3.   6.   2.  28.]]
*/
fprintf(stdout,"SST_Math_Mat44fAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fAddLocal(&X,&Y); /* for accuracy */
assert(fabsf((X.v[0])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-9.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(-10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(-35.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(30.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(11.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(-12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(28.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 13.000000f;
    v.v[1] = 0.000000f;
    v.v[2] = -12.000000f;
    v.v[3] = -6.000000f;
    X.v[0] = 14.000000f;
    X.v[1] = 4.000000f;
    X.v[2] = 6.000000f;
    X.v[3] = -13.000000f;
    X.v[4] = 13.000000f;
    X.v[5] = -3.000000f;
    X.v[6] = 19.000000f;
    X.v[7] = -3.000000f;
    X.v[8] = 10.000000f;
    X.v[9] = 17.000000f;
    X.v[10] = -7.000000f;
    X.v[11] = -8.000000f;
    X.v[12] = -10.000000f;
    X.v[13] = 13.000000f;
    X.v[14] = 13.000000f;
    X.v[15] = -9.000000f;
    Y.v[0] = -16.000000f;
    Y.v[1] = -5.000000f;
    Y.v[2] = 11.000000f;
    Y.v[3] = -8.000000f;
    Y.v[4] = -3.000000f;
    Y.v[5] = -8.000000f;
    Y.v[6] = 4.000000f;
    Y.v[7] = -10.000000f;
    Y.v[8] = 14.000000f;
    Y.v[9] = -19.000000f;
    Y.v[10] = -4.000000f;
    Y.v[11] = 11.000000f;
    Y.v[12] = -9.000000f;
    Y.v[13] = -8.000000f;
    Y.v[14] = -12.000000f;
    Y.v[15] = -11.000000f;
/*
[[ 14.  13.  10. -10.]
 [  4.  -3.  17.  13.]
 [  6.  19.  -7.  13.]
 [-13.  -3.  -8.  -9.]]
[[ 28.  26.  20. -20.]
 [  8.  -6.  34.  26.]
 [ 12.  38. -14.  26.]
 [-26.  -6. -16. -18.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyScalar(&X,2.000000f,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(28.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[12])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(8.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[9])-(34.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[13])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[10])-(-14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[14])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[11])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[15])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[ 14.  13.  10. -10.]
 [  4.  -3.  17.  13.]
 [  6.  19.  -7.  13.]
 [-13.  -3.  -8.  -9.]]
[[ 28.  26.  20. -20.]
 [  8.  -6.  34.  26.]
 [ 12.  38. -14.  26.]
 [-26.  -6. -16. -18.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyScalarLocal(&A,2.000000f);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fMultiplyScalarLocal(&X,2.000000f);
assert(fabsf((X.v[0])-(28.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(8.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(34.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(12.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(38.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(-14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-26.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(-16.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = 0.000000f;
    v.v[1] = -12.000000f;
    v.v[2] = -11.000000f;
    v.v[3] = 4.000000f;
    X.v[0] = -20.000000f;
    X.v[1] = 12.000000f;
    X.v[2] = -12.000000f;
    X.v[3] = 12.000000f;
    X.v[4] = 7.000000f;
    X.v[5] = -10.000000f;
    X.v[6] = 17.000000f;
    X.v[7] = -5.000000f;
    X.v[8] = -6.000000f;
    X.v[9] = 19.000000f;
    X.v[10] = 19.000000f;
    X.v[11] = -18.000000f;
    X.v[12] = 7.000000f;
    X.v[13] = -10.000000f;
    X.v[14] = -18.000000f;
    X.v[15] = -11.000000f;
    Y.v[0] = 10.000000f;
    Y.v[1] = 10.000000f;
    Y.v[2] = 14.000000f;
    Y.v[3] = 2.000000f;
    Y.v[4] = -13.000000f;
    Y.v[5] = 17.000000f;
    Y.v[6] = -14.000000f;
    Y.v[7] = 4.000000f;
    Y.v[8] = 9.000000f;
    Y.v[9] = 19.000000f;
    Y.v[10] = 17.000000f;
    Y.v[11] = 5.000000f;
    Y.v[12] = -17.000000f;
    Y.v[13] = -5.000000f;
    Y.v[14] = 13.000000f;
    Y.v[15] = 4.000000f;
/*
[[-20.   7.  -6.   7.]
 [ 12. -10.  19. -10.]
 [-12.  17.  19. -18.]
 [ 12.  -5. -18. -11.]]
[[ 10. -13.   9. -17.]
 [ 10.  17.  19.  -5.]
 [ 14. -14.  17.  13.]
 [  2.   4.   5.   4.]]
[[-200.  -91.  -54. -119.]
 [ 120. -170.  361.   50.]
 [-168. -238.  323. -234.]
 [  24.  -20.  -90.  -44.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(-200.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(-91.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(-54.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[12])-(-119.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(120.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-170.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[9])-(361.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[13])-(50.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(-168.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-238.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[10])-(323.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[14])-(-234.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(24.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[11])-(-90.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[15])-(-44.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[-20.   7.  -6.   7.]
 [ 12. -10.  19. -10.]
 [-12.  17.  19. -18.]
 [ 12.  -5. -18. -11.]]
[[ 10. -13.   9. -17.]
 [ 10.  17.  19.  -5.]
 [ 14. -14.  17.  13.]
 [  2.   4.   5.   4.]]
[[-200.  -91.  -54. -119.]
 [ 120. -170.  361.   50.]
 [-168. -238.  323. -234.]
 [  24.  -20.  -90.  -44.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fMultiplyElementwiseLocal(&X,&Y);
assert(fabsf((X.v[0])-(-200.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-91.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-54.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(-119.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(120.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-170.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(361.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(50.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(-168.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-238.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(323.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(-234.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(24.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-20.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(-90.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(-44.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -13.000000f;
    v.v[1] = -12.000000f;
    v.v[2] = -20.000000f;
    v.v[3] = 8.000000f;
    X.v[0] = 2.000000f;
    X.v[1] = 11.000000f;
    X.v[2] = 4.000000f;
    X.v[3] = -2.000000f;
    X.v[4] = 10.000000f;
    X.v[5] = 6.000000f;
    X.v[6] = -6.000000f;
    X.v[7] = -17.000000f;
    X.v[8] = -1.000000f;
    X.v[9] = 3.000000f;
    X.v[10] = 9.000000f;
    X.v[11] = 8.000000f;
    X.v[12] = -4.000000f;
    X.v[13] = -3.000000f;
    X.v[14] = -10.000000f;
    X.v[15] = 18.000000f;
    Y.v[0] = 12.000000f;
    Y.v[1] = -2.000000f;
    Y.v[2] = 5.000000f;
    Y.v[3] = -1.000000f;
    Y.v[4] = -12.000000f;
    Y.v[5] = 6.000000f;
    Y.v[6] = 2.000000f;
    Y.v[7] = -3.000000f;
    Y.v[8] = -13.000000f;
    Y.v[9] = 9.000000f;
    Y.v[10] = 5.000000f;
    Y.v[11] = 2.000000f;
    Y.v[12] = 16.000000f;
    Y.v[13] = -13.000000f;
    Y.v[14] = 14.000000f;
    Y.v[15] = -5.000000f;
/*
X
[[  2.  10.  -1.  -4.]
 [ 11.   6.   3.  -3.]
 [  4.  -6.   9. -10.]
 [ -2. -17.   8.  18.]]
Y
[[ 12. -12. -13.  16.]
 [ -2.   6.   9. -13.]
 [  5.   2.   5.  14.]
 [ -1.  -3.   2.  -5.]]
[[   3.   46.   51.  -92.]
 [ 138.  -81.  -80.  155.]
 [ 115.  -36.  -81.  318.]
 [  32. -116.  -51.  211.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(46.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(51.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[12])-(-92.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(138.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(-81.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[9])-(-80.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[13])-(155.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(115.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-36.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[10])-(-81.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[14])-(318.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(32.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(-116.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[11])-(-51.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[15])-(211.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[  2.  10.  -1.  -4.]
 [ 11.   6.   3.  -3.]
 [  4.  -6.   9. -10.]
 [ -2. -17.   8.  18.]]
Y
[[ 12. -12. -13.  16.]
 [ -2.   6.   9. -13.]
 [  5.   2.   5.  14.]
 [ -1.  -3.   2.  -5.]]
X
[[   3.   46.   51.  -92.]
 [ 138.  -81.  -80.  155.]
 [ 115.  -36.  -81.  318.]
 [  32. -116.  -51.  211.]]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fMultiplyMatrixLocal(&X,&Y);
assert(fabsf((X.v[0])-(3.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(46.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(51.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(-92.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(138.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(-81.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(-80.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(155.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(115.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-36.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(-81.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(318.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(32.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(-116.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(-51.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(211.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -14.000000f;
    v.v[1] = -16.000000f;
    v.v[2] = 15.000000f;
    v.v[3] = -20.000000f;
    X.v[0] = -14.000000f;
    X.v[1] = -20.000000f;
    X.v[2] = 11.000000f;
    X.v[3] = 18.000000f;
    X.v[4] = -15.000000f;
    X.v[5] = 18.000000f;
    X.v[6] = -2.000000f;
    X.v[7] = -11.000000f;
    X.v[8] = -4.000000f;
    X.v[9] = 4.000000f;
    X.v[10] = -16.000000f;
    X.v[11] = -12.000000f;
    X.v[12] = 13.000000f;
    X.v[13] = 9.000000f;
    X.v[14] = -6.000000f;
    X.v[15] = 0.000000f;
    Y.v[0] = 3.000000f;
    Y.v[1] = -8.000000f;
    Y.v[2] = 16.000000f;
    Y.v[3] = -4.000000f;
    Y.v[4] = -15.000000f;
    Y.v[5] = 2.000000f;
    Y.v[6] = 13.000000f;
    Y.v[7] = 18.000000f;
    Y.v[8] = 7.000000f;
    Y.v[9] = -13.000000f;
    Y.v[10] = -6.000000f;
    Y.v[11] = 6.000000f;
    Y.v[12] = -19.000000f;
    Y.v[13] = -1.000000f;
    Y.v[14] = 1.000000f;
    Y.v[15] = 10.000000f;
/*
X
[[-14. -15.  -4.  13.]
 [-20.  18.   4.   9.]
 [ 11.  -2. -16.  -6.]
 [ 18. -11. -12.   0.]]
v
[-14. -16.  15. -20.]
w
[ 116. -128. -242. -256.]
*/
i=0;
fprintf(stdout,"SST_Math_Mat44fMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((w.v[0])-(116.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[1])-(-128.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[2])-(-242.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((w.v[3])-(-256.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
X
[[-14. -15.  -4.  13.]
 [-20.  18.   4.   9.]
 [ 11.  -2. -16.  -6.]
 [ 18. -11. -12.   0.]]
v
[-14. -16.  15. -20.]
v
[ 116. -128. -242. -256.]
*/
fprintf(stdout,"SST_Math_Mat44fMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fMultiplyVectorLocal(&X,&v);
assert(fabsf((v.v[0])-(116.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[1])-(-128.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[2])-(-242.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((v.v[3])-(-256.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -8.000000f;
    v.v[1] = 10.000000f;
    v.v[2] = 4.000000f;
    v.v[3] = 5.000000f;
    X.v[0] = -4.000000f;
    X.v[1] = -6.000000f;
    X.v[2] = -18.000000f;
    X.v[3] = -15.000000f;
    X.v[4] = 14.000000f;
    X.v[5] = 13.000000f;
    X.v[6] = -15.000000f;
    X.v[7] = 11.000000f;
    X.v[8] = 14.000000f;
    X.v[9] = -2.000000f;
    X.v[10] = 0.000000f;
    X.v[11] = 10.000000f;
    X.v[12] = -1.000000f;
    X.v[13] = 4.000000f;
    X.v[14] = 9.000000f;
    X.v[15] = 6.000000f;
    Y.v[0] = 0.000000f;
    Y.v[1] = -8.000000f;
    Y.v[2] = -9.000000f;
    Y.v[3] = 2.000000f;
    Y.v[4] = 18.000000f;
    Y.v[5] = 16.000000f;
    Y.v[6] = 18.000000f;
    Y.v[7] = 9.000000f;
    Y.v[8] = 13.000000f;
    Y.v[9] = -6.000000f;
    Y.v[10] = 1.000000f;
    Y.v[11] = 15.000000f;
    Y.v[12] = 1.000000f;
    Y.v[13] = 4.000000f;
    Y.v[14] = 5.000000f;
    Y.v[15] = -14.000000f;
fprintf(stdout,"SST_Math_Mat44fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert(fabsf((A.v[0])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[4])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[8])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[12])-(-15.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[1])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[5])-(13.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[9])-(-15.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[13])-(11.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[2])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[6])-(-2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[10])-(0.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[14])-(10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[3])-(-1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[7])-(4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[11])-(9.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((A.v[15])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"SST_Math_Mat44fTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44fTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44fTransposeLocal(&X);
assert(fabsf((X.v[0])-(-4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(-18.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(-15.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(13.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(-15.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(11.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(14.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(-2.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(0.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(10.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(-1.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(4.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(9.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(6.000000f)) <=100*FLT_EPSILON /* yes this is bad */);
/*
[[-0.16316341 -0.51831281  0.642591   -0.54019099]
 [-0.24474511 -0.47715011 -0.75842094 -0.37043935]
 [-0.73423529  0.59570372  0.02088371 -0.32496071]
 [-0.61186278 -0.38576764  0.10695031  0.68217951]]
[[  1.00000000e+00   0.00000000e+00   7.45058060e-09   0.00000000e+00]
 [  0.00000000e+00   1.00000000e+00   7.45058060e-09  -2.98023224e-08]
 [  7.45058060e-09   7.45058060e-09   1.00000000e+00   2.98023224e-08]
 [  0.00000000e+00  -2.98023224e-08   2.98023224e-08   1.00000000e+00]]
*/
X.v[0] = (float)-0.163163f;
X.v[4] = (float)-0.518313f;
X.v[8] = (float)0.642591f;
X.v[12] = (float)-0.540191f;
X.v[1] = (float)-0.244745f;
X.v[5] = (float)-0.477150f;
X.v[9] = (float)-0.758421f;
X.v[13] = (float)-0.370439f;
X.v[2] = (float)-0.734235f;
X.v[6] = (float)0.595704f;
X.v[10] = (float)0.020884f;
X.v[14] = (float)-0.324961f;
X.v[3] = (float)-0.611863f;
X.v[7] = (float)-0.385768f;
X.v[11] = (float)0.106950f;
X.v[15] = (float)0.682180f;
fprintf(stdout,"SST_Math_Mat44fTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44fTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat44fMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat44fMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Negative Test */
assert(!SST_Math_Mat44fCheckOrthonormal(&X));
X.v[0] = (float)1.000000f;
X.v[4] = (float)0.000000f;
X.v[8] = (float)0.000000f;
X.v[12] = (float)0.000000f;
X.v[1] = (float)0.000000f;
X.v[5] = (float)1.000000f;
X.v[9] = (float)0.000000f;
X.v[13] = (float)0.000000f;
X.v[2] = (float)0.000000f;
X.v[6] = (float)0.000000f;
X.v[10] = (float)1.000000f;
X.v[14] = (float)0.000000f;
X.v[3] = (float)0.000000f;
X.v[7] = (float)0.000000f;
X.v[11] = (float)0.000000f;
X.v[15] = (float)1.000000f;
/* Check Positive Test */
assert(SST_Math_Mat44fCheckOrthonormal(&X));
/* Resetting test vectors / mats */
    v.v[0] = 12.000000f;
    v.v[1] = 10.000000f;
    v.v[2] = 8.000000f;
    v.v[3] = -2.000000f;
    X.v[0] = -7.000000f;
    X.v[1] = -12.000000f;
    X.v[2] = -6.000000f;
    X.v[3] = -16.000000f;
    X.v[4] = -18.000000f;
    X.v[5] = 7.000000f;
    X.v[6] = -2.000000f;
    X.v[7] = 17.000000f;
    X.v[8] = 9.000000f;
    X.v[9] = 3.000000f;
    X.v[10] = -10.000000f;
    X.v[11] = -2.000000f;
    X.v[12] = -16.000000f;
    X.v[13] = -9.000000f;
    X.v[14] = -2.000000f;
    X.v[15] = 6.000000f;
    Y.v[0] = -7.000000f;
    Y.v[1] = 6.000000f;
    Y.v[2] = -15.000000f;
    Y.v[3] = 9.000000f;
    Y.v[4] = -17.000000f;
    Y.v[5] = -5.000000f;
    Y.v[6] = 15.000000f;
    Y.v[7] = -13.000000f;
    Y.v[8] = 1.000000f;
    Y.v[9] = -12.000000f;
    Y.v[10] = -5.000000f;
    Y.v[11] = -4.000000f;
    Y.v[12] = -10.000000f;
    Y.v[13] = -18.000000f;
    Y.v[14] = 13.000000f;
    Y.v[15] = -17.000000f;
/*
[[-0.04568416  0.04019328 -0.01570393 -0.06676916]
 [-0.050604    0.07529102 -0.01739512 -0.02780584]
 [ 0.0311443  -0.01682407 -0.08304415  0.03013398]
 [ 0.03193499 -0.11175049 -0.02027235  0.07744344]]
*/
fprintf(stdout,"SST_Math_Mat44fInvert(X,B)\n");
t0 = rdtsc();
SST_Math_Mat44fInvert(&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"B[%d][%d] = %ff\n",0,0,B.v[0]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,1,B.v[1]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,2,B.v[2]);
fprintf(stdout,"B[%d][%d] = %ff\n",0,3,B.v[3]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,0,B.v[4]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,1,B.v[5]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,2,B.v[6]);
fprintf(stdout,"B[%d][%d] = %ff\n",1,3,B.v[7]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,0,B.v[8]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,1,B.v[9]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,2,B.v[10]);
fprintf(stdout,"B[%d][%d] = %ff\n",2,3,B.v[11]);
fprintf(stdout,"B[%d][%d] = %ff\n",3,0,B.v[12]);
fprintf(stdout,"B[%d][%d] = %ff\n",3,1,B.v[13]);
fprintf(stdout,"B[%d][%d] = %ff\n",3,2,B.v[14]);
fprintf(stdout,"B[%d][%d] = %ff\n",3,3,B.v[15]);
assert(fabsf((B.v[0])-(-0.045684f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[4])-(0.040193f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[8])-(-0.015704f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[12])-(-0.066769f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[1])-(-0.050604f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[5])-(0.075291f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[9])-(-0.017395f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[13])-(-0.027806f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[2])-(0.031144f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[6])-(-0.016824f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[10])-(-0.083044f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[14])-(0.030134f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[3])-(0.031935f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[7])-(-0.111750f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[11])-(-0.020272f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((B.v[15])-(0.077443f)) <=100*FLT_EPSILON /* yes this is bad */);
/* Resetting test vectors / mats */
    v.v[0] = -5.000000f;
    v.v[1] = 4.000000f;
    v.v[2] = -15.000000f;
    v.v[3] = 8.000000f;
    X.v[0] = -20.000000f;
    X.v[1] = -1.000000f;
    X.v[2] = -19.000000f;
    X.v[3] = 10.000000f;
    X.v[4] = 19.000000f;
    X.v[5] = -17.000000f;
    X.v[6] = 5.000000f;
    X.v[7] = 3.000000f;
    X.v[8] = -20.000000f;
    X.v[9] = 17.000000f;
    X.v[10] = -19.000000f;
    X.v[11] = -8.000000f;
    X.v[12] = -3.000000f;
    X.v[13] = 4.000000f;
    X.v[14] = 0.000000f;
    X.v[15] = 9.000000f;
    Y.v[0] = -3.000000f;
    Y.v[1] = -20.000000f;
    Y.v[2] = 8.000000f;
    Y.v[3] = 1.000000f;
    Y.v[4] = 3.000000f;
    Y.v[5] = 6.000000f;
    Y.v[6] = 9.000000f;
    Y.v[7] = -15.000000f;
    Y.v[8] = -19.000000f;
    Y.v[9] = -18.000000f;
    Y.v[10] = -16.000000f;
    Y.v[11] = 12.000000f;
    Y.v[12] = -14.000000f;
    Y.v[13] = 14.000000f;
    Y.v[14] = 2.000000f;
    Y.v[15] = 0.000000f;
/*
[[-0.04497354 -0.04884005  0.000814    0.00671551]
 [ 0.09047619  0.02087912 -0.08534799  0.02087912]
 [ 0.06878307  0.05433455 -0.07590558 -0.001221  ]
 [ 0.08095238  0.0956044  -0.03992674  0.0956044 ]]
*/
fprintf(stdout,"SST_Math_Mat44fInvert(X,B)\n");
fflush(stdout);
fprintf(stdout,"SST_Math_Mat44fInvertLocal(X,B)\n");
t0 = rdtsc();
SST_Math_Mat44fInvertLocal(&X);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fflush(stdout);
assert(fabsf((X.v[0])-(-0.044974f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[4])-(-0.048840f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[8])-(0.000814f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[12])-(0.006716f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[1])-(0.090476f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[5])-(0.020879f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[9])-(-0.085348f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[13])-(0.020879f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[2])-(0.068783f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[6])-(0.054335f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[10])-(-0.075906f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[14])-(-0.001221f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[3])-(0.080952f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[7])-(0.095604f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[11])-(-0.039927f)) <=100*FLT_EPSILON /* yes this is bad */);
assert(fabsf((X.v[15])-(0.095604f)) <=100*FLT_EPSILON /* yes this is bad */);
fprintf(stdout,"\n==== SST_Math_Mat44ftest_fxn COMPLETE ====\n");
return 0;
}
