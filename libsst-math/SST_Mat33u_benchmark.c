#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <xmmintrin.h>
#include <SST/SST_Timer_x86.h>
#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>




int SST_Math_Mat33u_test_fxns()
{
const int NTESTS = 10;
int i;
uint64_t t0,t1;
SST_Mat33u X; /* 3 x 3 matrix */
SST_Mat33u Y; /* 3 x 3 matrix */
SST_Mat33u A; /* 3 x 3 matrix */
SST_Mat33u B; /* 3 x 3 matrix */
SST_Vec3u v; /* 3 vector */
SST_Vec3u w; /* 3 vector */
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
/* Resetting test vectors / mats */
    v.v[0] = 28;
    v.v[1] = 0;
    v.v[2] = 25;
    X.v[0] = 37;
    X.v[1] = 35;
    X.v[2] = 27;
    X.v[3] = 16;
    X.v[4] = 34;
    X.v[5] = 18;
    X.v[6] = 29;
    X.v[7] = 15;
    X.v[8] = 26;
    Y.v[0] = 4;
    Y.v[1] = 19;
    Y.v[2] = 4;
    Y.v[3] = 9;
    Y.v[4] = 19;
    Y.v[5] = 35;
    Y.v[6] = 5;
    Y.v[7] = 6;
    Y.v[8] = 15;
SST_Math_Mat33uAdd(&X,&Y,&A); /* clear out the initial finding of object */
/* Clear out the rdtsc register */
fprintf(stdout,"SST_Math_Mat33uAdd(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uAdd(&X,&Y,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
/*
[[37 16 29]
 [35 34 15]
 [27 18 26]]
[[ 4  9  5]
 [19 19  6]
 [ 4 35 15]]
[[41 25 34]
 [54 53 21]
 [31 53 41]]
*/
assert((A.v[0])==(41));
assert((A.v[3])==(25));
assert((A.v[6])==(34));
assert((A.v[1])==(54));
assert((A.v[4])==(53));
assert((A.v[7])==(21));
assert((A.v[2])==(31));
assert((A.v[5])==(53));
assert((A.v[8])==(41));
/*
[[37 16 29]
 [35 34 15]
 [27 18 26]]
[[ 4  9  5]
 [19 19  6]
 [ 4 35 15]]
[[41 25 34]
 [54 53 21]
 [31 53 41]]
*/
fprintf(stdout,"SST_Math_Mat33uAddLocal(A,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uAddLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uAddLocal(&X,&Y); /* for accuracy */
assert((X.v[0])==(41));
assert((X.v[3])==(25));
assert((X.v[6])==(34));
assert((X.v[1])==(54));
assert((X.v[4])==(53));
assert((X.v[7])==(21));
assert((X.v[2])==(31));
assert((X.v[5])==(53));
assert((X.v[8])==(41));
/* Resetting test vectors / mats */
    v.v[0] = 31;
    v.v[1] = 21;
    v.v[2] = 22;
    X.v[0] = 0;
    X.v[1] = 11;
    X.v[2] = 3;
    X.v[3] = 35;
    X.v[4] = 25;
    X.v[5] = 31;
    X.v[6] = 15;
    X.v[7] = 14;
    X.v[8] = 33;
    Y.v[0] = 32;
    Y.v[1] = 23;
    Y.v[2] = 23;
    Y.v[3] = 35;
    Y.v[4] = 2;
    Y.v[5] = 31;
    Y.v[6] = 31;
    Y.v[7] = 2;
    Y.v[8] = 8;
/*
[[ 0 35 15]
 [11 25 14]
 [ 3 31 33]]
[[ 0 70 30]
 [22 50 28]
 [ 6 62 66]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyScalar(X,t,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyScalar(&X,2,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(0));
assert((A.v[3])==(70));
assert((A.v[6])==(30));
assert((A.v[1])==(22));
assert((A.v[4])==(50));
assert((A.v[7])==(28));
assert((A.v[2])==(6));
assert((A.v[5])==(62));
assert((A.v[8])==(66));
/*
[[ 0 35 15]
 [11 25 14]
 [ 3 31 33]]
[[ 0 70 30]
 [22 50 28]
 [ 6 62 66]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyScalarLocal(A,t)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyScalarLocal(&A,2);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uMultiplyScalarLocal(&X,2);
assert((X.v[0])==(0));
assert((X.v[3])==(70));
assert((X.v[6])==(30));
assert((X.v[1])==(22));
assert((X.v[4])==(50));
assert((X.v[7])==(28));
assert((X.v[2])==(6));
assert((X.v[5])==(62));
assert((X.v[8])==(66));
/* Resetting test vectors / mats */
    v.v[0] = 1;
    v.v[1] = 19;
    v.v[2] = 20;
    X.v[0] = 22;
    X.v[1] = 25;
    X.v[2] = 21;
    X.v[3] = 28;
    X.v[4] = 13;
    X.v[5] = 7;
    X.v[6] = 14;
    X.v[7] = 5;
    X.v[8] = 26;
    Y.v[0] = 28;
    Y.v[1] = 35;
    Y.v[2] = 21;
    Y.v[3] = 11;
    Y.v[4] = 29;
    Y.v[5] = 0;
    Y.v[6] = 13;
    Y.v[7] = 31;
    Y.v[8] = 9;
/*
[[22 28 14]
 [25 13  5]
 [21  7 26]]
[[28 11 13]
 [35 29 31]
 [21  0  9]]
[[616 308 182]
 [875 377 155]
 [441   0 234]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyElementwise(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyElementwise(&X, &Y, &A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(616));
assert((A.v[3])==(308));
assert((A.v[6])==(182));
assert((A.v[1])==(875));
assert((A.v[4])==(377));
assert((A.v[7])==(155));
assert((A.v[2])==(441));
assert((A.v[5])==(0));
assert((A.v[8])==(234));
/*
[[22 28 14]
 [25 13  5]
 [21  7 26]]
[[28 11 13]
 [35 29 31]
 [21  0  9]]
[[616 308 182]
 [875 377 155]
 [441   0 234]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyElementwiseLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyElementwiseLocal(&A,&Y);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uMultiplyElementwiseLocal(&X,&Y);
assert((X.v[0])==(616));
assert((X.v[3])==(308));
assert((X.v[6])==(182));
assert((X.v[1])==(875));
assert((X.v[4])==(377));
assert((X.v[7])==(155));
assert((X.v[2])==(441));
assert((X.v[5])==(0));
assert((X.v[8])==(234));
/* Resetting test vectors / mats */
    v.v[0] = 15;
    v.v[1] = 31;
    v.v[2] = 26;
    X.v[0] = 34;
    X.v[1] = 10;
    X.v[2] = 36;
    X.v[3] = 34;
    X.v[4] = 20;
    X.v[5] = 13;
    X.v[6] = 27;
    X.v[7] = 36;
    X.v[8] = 35;
    Y.v[0] = 31;
    Y.v[1] = 39;
    Y.v[2] = 18;
    Y.v[3] = 23;
    Y.v[4] = 6;
    Y.v[5] = 10;
    Y.v[6] = 22;
    Y.v[7] = 24;
    Y.v[8] = 37;
/*
X
[[34 34 27]
 [10 20 36]
 [36 13 35]]
Y
[[31 23 22]
 [39  6 24]
 [18 10 37]]
[[2866 1256 2563]
 [1738  710 2032]
 [2253 1256 2399]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyMatrix(X,Y,A)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyMatrix(&X,&Y,&A);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(2866));
assert((A.v[3])==(1256));
assert((A.v[6])==(2563));
assert((A.v[1])==(1738));
assert((A.v[4])==(710));
assert((A.v[7])==(2032));
assert((A.v[2])==(2253));
assert((A.v[5])==(1256));
assert((A.v[8])==(2399));
/*
X
[[34 34 27]
 [10 20 36]
 [36 13 35]]
Y
[[31 23 22]
 [39  6 24]
 [18 10 37]]
X
[[2866 1256 2563]
 [1738  710 2032]
 [2253 1256 2399]]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyMatrixLocal(X,Y)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyMatrixLocal(&A,&Y);
t1 = rdtsc();
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uMultiplyMatrixLocal(&X,&Y);
assert((X.v[0])==(2866));
assert((X.v[3])==(1256));
assert((X.v[6])==(2563));
assert((X.v[1])==(1738));
assert((X.v[4])==(710));
assert((X.v[7])==(2032));
assert((X.v[2])==(2253));
assert((X.v[5])==(1256));
assert((X.v[8])==(2399));
/* Resetting test vectors / mats */
    v.v[0] = 15;
    v.v[1] = 30;
    v.v[2] = 18;
    X.v[0] = 15;
    X.v[1] = 36;
    X.v[2] = 12;
    X.v[3] = 1;
    X.v[4] = 3;
    X.v[5] = 22;
    X.v[6] = 13;
    X.v[7] = 15;
    X.v[8] = 13;
    Y.v[0] = 33;
    Y.v[1] = 38;
    Y.v[2] = 32;
    Y.v[3] = 13;
    Y.v[4] = 28;
    Y.v[5] = 7;
    Y.v[6] = 39;
    Y.v[7] = 8;
    Y.v[8] = 32;
/*
X
[[15  1 13]
 [36  3 15]
 [12 22 13]]
v
[15 30 18]
w
[ 489  900 1074]
*/
i=0;
fprintf(stdout,"SST_Math_Mat33uMultiplyVector(X,v,w)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyVector(&X,&v,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((w.v[0])==(489));
assert((w.v[1])==(900));
assert((w.v[2])==(1074));
/*
X
[[15  1 13]
 [36  3 15]
 [12 22 13]]
v
[15 30 18]
v
[ 489  900 1074]
*/
fprintf(stdout,"SST_Math_Mat33uMultiplyVectorLocal(X,v)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uMultiplyVectorLocal(&X,&w);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uMultiplyVectorLocal(&X,&v);
assert((v.v[0])==(489));
assert((v.v[1])==(900));
assert((v.v[2])==(1074));
/* Resetting test vectors / mats */
    v.v[0] = 24;
    v.v[1] = 36;
    v.v[2] = 2;
    X.v[0] = 34;
    X.v[1] = 19;
    X.v[2] = 4;
    X.v[3] = 22;
    X.v[4] = 9;
    X.v[5] = 14;
    X.v[6] = 29;
    X.v[7] = 25;
    X.v[8] = 32;
    Y.v[0] = 5;
    Y.v[1] = 6;
    Y.v[2] = 26;
    Y.v[3] = 22;
    Y.v[4] = 22;
    Y.v[5] = 32;
    Y.v[6] = 36;
    Y.v[7] = 9;
    Y.v[8] = 16;
fprintf(stdout,"SST_Math_Mat33uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
assert((A.v[0])==(34));
assert((A.v[3])==(19));
assert((A.v[6])==(4));
assert((A.v[1])==(22));
assert((A.v[4])==(9));
assert((A.v[7])==(14));
assert((A.v[2])==(29));
assert((A.v[5])==(25));
assert((A.v[8])==(32));
fprintf(stdout,"SST_Math_Mat33uTransposeLocal(X)");
for(i = 0; i < NTESTS; i++) { 
t0 = rdtsc();
SST_Math_Mat33uTransposeLocal(&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
}
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
SST_Math_Mat33uTransposeLocal(&X);
assert((X.v[0])==(34));
assert((X.v[3])==(19));
assert((X.v[6])==(4));
assert((X.v[1])==(22));
assert((X.v[4])==(9));
assert((X.v[7])==(14));
assert((X.v[2])==(29));
assert((X.v[5])==(25));
assert((X.v[8])==(32));
/*
[[-0.86837606  0.03165458 -0.49489495]
 [-0.48526897 -0.25983137  0.83486627]
 [-0.10216189  0.96513504  0.24099232]]
[[  1.00000000e+00   0.00000000e+00  -7.63278329e-17]
 [  0.00000000e+00   1.00000000e+00   1.11022302e-16]
 [ -7.63278329e-17   1.11022302e-16   1.00000000e+00]]
*/
X.v[0] = (unsigned int)0;
X.v[3] = (unsigned int)0;
X.v[6] = (unsigned int)0;
X.v[1] = (unsigned int)0;
X.v[4] = (unsigned int)0;
X.v[7] = (unsigned int)0;
X.v[2] = (unsigned int)0;
X.v[5] = (unsigned int)0;
X.v[8] = (unsigned int)0;
fprintf(stdout,"SST_Math_Mat33uTranspose(X,A)");
t0 = rdtsc();
SST_Math_Mat33uTranspose(&X,&A);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"SST_Math_Mat33uMultiplyMatrix(A,X,B)");
t0 = rdtsc();
SST_Math_Mat33uMultiplyMatrix(&A,&X,&B);
t1 = rdtsc();
fprintf(stdout," timing:%llu\n",(long long unsigned int)(t1-t0));
fprintf(stdout,"\n==== SST_Math_Mat33utest_fxn COMPLETE ====\n");
return 0;
}
