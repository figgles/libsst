/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = unsigned int */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>
void SST_Math_Mat22uAdd(const SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B, SST_Mat22u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
	 _out->v[2] = _A->v[2] + _B->v[2];
	 _out->v[3] = _A->v[3] + _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uAddLocal(SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uSubtract(const SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B, SST_Mat22u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
	 _out->v[2] = _A->v[2] - _B->v[2];
	 _out->v[3] = _A->v[3] - _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uSubtractLocal(SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uMultiplyElementwise(const SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B, SST_Mat22u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
	 _out->v[2] = _A->v[2] * _B->v[2];
	 _out->v[3] = _A->v[3] * _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uMultiplyElementwiseLocal(SST_Mat22u* RESTRICT _A, const SST_Mat22u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22uMultiplyScalar(const SST_Mat22u* RESTRICT _A, const unsigned int k,  SST_Mat22u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Mat22uMultiplyScalarLocal(SST_Mat22u* RESTRICT _A, const unsigned int k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/


void SST_Math_Mat22uMultiplyMatrix(const SST_Mat22u* _A, const SST_Mat22u*  RESTRICT _B, SST_Mat22u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 2]*_B->v[ 1];
_out->v[ 2] = _A->v[ 0]*_B->v[ 2]+_A->v[ 2]*_B->v[ 3];
_out->v[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1];
_out->v[ 3] = _A->v[ 1]*_B->v[ 2]+_A->v[ 3]*_B->v[ 3];
}
void SST_Math_Mat22uMultiplyMatrixLocal(SST_Mat22u*  RESTRICT _A, const SST_Mat22u*  RESTRICT _B)
{
	unsigned int tmp[4];
	SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
tmp[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 2]*_B->v[ 1];
tmp[ 2] = _A->v[ 0]*_B->v[ 2]+_A->v[ 2]*_B->v[ 3];
_A->v[0] = tmp[0];
_A->v[2] = tmp[2];


tmp[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1];
tmp[ 3] = _A->v[ 1]*_B->v[ 2]+_A->v[ 3]*_B->v[ 3];
_A->v[1] = tmp[1];
_A->v[3] = tmp[3];


}
void SST_Math_Mat22uMultiplyVector(const SST_Mat22u*  RESTRICT _A, const SST_Vec2u*  RESTRICT _v, SST_Vec2u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
}
void SST_Math_Mat22uMultiplyVectorLocal(const SST_Mat22u*  RESTRICT _A, SST_Vec2u*  RESTRICT _v)
{
unsigned int tmp[2];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
}
void SST_Math_Mat22uTranspose(const SST_Mat22u*  RESTRICT _A, SST_Mat22u*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0];
_out->v[ 1] = _A->v[ 2];
_out->v[ 2] = _A->v[ 1];
_out->v[ 3] = _A->v[ 3];
}
void SST_Math_Mat22uTransposeLocal(SST_Mat22u*  RESTRICT _A)
{
unsigned int tmp[2];
SST_ASSUME_ALIGNED(_A,16);
tmp[1] = _A->v[ 2];
_A->v[ 2] = _A->v[ 1];
_A->v[ 1] = tmp[1];
}
