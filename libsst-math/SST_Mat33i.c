/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 3, TYPE = int */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat33.h>
#include <SST/SST_Vec3.h>
void SST_Math_Mat33iAdd(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out)
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

void SST_Math_Mat33iAddLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B)
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

void SST_Math_Mat33iSubtract(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out)
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

void SST_Math_Mat33iSubtractLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B)
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

void SST_Math_Mat33iMultiplyElementwise(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out)
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

void SST_Math_Mat33iMultiplyElementwiseLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B)
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

void SST_Math_Mat33iMultiplyScalar(const SST_Mat33i* RESTRICT _A, const int k,  SST_Mat33i* RESTRICT _out)
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

void SST_Math_Mat33iMultiplyScalarLocal(SST_Mat33i* RESTRICT _A, const int k)
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


void SST_Math_Mat33iMultiplyMatrix(const SST_Mat33i* _A, const SST_Mat33i*  RESTRICT _B, SST_Mat33i*  RESTRICT _out)
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
void SST_Math_Mat33iMultiplyMatrixLocal(SST_Mat33i*  RESTRICT _A, const SST_Mat33i*  RESTRICT _B)
{
	int tmp[9];
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
void SST_Math_Mat33iMultiplyVector(const SST_Mat33i*  RESTRICT _A, const SST_Vec3i*  RESTRICT _v, SST_Vec3i*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 3]*_v->v[1]+_A->v[ 6]*_v->v[2];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 7]*_v->v[2];
_out->v[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 8]*_v->v[2];
}
void SST_Math_Mat33iMultiplyVectorLocal(const SST_Mat33i*  RESTRICT _A, SST_Vec3i*  RESTRICT _v)
{
int tmp[3];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 3]*_v->v[1]+_A->v[ 6]*_v->v[2];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 4]*_v->v[1]+_A->v[ 7]*_v->v[2];
tmp[ 2] = _A->v[ 2]*_v->v[0]+_A->v[ 5]*_v->v[1]+_A->v[ 8]*_v->v[2];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
_v->v[2] = tmp[2];
}
void SST_Math_Mat33iTranspose(const SST_Mat33i*  RESTRICT _A, SST_Mat33i*  RESTRICT _out)
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
void SST_Math_Mat33iTransposeLocal(SST_Mat33i*  RESTRICT _A)
{
int tmp[3];
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
bool SST_Math_Mat33iCheckOrthonormal(const SST_Mat33i* _A)
{
const int diag = -_A->v[0]*_A->v[0] -_A->v[1]*_A->v[1] -_A->v[2]*_A->v[2] -_A->v[3]*_A->v[3] -_A->v[4]*_A->v[4] -_A->v[5]*_A->v[5] -_A->v[6]*_A->v[6] -_A->v[7]*_A->v[7] -_A->v[8]*_A->v[8];
const int odiag = _A->v[0]*_A->v[3]+ _A->v[1]*_A->v[4]+ _A->v[2]*_A->v[5]+ _A->v[0]*_A->v[6]+ _A->v[1]*_A->v[7]+ _A->v[2]*_A->v[8]+ _A->v[3]*_A->v[0]+ _A->v[4]*_A->v[1]+ _A->v[5]*_A->v[2]+ _A->v[3]*_A->v[6]+ _A->v[4]*_A->v[7]+ _A->v[5]*_A->v[8]+ _A->v[6]*_A->v[0]+ _A->v[7]*_A->v[1]+ _A->v[8]*_A->v[2]+ _A->v[6]*_A->v[3]+ _A->v[7]*_A->v[4]+ _A->v[8]*_A->v[5];
SST_ASSUME_ALIGNED(_A,16);
return 
((abs(3+diag)) <= 100*0) &
((abs(odiag)) <= 100*0);


}
int SST_Math_Mat33iDeterminant(const SST_Mat33i* _A)
{
	const int result = _A->v[0]*(_A->v[4]*_A->v[8]-_A->v[5]*_A->v[7])-_A->v[1]*(_A->v[3]*_A->v[8]-_A->v[6]*_A->v[5])+_A->v[2]*(_A->v[3]*_A->v[7]-_A->v[6]*_A->v[4]);
	SST_ASSUME_ALIGNED(_A,16);
	return result;
}
