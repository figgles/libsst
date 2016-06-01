/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = int */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec2.h>

void SST_Math_Vec2iAdd(const SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B, SST_Vec2i* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iAddLocal(SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B)
{
	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iSubtract(const SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B, SST_Vec2i* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iSubtractLocal(SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B)
{
	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iMultiply(const SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B, SST_Vec2i* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iMultiplyLocal(SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B)
{
	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iScale(const SST_Vec2i* RESTRICT _A,  const int k, SST_Vec2i* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
}

/******************************************************************************/

void SST_Math_Vec2iScaleLocal(SST_Vec2i* RESTRICT _A, const int k)
{
	 _A->v[0] *= k;
	 _A->v[1] *= k;
}

/******************************************************************************/

void SST_Math_Vec2iDivide(const SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B, SST_Vec2i* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2iDivideLocal(SST_Vec2i* RESTRICT _A, const SST_Vec2i* RESTRICT _B)
{
	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec2iAddMult(const SST_Vec2i* RESTRICT _X, const int _x, const SST_Vec2i* RESTRICT _Y, SST_Vec2i* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];

}


void SST_Math_Vec2iAddMultLocal(SST_Vec2i* RESTRICT _X, const int _x, const SST_Vec2i* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];

}


/******************************************************************************/


void SST_Math_Vec2iLerp(const SST_Vec2i* RESTRICT _X, const SST_Vec2i* RESTRICT _Y, const int _y, SST_Vec2i* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

void SST_Math_Vec2iLerpLocal(SST_Vec2i* RESTRICT _X, const SST_Vec2i* RESTRICT _Y, const int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec2iWeightedSum(const SST_Vec2i* RESTRICT _X, const int _x, const SST_Vec2i* RESTRICT _Y, const int _y, SST_Vec2i* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

void SST_Math_Vec2iWeightedSumLocal(SST_Vec2i* RESTRICT _X, const int _x, const SST_Vec2i* RESTRICT _Y, const int _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

/******************************************************************************/

bool SST_Math_Vec2iEquals(const SST_Vec2i* RESTRICT _a, const SST_Vec2i* RESTRICT _b)
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

int SST_Math_Vec2iMax(const SST_Vec2i* RESTRICT _a)
{
	int tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

int SST_Math_Vec2iMin(const SST_Vec2i* RESTRICT _a)
{
	int tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec2iAbs(const SST_Vec2i* RESTRICT _in, SST_Vec2i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = abs(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2iAbsLocal(SST_Vec2i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = abs(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2iNegate(const SST_Vec2i* RESTRICT _in, SST_Vec2i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2iNegateLocal(SST_Vec2i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2iRecip(const SST_Vec2i* RESTRICT _in, SST_Vec2i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2iRecipLocal(SST_Vec2i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

int SST_Math_Vec2iDot(const SST_Vec2i* RESTRICT _a, const SST_Vec2i* RESTRICT _b)
{
	int sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

int SST_Math_Vec2iMagnitudeSquared(const SST_Vec2i* RESTRICT _a)
{
	int sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec2iProject(const SST_Vec2i* RESTRICT _a, const SST_Vec2i* RESTRICT _b, SST_Vec2i* RESTRICT _out)
{
	int scalar = SST_Math_Vec2iDot(_a,_b) / SST_Math_Vec2iDot(_b,_b);
	SST_Math_Vec2iScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec2iProjectLocal(SST_Vec2i* RESTRICT _a, const SST_Vec2i* RESTRICT _b)
{
	int scalar = SST_Math_Vec2iDot(_a,_b) / SST_Math_Vec2iDot(_b,_b);
	SST_Math_Vec2iScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec2iBias(const SST_Vec2i* RESTRICT _a, const int _bias, SST_Vec2i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec2iBiasLocal(SST_Vec2i* RESTRICT _a, const int _bias)
{
	int i;
	for(i = 0; i < 2; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

