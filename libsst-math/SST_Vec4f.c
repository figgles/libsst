/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = float */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec4.h>

void SST_Math_Vec4fAdd(const SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B, SST_Vec4f* RESTRICT _out)
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

void SST_Math_Vec4fAddLocal(SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4fSubtract(const SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B, SST_Vec4f* RESTRICT _out)
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

void SST_Math_Vec4fSubtractLocal(SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4fMultiply(const SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B, SST_Vec4f* RESTRICT _out)
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

void SST_Math_Vec4fMultiplyLocal(SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4fScale(const SST_Vec4f* RESTRICT _A,  const float k, SST_Vec4f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Vec4fScaleLocal(SST_Vec4f* RESTRICT _A, const float k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/

void SST_Math_Vec4fDivide(const SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B, SST_Vec4f* RESTRICT _out)
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

void SST_Math_Vec4fDivideLocal(SST_Vec4f* RESTRICT _A, const SST_Vec4f* RESTRICT _B)
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


void SST_Math_Vec4fAddMult(const SST_Vec4f* RESTRICT _X, const float _x, const SST_Vec4f* RESTRICT _Y, SST_Vec4f* RESTRICT _Z)
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


void SST_Math_Vec4fAddMultLocal(SST_Vec4f* RESTRICT _X, const float _x, const SST_Vec4f* RESTRICT _Y)
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


void SST_Math_Vec4fLerp(const SST_Vec4f* RESTRICT _X, const SST_Vec4f* RESTRICT _Y, const float _y, SST_Vec4f* RESTRICT _Z)
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

void SST_Math_Vec4fLerpLocal(SST_Vec4f* RESTRICT _X, const SST_Vec4f* RESTRICT _Y, const float _y)
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


void SST_Math_Vec4fWeightedSum(const SST_Vec4f* RESTRICT _X, const float _x, const SST_Vec4f* RESTRICT _Y, const float _y, SST_Vec4f* RESTRICT _Z)
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

void SST_Math_Vec4fWeightedSumLocal(SST_Vec4f* RESTRICT _X, const float _x, const SST_Vec4f* RESTRICT _Y, const float _y)
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

bool SST_Math_Vec4fEquals(const SST_Vec4f* RESTRICT _a, const SST_Vec4f* RESTRICT _b, const float _tolerance)
{
	SST_Vec4f tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec4fSubtract(_a,_b,&tmp);
	for(i=0;i<4;i++)
	{
		returncode = (fabsf(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

float SST_Math_Vec4fMax(const SST_Vec4f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];
	if(tmp < _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

float SST_Math_Vec4fMin(const SST_Vec4f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];
	if(tmp > _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec4fNormalize(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	float scalar = 1.f/SST_Math_Vec4fMagnitude(_in);
	SST_Math_Vec4fScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec4fNormalizeLocal(SST_Vec4f* _inout)
{
	float scalar = 1.f/SST_Math_Vec4fMagnitude(_inout);
	SST_Math_Vec4fScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec4fRecipSqrt(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = 1/sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fRecipSqrtLocal(SST_Vec4f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = 1/sqrtf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fSqrt(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fSqrtLocal(SST_Vec4f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = sqrtf(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec4fMagnitude(const SST_Vec4f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrtf(sum);
}

/******************************************************************************/

void SST_Math_Vec4fAbs(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = fabsf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fAbsLocal(SST_Vec4f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = fabsf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fNegate(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fNegateLocal(SST_Vec4f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fRecip(const SST_Vec4f* RESTRICT _in, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4fRecipLocal(SST_Vec4f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec4fDot(const SST_Vec4f* RESTRICT _a, const SST_Vec4f* RESTRICT _b)
{
	float sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

float SST_Math_Vec4fMagnitudeSquared(const SST_Vec4f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec4fProject(const SST_Vec4f* RESTRICT _a, const SST_Vec4f* RESTRICT _b, SST_Vec4f* RESTRICT _out)
{
	float scalar = SST_Math_Vec4fDot(_a,_b) / SST_Math_Vec4fDot(_b,_b);
	SST_Math_Vec4fScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec4fProjectLocal(SST_Vec4f* RESTRICT _a, const SST_Vec4f* RESTRICT _b)
{
	float scalar = SST_Math_Vec4fDot(_a,_b) / SST_Math_Vec4fDot(_b,_b);
	SST_Math_Vec4fScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec4fBias(const SST_Vec4f* RESTRICT _a, const float _bias, SST_Vec4f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec4fBiasLocal(SST_Vec4f* RESTRICT _a, const float _bias)
{
	int i;
	for(i = 0; i < 4; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

