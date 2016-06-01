#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>




int SST_Math_Mat22u_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat22u X; /* 2 x 2 matrix */
SST_Mat22u Y; /* 2 x 2 matrix */
SST_Mat22u A; /* 2 x 2 matrix */
SST_Mat22u B; /* 2 x 2 matrix */
SST_Vec2u v; /* 2 vector */
SST_Vec2u w; /* 2 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = 7;
    v.v[1] = 16;
    X.v[0] = 2;
    X.v[1] = 8;
    X.v[2] = 15;
    X.v[3] = 17;
    Y.v[0] = 15;
    Y.v[1] = 6;
    Y.v[2] = 15;
    Y.v[3] = 38;
SST_Math_Mat22uAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat22uAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ 2 15]
 [ 8 17]]
[[15 15]
 [ 6 38]]
[[17 30]
 [14 55]]
*/
assert((A.v[0])==(17));
assert((A.v[2])==(30));
assert((A.v[1])==(14));
assert((A.v[3])==(55));
/*
[[ 2 15]
 [ 8 17]]
[[15 15]
 [ 6 38]]
[[17 30]
 [14 55]]
*/
fprintf(stdout,"SST_Math_Mat22uAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(17));
assert((X.v[2])==(30));
assert((X.v[1])==(14));
assert((X.v[3])==(55));
/* Resetting test vectors / mats */
    v.v[0] = 30;
    v.v[1] = 15;
    X.v[0] = 6;
    X.v[1] = 13;
    X.v[2] = 26;
    X.v[3] = 33;
    Y.v[0] = 13;
    Y.v[1] = 32;
    Y.v[2] = 15;
    Y.v[3] = 33;
/*
[[ 6 26]
 [13 33]]
[[12 52]
 [26 66]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(12));
assert((A.v[2])==(52));
assert((A.v[1])==(26));
assert((A.v[3])==(66));
/*
[[ 6 26]
 [13 33]]
[[12 52]
 [26 66]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uMultiplyScalarLocal(&X,2);
assert((X.v[0])==(12));
assert((X.v[2])==(52));
assert((X.v[1])==(26));
assert((X.v[3])==(66));
/* Resetting test vectors / mats */
    v.v[0] = 10;
    v.v[1] = 33;
    X.v[0] = 37;
    X.v[1] = 9;
    X.v[2] = 15;
    X.v[3] = 8;
    Y.v[0] = 34;
    Y.v[1] = 13;
    Y.v[2] = 28;
    Y.v[3] = 16;
/*
[[37 15]
 [ 9  8]]
[[34 28]
 [13 16]]
[[1258  420]
 [ 117  128]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(1258));
assert((A.v[2])==(420));
assert((A.v[1])==(117));
assert((A.v[3])==(128));
/*
[[37 15]
 [ 9  8]]
[[34 28]
 [13 16]]
[[1258  420]
 [ 117  128]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(1258));
assert((X.v[2])==(420));
assert((X.v[1])==(117));
assert((X.v[3])==(128));
/* Resetting test vectors / mats */
    v.v[0] = 1;
    v.v[1] = 22;
    X.v[0] = 10;
    X.v[1] = 29;
    X.v[2] = 13;
    X.v[3] = 38;
    Y.v[0] = 10;
    Y.v[1] = 4;
    Y.v[2] = 15;
    Y.v[3] = 3;
/*
X
[[10 13]
 [29 38]]
Y
[[10 15]
 [ 4  3]]
[[152 189]
 [442 549]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(152));
assert((A.v[2])==(189));
assert((A.v[1])==(442));
assert((A.v[3])==(549));
/*
X
[[10 13]
 [29 38]]
Y
[[10 15]
 [ 4  3]]
X
[[152 189]
 [442 549]]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(152));
assert((X.v[2])==(189));
assert((X.v[1])==(442));
assert((X.v[3])==(549));
/* Resetting test vectors / mats */
    v.v[0] = 8;
    v.v[1] = 3;
    X.v[0] = 27;
    X.v[1] = 36;
    X.v[2] = 5;
    X.v[3] = 20;
    Y.v[0] = 32;
    Y.v[1] = 31;
    Y.v[2] = 26;
    Y.v[3] = 1;
/*
X
[[27  5]
 [36 20]]
v
[8 3]
w
[231 348]
*/
i=0;
fprintf(stdout,"SST_Math_Mat22uMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(231));
assert((w.v[1])==(348));
/*
X
[[27  5]
 [36 20]]
v
[8 3]
v
[231 348]
*/
fprintf(stdout,"SST_Math_Mat22uMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(231));
assert((v.v[1])==(348));
/* Resetting test vectors / mats */
    v.v[0] = 27;
    v.v[1] = 37;
    X.v[0] = 35;
    X.v[1] = 17;
    X.v[2] = 16;
    X.v[3] = 1;
    Y.v[0] = 32;
    Y.v[1] = 8;
    Y.v[2] = 0;
    Y.v[3] = 33;
fprintf(stdout,"SST_Math_Mat22uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(35));
assert((A.v[2])==(17));
assert((A.v[1])==(16));
assert((A.v[3])==(1));
fprintf(stdout,"SST_Math_Mat22uTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat22uTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat22uTransposeLocal(&X);
assert((X.v[0])==(35));
assert((X.v[2])==(17));
assert((X.v[1])==(16));
assert((X.v[3])==(1));
/*
[[-0.89950816 -0.43690396]
 [-0.43690396  0.89950816]]
[[ 1.  0.]
 [ 0.  1.]]
*/
X.v[0] = (unsigned int)0;
X.v[2] = (unsigned int)0;
X.v[1] = (unsigned int)0;
X.v[3] = (unsigned int)0;
fprintf(stdout,"SST_Math_Mat22uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat22uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat22uMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat22uMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"\n==== SST_Math_Mat22utest_fxn COMPLETE ====\n");
return 0;
}
