/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = unsigned int */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>
void SST_Math_Mat44uAdd(const SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B, SST_Mat44u* RESTRICT _out)
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
	 _out->v[9] = _A->v[9] + _B->v[9];
	 _out->v[10] = _A->v[10] + _B->v[10];
	 _out->v[11] = _A->v[11] + _B->v[11];
	 _out->v[12] = _A->v[12] + _B->v[12];
	 _out->v[13] = _A->v[13] + _B->v[13];
	 _out->v[14] = _A->v[14] + _B->v[14];
	 _out->v[15] = _A->v[15] + _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uAddLocal(SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B)
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
	 _A->v[9] += _B->v[9];
	 _A->v[10] += _B->v[10];
	 _A->v[11] += _B->v[11];
	 _A->v[12] += _B->v[12];
	 _A->v[13] += _B->v[13];
	 _A->v[14] += _B->v[14];
	 _A->v[15] += _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uSubtract(const SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B, SST_Mat44u* RESTRICT _out)
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
	 _out->v[9] = _A->v[9] - _B->v[9];
	 _out->v[10] = _A->v[10] - _B->v[10];
	 _out->v[11] = _A->v[11] - _B->v[11];
	 _out->v[12] = _A->v[12] - _B->v[12];
	 _out->v[13] = _A->v[13] - _B->v[13];
	 _out->v[14] = _A->v[14] - _B->v[14];
	 _out->v[15] = _A->v[15] - _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uSubtractLocal(SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B)
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
	 _A->v[9] -= _B->v[9];
	 _A->v[10] -= _B->v[10];
	 _A->v[11] -= _B->v[11];
	 _A->v[12] -= _B->v[12];
	 _A->v[13] -= _B->v[13];
	 _A->v[14] -= _B->v[14];
	 _A->v[15] -= _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uMultiplyElementwise(const SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B, SST_Mat44u* RESTRICT _out)
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
	 _out->v[9] = _A->v[9] * _B->v[9];
	 _out->v[10] = _A->v[10] * _B->v[10];
	 _out->v[11] = _A->v[11] * _B->v[11];
	 _out->v[12] = _A->v[12] * _B->v[12];
	 _out->v[13] = _A->v[13] * _B->v[13];
	 _out->v[14] = _A->v[14] * _B->v[14];
	 _out->v[15] = _A->v[15] * _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uMultiplyElementwiseLocal(SST_Mat44u* RESTRICT _A, const SST_Mat44u* RESTRICT _B)
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
	 _A->v[9] *= _B->v[9];
	 _A->v[10] *= _B->v[10];
	 _A->v[11] *= _B->v[11];
	 _A->v[12] *= _B->v[12];
	 _A->v[13] *= _B->v[13];
	 _A->v[14] *= _B->v[14];
	 _A->v[15] *= _B->v[15];
}

/******************************************************************************/

void SST_Math_Mat44uMultiplyScalar(const SST_Mat44u* RESTRICT _A, const unsigned int k,  SST_Mat44u* RESTRICT _out)
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
	 _out->v[9] = _A->v[9] * k;
	 _out->v[10] = _A->v[10] * k;
	 _out->v[11] = _A->v[11] * k;
	 _out->v[12] = _A->v[12] * k;
	 _out->v[13] = _A->v[13] * k;
	 _out->v[14] = _A->v[14] * k;
	 _out->v[15] = _A->v[15] * k;
}

/******************************************************************************/

void SST_Math_Mat44uMultiplyScalarLocal(SST_Mat44u* RESTRICT _A, const unsigned int k)
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
	 _A->v[9] *= k;
	 _A->v[10] *= k;
	 _A->v[11] *= k;
	 _A->v[12] *= k;
	 _A->v[13] *= k;
	 _A->v[14] *= k;
	 _A->v[15] *= k;
}

/******************************************************************************/


