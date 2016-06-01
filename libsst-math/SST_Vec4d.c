/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = double */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec4.h>

void SST_Math_Vec4dAdd(const SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B, SST_Vec4d* RESTRICT _out)
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

void SST_Math_Vec4dAddLocal(SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4dSubtract(const SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B, SST_Vec4d* RESTRICT _out)
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

void SST_Math_Vec4dSubtractLocal(SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4dMultiply(const SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B, SST_Vec4d* RESTRICT _out)
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

void SST_Math_Vec4dMultiplyLocal(SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4dScale(const SST_Vec4d* RESTRICT _A,  const double k, SST_Vec4d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Vec4dScaleLocal(SST_Vec4d* RESTRICT _A, const double k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/

void SST_Math_Vec4dDivide(const SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B, SST_Vec4d* RESTRICT _out)
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

void SST_Math_Vec4dDivideLocal(SST_Vec4d* RESTRICT _A, const SST_Vec4d* RESTRICT _B)
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


void SST_Math_Vec4dAddMult(const SST_Vec4d* RESTRICT _X, const double _x, const SST_Vec4d* RESTRICT _Y, SST_Vec4d* RESTRICT _Z)
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


void SST_Math_Vec4dAddMultLocal(SST_Vec4d* RESTRICT _X, const double _x, const SST_Vec4d* RESTRICT _Y)
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


void SST_Math_Vec4dLerp(const SST_Vec4d* RESTRICT _X, const SST_Vec4d* RESTRICT _Y, const double _y, SST_Vec4d* RESTRICT _Z)
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

void SST_Math_Vec4dLerpLocal(SST_Vec4d* RESTRICT _X, const SST_Vec4d* RESTRICT _Y, const double _y)
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


void SST_Math_Vec4dWeightedSum(const SST_Vec4d* RESTRICT _X, const double _x, const SST_Vec4d* RESTRICT _Y, const double _y, SST_Vec4d* RESTRICT _Z)
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

void SST_Math_Vec4dWeightedSumLocal(SST_Vec4d* RESTRICT _X, const double _x, const SST_Vec4d* RESTRICT _Y, const double _y)
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

bool SST_Math_Vec4dEquals(const SST_Vec4d* RESTRICT _a, const SST_Vec4d* RESTRICT _b, const double _tolerance)
{
	SST_Vec4d tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec4dSubtract(_a,_b,&tmp);
	for(i=0;i<4;i++)
	{
		returncode = (fabs(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

double SST_Math_Vec4dMax(const SST_Vec4d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];
	if(tmp < _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

double SST_Math_Vec4dMin(const SST_Vec4d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];
	if(tmp > _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec4dNormalize(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	double scalar = 1.f/SST_Math_Vec4dMagnitude(_in);
	SST_Math_Vec4dScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec4dNormalizeLocal(SST_Vec4d* _inout)
{
	double scalar = 1.f/SST_Math_Vec4dMagnitude(_inout);
	SST_Math_Vec4dScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec4dRecipSqrt(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = 1/sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dRecipSqrtLocal(SST_Vec4d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = 1/sqrt(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dSqrt(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dSqrtLocal(SST_Vec4d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = sqrt(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec4dMagnitude(const SST_Vec4d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrt(sum);
}

/******************************************************************************/

void SST_Math_Vec4dAbs(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = fabs(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dAbsLocal(SST_Vec4d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = fabs(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dNegate(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dNegateLocal(SST_Vec4d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dRecip(const SST_Vec4d* RESTRICT _in, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4dRecipLocal(SST_Vec4d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec4dDot(const SST_Vec4d* RESTRICT _a, const SST_Vec4d* RESTRICT _b)
{
	double sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

double SST_Math_Vec4dMagnitudeSquared(const SST_Vec4d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec4dProject(const SST_Vec4d* RESTRICT _a, const SST_Vec4d* RESTRICT _b, SST_Vec4d* RESTRICT _out)
{
	double scalar = SST_Math_Vec4dDot(_a,_b) / SST_Math_Vec4dDot(_b,_b);
	SST_Math_Vec4dScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec4dProjectLocal(SST_Vec4d* RESTRICT _a, const SST_Vec4d* RESTRICT _b)
{
	double scalar = SST_Math_Vec4dDot(_a,_b) / SST_Math_Vec4dDot(_b,_b);
	SST_Math_Vec4dScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec4dBias(const SST_Vec4d* RESTRICT _a, const double _bias, SST_Vec4d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec4dBiasLocal(SST_Vec4d* RESTRICT _a, const double _bias)
{
	int i;
	for(i = 0; i < 4; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

