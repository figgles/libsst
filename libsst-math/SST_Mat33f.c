/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 3, TYPE = float */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>
void SST_Math_Mat33fAdd(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
	 _out->v[2] = _A->v[2] + _B->v[2];
	 _out->v[3] = _A->v[3] + _B->v[3];
	 _out->v[4] = _A->v[4] + _B->v[4];
	 _out->v[5] = _A->v[5] + _B->v[5];
	 _out->v[6] = _A->v[6] + _B->v[6];
	 _out->v[7] = _A->v[7] + _B->v[7];
	 _out->v[8] = _A->v[8] + _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fAddLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
	 _A->v[4] += _B->v[4];
	 _A->v[5] += _B->v[5];
	 _A->v[6] += _B->v[6];
	 _A->v[7] += _B->v[7];
	 _A->v[8] += _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fSubtract(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
	 _out->v[2] = _A->v[2] - _B->v[2];
	 _out->v[3] = _A->v[3] - _B->v[3];
	 _out->v[4] = _A->v[4] - _B->v[4];
	 _out->v[5] = _A->v[5] - _B->v[5];
	 _out->v[6] = _A->v[6] - _B->v[6];
	 _out->v[7] = _A->v[7] - _B->v[7];
	 _out->v[8] = _A->v[8] - _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fSubtractLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
	 _A->v[4] -= _B->v[4];
	 _A->v[5] -= _B->v[5];
	 _A->v[6] -= _B->v[6];
	 _A->v[7] -= _B->v[7];
	 _A->v[8] -= _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fMultiplyElementwise(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
	 _out->v[2] = _A->v[2] * _B->v[2];
	 _out->v[3] = _A->v[3] * _B->v[3];
	 _out->v[4] = _A->v[4] * _B->v[4];
	 _out->v[5] = _A->v[5] * _B->v[5];
	 _out->v[6] = _A->v[6] * _B->v[6];
	 _out->v[7] = _A->v[7] * _B->v[7];
	 _out->v[8] = _A->v[8] * _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fMultiplyElementwiseLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
	 _A->v[4] *= _B->v[4];
	 _A->v[5] *= _B->v[5];
	 _A->v[6] *= _B->v[6];
	 _A->v[7] *= _B->v[7];
	 _A->v[8] *= _B->v[8];
}

/******************************************************************************/

void SST_Math_Mat33fMultiplyScalar(const SST_Mat33f* RESTRICT _A, const float k,  SST_Mat33f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
	 _out->v[4] = _A->v[4] * k;
	 _out->v[5] = _A->v[5] * k;
	 _out->v[6] = _A->v[6] * k;
	 _out->v[7] = _A->v[7] * k;
	 _out->v[8] = _A->v[8] * k;
}

/******************************************************************************/

void SST_Math_Mat33fMultiplyScalarLocal(SST_Mat33f* RESTRICT _A, const float k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
	 _A->v[4] *= k;
	 _A->v[5] *= k;
	 _A->v[6] *= k;
	 _A->v[7] *= k;
	 _A->v[8] *= k;
}

/******************************************************************************/


void SST_Math_Mat33fMultiplyMatrix(const SST_Mat33f* _A, const SST_Mat33f*  RESTRICT _B, SST_Mat33f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1]+_A->v[ 6]*_B->v[ 2];
_out->v[ 3] = _A->v[ 0]*_B->v[ 3]+_A->v[ 3]*_B->v[ 4]+_A->v[ 6]*_B->v[ 5];
_out->v[ 6] = _A->v[ 0]*_B->v[ 6]+_A->v[ 3]*_B->v[ 7]+_A->v[ 6]*_B->v[ 8];
_out->v[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 4]*_B->v[ 1]+_A->v[ 7]*_B->v[ 2];
_out->v[ 4] = _A->v[ 1]*_B->v[ 3]+_A->v[ 4]*_B->v[ 4]+_A->v[ 7]*_B->v[ 5];
_out->v[ 7] = _A->v[ 1]*_B->v[ 6]+_A->v[ 4]*_B->v[ 7]+_A->v[ 7]*_B->v[ 8];
_out->v[ 2] = _A->v[ 2]*_B->v[ 0]+_A->v[ 5]*_B->v[ 1]+_A->v[ 8]*_B->v[ 2];
_out->v[ 5] = _A->v[ 2]*_B->v[ 3]+_A->v[ 5]*_B->v[ 4]+_A->v[ 8]*_B->v[ 5];
_out->v[ 8] = _A->v[ 2]*_B->v[ 6]+_A->v[ 5]*_B->v[ 7]+_A->v[ 8]*_B->v[ 8];
}
void SST_Math_Mat33fMultiplyMatrixLocal(SST_Mat33f*  RESTRICT _A, const SST_Mat33f*  RESTRICT _B)
{
	float tmp[9];
	SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
tmp[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1]+_A->v[ 6]*_B->v[ 2];
tmp[ 3] = _A->v[ 0]*_B->v[ 3]+_A->v[ 3]*_B->v[ 4]+_A->v[ 6]*_B->v[ 5];
tmp[ 6] = _A->v[ 0]*_B->v[ 6]+_A->v[ 3]*_B->v[ 7]+_A->v[ 6]*_B->v[ 8];
_A->v[0] = tmp[0];
_A->v[3] = tmp[3];
_A->v[6] = tmp[6];


tmp[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 4]*_B->v[ 1]+_A->v[ 7]*_B->v[ 2];
tmp[ 4] = _A->v[ 1]*_B->v[ 3]+_A->v[ 4]*_B->v[ 4]+_A->v[ 7]*_B->v[ 5];
tmp[ 7] = _A->v[ 1]*_B->v[ 6]+_A->v[ 4]*_B->v[ 7]+_A->v[ 7]*_B->v[ 8];
_A->v[1] = tmp[1];
_A->v[4] = tmp[4];
_A->v[7] = tmp[7];


tmp[ 2] = _A->v[ 2]*_B->v[ 0]+_A->v[ 5]*_B->v[ 1]+_A->v[ 8]*_B->v[ 2];
tmp[ 5] = _A->v[ 2]*_B->v[ 3]+_A->v[ 5]*_B->v[ 4]+_A->v[ 8]*_B->v[ 5];
tmp[ 8] = _A->v[ 2]*_B->v[ 6]+_A->v[ 5]*_B->v[ 7]+_A->v[ 8]*_B->v[ 8];
_A->v[2] = tmp[2];
_A->v[5] = tmp[5];
_A->v[8] = tmp[8];


}
void SST_Math_Mat33fMultiplyVector(const SST_Mat33f*  RESTRICT _A, const SST_Vec3f*  RESTRICT _v, SST_Vec3f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 3]*_v->v[1]+_A->v[ 6]*_v->v[2];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 7]*_v->v[2];
_out->v[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 8]*_v->v[2];
}
void SST_Math_Mat33fMultiplyVectorLocal(const SST_Mat33f*  RESTRICT _A, SST_Vec3f*  RESTRICT _v)
{
float tmp[3];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 3]*_v->v[1]+_A->v[ 6]*_v->v[2];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 7]*_v->v[2];
tmp[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 8]*_v->v[2];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
_v->v[2] = tmp[2];
}
void SST_Math_Mat33fTranspose(const SST_Mat33f*  RESTRICT _A, SST_Mat33f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0];
_out->v[ 1] = _A->v[ 3];
_out->v[ 2] = _A->v[ 6];
_out->v[ 3] = _A->v[ 1];
_out->v[ 4] = _A->v[ 4];
_out->v[ 5] = _A->v[ 7];
_out->v[ 6] = _A->v[ 2];
_out->v[ 7] = _A->v[ 5];
_out->v[ 8] = _A->v[ 8];
}
void SST_Math_Mat33fTransposeLocal(SST_Mat33f*  RESTRICT _A)
{
float tmp[3];
SST_ASSUME_ALIGNED(_A,16);
tmp[1] = _A->v[ 3];
_A->v[ 3] = _A->v[ 1];
_A->v[ 1] = tmp[1];
tmp[2] = _A->v[ 6];
_A->v[ 6] = _A->v[ 2];
_A->v[ 2] = tmp[2];
tmp[2] = _A->v[ 7];
_A->v[ 7] = _A->v[ 5];
_A->v[ 5] = tmp[2];
}
bool SST_Math_Mat33fCheckOrthonormal(const SST_Mat33f* _A)
{
const float diag = -_A->v[0]*_A->v[0] -_A->v[1]*_A->v[1] -_A->v[2]*_A->v[2] -_A->v[3]*_A->v[3] -_A->v[4]*_A->v[4] -_A->v[5]*_A->v[5] -_A->v[6]*_A->v[6] -_A->v[7]*_A->v[7] -_A->v[8]*_A->v[8];
const float odiag = _A->v[0]*_A->v[3]+ _A->v[1]*_A->v[4]+ _A->v[2]*_A->v[5]+ _A->v[0]*_A->v[6]+ _A->v[1]*_A->v[7]+ _A->v[2]*_A->v[8]+ _A->v[3]*_A->v[0]+ _A->v[4]*_A->v[1]+ _A->v[5]*_A->v[2]+ _A->v[3]*_A->v[6]+ _A->v[4]*_A->v[7]+ _A->v[5]*_A->v[8]+ _A->v[6]*_A->v[0]+ _A->v[7]*_A->v[1]+ _A->v[8]*_A->v[2]+ _A->v[6]*_A->v[3]+ _A->v[7]*_A->v[4]+ _A->v[8]*_A->v[5];
SST_ASSUME_ALIGNED(_A,16);
return 
((fabsf(3.000000f+diag)) <= 100*FLT_EPSILON) &
((fabsf(odiag)) <= 100*FLT_EPSILON);


}
float SST_Math_Mat33fDeterminant(const SST_Mat33f* _A)
{
	const float result = _A->v[0]*(_A->v[4]*_A->v[8]-_A->v[5]*_A->v[7])-_A->v[1]*(_A->v[3]*_A->v[8]-_A->v[6]*_A->v[5])+_A->v[2]*(_A->v[3]*_A->v[7]-_A->v[6]*_A->v[4]);
	SST_ASSUME_ALIGNED(_A,16);
	return result;
}
void SST_Math_Mat33fInvert(const SST_Mat33f*  RESTRICT _A, SST_Mat33f*  RESTRICT _out)
{
/* Gaussian Elimination */
#define _A(i,j) _A->v[i+3*j]
#define _out(i,j) _out->v[i+3*j]
#define Pinv(i,j) Pinv.v[i+3*j]
float aij;
float  norm_aij;
SST_Mat33f Pinv;
SST_ASSUME_ALIGNED(_A,16);
/* Set _out to the identity */
_out(0,0) = 1.000000f;
_out(1,0) = 0.000000f;
_out(2,0) = 0.000000f;
_out(0,1) = 0.000000f;
_out(1,1) = 1.000000f;
_out(2,1) = 0.000000f;
_out(0,2) = 0.000000f;
_out(1,2) = 0.000000f;
_out(2,2) = 1.000000f;
/* Set _Pinv to _A so we don't overwrite it */
Pinv.v[0] = _A->v[0];
Pinv.v[1] = _A->v[1];
Pinv.v[2] = _A->v[2];
Pinv.v[3] = _A->v[3];
Pinv.v[4] = _A->v[4];
Pinv.v[5] = _A->v[5];
Pinv.v[6] = _A->v[6];
Pinv.v[7] = _A->v[7];
Pinv.v[8] = _A->v[8];
/* Put in Reduced Row Echelon form */
/* Note that we can set the entry to 0, or just calculate it. 
 The latter will be helpful when recognizing that these are all simple vector moves */
/* Sort if need be */
aij = -Pinv(1,0) / Pinv(0,0) ;
Pinv(1,0) += aij*Pinv(0,0) ;
Pinv(1,1) += aij*Pinv(0,1) ;
Pinv(1,2) += aij*Pinv(0,2) ;
_out(1,0) += aij*_out(0,0) ;
_out(1,1) += aij*_out(0,1) ;
_out(1,2) += aij*_out(0,2) ;
/* Sort if need be */
aij = -Pinv(2,0) / Pinv(0,0) ;
Pinv(2,0) += aij*Pinv(0,0) ;
Pinv(2,1) += aij*Pinv(0,1) ;
Pinv(2,2) += aij*Pinv(0,2) ;
_out(2,0) += aij*_out(0,0) ;
_out(2,1) += aij*_out(0,1) ;
_out(2,2) += aij*_out(0,2) ;
/* Sort if need be */
aij = -Pinv(2,1) / Pinv(1,1) ;
Pinv(2,0) += aij*Pinv(1,0) ;
Pinv(2,1) += aij*Pinv(1,1) ;
Pinv(2,2) += aij*Pinv(1,2) ;
_out(2,0) += aij*_out(1,0) ;
_out(2,1) += aij*_out(1,1) ;
_out(2,2) += aij*_out(1,2) ;
/* Backsubstitution */
norm_aij = 1.000000f / Pinv(2,2) ;
Pinv(2,2) = 1.000000f;
_out(2,0) *= norm_aij;
_out(2,1) *= norm_aij;
_out(2,2) *= norm_aij;
aij = -Pinv(0,2);
Pinv(0,0) += aij*Pinv(2,0);
Pinv(0,1) += aij*Pinv(2,1);
Pinv(0,2) += aij*Pinv(2,2);
_out(0,0) += aij*_out(2,0);
_out(0,1) += aij*_out(2,1);
_out(0,2) += aij*_out(2,2);
aij = -Pinv(1,2);
Pinv(1,0) += aij*Pinv(2,0);
Pinv(1,1) += aij*Pinv(2,1);
Pinv(1,2) += aij*Pinv(2,2);
_out(1,0) += aij*_out(2,0);
_out(1,1) += aij*_out(2,1);
_out(1,2) += aij*_out(2,2);
norm_aij = 1.000000f / Pinv(1,1) ;
Pinv(1,1) = 1.000000f;
_out(1,0) *= norm_aij;
_out(1,1) *= norm_aij;
_out(1,2) *= norm_aij;
aij = -Pinv(0,1);
Pinv(0,0) += aij*Pinv(1,0);
Pinv(0,1) += aij*Pinv(1,1);
Pinv(0,2) += aij*Pinv(1,2);
_out(0,0) += aij*_out(1,0);
_out(0,1) += aij*_out(1,1);
_out(0,2) += aij*_out(1,2);
norm_aij = 1.000000f / Pinv(0,0) ;
Pinv(0,0) = 1.000000f;
_out(0,0) *= norm_aij;
_out(0,1) *= norm_aij;
_out(0,2) *= norm_aij;
#undef _A
#undef _out
#undef Pinv
}
void SST_Math_Mat33fInvertLocal(SST_Mat33f* RESTRICT _A)
{
/* Gaussian Elimination */
#define _A(i,j) _A->v[i+3*j]
#define out(i,j) out->v[i+3*j]
#define Pinv(i,j) Pinv.v[i+3*j]
float aij;
float  norm_aij;
SST_Mat33f Pinv;
SST_ASSUME_ALIGNED(_A,16);
/* Set _out to the identity */
/* Set _Pinv to _A so we don't overwrite it */
Pinv.v[0] = _A->v[0];
Pinv.v[1] = _A->v[1];
Pinv.v[2] = _A->v[2];
Pinv.v[3] = _A->v[3];
Pinv.v[4] = _A->v[4];
Pinv.v[5] = _A->v[5];
Pinv.v[6] = _A->v[6];
Pinv.v[7] = _A->v[7];
Pinv.v[8] = _A->v[8];
_A(0,0) = 1.000000f;
_A(1,0) = 0.000000f;
_A(2,0) = 0.000000f;
_A(0,1) = 0.000000f;
_A(1,1) = 1.000000f;
_A(2,1) = 0.000000f;
_A(0,2) = 0.000000f;
_A(1,2) = 0.000000f;
_A(2,2) = 1.000000f;
/* Put in Reduced Row Echelon form */
/* Note that we can set the entry to 0, or just calculate it. 
 The latter will be helpful when recognizing that these are all simple vector moves */
/* Sort if need be */
aij = -Pinv(1,0) / Pinv(0,0) ;
Pinv(1,0) += aij*Pinv(0,0) ;
Pinv(1,1) += aij*Pinv(0,1) ;
Pinv(1,2) += aij*Pinv(0,2) ;
_A(1,0) += aij*_A(0,0) ;
_A(1,1) += aij*_A(0,1) ;
_A(1,2) += aij*_A(0,2) ;
/* Sort if need be */
aij = -Pinv(2,0) / Pinv(0,0) ;
Pinv(2,0) += aij*Pinv(0,0) ;
Pinv(2,1) += aij*Pinv(0,1) ;
Pinv(2,2) += aij*Pinv(0,2) ;
_A(2,0) += aij*_A(0,0) ;
_A(2,1) += aij*_A(0,1) ;
_A(2,2) += aij*_A(0,2) ;
/* Sort if need be */
aij = -Pinv(2,1) / Pinv(1,1) ;
Pinv(2,0) += aij*Pinv(1,0) ;
Pinv(2,1) += aij*Pinv(1,1) ;
Pinv(2,2) += aij*Pinv(1,2) ;
_A(2,0) += aij*_A(1,0) ;
_A(2,1) += aij*_A(1,1) ;
_A(2,2) += aij*_A(1,2) ;
/* Backsubstitution */
norm_aij = 1.000000f / Pinv(2,2) ;
Pinv(2,2) = 1.000000f;
_A(2,0) *= norm_aij;
_A(2,1) *= norm_aij;
_A(2,2) *= norm_aij;
aij = -Pinv.v[6];
Pinv.v[0] += aij*Pinv.v[2];
Pinv.v[3] += aij*Pinv.v[5];
Pinv.v[6] += aij*Pinv.v[8];
_A->v[0] += aij*_A->v[2];
_A->v[3] += aij*_A->v[5];
_A->v[6] += aij*_A->v[8];
aij = -Pinv.v[7];
Pinv.v[1] += aij*Pinv.v[2];
Pinv.v[4] += aij*Pinv.v[5];
Pinv.v[7] += aij*Pinv.v[8];
_A->v[1] += aij*_A->v[2];
_A->v[4] += aij*_A->v[5];
_A->v[7] += aij*_A->v[8];
norm_aij = 1.000000f / Pinv(1,1) ;
Pinv(1,1) = 1.000000f;
_A(1,0) *= norm_aij;
_A(1,1) *= norm_aij;
_A(1,2) *= norm_aij;
aij = -Pinv.v[3];
Pinv.v[0] += aij*Pinv.v[1];
Pinv.v[3] += aij*Pinv.v[4];
Pinv.v[6] += aij*Pinv.v[7];
_A->v[0] += aij*_A->v[1];
_A->v[3] += aij*_A->v[4];
_A->v[6] += aij*_A->v[7];
norm_aij = 1.000000f / Pinv(0,0) ;
Pinv(0,0) = 1.000000f;
_A(0,0) *= norm_aij;
_A(0,1) *= norm_aij;
_A(0,2) *= norm_aij;
}
void SST_Math_Mat33fCreateLU(const SST_Mat33f* RESTRICT _A, SST_Mat33f* RESTRICT _LU)
{
#define _A(i,j) _A->v[i+3*j]
#define _LU(i,j) _LU->v[i+3*j]
    int i,j,k;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
    _LU(0,0) = _A(0,0);
    _LU(0,1) = 0;
    _LU(0,2) = 0;
    _LU(1,0) = _A(1,0);
    _LU(1,2) = 0;
    _LU(2,0) = _A(2,0);
    /* _U(0,0) = 1.000000f; */
    /* _U(1,1) = 1.000000f; */
    /* _U(2,2) = 1.000000f; */
    _LU(0,1) = _A(0,1) / _LU(0,0);
    _LU(0,2) = _A(0,2) / _LU(0,0);
    for(i=1; i < 3; i++) {

        for(j=1; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 3; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = (_A(i,j) + sum) / _LU(i,i);
        }
    }
#undef _A
#undef _LU
}
void SST_Math_Mat33fApplyLUMat(const SST_Mat33f* _LU, const SST_Mat33f* _A, SST_Mat33f* _out)
{
 
#define _LU(i,j) _LU->v[i+3*j]
#define _A(i,j) _A->v[i+3*j]
#define _out(i,j) _out->v[i+3*j]
    int i, j, col;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
SST_ASSUME_ALIGNED(_out,16);
    for(col = 0; col < 3; col++) {
        _out(0,col) = _A(0,col);
        _out(1,col) = _A(1,col);
        _out(2,col) = _A(2,col);
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 3; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 2; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 3; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) ; /* divide by U(i,i)=1 */
        }
    }
