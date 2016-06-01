/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = float */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat44.h>
#include <SST/SST_Vec4.h>
void SST_Math_Mat44fAdd(const SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B, SST_Mat44f* RESTRICT _out)
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

void SST_Math_Mat44fAddLocal(SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B)
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

void SST_Math_Mat44fSubtract(const SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B, SST_Mat44f* RESTRICT _out)
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

void SST_Math_Mat44fSubtractLocal(SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B)
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

void SST_Math_Mat44fMultiplyElementwise(const SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B, SST_Mat44f* RESTRICT _out)
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

void SST_Math_Mat44fMultiplyElementwiseLocal(SST_Mat44f* RESTRICT _A, const SST_Mat44f* RESTRICT _B)
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

void SST_Math_Mat44fMultiplyScalar(const SST_Mat44f* RESTRICT _A, const float k,  SST_Mat44f* RESTRICT _out)
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

void SST_Math_Mat44fMultiplyScalarLocal(SST_Mat44f* RESTRICT _A, const float k)
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


void SST_Math_Mat44fMultiplyMatrix(const SST_Mat44f* _A, const SST_Mat44f*  RESTRICT _B, SST_Mat44f*  RESTRICT _out)
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
void SST_Math_Mat44fMultiplyMatrixLocal(SST_Mat44f*  RESTRICT _A, const SST_Mat44f*  RESTRICT _B)
{
	float tmp[16];
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
void SST_Math_Mat44fMultiplyVector(const SST_Mat44f*  RESTRICT _A, const SST_Vec4f*  RESTRICT _v, SST_Vec4f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 8]*_v->v[2]+_A->v[12]*_v->v[3];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 9]*_v->v[2]+_A->v[13]*_v->v[3];
_out->v[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 6]*_v->v[1]+_A->v[10]*_v->v[2]+_A->v[14]*_v->v[3];
_out->v[ 3] = _A->v[ 3]*_v->v[0]+_A->v[ 7]*_v->v[1]+_A->v[11]*_v->v[2]+_A->v[15]*_v->v[3];
}
void SST_Math_Mat44fMultiplyVectorLocal(const SST_Mat44f*  RESTRICT _A, SST_Vec4f*  RESTRICT _v)
{
float tmp[4];
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
void SST_Math_Mat44fTranspose(const SST_Mat44f*  RESTRICT _A, SST_Mat44f*  RESTRICT _out)
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
void SST_Math_Mat44fTransposeLocal(SST_Mat44f*  RESTRICT _A)
{
float tmp[4];
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
bool SST_Math_Mat44fCheckOrthonormal(const SST_Mat44f* _A)
{
const float diag = -_A->v[0]*_A->v[0] -_A->v[1]*_A->v[1] -_A->v[2]*_A->v[2] -_A->v[3]*_A->v[3] -_A->v[4]*_A->v[4] -_A->v[5]*_A->v[5] -_A->v[6]*_A->v[6] -_A->v[7]*_A->v[7] -_A->v[8]*_A->v[8] -_A->v[9]*_A->v[9] -_A->v[10]*_A->v[10] -_A->v[11]*_A->v[11] -_A->v[12]*_A->v[12] -_A->v[13]*_A->v[13] -_A->v[14]*_A->v[14] -_A->v[15]*_A->v[15];
const float odiag = _A->v[0]*_A->v[4]+ _A->v[1]*_A->v[5]+ _A->v[2]*_A->v[6]+ _A->v[3]*_A->v[7]+ _A->v[0]*_A->v[8]+ _A->v[1]*_A->v[9]+ _A->v[2]*_A->v[10]+ _A->v[3]*_A->v[11]+ _A->v[0]*_A->v[12]+ _A->v[1]*_A->v[13]+ _A->v[2]*_A->v[14]+ _A->v[3]*_A->v[15]+ _A->v[4]*_A->v[0]+ _A->v[5]*_A->v[1]+ _A->v[6]*_A->v[2]+ _A->v[7]*_A->v[3]+ _A->v[4]*_A->v[8]+ _A->v[5]*_A->v[9]+ _A->v[6]*_A->v[10]+ _A->v[7]*_A->v[11]+ _A->v[4]*_A->v[12]+ _A->v[5]*_A->v[13]+ _A->v[6]*_A->v[14]+ _A->v[7]*_A->v[15]+ _A->v[8]*_A->v[0]+ _A->v[9]*_A->v[1]+ _A->v[10]*_A->v[2]+ _A->v[11]*_A->v[3]+ _A->v[8]*_A->v[4]+ _A->v[9]*_A->v[5]+ _A->v[10]*_A->v[6]+ _A->v[11]*_A->v[7]+ _A->v[8]*_A->v[12]+ _A->v[9]*_A->v[13]+ _A->v[10]*_A->v[14]+ _A->v[11]*_A->v[15]+ _A->v[12]*_A->v[0]+ _A->v[13]*_A->v[1]+ _A->v[14]*_A->v[2]+ _A->v[15]*_A->v[3]+ _A->v[12]*_A->v[4]+ _A->v[13]*_A->v[5]+ _A->v[14]*_A->v[6]+ _A->v[15]*_A->v[7]+ _A->v[12]*_A->v[8]+ _A->v[13]*_A->v[9]+ _A->v[14]*_A->v[10]+ _A->v[15]*_A->v[11];
SST_ASSUME_ALIGNED(_A,16);
return 
((fabsf(4.000000f+diag)) <= 100*FLT_EPSILON) &
((fabsf(odiag)) <= 100*FLT_EPSILON);


}
float SST_Math_Mat44fDeterminant(const SST_Mat44f* _A)
{
	const float a10151411 = _A->v[10]*_A->v[15]-_A->v[11]*_A->v[14];
	const float a9151311  =  _A->v[6]*_A->v[15]-_A->v[7]*_A->v[14];
	const float a9141310  =  _A->v[6]*_A->v[11]-_A->v[7]*_A->v[10];
	const float a8151112  =  _A->v[2]*_A->v[15]-_A->v[14]*_A->v[3];
	const float a8141210  =  _A->v[2]*_A->v[11]-_A->v[3]*_A->v[10];
	const float a813129   =  _A->v[2]*_A->v[7]-_A->v[3]*_A->v[6];
	const float result = _A->v[0]*(_A->v[5]*a10151411-_A->v[9]*a9151311+_A->v[13]*a9141310)-_A->v[4]*(_A->v[1]*a10151411-_A->v[9]*a8151112+_A->v[13]*a8141210)+_A->v[8]*(_A->v[1]*a9151311 -_A->v[5]*a8151112+_A->v[13]*a813129)-_A->v[12]*(_A->v[1]*a9141310 -_A->v[5]*a8141210+_A->v[9]*a813129);
	SST_ASSUME_ALIGNED(_A,16);
	return result;
}
void SST_Math_Mat44fInvert(const SST_Mat44f*  RESTRICT _A, SST_Mat44f*  RESTRICT _out)
{
/* Gaussian Elimination */
#define _A(i,j) _A->v[i+4*j]
#define _out(i,j) _out->v[i+4*j]
#define Pinv(i,j) Pinv.v[i+4*j]
float aij;
float  norm_aij;
SST_Mat44f Pinv;
SST_ASSUME_ALIGNED(_A,16);
/* Set _out to the identity */
_out(0,0) = 1.000000f;
_out(1,0) = 0.000000f;
_out(2,0) = 0.000000f;
_out(3,0) = 0.000000f;
_out(0,1) = 0.000000f;
_out(1,1) = 1.000000f;
_out(2,1) = 0.000000f;
_out(3,1) = 0.000000f;
_out(0,2) = 0.000000f;
_out(1,2) = 0.000000f;
_out(2,2) = 1.000000f;
_out(3,2) = 0.000000f;
_out(0,3) = 0.000000f;
_out(1,3) = 0.000000f;
_out(2,3) = 0.000000f;
_out(3,3) = 1.000000f;
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
Pinv.v[9] = _A->v[9];
Pinv.v[10] = _A->v[10];
Pinv.v[11] = _A->v[11];
Pinv.v[12] = _A->v[12];
Pinv.v[13] = _A->v[13];
Pinv.v[14] = _A->v[14];
Pinv.v[15] = _A->v[15];
/* Put in Reduced Row Echelon form */
/* Note that we can set the entry to 0, or just calculate it. 
 The latter will be helpful when recognizing that these are all simple vector moves */
/* Sort if need be */
aij = -Pinv(1,0) / Pinv(0,0) ;
Pinv(1,0) += aij*Pinv(0,0) ;
Pinv(1,1) += aij*Pinv(0,1) ;
Pinv(1,2) += aij*Pinv(0,2) ;
Pinv(1,3) += aij*Pinv(0,3) ;
_out(1,0) += aij*_out(0,0) ;
_out(1,1) += aij*_out(0,1) ;
_out(1,2) += aij*_out(0,2) ;
_out(1,3) += aij*_out(0,3) ;
/* Sort if need be */
aij = -Pinv(2,0) / Pinv(0,0) ;
Pinv(2,0) += aij*Pinv(0,0) ;
Pinv(2,1) += aij*Pinv(0,1) ;
Pinv(2,2) += aij*Pinv(0,2) ;
Pinv(2,3) += aij*Pinv(0,3) ;
_out(2,0) += aij*_out(0,0) ;
_out(2,1) += aij*_out(0,1) ;
_out(2,2) += aij*_out(0,2) ;
_out(2,3) += aij*_out(0,3) ;
/* Sort if need be */
aij = -Pinv(3,0) / Pinv(0,0) ;
Pinv(3,0) += aij*Pinv(0,0) ;
Pinv(3,1) += aij*Pinv(0,1) ;
Pinv(3,2) += aij*Pinv(0,2) ;
Pinv(3,3) += aij*Pinv(0,3) ;
_out(3,0) += aij*_out(0,0) ;
_out(3,1) += aij*_out(0,1) ;
_out(3,2) += aij*_out(0,2) ;
_out(3,3) += aij*_out(0,3) ;
/* Sort if need be */
aij = -Pinv(2,1) / Pinv(1,1) ;
Pinv(2,0) += aij*Pinv(1,0) ;
Pinv(2,1) += aij*Pinv(1,1) ;
Pinv(2,2) += aij*Pinv(1,2) ;
Pinv(2,3) += aij*Pinv(1,3) ;
_out(2,0) += aij*_out(1,0) ;
_out(2,1) += aij*_out(1,1) ;
_out(2,2) += aij*_out(1,2) ;
_out(2,3) += aij*_out(1,3) ;
/* Sort if need be */
aij = -Pinv(3,1) / Pinv(1,1) ;
Pinv(3,0) += aij*Pinv(1,0) ;
Pinv(3,1) += aij*Pinv(1,1) ;
Pinv(3,2) += aij*Pinv(1,2) ;
Pinv(3,3) += aij*Pinv(1,3) ;
_out(3,0) += aij*_out(1,0) ;
_out(3,1) += aij*_out(1,1) ;
_out(3,2) += aij*_out(1,2) ;
_out(3,3) += aij*_out(1,3) ;
/* Sort if need be */
aij = -Pinv(3,2) / Pinv(2,2) ;
Pinv(3,0) += aij*Pinv(2,0) ;
Pinv(3,1) += aij*Pinv(2,1) ;
Pinv(3,2) += aij*Pinv(2,2) ;
Pinv(3,3) += aij*Pinv(2,3) ;
_out(3,0) += aij*_out(2,0) ;
_out(3,1) += aij*_out(2,1) ;
_out(3,2) += aij*_out(2,2) ;
_out(3,3) += aij*_out(2,3) ;
/* Backsubstitution */
norm_aij = 1.000000f / Pinv(3,3) ;
Pinv(3,3) = 1.000000f;
_out(3,0) *= norm_aij;
_out(3,1) *= norm_aij;
_out(3,2) *= norm_aij;
_out(3,3) *= norm_aij;
aij = -Pinv(0,3);
Pinv(0,0) += aij*Pinv(3,0);
Pinv(0,1) += aij*Pinv(3,1);
Pinv(0,2) += aij*Pinv(3,2);
Pinv(0,3) += aij*Pinv(3,3);
_out(0,0) += aij*_out(3,0);
_out(0,1) += aij*_out(3,1);
_out(0,2) += aij*_out(3,2);
_out(0,3) += aij*_out(3,3);
aij = -Pinv(1,3);
Pinv(1,0) += aij*Pinv(3,0);
Pinv(1,1) += aij*Pinv(3,1);
Pinv(1,2) += aij*Pinv(3,2);
Pinv(1,3) += aij*Pinv(3,3);
_out(1,0) += aij*_out(3,0);
_out(1,1) += aij*_out(3,1);
_out(1,2) += aij*_out(3,2);
_out(1,3) += aij*_out(3,3);
aij = -Pinv(2,3);
Pinv(2,0) += aij*Pinv(3,0);
Pinv(2,1) += aij*Pinv(3,1);
Pinv(2,2) += aij*Pinv(3,2);
Pinv(2,3) += aij*Pinv(3,3);
_out(2,0) += aij*_out(3,0);
_out(2,1) += aij*_out(3,1);
_out(2,2) += aij*_out(3,2);
_out(2,3) += aij*_out(3,3);
norm_aij = 1.000000f / Pinv(2,2) ;
Pinv(2,2) = 1.000000f;
_out(2,0) *= norm_aij;
_out(2,1) *= norm_aij;
_out(2,2) *= norm_aij;
_out(2,3) *= norm_aij;
aij = -Pinv(0,2);
Pinv(0,0) += aij*Pinv(2,0);
Pinv(0,1) += aij*Pinv(2,1);
Pinv(0,2) += aij*Pinv(2,2);
Pinv(0,3) += aij*Pinv(2,3);
_out(0,0) += aij*_out(2,0);
_out(0,1) += aij*_out(2,1);
_out(0,2) += aij*_out(2,2);
_out(0,3) += aij*_out(2,3);
aij = -Pinv(1,2);
Pinv(1,0) += aij*Pinv(2,0);
Pinv(1,1) += aij*Pinv(2,1);
Pinv(1,2) += aij*Pinv(2,2);
Pinv(1,3) += aij*Pinv(2,3);
_out(1,0) += aij*_out(2,0);
_out(1,1) += aij*_out(2,1);
_out(1,2) += aij*_out(2,2);
_out(1,3) += aij*_out(2,3);
norm_aij = 1.000000f / Pinv(1,1) ;
Pinv(1,1) = 1.000000f;
_out(1,0) *= norm_aij;
_out(1,1) *= norm_aij;
_out(1,2) *= norm_aij;
_out(1,3) *= norm_aij;
aij = -Pinv(0,1);
Pinv(0,0) += aij*Pinv(1,0);
Pinv(0,1) += aij*Pinv(1,1);
Pinv(0,2) += aij*Pinv(1,2);
Pinv(0,3) += aij*Pinv(1,3);
_out(0,0) += aij*_out(1,0);
_out(0,1) += aij*_out(1,1);
_out(0,2) += aij*_out(1,2);
_out(0,3) += aij*_out(1,3);
norm_aij = 1.000000f / Pinv(0,0) ;
Pinv(0,0) = 1.000000f;
_out(0,0) *= norm_aij;
_out(0,1) *= norm_aij;
_out(0,2) *= norm_aij;
_out(0,3) *= norm_aij;
#undef _A
#undef _out
#undef Pinv
}
void SST_Math_Mat44fInvertLocal(SST_Mat44f* RESTRICT _A)
{
/* Gaussian Elimination */
#define _A(i,j) _A->v[i+4*j]
#define out(i,j) out->v[i+4*j]
#define Pinv(i,j) Pinv.v[i+4*j]
float aij;
float  norm_aij;
SST_Mat44f Pinv;
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
Pinv.v[9] = _A->v[9];
Pinv.v[10] = _A->v[10];
Pinv.v[11] = _A->v[11];
Pinv.v[12] = _A->v[12];
Pinv.v[13] = _A->v[13];
Pinv.v[14] = _A->v[14];
Pinv.v[15] = _A->v[15];
_A(0,0) = 1.000000f;
_A(1,0) = 0.000000f;
_A(2,0) = 0.000000f;
_A(3,0) = 0.000000f;
_A(0,1) = 0.000000f;
_A(1,1) = 1.000000f;
_A(2,1) = 0.000000f;
_A(3,1) = 0.000000f;
_A(0,2) = 0.000000f;
_A(1,2) = 0.000000f;
_A(2,2) = 1.000000f;
_A(3,2) = 0.000000f;
_A(0,3) = 0.000000f;
_A(1,3) = 0.000000f;
_A(2,3) = 0.000000f;
_A(3,3) = 1.000000f;
/* Put in Reduced Row Echelon form */
/* Note that we can set the entry to 0, or just calculate it. 
 The latter will be helpful when recognizing that these are all simple vector moves */
/* Sort if need be */
aij = -Pinv(1,0) / Pinv(0,0) ;
Pinv(1,0) += aij*Pinv(0,0) ;
Pinv(1,1) += aij*Pinv(0,1) ;
Pinv(1,2) += aij*Pinv(0,2) ;
Pinv(1,3) += aij*Pinv(0,3) ;
_A(1,0) += aij*_A(0,0) ;
_A(1,1) += aij*_A(0,1) ;
_A(1,2) += aij*_A(0,2) ;
_A(1,3) += aij*_A(0,3) ;
/* Sort if need be */
aij = -Pinv(2,0) / Pinv(0,0) ;
Pinv(2,0) += aij*Pinv(0,0) ;
Pinv(2,1) += aij*Pinv(0,1) ;
Pinv(2,2) += aij*Pinv(0,2) ;
Pinv(2,3) += aij*Pinv(0,3) ;
_A(2,0) += aij*_A(0,0) ;
_A(2,1) += aij*_A(0,1) ;
_A(2,2) += aij*_A(0,2) ;
_A(2,3) += aij*_A(0,3) ;
/* Sort if need be */
aij = -Pinv(3,0) / Pinv(0,0) ;
Pinv(3,0) += aij*Pinv(0,0) ;
Pinv(3,1) += aij*Pinv(0,1) ;
Pinv(3,2) += aij*Pinv(0,2) ;
Pinv(3,3) += aij*Pinv(0,3) ;
_A(3,0) += aij*_A(0,0) ;
_A(3,1) += aij*_A(0,1) ;
_A(3,2) += aij*_A(0,2) ;
_A(3,3) += aij*_A(0,3) ;
/* Sort if need be */
aij = -Pinv(2,1) / Pinv(1,1) ;
Pinv(2,0) += aij*Pinv(1,0) ;
Pinv(2,1) += aij*Pinv(1,1) ;
Pinv(2,2) += aij*Pinv(1,2) ;
Pinv(2,3) += aij*Pinv(1,3) ;
_A(2,0) += aij*_A(1,0) ;
_A(2,1) += aij*_A(1,1) ;
_A(2,2) += aij*_A(1,2) ;
_A(2,3) += aij*_A(1,3) ;
/* Sort if need be */
aij = -Pinv(3,1) / Pinv(1,1) ;
Pinv(3,0) += aij*Pinv(1,0) ;
Pinv(3,1) += aij*Pinv(1,1) ;
Pinv(3,2) += aij*Pinv(1,2) ;
Pinv(3,3) += aij*Pinv(1,3) ;
_A(3,0) += aij*_A(1,0) ;
_A(3,1) += aij*_A(1,1) ;
_A(3,2) += aij*_A(1,2) ;
_A(3,3) += aij*_A(1,3) ;
/* Sort if need be */
aij = -Pinv(3,2) / Pinv(2,2) ;
Pinv(3,0) += aij*Pinv(2,0) ;
Pinv(3,1) += aij*Pinv(2,1) ;
Pinv(3,2) += aij*Pinv(2,2) ;
Pinv(3,3) += aij*Pinv(2,3) ;
_A(3,0) += aij*_A(2,0) ;
_A(3,1) += aij*_A(2,1) ;
_A(3,2) += aij*_A(2,2) ;
_A(3,3) += aij*_A(2,3) ;
/* Backsubstitution */
norm_aij = 1.000000f / Pinv(3,3) ;
Pinv(3,3) = 1.000000f;
_A(3,0) *= norm_aij;
_A(3,1) *= norm_aij;
_A(3,2) *= norm_aij;
_A(3,3) *= norm_aij;
aij = -Pinv.v[12];
Pinv.v[0] += aij*Pinv.v[3];
Pinv.v[4] += aij*Pinv.v[7];
Pinv.v[8] += aij*Pinv.v[11];
Pinv.v[12] += aij*Pinv.v[15];
_A->v[0] += aij*_A->v[3];
_A->v[4] += aij*_A->v[7];
_A->v[8] += aij*_A->v[11];
_A->v[12] += aij*_A->v[15];
aij = -Pinv.v[13];
Pinv.v[1] += aij*Pinv.v[3];
Pinv.v[5] += aij*Pinv.v[7];
Pinv.v[9] += aij*Pinv.v[11];
Pinv.v[13] += aij*Pinv.v[15];
_A->v[1] += aij*_A->v[3];
_A->v[5] += aij*_A->v[7];
_A->v[9] += aij*_A->v[11];
_A->v[13] += aij*_A->v[15];
aij = -Pinv.v[14];
Pinv.v[2] += aij*Pinv.v[3];
Pinv.v[6] += aij*Pinv.v[7];
Pinv.v[10] += aij*Pinv.v[11];
Pinv.v[14] += aij*Pinv.v[15];
_A->v[2] += aij*_A->v[3];
_A->v[6] += aij*_A->v[7];
_A->v[10] += aij*_A->v[11];
_A->v[14] += aij*_A->v[15];
norm_aij = 1.000000f / Pinv(2,2) ;
Pinv(2,2) = 1.000000f;
_A(2,0) *= norm_aij;
_A(2,1) *= norm_aij;
_A(2,2) *= norm_aij;
_A(2,3) *= norm_aij;
aij = -Pinv.v[8];
Pinv.v[0] += aij*Pinv.v[2];
Pinv.v[4] += aij*Pinv.v[6];
Pinv.v[8] += aij*Pinv.v[10];
Pinv.v[12] += aij*Pinv.v[14];
_A->v[0] += aij*_A->v[2];
_A->v[4] += aij*_A->v[6];
_A->v[8] += aij*_A->v[10];
_A->v[12] += aij*_A->v[14];
aij = -Pinv.v[9];
Pinv.v[1] += aij*Pinv.v[2];
Pinv.v[5] += aij*Pinv.v[6];
Pinv.v[9] += aij*Pinv.v[10];
Pinv.v[13] += aij*Pinv.v[14];
_A->v[1] += aij*_A->v[2];
_A->v[5] += aij*_A->v[6];
_A->v[9] += aij*_A->v[10];
_A->v[13] += aij*_A->v[14];
norm_aij = 1.000000f / Pinv(1,1) ;
Pinv(1,1) = 1.000000f;
_A(1,0) *= norm_aij;
_A(1,1) *= norm_aij;
_A(1,2) *= norm_aij;
_A(1,3) *= norm_aij;
aij = -Pinv.v[4];
Pinv.v[0] += aij*Pinv.v[1];
Pinv.v[4] += aij*Pinv.v[5];
Pinv.v[8] += aij*Pinv.v[9];
Pinv.v[12] += aij*Pinv.v[13];
_A->v[0] += aij*_A->v[1];
_A->v[4] += aij*_A->v[5];
_A->v[8] += aij*_A->v[9];
_A->v[12] += aij*_A->v[13];
norm_aij = 1.000000f / Pinv(0,0) ;
Pinv(0,0) = 1.000000f;
_A(0,0) *= norm_aij;
_A(0,1) *= norm_aij;
_A(0,2) *= norm_aij;
_A(0,3) *= norm_aij;
}
void SST_Math_Mat44fCreateLU(const SST_Mat44f* RESTRICT _A, SST_Mat44f* RESTRICT _LU)
{
#define _A(i,j) _A->v[i+4*j]
#define _LU(i,j) _LU->v[i+4*j]
    int i,j,k;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
    _LU(0,0) = _A(0,0);
    _LU(0,1) = 0;
    _LU(0,2) = 0;
    _LU(0,3) = 0;
    _LU(1,0) = _A(1,0);
    _LU(1,2) = 0;
    _LU(1,3) = 0;
    _LU(2,0) = _A(2,0);
    _LU(2,3) = 0;
    _LU(3,0) = _A(3,0);
    /* _U(0,0) = 1.000000f; */
    /* _U(1,1) = 1.000000f; */
    /* _U(2,2) = 1.000000f; */
    /* _U(3,3) = 1.000000f; */
    _LU(0,1) = _A(0,1) / _LU(0,0);
    _LU(0,2) = _A(0,2) / _LU(0,0);
    _LU(0,3) = _A(0,3) / _LU(0,0);
    for(i=1; i < 4; i++) {

        for(j=1; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 4; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = (_A(i,j) + sum) / _LU(i,i);
        }
    }
#undef _A
#undef _LU
}
void SST_Math_Mat44fApplyLUMat(const SST_Mat44f* _LU, const SST_Mat44f* _A, SST_Mat44f* _out)
{
 
#define _LU(i,j) _LU->v[i+4*j]
#define _A(i,j) _A->v[i+4*j]
#define _out(i,j) _out->v[i+4*j]
    int i, j, col;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
SST_ASSUME_ALIGNED(_out,16);
    for(col = 0; col < 4; col++) {
        _out(0,col) = _A(0,col);
        _out(1,col) = _A(1,col);
        _out(2,col) = _A(2,col);
        _out(3,col) = _A(3,col);
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 4; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 3; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 4; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) ; /* divide by U(i,i)=1 */
        }
    }
#undef _LU /* (i,j) _LU->v[i+4*j] */
#undef _A /* (i,j) _A->v[i+4*j] */
#undef _out /* (i,j) _out->v[i+4*j] */
}
void SST_Math_Mat44fApplyLUMatLocal(const SST_Mat44f* _LU,SST_Mat44f* _A)
{
 
#define _LU(i,j) _LU->v[i+4*j]
#define _A(i,j)  _A->v[i+4*j]
    int i, j, col;
    float sum;
    for(col = 0; col < 4; col++) {
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 4; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 3; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 4; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) ; /* U is 1s along the diagonal */
        }
    }
}
void SST_Math_Mat44fApplyLUVec(const SST_Mat44f* _LU, const SST_Vec4f* _v,SST_Vec4f* _w)
{
 
#define _LU(i,j) _LU->v[i+4*j]
    int i, j;
    float sum;
    _w->v[0] = _v->v[0];
    _w->v[1] = _v->v[1];
    _w->v[2] = _v->v[2];
    _w->v[3] = _v->v[3];
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 4; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 3; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 4; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+4*j] */
}
void SST_Math_Mat44fApplyLUVecLocal(const SST_Mat44f* _LU,SST_Vec4f* _w)
{
 
#define _LU(i,j) _LU->v[i+4*j]
    int i, j;
    float sum;
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 4; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 3; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 4; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+4*j] */
}
void SST_Math_Mat44fCreateLULocal(SST_Mat44f* RESTRICT _A)
{
 /* Note this code stores both L and U inside of A */
 /* For A in R[n x m] we say that for n = m there is an LU = A decomposition [In our decomp, diag[L] = I. Furthermore there is an LU=PA decomposition, where P is a permutation matrix
 Step 1:  U(i,i:m) = A(i,i:m) 
 Step 2: L(i+1:n,i) = -A(i+1:n,i) 
 Step 3: ??? 
 Step 4: Profit */ 
#define _A(i,j) _A->v[i+4*j]
    int i,j,k;
    float sum;
/* These entries are the same as before in the algorithm. This is left in for purposes of clarity and completeness 
_L(0,0) = _A(0,0);
_L(1,0) = _A(1,0);
_L(2,0) = _A(2,0);
_L(3,0) = _A(3,0);
These entries are understood to be 1 in this storage format. This is left in for purposes of clarity and completeness 
_U(0,0) = 1.000000f;
_U(1,1) = 1.000000f;
_U(2,2) = 1.000000f;
_U(3,3) = 1.000000f;
*/
_A(0,1) = _A(0,1) / _A(0,0);
_A(0,2) = _A(0,2) / _A(0,0);
_A(0,3) = _A(0,3) / _A(0,0);
    for(i=1; i < 4; i++) {

        for(j=0; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 4; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = (_A(i,j) + sum) / _A(i,i);
        }
    }
#undef _A
}
