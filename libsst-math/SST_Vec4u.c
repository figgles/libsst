/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = unsigned int */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec4.h>

void SST_Math_Vec4uAdd(const SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B, SST_Vec4u* RESTRICT _out)
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

void SST_Math_Vec4uAddLocal(SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4uSubtract(const SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B, SST_Vec4u* RESTRICT _out)
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

void SST_Math_Vec4uSubtractLocal(SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4uMultiply(const SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B, SST_Vec4u* RESTRICT _out)
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

void SST_Math_Vec4uMultiplyLocal(SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4uScale(const SST_Vec4u* RESTRICT _A,  const unsigned int k, SST_Vec4u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Vec4uScaleLocal(SST_Vec4u* RESTRICT _A, const unsigned int k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/

void SST_Math_Vec4uDivide(const SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B, SST_Vec4u* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
	 _out->v[2] = _A->v[2] / _B->v[2];
	 _out->v[3] = _A->v[3] / _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4uDivideLocal(SST_Vec4u* RESTRICT _A, const SST_Vec4u* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
	 _A->v[2] /= _B->v[2];
	 _A->v[3] /= _B->v[3];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec4uAddMult(const SST_Vec4u* RESTRICT _X, const unsigned int _x, const SST_Vec4u* RESTRICT _Y, SST_Vec4u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _Y->v[2];
	_Z->v[3] = _x * _X->v[3] + _Y->v[3];

}


void SST_Math_Vec4uAddMultLocal(SST_Vec4u* RESTRICT _X, const unsigned int _x, const SST_Vec4u* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _Y->v[2];
	_X->v[3] = _x * _X->v[3] + _Y->v[3];

}


/******************************************************************************/


void SST_Math_Vec4uLerp(const SST_Vec4u* RESTRICT _X, const SST_Vec4u* RESTRICT _Y, const unsigned int _y, SST_Vec4u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_Z->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;
	_Z->v[3] = _X->v[3] + (_Y->v[3] - _X->v[3]) * _y ;

}

void SST_Math_Vec4uLerpLocal(SST_Vec4u* RESTRICT _X, const SST_Vec4u* RESTRICT _Y, const unsigned int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_X->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;
	_X->v[3] = _X->v[3] + (_Y->v[3] - _X->v[3]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec4uWeightedSum(const SST_Vec4u* RESTRICT _X, const unsigned int _x, const SST_Vec4u* RESTRICT _Y, const unsigned int _y, SST_Vec4u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _y * _Y->v[2];
	_Z->v[3] = _x * _X->v[3] + _y * _Y->v[3];

}

void SST_Math_Vec4uWeightedSumLocal(SST_Vec4u* RESTRICT _X, const unsigned int _x, const SST_Vec4u* RESTRICT _Y, const unsigned int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _y * _Y->v[2];
	_X->v[3] = _x * _X->v[3] + _y * _Y->v[3];

}

/******************************************************************************/

bool SST_Math_Vec4uEquals(const SST_Vec4u* RESTRICT _a, const SST_Vec4u* RESTRICT _b)
{
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;
	for(i=0;i<4;i++)
	{
		returncode = (_a->v[i]==_b->v[i]) && returncode;
	}
	return returncode;
} 
			

/******************************************************************************/

unsigned int SST_Math_Vec4uMax(const SST_Vec4u* RESTRICT _a)
{
	unsigned int tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];
	if(tmp < _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

unsigned int SST_Math_Vec4uMin(const SST_Vec4u* RESTRICT _a)
{
	unsigned int tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];
	if(tmp > _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

unsigned int SST_Math_Vec4uDot(const SST_Vec4u* RESTRICT _a, const SST_Vec4u* RESTRICT _b)
{
	unsigned int sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

unsigned int SST_Math_Vec4uMagnitudeSquared(const SST_Vec4u* RESTRICT _a)
{
	unsigned int sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec4uProject(const SST_Vec4u* RESTRICT _a, const SST_Vec4u* RESTRICT _b, SST_Vec4u* RESTRICT _out)
{
	unsigned int scalar = SST_Math_Vec4uDot(_a,_b) / SST_Math_Vec4uDot(_b,_b);
	SST_Math_Vec4uScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec4uProjectLocal(SST_Vec4u* RESTRICT _a, const SST_Vec4u* RESTRICT _b)
{
	unsigned int scalar = SST_Math_Vec4uDot(_a,_b) / SST_Math_Vec4uDot(_b,_b);
	SST_Math_Vec4uScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec4uBias(const SST_Vec4u* RESTRICT _a, const unsigned int _bias, SST_Vec4u* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec4uBiasLocal(SST_Vec4u* RESTRICT _a, const unsigned int _bias)
{
	int i;
	for(i = 0; i < 4; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