#undef _LU /* (i,j) _LU->v[i+3*j] */
#undef _A /* (i,j) _A->v[i+3*j] */
#undef _out /* (i,j) _out->v[i+3*j] */
}
void SST_Math_Mat33fApplyLUMatLocal(const SST_Mat33f* _LU,SST_Mat33f* _A)
{
 
#define _LU(i,j) _LU->v[i+3*j]
#define _A(i,j)  _A->v[i+3*j]
    int i, j, col;
    float sum;
    for(col = 0; col < 3; col++) {
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 3; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 2; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 3; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) ; /* U is 1s along the diagonal */
        }
    }
}
void SST_Math_Mat33fApplyLUVec(const SST_Mat33f* _LU, const SST_Vec3f* _v,SST_Vec3f* _w)
{
 
#define _LU(i,j) _LU->v[i+3*j]
    int i, j;
    float sum;
    _w->v[0] = _v->v[0];
    _w->v[1] = _v->v[1];
    _w->v[2] = _v->v[2];
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 3; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 2; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 3; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+3*j] */
}
void SST_Math_Mat33fApplyLUVecLocal(const SST_Mat33f* _LU,SST_Vec3f* _w)
{
 
#define _LU(i,j) _LU->v[i+3*j]
    int i, j;
    float sum;
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 3; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 2; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 3; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+3*j] */
}
void SST_Math_Mat33fCreateLULocal(SST_Mat33f* RESTRICT _A)
{
 /* Note this code stores both L and U inside of A */
 /* For A in R[n x m] we say that for n = m there is an LU = A decomposition [In our decomp, diag[L] = I. Furthermore there is an LU=PA decomposition, where P is a permutation matrix
 Step 1:  U(i,i:m) = A(i,i:m) 
 Step 2: L(i+1:n,i) = -A(i+1:n,i) 
 Step 3: ??? 
 Step 4: Profit */ 
#define _A(i,j) _A->v[i+3*j]
    int i,j,k;
    float sum;
/* These entries are the same as before in the algorithm. This is left in for purposes of clarity and completeness 
_L(0,0) = _A(0,0);
_L(1,0) = _A(1,0);
_L(2,0) = _A(2,0);
These entries are understood to be 1 in this storage format. This is left in for purposes of clarity and completeness 
_U(0,0) = 1.000000f;
_U(1,1) = 1.000000f;
_U(2,2) = 1.000000f;
*/
_A(0,1) = _A(0,1) / _A(0,0);
_A(0,2) = _A(0,2) / _A(0,0);
    for(i=1; i < 3; i++) {

        for(j=0; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 3; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = (_A(i,j) + sum) / _A(i,i);
        }
    }
#undef _A
}
