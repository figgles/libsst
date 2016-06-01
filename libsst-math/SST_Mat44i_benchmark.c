#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>




int SST_Math_Mat44i_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat44i X; /* 4 x 4 matrix */
SST_Mat44i Y; /* 4 x 4 matrix */
SST_Mat44i A; /* 4 x 4 matrix */
SST_Mat44i B; /* 4 x 4 matrix */
SST_Vec4i v; /* 4 vector */
SST_Vec4i w; /* 4 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = 16;
    v.v[1] = 7;
    v.v[2] = 11;
    v.v[3] = -12;
    X.v[0] = -7;
    X.v[1] = 6;
    X.v[2] = 4;
    X.v[3] = 19;
    X.v[4] = -7;
    X.v[5] = 14;
    X.v[6] = -15;
    X.v[7] = -17;
    X.v[8] = -1;
    X.v[9] = -4;
    X.v[10] = 1;
    X.v[11] = 5;
    X.v[12] = 4;
    X.v[13] = 3;
    X.v[14] = -4;
    X.v[15] = 5;
    Y.v[0] = -13;
    Y.v[1] = 7;
    Y.v[2] = 10;
    Y.v[3] = -2;
    Y.v[4] = 13;
    Y.v[5] = 5;
    Y.v[6] = 15;
    Y.v[7] = -15;
    Y.v[8] = -5;
    Y.v[9] = 5;
    Y.v[10] = -17;
    Y.v[11] = 7;
    Y.v[12] = 19;
    Y.v[13] = 17;
    Y.v[14] = 15;
    Y.v[15] = -9;
SST_Math_Mat44iAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat44iAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ -7  -7  -1   4]
 [  6  14  -4   3]
 [  4 -15   1  -4]
 [ 19 -17   5   5]]
[[-13  13  -5  19]
 [  7   5   5  17]
 [ 10  15 -17  15]
 [ -2 -15   7  -9]]
[[-20   6  -6  23]
 [ 13  19   1  20]
 [ 14   0 -16  11]
 [ 17 -32  12  -4]]
*/
assert((A.v[0])==(-20));
assert((A.v[4])==(6));
assert((A.v[8])==(-6));
assert((A.v[12])==(23));
assert((A.v[1])==(13));
assert((A.v[5])==(19));
assert((A.v[9])==(1));
assert((A.v[13])==(20));
assert((A.v[2])==(14));
assert((A.v[6])==(0));
assert((A.v[10])==(-16));
assert((A.v[14])==(11));
assert((A.v[3])==(17));
assert((A.v[7])==(-32));
assert((A.v[11])==(12));
assert((A.v[15])==(-4));
/*
[[ -7  -7  -1   4]
 [  6  14  -4   3]
 [  4 -15   1  -4]
 [ 19 -17   5   5]]
[[-13  13  -5  19]
 [  7   5   5  17]
 [ 10  15 -17  15]
 [ -2 -15   7  -9]]
[[-20   6  -6  23]
 [ 13  19   1  20]
 [ 14   0 -16  11]
 [ 17 -32  12  -4]]
*/
fprintf(stdout,"SST_Math_Mat44iAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(-20));
assert((X.v[4])==(6));
assert((X.v[8])==(-6));
assert((X.v[12])==(23));
assert((X.v[1])==(13));
assert((X.v[5])==(19));
assert((X.v[9])==(1));
assert((X.v[13])==(20));
assert((X.v[2])==(14));
assert((X.v[6])==(0));
assert((X.v[10])==(-16));
assert((X.v[14])==(11));
assert((X.v[3])==(17));
assert((X.v[7])==(-32));
assert((X.v[11])==(12));
assert((X.v[15])==(-4));
/* Resetting test vectors / mats */
    v.v[0] = -15;
    v.v[1] = -16;
    v.v[2] = -2;
    v.v[3] = -16;
    X.v[0] = -16;
    X.v[1] = -11;
    X.v[2] = 15;
    X.v[3] = -19;
    X.v[4] = 1;
    X.v[5] = -12;
    X.v[6] = 10;
    X.v[7] = -4;
    X.v[8] = -18;
    X.v[9] = 10;
    X.v[10] = 3;
    X.v[11] = -4;
    X.v[12] = -11;
    X.v[13] = 7;
    X.v[14] = 17;
    X.v[15] = 3;
    Y.v[0] = 11;
    Y.v[1] = -12;
    Y.v[2] = 18;
    Y.v[3] = -18;
    Y.v[4] = -4;
    Y.v[5] = -3;
    Y.v[6] = -4;
    Y.v[7] = -14;
    Y.v[8] = -3;
    Y.v[9] = 7;
    Y.v[10] = -11;
    Y.v[11] = -11;
    Y.v[12] = -5;
    Y.v[13] = -15;
    Y.v[14] = 2;
    Y.v[15] = 0;
/*
[[-16   1 -18 -11]
 [-11 -12  10   7]
 [ 15  10   3  17]
 [-19  -4  -4   3]]
[[-32   2 -36 -22]
 [-22 -24  20  14]
 [ 30  20   6  34]
 [-38  -8  -8   6]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(-32));
assert((A.v[4])==(2));
assert((A.v[8])==(-36));
assert((A.v[12])==(-22));
assert((A.v[1])==(-22));
assert((A.v[5])==(-24));
assert((A.v[9])==(20));
assert((A.v[13])==(14));
assert((A.v[2])==(30));
assert((A.v[6])==(20));
assert((A.v[10])==(6));
assert((A.v[14])==(34));
assert((A.v[3])==(-38));
assert((A.v[7])==(-8));
assert((A.v[11])==(-8));
assert((A.v[15])==(6));
/*
[[-16   1 -18 -11]
 [-11 -12  10   7]
 [ 15  10   3  17]
 [-19  -4  -4   3]]
[[-32   2 -36 -22]
 [-22 -24  20  14]
 [ 30  20   6  34]
 [-38  -8  -8   6]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iMultiplyScalarLocal(&X,2);
assert((X.v[0])==(-32));
assert((X.v[4])==(2));
assert((X.v[8])==(-36));
assert((X.v[12])==(-22));
assert((X.v[1])==(-22));
assert((X.v[5])==(-24));
assert((X.v[9])==(20));
assert((X.v[13])==(14));
assert((X.v[2])==(30));
assert((X.v[6])==(20));
assert((X.v[10])==(6));
assert((X.v[14])==(34));
assert((X.v[3])==(-38));
assert((X.v[7])==(-8));
assert((X.v[11])==(-8));
assert((X.v[15])==(6));
/* Resetting test vectors / mats */
    v.v[0] = 11;
    v.v[1] = -13;
    v.v[2] = -2;
    v.v[3] = 11;
    X.v[0] = 0;
    X.v[1] = 4;
    X.v[2] = 16;
    X.v[3] = 8;
    X.v[4] = -20;
    X.v[5] = -15;
    X.v[6] = 13;
    X.v[7] = -9;
    X.v[8] = -18;
    X.v[9] = -12;
    X.v[10] = 8;
    X.v[11] = -18;
    X.v[12] = -4;
    X.v[13] = 11;
    X.v[14] = -14;
    X.v[15] = 15;
    Y.v[0] = -15;
    Y.v[1] = -5;
    Y.v[2] = -7;
    Y.v[3] = 19;
    Y.v[4] = -1;
    Y.v[5] = 16;
    Y.v[6] = -4;
    Y.v[7] = -12;
    Y.v[8] = -17;
    Y.v[9] = -7;
    Y.v[10] = 0;
    Y.v[11] = -3;
    Y.v[12] = -9;
    Y.v[13] = -17;
    Y.v[14] = -14;
    Y.v[15] = -14;
/*
[[  0 -20 -18  -4]
 [  4 -15 -12  11]
 [ 16  13   8 -14]
 [  8  -9 -18  15]]
[[-15  -1 -17  -9]
 [ -5  16  -7 -17]
 [ -7  -4   0 -14]
 [ 19 -12  -3 -14]]
[[   0   20  306   36]
 [ -20 -240   84 -187]
 [-112  -52    0  196]
 [ 152  108   54 -210]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(0));
assert((A.v[4])==(20));
assert((A.v[8])==(306));
assert((A.v[12])==(36));
assert((A.v[1])==(-20));
assert((A.v[5])==(-240));
assert((A.v[9])==(84));
assert((A.v[13])==(-187));
assert((A.v[2])==(-112));
assert((A.v[6])==(-52));
assert((A.v[10])==(0));
assert((A.v[14])==(196));
assert((A.v[3])==(152));
assert((A.v[7])==(108));
assert((A.v[11])==(54));
assert((A.v[15])==(-210));
/*
[[  0 -20 -18  -4]
 [  4 -15 -12  11]
 [ 16  13   8 -14]
 [  8  -9 -18  15]]
[[-15  -1 -17  -9]
 [ -5  16  -7 -17]
 [ -7  -4   0 -14]
 [ 19 -12  -3 -14]]
[[   0   20  306   36]
 [ -20 -240   84 -187]
 [-112  -52    0  196]
 [ 152  108   54 -210]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(0));
assert((X.v[4])==(20));
assert((X.v[8])==(306));
assert((X.v[12])==(36));
assert((X.v[1])==(-20));
assert((X.v[5])==(-240));
assert((X.v[9])==(84));
assert((X.v[13])==(-187));
assert((X.v[2])==(-112));
assert((X.v[6])==(-52));
assert((X.v[10])==(0));
assert((X.v[14])==(196));
assert((X.v[3])==(152));
assert((X.v[7])==(108));
assert((X.v[11])==(54));
assert((X.v[15])==(-210));
/* Resetting test vectors / mats */
    v.v[0] = -14;
    v.v[1] = -14;
    v.v[2] = 12;
    v.v[3] = -12;
    X.v[0] = -16;
    X.v[1] = -19;
    X.v[2] = 6;
    X.v[3] = 19;
    X.v[4] = 14;
    X.v[5] = 10;
    X.v[6] = 16;
    X.v[7] = -17;
    X.v[8] = -10;
    X.v[9] = -5;
    X.v[10] = -8;
    X.v[11] = -20;
    X.v[12] = 14;
    X.v[13] = -12;
    X.v[14] = 19;
    X.v[15] = -2;
    Y.v[0] = -10;
    Y.v[1] = 6;
    Y.v[2] = -6;
    Y.v[3] = -17;
    Y.v[4] = -8;
    Y.v[5] = -6;
    Y.v[6] = -19;
    Y.v[7] = -5;
    Y.v[8] = 14;
    Y.v[9] = -6;
    Y.v[10] = 0;
    Y.v[11] = 12;
    Y.v[12] = -17;
    Y.v[13] = -12;
    Y.v[14] = 8;
    Y.v[15] = 14;
/*
X
[[-16  14 -10  14]
 [-19  10  -5 -12]
 [  6  16  -8  19]
 [ 19 -17 -20  -2]]
Y
[[-10  -8  14 -17]
 [  6  -6  -6 -12]
 [ -6 -19   0   8]
 [-17  -5  12  14]]
[[  66  164 -140  220]
 [ 484  247 -470   -5]
 [-239  -87  216  -92]
 [-138  340  344 -307]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(66));
assert((A.v[4])==(164));
assert((A.v[8])==(-140));
assert((A.v[12])==(220));
assert((A.v[1])==(484));
assert((A.v[5])==(247));
assert((A.v[9])==(-470));
assert((A.v[13])==(-5));
assert((A.v[2])==(-239));
assert((A.v[6])==(-87));
assert((A.v[10])==(216));
assert((A.v[14])==(-92));
assert((A.v[3])==(-138));
assert((A.v[7])==(340));
assert((A.v[11])==(344));
assert((A.v[15])==(-307));
/*
X
[[-16  14 -10  14]
 [-19  10  -5 -12]
 [  6  16  -8  19]
 [ 19 -17 -20  -2]]
Y
[[-10  -8  14 -17]
 [  6  -6  -6 -12]
 [ -6 -19   0   8]
 [-17  -5  12  14]]
X
[[  66  164 -140  220]
 [ 484  247 -470   -5]
 [-239  -87  216  -92]
 [-138  340  344 -307]]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(66));
assert((X.v[4])==(164));
assert((X.v[8])==(-140));
assert((X.v[12])==(220));
assert((X.v[1])==(484));
assert((X.v[5])==(247));
assert((X.v[9])==(-470));
assert((X.v[13])==(-5));
assert((X.v[2])==(-239));
assert((X.v[6])==(-87));
assert((X.v[10])==(216));
assert((X.v[14])==(-92));
assert((X.v[3])==(-138));
assert((X.v[7])==(340));
assert((X.v[11])==(344));
assert((X.v[15])==(-307));
/* Resetting test vectors / mats */
    v.v[0] = -13;
    v.v[1] = -15;
    v.v[2] = -5;
    v.v[3] = 8;
    X.v[0] = -1;
    X.v[1] = 14;
    X.v[2] = 17;
    X.v[3] = 7;
    X.v[4] = 14;
    X.v[5] = -3;
    X.v[6] = -15;
    X.v[7] = 19;
    X.v[8] = -20;
    X.v[9] = -2;
    X.v[10] = -2;
    X.v[11] = 16;
    X.v[12] = 5;
    X.v[13] = 9;
    X.v[14] = 14;
    X.v[15] = 9;
    Y.v[0] = -15;
    Y.v[1] = -11;
    Y.v[2] = 11;
    Y.v[3] = -14;
    Y.v[4] = 11;
    Y.v[5] = -8;
    Y.v[6] = -9;
    Y.v[7] = -2;
    Y.v[8] = 15;
    Y.v[9] = -15;
    Y.v[10] = -10;
    Y.v[11] = -7;
    Y.v[12] = 8;
    Y.v[13] = 10;
    Y.v[14] = 4;
    Y.v[15] = -11;
/*
X
[[ -1  14 -20   5]
 [ 14  -3  -2   9]
 [ 17 -15  -2  14]
 [  7  19  16   9]]
v
[-13 -15  -5   8]
w
[ -57  -55  126 -384]
*/
i=0;
fprintf(stdout,"SST_Math_Mat44iMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(-57));
assert((w.v[1])==(-55));
assert((w.v[2])==(126));
assert((w.v[3])==(-384));
/*
X
[[ -1  14 -20   5]
 [ 14  -3  -2   9]
 [ 17 -15  -2  14]
 [  7  19  16   9]]
v
[-13 -15  -5   8]
v
[ -57  -55  126 -384]
*/
fprintf(stdout,"SST_Math_Mat44iMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(-57));
assert((v.v[1])==(-55));
assert((v.v[2])==(126));
assert((v.v[3])==(-384));
/* Resetting test vectors / mats */
    v.v[0] = 6;
    v.v[1] = 8;
    v.v[2] = -16;
    v.v[3] = -4;
    X.v[0] = 2;
    X.v[1] = 7;
    X.v[2] = 7;
    X.v[3] = 15;
    X.v[4] = -3;
    X.v[5] = -12;
    X.v[6] = 3;
    X.v[7] = -5;
    X.v[8] = -4;
    X.v[9] = 3;
    X.v[10] = 17;
    X.v[11] = 5;
    X.v[12] = 11;
    X.v[13] = 4;
    X.v[14] = -19;
    X.v[15] = -3;
    Y.v[0] = 10;
    Y.v[1] = -20;
    Y.v[2] = 12;
    Y.v[3] = -20;
    Y.v[4] = 4;
    Y.v[5] = 5;
    Y.v[6] = 5;
    Y.v[7] = -10;
    Y.v[8] = -4;
    Y.v[9] = -5;
    Y.v[10] = 18;
    Y.v[11] = -12;
    Y.v[12] = 19;
    Y.v[13] = -8;
    Y.v[14] = -12;
    Y.v[15] = 11;
fprintf(stdout,"SST_Math_Mat44iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(2));
assert((A.v[4])==(7));
assert((A.v[8])==(7));
assert((A.v[12])==(15));
assert((A.v[1])==(-3));
assert((A.v[5])==(-12));
assert((A.v[9])==(3));
assert((A.v[13])==(-5));
assert((A.v[2])==(-4));
assert((A.v[6])==(3));
assert((A.v[10])==(17));
assert((A.v[14])==(5));
assert((A.v[3])==(11));
assert((A.v[7])==(4));
assert((A.v[11])==(-19));
assert((A.v[15])==(-3));
fprintf(stdout,"SST_Math_Mat44iTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44iTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44iTransposeLocal(&X);
assert((X.v[0])==(2));
assert((X.v[4])==(7));
assert((X.v[8])==(7));
assert((X.v[12])==(15));
assert((X.v[1])==(-3));
assert((X.v[5])==(-12));
assert((X.v[9])==(3));
assert((X.v[13])==(-5));
assert((X.v[2])==(-4));
assert((X.v[6])==(3));
assert((X.v[10])==(17));
assert((X.v[14])==(5));
assert((X.v[3])==(11));
assert((X.v[7])==(4));
assert((X.v[11])==(-19));
assert((X.v[15])==(-3));
/*
[[-0.11060025 -0.19063332  0.3125823  -0.92396906]
 [-0.38710088 -0.8021454  -0.45077126  0.05933746]
 [-0.38710088  0.54714239 -0.68026815 -0.29668731]
 [-0.8295019   0.14441918  0.48614075  0.23395914]]
[[  1.00000000e+00  -2.77555756e-17   1.66533454e-16  -3.05311332e-16]
 [ -2.77555756e-17   1.00000000e+00   2.63677968e-16  -4.16333634e-17]
 [  1.66533454e-16   2.63677968e-16   1.00000000e+00   1.11022302e-16]
 [ -3.05311332e-16  -4.16333634e-17   1.11022302e-16   1.00000000e+00]]
*/
X.v[0] = (int)0;
X.v[4] = (int)0;
X.v[8] = (int)0;
X.v[12] = (int)0;
X.v[1] = (int)0;
X.v[5] = (int)0;
X.v[9] = (int)0;
X.v[13] = (int)0;
X.v[2] = (int)0;
X.v[6] = (int)0;
X.v[10] = (int)0;
X.v[14] = (int)0;
X.v[3] = (int)0;
X.v[7] = (int)0;
X.v[11] = (int)0;
X.v[15] = (int)0;
fprintf(stdout,"SST_Math_Mat44iTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44iTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat44iMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat44iMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Check Positive Test */
assert(SST_Math_Mat44iCheckOrthonormal(&X));
/* Check Negative Test */
assert(!SST_Math_Mat44iCheckOrthonormal(&Y));
fprintf(stdout,"\n==== SST_Math_Mat44itest_fxn COMPLETE ====\n");
return 0;
}