void SST_Math_Mat44uMultiplyMatrix(const SST_Mat44u* _A, const SST_Mat44u*  RESTRICT _B, SST_Mat44u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 4]*_B->v[ 1]+_A->v[ 8]*_B->v[ 2]+_A->v[12]*_B->v[ 3];
_out->v[ 4] = _A->v[ 0]*_B->v[ 4]+_A->v[ 4]*_B->v[ 5]+_A->v[ 8]*_B->v[ 6]+_A->v[12]*_B->v[ 7];
_out->v[ 8] = _A->v[ 0]*_B->v[ 8]+_A->v[ 4]*_B->v[ 9]+_A->v[ 8]*_B->v[10]+_A->v[12]*_B->v[11];
_out->v[12] = _A->v[ 0]*_B->v[12]+_A->v[ 4]*_B->v[13]+_A->v[ 8]*_B->v[14]+_A->v[12]*_B->v[15];
_out->v[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 5]*_B->v[ 1]+_A->v[ 9]*_B->v[ 2]+_A->v[13]*_B->v[ 3];
_out->v[ 5] = _A->v[ 1]*_B->v[ 4]+_A->v[ 5]*_B->v[ 5]+_A->v[ 9]*_B->v[ 6]+_A->v[13]*_B->v[ 7];
_out->v[ 9] = _A->v[ 1]*_B->v[ 8]+_A->v[ 5]*_B->v[ 9]+_A->v[ 9]*_B->v[10]+_A->v[13]*_B->v[11];
_out->v[13] = _A->v[ 1]*_B->v[12]+_A->v[ 5]*_B->v[13]+_A->v[ 9]*_B->v[14]+_A->v[13]*_B->v[15];
_out->v[ 2] = _A->v[ 2]*_B->v[ 0]+_A->v[ 6]*_B->v[ 1]+_A->v[10]*_B->v[ 2]+_A->v[14]*_B->v[ 3];
_out->v[ 6] = _A->v[ 2]*_B->v[ 4]+_A->v[ 6]*_B->v[ 5]+_A->v[10]*_B->v[ 6]+_A->v[14]*_B->v[ 7];
_out->v[10] = _A->v[ 2]*_B->v[ 8]+_A->v[ 6]*_B->v[ 9]+_A->v[10]*_B->v[10]+_A->v[14]*_B->v[11];
_out->v[14] = _A->v[ 2]*_B->v[12]+_A->v[ 6]*_B->v[13]+_A->v[10]*_B->v[14]+_A->v[14]*_B->v[15];
_out->v[ 3] = _A->v[ 3]*_B->v[ 0]+_A->v[ 7]*_B->v[ 1]+_A->v[11]*_B->v[ 2]+_A->v[15]*_B->v[ 3];
_out->v[ 7] = _A->v[ 3]*_B->v[ 4]+_A->v[ 7]*_B->v[ 5]+_A->v[11]*_B->v[ 6]+_A->v[15]*_B->v[ 7];
_out->v[11] = _A->v[ 3]*_B->v[ 8]+_A->v[ 7]*_B->v[ 9]+_A->v[11]*_B->v[10]+_A->v[15]*_B->v[11];
_out->v[15] = _A->v[ 3]*_B->v[12]+_A->v[ 7]*_B->v[13]+_A->v[11]*_B->v[14]+_A->v[15]*_B->v[15];
}
void SST_Math_Mat44uMultiplyMatrixLocal(SST_Mat44u*  RESTRICT _A, const SST_Mat44u*  RESTRICT _B)
{
	unsigned int tmp[16];
	SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
tmp[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 4]*_B->v[ 1]+_A->v[ 8]*_B->v[ 2]+_A->v[12]*_B->v[ 3];
tmp[ 4] = _A->v[ 0]*_B->v[ 4]+_A->v[ 4]*_B->v[ 5]+_A->v[ 8]*_B->v[ 6]+_A->v[12]*_B->v[ 7];
tmp[ 8] = _A->v[ 0]*_B->v[ 8]+_A->v[ 4]*_B->v[ 9]+_A->v[ 8]*_B->v[10]+_A->v[12]*_B->v[11];
tmp[12] = _A->v[ 0]*_B->v[12]+_A->v[ 4]*_B->v[13]+_A->v[ 8]*_B->v[14]+_A->v[12]*_B->v[15];
_A->v[0] = tmp[0];
_A->v[4] = tmp[4];
_A->v[8] = tmp[8];
_A->v[12] = tmp[12];


tmp[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 5]*_B->v[ 1]+_A->v[ 9]*_B->v[ 2]+_A->v[13]*_B->v[ 3];
tmp[ 5] = _A->v[ 1]*_B->v[ 4]+_A->v[ 5]*_B->v[ 5]+_A->v[ 9]*_B->v[ 6]+_A->v[13]*_B->v[ 7];
tmp[ 9] = _A->v[ 1]*_B->v[ 8]+_A->v[ 5]*_B->v[ 9]+_A->v[ 9]*_B->v[10]+_A->v[13]*_B->v[11];
tmp[13] = _A->v[ 1]*_B->v[12]+_A->v[ 5]*_B->v[13]+_A->v[ 9]*_B->v[14]+_A->v[13]*_B->v[15];
_A->v[1] = tmp[1];
_A->v[5] = tmp[5];
_A->v[9] = tmp[9];
_A->v[13] = tmp[13];


tmp[ 2] = _A->v[ 2]*_B->v[ 0]+_A->v[ 6]*_B->v[ 1]+_A->v[10]*_B->v[ 2]+_A->v[14]*_B->v[ 3];
tmp[ 6] = _A->v[ 2]*_B->v[ 4]+_A->v[ 6]*_B->v[ 5]+_A->v[10]*_B->v[ 6]+_A->v[14]*_B->v[ 7];
tmp[10] = _A->v[ 2]*_B->v[ 8]+_A->v[ 6]*_B->v[ 9]+_A->v[10]*_B->v[10]+_A->v[14]*_B->v[11];
tmp[14] = _A->v[ 2]*_B->v[12]+_A->v[ 6]*_B->v[13]+_A->v[10]*_B->v[14]+_A->v[14]*_B->v[15];
_A->v[2] = tmp[2];
_A->v[6] = tmp[6];
_A->v[10] = tmp[10];
_A->v[14] = tmp[14];


tmp[ 3] = _A->v[ 3]*_B->v[ 0]+_A->v[ 7]*_B->v[ 1]+_A->v[11]*_B->v[ 2]+_A->v[15]*_B->v[ 3];
tmp[ 7] = _A->v[ 3]*_B->v[ 4]+_A->v[ 7]*_B->v[ 5]+_A->v[11]*_B->v[ 6]+_A->v[15]*_B->v[ 7];
tmp[11] = _A->v[ 3]*_B->v[ 8]+_A->v[ 7]*_B->v[ 9]+_A->v[11]*_B->v[10]+_A->v[15]*_B->v[11];
tmp[15] = _A->v[ 3]*_B->v[12]+_A->v[ 7]*_B->v[13]+_A->v[11]*_B->v[14]+_A->v[15]*_B->v[15];
_A->v[3] = tmp[3];
_A->v[7] = tmp[7];
_A->v[11] = tmp[11];
_A->v[15] = tmp[15];


}
void SST_Math_Mat44uMultiplyVector(const SST_Mat44u*  RESTRICT _A, const SST_Vec4u*  RESTRICT _v, SST_Vec4u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 8]*_v->v[2]+_A->v[12]*_v->v[3];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 9]*_v->v[2]+_A->v[13]*_v->v[3];
_out->v[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 6]*_v->v[1]+_A->v[10]*_v->v[2]+_A->v[14]*_v->v[3];
_out->v[ 3] = _A->v[ 3]*_v->v[0]+_A->v[ 7]*_v->v[1]+_A->v[11]*_v->v[2]+_A->v[15]*_v->v[3];
}
void SST_Math_Mat44uMultiplyVectorLocal(const SST_Mat44u*  RESTRICT _A, SST_Vec4u*  RESTRICT _v)
{
unsigned int tmp[4];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 8]*_v->v[2]+_A->v[12]*_v->v[3];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 9]*_v->v[2]+_A->v[13]*_v->v[3];
tmp[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 6]*_v->v[1]+_A->v[10]*_v->v[2]+_A->v[14]*_v->v[3];
tmp[ 3] = _A->v[ 3]*_v->v[0]+_A->v[ 7]*_v->v[1]+_A->v[11]*_v->v[2]+_A->v[15]*_v->v[3];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
_v->v[2] = tmp[2];
_v->v[3] = tmp[3];
}
void SST_Math_Mat44uTranspose(const SST_Mat44u*  RESTRICT _A, SST_Mat44u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0];
_out->v[ 1] = _A->v[ 4];
_out->v[ 2] = _A->v[ 8];
_out->v[ 3] = _A->v[12];
_out->v[ 4] = _A->v[ 1];
_out->v[ 5] = _A->v[ 5];
_out->v[ 6] = _A->v[ 9];
_out->v[ 7] = _A->v[13];
_out->v[ 8] = _A->v[ 2];
_out->v[ 9] = _A->v[ 6];
_out->v[10] = _A->v[10];
_out->v[11] = _A->v[14];
_out->v[12] = _A->v[ 3];
_out->v[13] = _A->v[ 7];
_out->v[14] = _A->v[11];
_out->v[15] = _A->v[15];
}
void SST_Math_Mat44uTransposeLocal(SST_Mat44u*  RESTRICT _A)
{
unsigned int tmp[4];
SST_ASSUME_ALIGNED(_A,16);
tmp[1] = _A->v[ 4];
_A->v[ 4] = _A->v[ 1];
_A->v[ 1] = tmp[1];
tmp[2] = _A->v[ 8];
_A->v[ 8] = _A->v[ 2];
_A->v[ 2] = tmp[2];
tmp[3] = _A->v[12];
_A->v[12] = _A->v[ 3];
_A->v[ 3] = tmp[3];
tmp[2] = _A->v[ 9];
_A->v[ 9] = _A->v[ 6];
_A->v[ 6] = tmp[2];
tmp[3] = _A->v[13];
_A->v[13] = _A->v[ 7];
_A->v[ 7] = tmp[3];
tmp[3] = _A->v[14];
_A->v[14] = _A->v[11];
_A->v[11] = tmp[3];
}
