#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>




int SST_Math_Mat44u_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat44u X; /* 4 x 4 matrix */
SST_Mat44u Y; /* 4 x 4 matrix */
SST_Mat44u A; /* 4 x 4 matrix */
SST_Mat44u B; /* 4 x 4 matrix */
SST_Vec4u v; /* 4 vector */
SST_Vec4u w; /* 4 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = 15;
    v.v[1] = 7;
    v.v[2] = 12;
    v.v[3] = 29;
    X.v[0] = 6;
    X.v[1] = 36;
    X.v[2] = 21;
    X.v[3] = 26;
    X.v[4] = 28;
    X.v[5] = 22;
    X.v[6] = 31;
    X.v[7] = 11;
    X.v[8] = 22;
    X.v[9] = 11;
    X.v[10] = 20;
    X.v[11] = 9;
    X.v[12] = 4;
    X.v[13] = 25;
    X.v[14] = 26;
    X.v[15] = 32;
    Y.v[0] = 9;
    Y.v[1] = 22;
    Y.v[2] = 6;
    Y.v[3] = 0;
    Y.v[4] = 34;
    Y.v[5] = 12;
    Y.v[6] = 36;
    Y.v[7] = 16;
    Y.v[8] = 33;
    Y.v[9] = 29;
    Y.v[10] = 10;
    Y.v[11] = 38;
    Y.v[12] = 8;
    Y.v[13] = 3;
    Y.v[14] = 5;
    Y.v[15] = 31;
SST_Math_Mat44uAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat44uAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[ 6 28 22  4]
 [36 22 11 25]
 [21 31 20 26]
 [26 11  9 32]]
[[ 9 34 33  8]
 [22 12 29  3]
 [ 6 36 10  5]
 [ 0 16 38 31]]
[[15 62 55 12]
 [58 34 40 28]
 [27 67 30 31]
 [26 27 47 63]]
*/
assert((A.v[0])==(15));
assert((A.v[4])==(62));
assert((A.v[8])==(55));
assert((A.v[12])==(12));
assert((A.v[1])==(58));
assert((A.v[5])==(34));
assert((A.v[9])==(40));
assert((A.v[13])==(28));
assert((A.v[2])==(27));
assert((A.v[6])==(67));
assert((A.v[10])==(30));
assert((A.v[14])==(31));
assert((A.v[3])==(26));
assert((A.v[7])==(27));
assert((A.v[11])==(47));
assert((A.v[15])==(63));
/*
[[ 6 28 22  4]
 [36 22 11 25]
 [21 31 20 26]
 [26 11  9 32]]
[[ 9 34 33  8]
 [22 12 29  3]
 [ 6 36 10  5]
 [ 0 16 38 31]]
[[15 62 55 12]
 [58 34 40 28]
 [27 67 30 31]
 [26 27 47 63]]
*/
fprintf(stdout,"SST_Math_Mat44uAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(15));
assert((X.v[4])==(62));
assert((X.v[8])==(55));
assert((X.v[12])==(12));
assert((X.v[1])==(58));
assert((X.v[5])==(34));
assert((X.v[9])==(40));
assert((X.v[13])==(28));
assert((X.v[2])==(27));
assert((X.v[6])==(67));
assert((X.v[10])==(30));
assert((X.v[14])==(31));
assert((X.v[3])==(26));
assert((X.v[7])==(27));
assert((X.v[11])==(47));
assert((X.v[15])==(63));
/* Resetting test vectors / mats */
    v.v[0] = 7;
    v.v[1] = 34;
    v.v[2] = 14;
    v.v[3] = 35;
    X.v[0] = 30;
    X.v[1] = 26;
    X.v[2] = 28;
    X.v[3] = 21;
    X.v[4] = 24;
    X.v[5] = 32;
    X.v[6] = 35;
    X.v[7] = 6;
    X.v[8] = 17;
    X.v[9] = 18;
    X.v[10] = 10;
    X.v[11] = 34;
    X.v[12] = 14;
    X.v[13] = 2;
    X.v[14] = 25;
    X.v[15] = 26;
    Y.v[0] = 22;
    Y.v[1] = 1;
    Y.v[2] = 21;
    Y.v[3] = 27;
    Y.v[4] = 2;
    Y.v[5] = 39;
    Y.v[6] = 38;
    Y.v[7] = 17;
    Y.v[8] = 20;
    Y.v[9] = 22;
    Y.v[10] = 35;
    Y.v[11] = 37;
    Y.v[12] = 24;
    Y.v[13] = 0;
    Y.v[14] = 20;
    Y.v[15] = 9;
/*
[[30 24 17 14]
 [26 32 18  2]
 [28 35 10 25]
 [21  6 34 26]]
[[60 48 34 28]
 [52 64 36  4]
 [56 70 20 50]
 [42 12 68 52]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(60));
assert((A.v[4])==(48));
assert((A.v[8])==(34));
assert((A.v[12])==(28));
assert((A.v[1])==(52));
assert((A.v[5])==(64));
assert((A.v[9])==(36));
assert((A.v[13])==(4));
assert((A.v[2])==(56));
assert((A.v[6])==(70));
assert((A.v[10])==(20));
assert((A.v[14])==(50));
assert((A.v[3])==(42));
assert((A.v[7])==(12));
assert((A.v[11])==(68));
assert((A.v[15])==(52));
/*
[[30 24 17 14]
 [26 32 18  2]
 [28 35 10 25]
 [21  6 34 26]]
[[60 48 34 28]
 [52 64 36  4]
 [56 70 20 50]
 [42 12 68 52]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uMultiplyScalarLocal(&X,2);
assert((X.v[0])==(60));
assert((X.v[4])==(48));
assert((X.v[8])==(34));
assert((X.v[12])==(28));
assert((X.v[1])==(52));
assert((X.v[5])==(64));
assert((X.v[9])==(36));
assert((X.v[13])==(4));
assert((X.v[2])==(56));
assert((X.v[6])==(70));
assert((X.v[10])==(20));
assert((X.v[14])==(50));
assert((X.v[3])==(42));
assert((X.v[7])==(12));
assert((X.v[11])==(68));
assert((X.v[15])==(52));
/* Resetting test vectors / mats */
    v.v[0] = 3;
    v.v[1] = 26;
    v.v[2] = 14;
    v.v[3] = 12;
    X.v[0] = 22;
    X.v[1] = 9;
    X.v[2] = 9;
    X.v[3] = 11;
    X.v[4] = 39;
    X.v[5] = 37;
    X.v[6] = 35;
    X.v[7] = 1;
    X.v[8] = 3;
    X.v[9] = 33;
    X.v[10] = 25;
    X.v[11] = 13;
    X.v[12] = 34;
    X.v[13] = 9;
    X.v[14] = 32;
    X.v[15] = 16;
    Y.v[0] = 30;
    Y.v[1] = 17;
    Y.v[2] = 29;
    Y.v[3] = 11;
    Y.v[4] = 22;
    Y.v[5] = 25;
    Y.v[6] = 10;
    Y.v[7] = 13;
    Y.v[8] = 14;
    Y.v[9] = 10;
    Y.v[10] = 13;
    Y.v[11] = 32;
    Y.v[12] = 35;
    Y.v[13] = 19;
    Y.v[14] = 21;
    Y.v[15] = 31;
/*
[[22 39  3 34]
 [ 9 37 33  9]
 [ 9 35 25 32]
 [11  1 13 16]]
[[30 22 14 35]
 [17 25 10 19]
 [29 10 13 21]
 [11 13 32 31]]
[[ 660  858   42 1190]
 [ 153  925  330  171]
 [ 261  350  325  672]
 [ 121   13  416  496]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(660));
assert((A.v[4])==(858));
assert((A.v[8])==(42));
assert((A.v[12])==(1190));
assert((A.v[1])==(153));
assert((A.v[5])==(925));
assert((A.v[9])==(330));
assert((A.v[13])==(171));
assert((A.v[2])==(261));
assert((A.v[6])==(350));
assert((A.v[10])==(325));
assert((A.v[14])==(672));
assert((A.v[3])==(121));
assert((A.v[7])==(13));
assert((A.v[11])==(416));
assert((A.v[15])==(496));
/*
[[22 39  3 34]
 [ 9 37 33  9]
 [ 9 35 25 32]
 [11  1 13 16]]
[[30 22 14 35]
 [17 25 10 19]
 [29 10 13 21]
 [11 13 32 31]]
[[ 660  858   42 1190]
 [ 153  925  330  171]
 [ 261  350  325  672]
 [ 121   13  416  496]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(660));
assert((X.v[4])==(858));
assert((X.v[8])==(42));
assert((X.v[12])==(1190));
assert((X.v[1])==(153));
assert((X.v[5])==(925));
assert((X.v[9])==(330));
assert((X.v[13])==(171));
assert((X.v[2])==(261));
assert((X.v[6])==(350));
assert((X.v[10])==(325));
assert((X.v[14])==(672));
assert((X.v[3])==(121));
assert((X.v[7])==(13));
assert((X.v[11])==(416));
assert((X.v[15])==(496));
/* Resetting test vectors / mats */
    v.v[0] = 12;
    v.v[1] = 32;
    v.v[2] = 34;
    v.v[3] = 7;
    X.v[0] = 9;
    X.v[1] = 38;
    X.v[2] = 14;
    X.v[3] = 19;
    X.v[4] = 5;
    X.v[5] = 6;
    X.v[6] = 34;
    X.v[7] = 34;
    X.v[8] = 7;
    X.v[9] = 26;
    X.v[10] = 9;
    X.v[11] = 37;
    X.v[12] = 39;
    X.v[13] = 3;
    X.v[14] = 8;
    X.v[15] = 4;
    Y.v[0] = 2;
    Y.v[1] = 25;
    Y.v[2] = 12;
    Y.v[3] = 4;
    Y.v[4] = 25;
    Y.v[5] = 29;
    Y.v[6] = 16;
    Y.v[7] = 6;
    Y.v[8] = 20;
    Y.v[9] = 37;
    Y.v[10] = 36;
    Y.v[11] = 34;
    Y.v[12] = 18;
    Y.v[13] = 5;
    Y.v[14] = 2;
    Y.v[15] = 4;
/*
X
[[ 9  5  7 39]
 [38  6 26  3]
 [14 34  9  8]
 [19 34 37  4]]
Y
[[ 2 25 20 18]
 [25 29 37  5]
 [12 16 36  2]
 [ 4  6 34  4]]
[[ 383  716 1943  357]
 [ 550 1558 2020  778]
 [1018 1528 2134  472]
 [1348 2077 3106  602]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(383));
assert((A.v[4])==(716));
assert((A.v[8])==(1943));
assert((A.v[12])==(357));
assert((A.v[1])==(550));
assert((A.v[5])==(1558));
assert((A.v[9])==(2020));
assert((A.v[13])==(778));
assert((A.v[2])==(1018));
assert((A.v[6])==(1528));
assert((A.v[10])==(2134));
assert((A.v[14])==(472));
assert((A.v[3])==(1348));
assert((A.v[7])==(2077));
assert((A.v[11])==(3106));
assert((A.v[15])==(602));
/*
X
[[ 9  5  7 39]
 [38  6 26  3]
 [14 34  9  8]
 [19 34 37  4]]
Y
[[ 2 25 20 18]
 [25 29 37  5]
 [12 16 36  2]
 [ 4  6 34  4]]
X
[[ 383  716 1943  357]
 [ 550 1558 2020  778]
 [1018 1528 2134  472]
 [1348 2077 3106  602]]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(383));
assert((X.v[4])==(716));
assert((X.v[8])==(1943));
assert((X.v[12])==(357));
assert((X.v[1])==(550));
assert((X.v[5])==(1558));
assert((X.v[9])==(2020));
assert((X.v[13])==(778));
assert((X.v[2])==(1018));
assert((X.v[6])==(1528));
assert((X.v[10])==(2134));
assert((X.v[14])==(472));
assert((X.v[3])==(1348));
assert((X.v[7])==(2077));
assert((X.v[11])==(3106));
assert((X.v[15])==(602));
/* Resetting test vectors / mats */
    v.v[0] = 8;
    v.v[1] = 4;
    v.v[2] = 7;
    v.v[3] = 3;
    X.v[0] = 20;
    X.v[1] = 11;
    X.v[2] = 0;
    X.v[3] = 12;
    X.v[4] = 11;
    X.v[5] = 6;
    X.v[6] = 34;
    X.v[7] = 20;
    X.v[8] = 3;
    X.v[9] = 13;
    X.v[10] = 17;
    X.v[11] = 11;
    X.v[12] = 9;
    X.v[13] = 16;
    X.v[14] = 34;
    X.v[15] = 20;
    Y.v[0] = 12;
    Y.v[1] = 17;
    Y.v[2] = 27;
    Y.v[3] = 3;
    Y.v[4] = 33;
    Y.v[5] = 29;
    Y.v[6] = 14;
    Y.v[7] = 13;
    Y.v[8] = 29;
    Y.v[9] = 18;
    Y.v[10] = 28;
    Y.v[11] = 31;
    Y.v[12] = 33;
    Y.v[13] = 9;
    Y.v[14] = 35;
    Y.v[15] = 16;
/*
X
[[20 11  3  9]
 [11  6 13 16]
 [ 0 34 17 34]
 [12 20 11 20]]
v
[8 4 7 3]
w
[252 251 357 313]
*/
i=0;
fprintf(stdout,"SST_Math_Mat44uMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(252));
assert((w.v[1])==(251));
assert((w.v[2])==(357));
assert((w.v[3])==(313));
/*
X
[[20 11  3  9]
 [11  6 13 16]
 [ 0 34 17 34]
 [12 20 11 20]]
v
[8 4 7 3]
v
[252 251 357 313]
*/
fprintf(stdout,"SST_Math_Mat44uMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(252));
assert((v.v[1])==(251));
assert((v.v[2])==(357));
assert((v.v[3])==(313));
/* Resetting test vectors / mats */
    v.v[0] = 20;
    v.v[1] = 16;
    v.v[2] = 38;
    v.v[3] = 29;
    X.v[0] = 35;
    X.v[1] = 31;
    X.v[2] = 23;
    X.v[3] = 0;
    X.v[4] = 10;
    X.v[5] = 32;
    X.v[6] = 37;
    X.v[7] = 21;
    X.v[8] = 26;
    X.v[9] = 6;
    X.v[10] = 18;
    X.v[11] = 20;
    X.v[12] = 22;
    X.v[13] = 33;
    X.v[14] = 2;
    X.v[15] = 30;
    Y.v[0] = 20;
    Y.v[1] = 33;
    Y.v[2] = 7;
    Y.v[3] = 30;
    Y.v[4] = 34;
    Y.v[5] = 37;
    Y.v[6] = 30;
    Y.v[7] = 30;
    Y.v[8] = 9;
    Y.v[9] = 0;
    Y.v[10] = 10;
    Y.v[11] = 31;
    Y.v[12] = 22;
    Y.v[13] = 7;
    Y.v[14] = 1;
    Y.v[15] = 32;
fprintf(stdout,"SST_Math_Mat44uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(35));
assert((A.v[4])==(31));
assert((A.v[8])==(23));
assert((A.v[12])==(0));
assert((A.v[1])==(10));
assert((A.v[5])==(32));
assert((A.v[9])==(37));
assert((A.v[13])==(21));
assert((A.v[2])==(26));
assert((A.v[6])==(6));
assert((A.v[10])==(18));
assert((A.v[14])==(20));
assert((A.v[3])==(22));
assert((A.v[7])==(33));
assert((A.v[11])==(2));
assert((A.v[15])==(30));
fprintf(stdout,"SST_Math_Mat44uTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat44uTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat44uTransposeLocal(&X);
assert((X.v[0])==(35));
assert((X.v[4])==(31));
assert((X.v[8])==(23));
assert((X.v[12])==(0));
assert((X.v[1])==(10));
assert((X.v[5])==(32));
assert((X.v[9])==(37));
assert((X.v[13])==(21));
assert((X.v[2])==(26));
assert((X.v[6])==(6));
assert((X.v[10])==(18));
assert((X.v[14])==(20));
assert((X.v[3])==(22));
assert((X.v[7])==(33));
assert((X.v[11])==(2));
assert((X.v[15])==(30));
/*
[[-0.67171203  0.53583792 -0.51132829  0.01496829]
 [-0.59494494 -0.20412719  0.58270865  0.51460979]
 [-0.44141076 -0.54027758 -0.00728165 -0.71638234]
 [-0.         -0.61588144 -0.63161776  0.47090239]]
[[  1.00000000e+00  -8.32667268e-17   3.51281504e-17   5.55111512e-17]
 [ -8.32667268e-17   1.00000000e+00   2.22044605e-16   2.22044605e-16]
 [  3.51281504e-17   2.22044605e-16   1.00000000e+00   5.55111512e-17]
 [  5.55111512e-17   2.22044605e-16   5.55111512e-17   1.00000000e+00]]
*/
X.v[0] = (unsigned int)0;
X.v[4] = (unsigned int)0;
X.v[8] = (unsigned int)0;
X.v[12] = (unsigned int)0;
X.v[1] = (unsigned int)0;
X.v[5] = (unsigned int)0;
X.v[9] = (unsigned int)0;
X.v[13] = (unsigned int)0;
X.v[2] = (unsigned int)0;
X.v[6] = (unsigned int)0;
X.v[10] = (unsigned int)0;
X.v[14] = (unsigned int)0;
X.v[3] = (unsigned int)0;
X.v[7] = (unsigned int)0;
X.v[11] = (unsigned int)0;
X.v[15] = (unsigned int)0;
fprintf(stdout,"SST_Math_Mat44uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat44uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat44uMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat44uMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"\n==== SST_Math_Mat44utest_fxn COMPLETE ====\n");
return 0;
}
