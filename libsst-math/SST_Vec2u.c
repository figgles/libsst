/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = unsigned int */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec2.h>

void SST_Math_Vec2uAdd(const SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B, SST_Vec2u* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uAddLocal(SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B)
{
	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uSubtract(const SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B, SST_Vec2u* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uSubtractLocal(SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B)
{
	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uMultiply(const SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B, SST_Vec2u* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uMultiplyLocal(SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B)
{
	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uScale(const SST_Vec2u* RESTRICT _A,  const unsigned int k, SST_Vec2u* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
}

/******************************************************************************/

void SST_Math_Vec2uScaleLocal(SST_Vec2u* RESTRICT _A, const unsigned int k)
{
	 _A->v[0] *= k;
	 _A->v[1] *= k;
}

/******************************************************************************/

void SST_Math_Vec2uDivide(const SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B, SST_Vec2u* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2uDivideLocal(SST_Vec2u* RESTRICT _A, const SST_Vec2u* RESTRICT _B)
{
	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec2uAddMult(const SST_Vec2u* RESTRICT _X, const unsigned int _x, const SST_Vec2u* RESTRICT _Y, SST_Vec2u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];

}


void SST_Math_Vec2uAddMultLocal(SST_Vec2u* RESTRICT _X, const unsigned int _x, const SST_Vec2u* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];

}


/******************************************************************************/


void SST_Math_Vec2uLerp(const SST_Vec2u* RESTRICT _X, const SST_Vec2u* RESTRICT _Y, const unsigned int _y, SST_Vec2u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

void SST_Math_Vec2uLerpLocal(SST_Vec2u* RESTRICT _X, const SST_Vec2u* RESTRICT _Y, const unsigned int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec2uWeightedSum(const SST_Vec2u* RESTRICT _X, const unsigned int _x, const SST_Vec2u* RESTRICT _Y, const unsigned int _y, SST_Vec2u* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

void SST_Math_Vec2uWeightedSumLocal(SST_Vec2u* RESTRICT _X, const unsigned int _x, const SST_Vec2u* RESTRICT _Y, const unsigned int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

/******************************************************************************/

bool SST_Math_Vec2uEquals(const SST_Vec2u* RESTRICT _a, const SST_Vec2u* RESTRICT _b)
{
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;
	for(i=0;i<2;i++)
	{
		returncode = (_a->v[i]==_b->v[i]) && returncode;
	}
	return returncode;
} 
			

/******************************************************************************/

unsigned int SST_Math_Vec2uMax(const SST_Vec2u* RESTRICT _a)
{
	unsigned int tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

unsigned int SST_Math_Vec2uMin(const SST_Vec2u* RESTRICT _a)
{
	unsigned int tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

unsigned int SST_Math_Vec2uDot(const SST_Vec2u* RESTRICT _a, const SST_Vec2u* RESTRICT _b)
{
	unsigned int sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

unsigned int SST_Math_Vec2uMagnitudeSquared(const SST_Vec2u* RESTRICT _a)
{
	unsigned int sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec2uProject(const SST_Vec2u* RESTRICT _a, const SST_Vec2u* RESTRICT _b, SST_Vec2u* RESTRICT _out)
{
	unsigned int scalar = SST_Math_Vec2uDot(_a,_b) / SST_Math_Vec2uDot(_b,_b);
	SST_Math_Vec2uScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec2uProjectLocal(SST_Vec2u* RESTRICT _a, const SST_Vec2u* RESTRICT _b)
{
	unsigned int scalar = SST_Math_Vec2uDot(_a,_b) / SST_Math_Vec2uDot(_b,_b);
	SST_Math_Vec2uScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec2uBias(const SST_Vec2u* RESTRICT _a, const unsigned int _bias, SST_Vec2u* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec2uBiasLocal(SST_Vec2u* RESTRICT _a, const unsigned int _bias)
{
	int i;
	for(i = 0; i < 2; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

