/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 3, TYPE = float */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec3.h>

void SST_Math_Vec3fAdd(const SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B, SST_Vec3f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
	 _out->v[2] = _A->v[2] + _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fAddLocal(SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fSubtract(const SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B, SST_Vec3f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
	 _out->v[2] = _A->v[2] - _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fSubtractLocal(SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fMultiply(const SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B, SST_Vec3f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
	 _out->v[2] = _A->v[2] * _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fMultiplyLocal(SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fScale(const SST_Vec3f* RESTRICT _A,  const float k, SST_Vec3f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
}

/******************************************************************************/

void SST_Math_Vec3fScaleLocal(SST_Vec3f* RESTRICT _A, const float k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
}

/******************************************************************************/

void SST_Math_Vec3fDivide(const SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B, SST_Vec3f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
	 _out->v[2] = _A->v[2] / _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3fDivideLocal(SST_Vec3f* RESTRICT _A, const SST_Vec3f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
	 _A->v[2] /= _B->v[2];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec3fAddMult(const SST_Vec3f* RESTRICT _X, const float _x, const SST_Vec3f* RESTRICT _Y, SST_Vec3f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _Y->v[2];

}


void SST_Math_Vec3fAddMultLocal(SST_Vec3f* RESTRICT _X, const float _x, const SST_Vec3f* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _Y->v[2];

}


/******************************************************************************/


void SST_Math_Vec3fLerp(const SST_Vec3f* RESTRICT _X, const SST_Vec3f* RESTRICT _Y, const float _y, SST_Vec3f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_Z->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;

}

void SST_Math_Vec3fLerpLocal(SST_Vec3f* RESTRICT _X, const SST_Vec3f* RESTRICT _Y, const float _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_X->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec3fWeightedSum(const SST_Vec3f* RESTRICT _X, const float _x, const SST_Vec3f* RESTRICT _Y, const float _y, SST_Vec3f* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _y * _Y->v[2];

}

void SST_Math_Vec3fWeightedSumLocal(SST_Vec3f* RESTRICT _X, const float _x, const SST_Vec3f* RESTRICT _Y, const float _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _y * _Y->v[2];

}

/******************************************************************************/

bool SST_Math_Vec3fEquals(const SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b, const float _tolerance)
{
	SST_Vec3f tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec3fSubtract(_a,_b,&tmp);
	for(i=0;i<3;i++)
	{
		returncode = (fabsf(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

float SST_Math_Vec3fMax(const SST_Vec3f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];

	return tmp;
}

/******************************************************************************/

float SST_Math_Vec3fMin(const SST_Vec3f* RESTRICT _a)
{
	float tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec3fCross(const SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b, SST_Vec3f* RESTRICT _out)
				{
 
	_out->v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	_out->v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	_out->v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
}

/******************************************************************************/

void SST_Math_Vec3fCrossLocal(SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b)
{
	SST_Vec3f out;
	
	out.v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	out.v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	out.v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[1];
	_a->v[2] = out.v[2]; 
}

/******************************************************************************/

void SST_Math_Vec3fRotateAbout(const SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _about,float _theta, SST_Vec3f* RESTRICT _out)
{
					

	SST_Vec3f tmp;
	float scalar = (1.000000f-cosf(_theta)) * SST_Math_Vec3fDot(_about,_a);
	SST_Math_Vec3fScale(_about,scalar,_out);
	SST_Math_Vec3fCross(_about,_a,&tmp);
	SST_Math_Vec3fScaleLocal(&tmp,sinf(_theta));
	SST_Math_Vec3fAddLocal(_out,&tmp);
	SST_Math_Vec3fScale(_a,cosf(_theta),&tmp);
	SST_Math_Vec3fAddLocal(_out,&tmp);
				
}

/******************************************************************************/

void SST_Math_Vec3fRotateAboutLocal(SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _about,float _theta)
{
	

	int i;
	SST_Vec3f tmp;
	SST_Vec3f tmp2;
	float scalar = (1.000000f-cosf(_theta)) * SST_Math_Vec3fDot(_about,_a);
			
	SST_Math_Vec3fScale(_about,scalar,&tmp2);
	SST_Math_Vec3fCross(_about,_a,&tmp);
	SST_Math_Vec3fScaleLocal(&tmp,sinf(_theta));
	SST_Math_Vec3fAddLocal(&tmp2,&tmp);
	SST_Math_Vec3fScale(_a,cosf(_theta),&tmp);
	SST_Math_Vec3fAddLocal(&tmp2,&tmp);

	for(i = 0; i < 3; i++)
		_a->v[i] = tmp2.v[i];

					
}

/******************************************************************************/

void SST_Math_Vec3fRotate(const SST_Vec3f* RESTRICT _a,float _theta, SST_Vec3f* RESTRICT _out)
{
					

	SST_Vec3f tmp;
	SST_Vec3f about;
	float scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0; 
	scalar = (1.000000f-cosf(_theta)) * SST_Math_Vec3fDot(&about,_a);
	SST_Math_Vec3fScale(&about,scalar,_out);
	SST_Math_Vec3fCross(&about,_a,&tmp);
	SST_Math_Vec3fScaleLocal(&tmp,sinf(_theta));
	SST_Math_Vec3fAddLocal(_out,&tmp);
	SST_Math_Vec3fScale(_a,cosf(_theta),&tmp);
	SST_Math_Vec3fAddLocal(_out,&tmp);
				
}

/******************************************************************************/

void SST_Math_Vec3fRotateLocal(SST_Vec3f* RESTRICT _a, float _theta)
{
	

	int i;
	SST_Vec3f tmp;
	SST_Vec3f tmp2;
	SST_Vec3f about;
	float scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0;
	scalar = (1.000000f-cosf(_theta)) * SST_Math_Vec3fDot(&about,_a);
			
	SST_Math_Vec3fScale(&about,scalar,&tmp2);
	SST_Math_Vec3fCross(&about,_a,&tmp);
	SST_Math_Vec3fScaleLocal(&tmp,sinf(_theta));
	SST_Math_Vec3fAddLocal(&tmp2,&tmp);
	SST_Math_Vec3fScale(_a,cosf(_theta),&tmp);
	SST_Math_Vec3fAddLocal(&tmp2,&tmp);

	for(i = 0; i < 3; i++)
		_a->v[i] = tmp2.v[i];

					
}
void SST_Math_Vec3fNormalize(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	float scalar = 1.f/SST_Math_Vec3fMagnitude(_in);
	SST_Math_Vec3fScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec3fNormalizeLocal(SST_Vec3f* _inout)
{
	float scalar = 1.f/SST_Math_Vec3fMagnitude(_inout);
	SST_Math_Vec3fScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec3fRecipSqrt(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = 1/sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fRecipSqrtLocal(SST_Vec3f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = 1/sqrtf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fSqrt(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = sqrtf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fSqrtLocal(SST_Vec3f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = sqrtf(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec3fMagnitude(const SST_Vec3f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrtf(sum);
}

/******************************************************************************/

void SST_Math_Vec3fAbs(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = fabsf(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fAbsLocal(SST_Vec3f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = fabsf(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fNegate(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fNegateLocal(SST_Vec3f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fRecip(const SST_Vec3f* RESTRICT _in, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3fRecipLocal(SST_Vec3f* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

float SST_Math_Vec3fDot(const SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b)
{
	float sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

float SST_Math_Vec3fMagnitudeSquared(const SST_Vec3f* RESTRICT _a)
{
	float sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec3fProject(const SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b, SST_Vec3f* RESTRICT _out)
{
	float scalar = SST_Math_Vec3fDot(_a,_b) / SST_Math_Vec3fDot(_b,_b);
	SST_Math_Vec3fScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec3fProjectLocal(SST_Vec3f* RESTRICT _a, const SST_Vec3f* RESTRICT _b)
{
	float scalar = SST_Math_Vec3fDot(_a,_b) / SST_Math_Vec3fDot(_b,_b);
	SST_Math_Vec3fScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec3fBias(const SST_Vec3f* RESTRICT _a, const float _bias, SST_Vec3f* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec3fBiasLocal(SST_Vec3f* RESTRICT _a, const float _bias)
{
	int i;
	for(i = 0; i < 3; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

