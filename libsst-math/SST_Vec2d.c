/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = double */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec2.h>

void SST_Math_Vec2dAdd(const SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B, SST_Vec2d* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dAddLocal(SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B)
{
	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dSubtract(const SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B, SST_Vec2d* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dSubtractLocal(SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B)
{
	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dMultiply(const SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B, SST_Vec2d* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dMultiplyLocal(SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B)
{
	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dScale(const SST_Vec2d* RESTRICT _A,  const double k, SST_Vec2d* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
}

/******************************************************************************/

void SST_Math_Vec2dScaleLocal(SST_Vec2d* RESTRICT _A, const double k)
{
	 _A->v[0] *= k;
	 _A->v[1] *= k;
}

/******************************************************************************/

void SST_Math_Vec2dDivide(const SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B, SST_Vec2d* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2dDivideLocal(SST_Vec2d* RESTRICT _A, const SST_Vec2d* RESTRICT _B)
{
	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec2dAddMult(const SST_Vec2d* RESTRICT _X, const double _x, const SST_Vec2d* RESTRICT _Y, SST_Vec2d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];

}


void SST_Math_Vec2dAddMultLocal(SST_Vec2d* RESTRICT _X, const double _x, const SST_Vec2d* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];

}


/******************************************************************************/


void SST_Math_Vec2dLerp(const SST_Vec2d* RESTRICT _X, const SST_Vec2d* RESTRICT _Y, const double _y, SST_Vec2d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

void SST_Math_Vec2dLerpLocal(SST_Vec2d* RESTRICT _X, const SST_Vec2d* RESTRICT _Y, const double _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec2dWeightedSum(const SST_Vec2d* RESTRICT _X, const double _x, const SST_Vec2d* RESTRICT _Y, const double _y, SST_Vec2d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

void SST_Math_Vec2dWeightedSumLocal(SST_Vec2d* RESTRICT _X, const double _x, const SST_Vec2d* RESTRICT _Y, const double _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

/******************************************************************************/

bool SST_Math_Vec2dEquals(const SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b, const double _tolerance)
{
	SST_Vec2d tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec2dSubtract(_a,_b,&tmp);
	for(i=0;i<2;i++)
	{
		returncode = (fabs(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

double SST_Math_Vec2dMax(const SST_Vec2d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

double SST_Math_Vec2dMin(const SST_Vec2d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec2dCross(const SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b, SST_Vec2d* RESTRICT _out)
				{

	_out->v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_out->v[1] = _out->v[0];
}

/******************************************************************************/

void SST_Math_Vec2dCrossLocal(SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b)
{
	SST_Vec2d out;
	
	out.v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[0];
}

/******************************************************************************/

void SST_Math_Vec2dRotateAbout(const SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _about,double _theta, SST_Vec2d* RESTRICT _out)
{
					

	const double cosa = cos(_theta);
	const double sina = sin(_theta);
	_out->x =  cosa * (_a->x-_about->x) + sina * (_a->y-_about->y) + _about->x;
	_out->y = -sina * (_a->x-_about->x) + cosa * (_a->y-_about->y) + _about->y;
					
}

/******************************************************************************/

void SST_Math_Vec2dRotateAboutLocal(SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _about,double _theta)
{
	

	double tmp;
	const double cosa = cos(_theta);
	const double sina = sin(_theta);

	_a->x -= _about->x;
	_a->y -= _about->y;

	tmp =  cosa * (_a->x) + sina * (_a->y) + _about->x;
	_a->y = -sina * (_a->x) + cosa * (_a->y) + _about->y;
	_a->x = tmp;
					
}

/******************************************************************************/

void SST_Math_Vec2dRotate(const SST_Vec2d* RESTRICT _a,double _theta, SST_Vec2d* RESTRICT _out)
{
					

	const double cosa = cos(_theta);
	const double sina = sin(_theta);
	_out->x =  cosa * (_a->x) + sina * (_a->y);
	_out->y = -sina * (_a->x) + cosa * (_a->y);
					
}

/******************************************************************************/

void SST_Math_Vec2dRotateLocal(SST_Vec2d* RESTRICT _a, double _theta)
{
	

	const double cosa = cos(_theta);
	const double sina = sin(_theta);
	double tmp;

	tmp =  cosa * (_a->x) + sina * (_a->y);
	_a->y = -sina * (_a->x) + cosa * (_a->y);
	_a->x = tmp;
					
}
void SST_Math_Vec2dNormalize(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	double scalar = 1.f/SST_Math_Vec2dMagnitude(_in);
	SST_Math_Vec2dScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec2dNormalizeLocal(SST_Vec2d* _inout)
{
	double scalar = 1.f/SST_Math_Vec2dMagnitude(_inout);
	SST_Math_Vec2dScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec2dRecipSqrt(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = 1/sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dRecipSqrtLocal(SST_Vec2d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = 1/sqrt(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dSqrt(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dSqrtLocal(SST_Vec2d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = sqrt(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec2dMagnitude(const SST_Vec2d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrt(sum);
}

/******************************************************************************/

void SST_Math_Vec2dAbs(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = fabs(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dAbsLocal(SST_Vec2d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = fabs(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dNegate(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dNegateLocal(SST_Vec2d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dRecip(const SST_Vec2d* RESTRICT _in, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2dRecipLocal(SST_Vec2d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec2dDot(const SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b)
{
	double sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

double SST_Math_Vec2dMagnitudeSquared(const SST_Vec2d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec2dProject(const SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b, SST_Vec2d* RESTRICT _out)
{
	double scalar = SST_Math_Vec2dDot(_a,_b) / SST_Math_Vec2dDot(_b,_b);
	SST_Math_Vec2dScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec2dProjectLocal(SST_Vec2d* RESTRICT _a, const SST_Vec2d* RESTRICT _b)
{
	double scalar = SST_Math_Vec2dDot(_a,_b) / SST_Math_Vec2dDot(_b,_b);
	SST_Math_Vec2dScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec2dBias(const SST_Vec2d* RESTRICT _a, const double _bias, SST_Vec2d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec2dBiasLocal(SST_Vec2d* RESTRICT _a, const double _bias)
{
	int i;
	for(i = 0; i < 2; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

