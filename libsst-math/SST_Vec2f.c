/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = float */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec2.h>

void SST_Math_Vec2fAdd(const SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B, SST_Vec2f* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fAddLocal(SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B)
{
	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fSubtract(const SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B, SST_Vec2f* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fSubtractLocal(SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B)
{
	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fMultiply(const SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B, SST_Vec2f* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fMultiplyLocal(SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B)
{
	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fScale(const SST_Vec2f* RESTRICT _A,  const float k, SST_Vec2f* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
}

/******************************************************************************/

void SST_Math_Vec2fScaleLocal(SST_Vec2f* RESTRICT _A, const float k)
{
	 _A->v[0] *= k;
	 _A->v[1] *= k;
}

/******************************************************************************/

void SST_Math_Vec2fDivide(const SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B, SST_Vec2f* RESTRICT _out)
{
	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
}

/******************************************************************************/

void SST_Math_Vec2fDivideLocal(SST_Vec2f* RESTRICT _A, const SST_Vec2f* RESTRICT _B)
{
	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec2fAddMult(const SST_Vec2f* RESTRICT _X, const float _x, const SST_Vec2f* RESTRICT _Y, SST_Vec2f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];

}


void SST_Math_Vec2fAddMultLocal(SST_Vec2f* RESTRICT _X, const float _x, const SST_Vec2f* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];

}


/******************************************************************************/


void SST_Math_Vec2fLerp(const SST_Vec2f* RESTRICT _X, const SST_Vec2f* RESTRICT _Y, const float _y, SST_Vec2f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

void SST_Math_Vec2fLerpLocal(SST_Vec2f* RESTRICT _X, const SST_Vec2f* RESTRICT _Y, const float _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec2fWeightedSum(const SST_Vec2f* RESTRICT _X, const float _x, const SST_Vec2f* RESTRICT _Y, const float _y, SST_Vec2f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

void SST_Math_Vec2fWeightedSumLocal(SST_Vec2f* RESTRICT _X, const float _x, const SST_Vec2f* RESTRICT _Y, const float _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];

}

/******************************************************************************/

bool SST_Math_Vec2fEquals(const SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b, const float _tolerance)
{
	SST_Vec2f tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec2fSubtract(_a,_b,&tmp);
	for(i=0;i<2;i++)
	{
		returncode = (fabsf(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

float SST_Math_Vec2fMax(const SST_Vec2f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

float SST_Math_Vec2fMin(const SST_Vec2f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec2fCross(const SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b, SST_Vec2f* RESTRICT _out)
				{

	_out->v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_out->v[1] = _out->v[0];
}

/******************************************************************************/

void SST_Math_Vec2fCrossLocal(SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b)
{
	SST_Vec2f out;
	
	out.v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[0];
}

/******************************************************************************/

void SST_Math_Vec2fRotateAbout(const SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _about,float _theta, SST_Vec2f* RESTRICT _out)
{
					

	const float cosa = cosf(_theta);
	const float sina = sinf(_theta);
	_out->x =  cosa * (_a->x-_about->x) + sina * (_a->y-_about->y) + _about->x;
	_out->y = -sina * (_a->x-_about->x) + cosa * (_a->y-_about->y) + _about->y;
					
}

/******************************************************************************/

void SST_Math_Vec2fRotateAboutLocal(SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _about,float _theta)
{
	

	float tmp;
	const float cosa = cosf(_theta);
	const float sina = sinf(_theta);

	_a->x -= _about->x;
	_a->y -= _about->y;

	tmp =  cosa * (_a->x) + sina * (_a->y) + _about->x;
	_a->y = -sina * (_a->x) + cosa * (_a->y) + _about->y;
	_a->x = tmp;
					
}

/******************************************************************************/

void SST_Math_Vec2fRotate(const SST_Vec2f* RESTRICT _a,float _theta, SST_Vec2f* RESTRICT _out)
{
					

	const float cosa = cosf(_theta);
	const float sina = sinf(_theta);
	_out->x =  cosa * (_a->x) + sina * (_a->y);
	_out->y = -sina * (_a->x) + cosa * (_a->y);
					
}

/******************************************************************************/

void SST_Math_Vec2fRotateLocal(SST_Vec2f* RESTRICT _a, float _theta)
{
	

	const float cosa = cosf(_theta);
	const float sina = sinf(_theta);
	float tmp;

	tmp =  cosa * (_a->x) + sina * (_a->y);
	_a->y = -sina * (_a->x) + cosa * (_a->y);
	_a->x = tmp;
					
}
void SST_Math_Vec2fNormalize(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	float scalar = 1.f/SST_Math_Vec2fMagnitude(_in);
	SST_Math_Vec2fScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec2fNormalizeLocal(SST_Vec2f* _inout)
{
	float scalar = 1.f/SST_Math_Vec2fMagnitude(_inout);
	SST_Math_Vec2fScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec2fRecipSqrt(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = 1/sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fRecipSqrtLocal(SST_Vec2f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = 1/sqrtf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fSqrt(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fSqrtLocal(SST_Vec2f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = sqrtf(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec2fMagnitude(const SST_Vec2f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrtf(sum);
}

/******************************************************************************/

void SST_Math_Vec2fAbs(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = fabsf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fAbsLocal(SST_Vec2f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = fabsf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fNegate(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fNegateLocal(SST_Vec2f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fRecip(const SST_Vec2f* RESTRICT _in, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec2fRecipLocal(SST_Vec2f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 2; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec2fDot(const SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b)
{
	float sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

float SST_Math_Vec2fMagnitudeSquared(const SST_Vec2f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 2; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec2fProject(const SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b, SST_Vec2f* RESTRICT _out)
{
	float scalar = SST_Math_Vec2fDot(_a,_b) / SST_Math_Vec2fDot(_b,_b);
	SST_Math_Vec2fScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec2fProjectLocal(SST_Vec2f* RESTRICT _a, const SST_Vec2f* RESTRICT _b)
{
	float scalar = SST_Math_Vec2fDot(_a,_b) / SST_Math_Vec2fDot(_b,_b);
	SST_Math_Vec2fScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec2fBias(const SST_Vec2f* RESTRICT _a, const float _bias, SST_Vec2f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 2; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec2fBiasLocal(SST_Vec2f* RESTRICT _a, const float _bias)
{
	int i;
	for(i = 0; i < 2; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

