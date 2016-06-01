/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = int */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>
void SST_Math_Mat22iAdd(const SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B, SST_Mat22i* RESTRICT _out)
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

void SST_Math_Mat22iAddLocal(SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22iSubtract(const SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B, SST_Mat22i* RESTRICT _out)
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

void SST_Math_Mat22iSubtractLocal(SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22iMultiplyElementwise(const SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B, SST_Mat22i* RESTRICT _out)
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

void SST_Math_Mat22iMultiplyElementwiseLocal(SST_Mat22i* RESTRICT _A, const SST_Mat22i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22iMultiplyScalar(const SST_Mat22i* RESTRICT _A, const int k,  SST_Mat22i* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Mat22iMultiplyScalarLocal(SST_Mat22i* RESTRICT _A, const int k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/


void SST_Math_Mat22iMultiplyMatrix(const SST_Mat22i* _A, const SST_Mat22i*  RESTRICT _B, SST_Mat22i*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 2]*_B->v[ 1];
_out->v[ 2] = _A->v[ 0]*_B->v[ 2]+_A->v[ 2]*_B->v[ 3];
_out->v[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1];
_out->v[ 3] = _A->v[ 1]*_B->v[ 2]+_A->v[ 3]*_B->v[ 3];
}
void SST_Math_Mat22iMultiplyMatrixLocal(SST_Mat22i*  RESTRICT _A, const SST_Mat22i*  RESTRICT _B)
{
	int tmp[4];
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
void SST_Math_Mat22iMultiplyVector(const SST_Mat22i*  RESTRICT _A, const SST_Vec2i*  RESTRICT _v, SST_Vec2i*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
}
void SST_Math_Mat22iMultiplyVectorLocal(const SST_Mat22i*  RESTRICT _A, SST_Vec2i*  RESTRICT _v)
{
int tmp[2];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
}
void SST_Math_Mat22iTranspose(const SST_Mat22i*  RESTRICT _A, SST_Mat22i*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0];
_out->v[ 1] = _A->v[ 2];
_out->v[ 2] = _A->v[ 1];
_out->v[ 3] = _A->v[ 3];
}
void SST_Math_Mat22iTransposeLocal(SST_Mat22i*  RESTRICT _A)
{
int tmp[2];
SST_ASSUME_ALIGNED(_A,16);
tmp[1] = _A->v[ 2];
_A->v[ 2] = _A->v[ 1];
_A->v[ 1] = tmp[1];
}
bool SST_Math_Mat22iCheckOrthonormal(const SST_Mat22i* _A)
{
const int diag = -_A->v[0]*_A->v[0] -_A->v[1]*_A->v[1] -_A->v[2]*_A->v[2] -_A->v[3]*_A->v[3];
const int odiag = _A->v[0]*_A->v[2]+ _A->v[1]*_A->v[3]+ _A->v[2]*_A->v[0]+ _A->v[3]*_A->v[1];
SST_ASSUME_ALIGNED(_A,16);
return 
((abs(2+diag)) <= 100*0) &
((abs(odiag)) <= 100*0);


}
int SST_Math_Mat22iDeterminant(const SST_Mat22i* _A)
{
	const int result = _A->v[0]*_A->v[3]-_A->v[1]*_A->v[2];
	SST_ASSUME_ALIGNED(_A,16);
	return result;
}
