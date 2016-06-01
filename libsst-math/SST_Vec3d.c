/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 3, TYPE = double */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec3.h>

void SST_Math_Vec3dAdd(const SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B, SST_Vec3d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] + _B->v[0];
	 _out->v[1] = _A->v[1] + _B->v[1];
	 _out->v[2] = _A->v[2] + _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dAddLocal(SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dSubtract(const SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B, SST_Vec3d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] - _B->v[0];
	 _out->v[1] = _A->v[1] - _B->v[1];
	 _out->v[2] = _A->v[2] - _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dSubtractLocal(SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dMultiply(const SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B, SST_Vec3d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * _B->v[0];
	 _out->v[1] = _A->v[1] * _B->v[1];
	 _out->v[2] = _A->v[2] * _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dMultiplyLocal(SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dScale(const SST_Vec3d* RESTRICT _A,  const double k, SST_Vec3d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
}

/******************************************************************************/

void SST_Math_Vec3dScaleLocal(SST_Vec3d* RESTRICT _A, const double k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
}

/******************************************************************************/

void SST_Math_Vec3dDivide(const SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B, SST_Vec3d* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] / _B->v[0];
	 _out->v[1] = _A->v[1] / _B->v[1];
	 _out->v[2] = _A->v[2] / _B->v[2];
}

/******************************************************************************/

void SST_Math_Vec3dDivideLocal(SST_Vec3d* RESTRICT _A, const SST_Vec3d* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] /= _B->v[0];
	 _A->v[1] /= _B->v[1];
	 _A->v[2] /= _B->v[2];
}

/******************************************************************************/


/******************************************************************************/


void SST_Math_Vec3dAddMult(const SST_Vec3d* RESTRICT _X, const double _x, const SST_Vec3d* RESTRICT _Y, SST_Vec3d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
	_Z->v[0] = _x * _X->v[0] + _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _Y->v[2];

}


void SST_Math_Vec3dAddMultLocal(SST_Vec3d* RESTRICT _X, const double _x, const SST_Vec3d* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
	_X->v[0] = _x * _X->v[0] + _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _Y->v[2];

}


/******************************************************************************/


void SST_Math_Vec3dLerp(const SST_Vec3d* RESTRICT _X, const SST_Vec3d* RESTRICT _Y, const double _y, SST_Vec3d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_Z->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_Z->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;

}

void SST_Math_Vec3dLerpLocal(SST_Vec3d* RESTRICT _X, const SST_Vec3d* RESTRICT _Y, const double _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _X->v[0] + (_Y->v[0] - _X->v[0]) * _y ;
	_X->v[1] = _X->v[1] + (_Y->v[1] - _X->v[1]) * _y ;
	_X->v[2] = _X->v[2] + (_Y->v[2] - _X->v[2]) * _y ;

}

/******************************************************************************/


void SST_Math_Vec3dWeightedSum(const SST_Vec3d* RESTRICT _X, const double _x, const SST_Vec3d* RESTRICT _Y, const double _y, SST_Vec3d* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
	_Z->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_Z->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_Z->v[2] = _x * _X->v[2] + _y * _Y->v[2];

}

void SST_Math_Vec3dWeightedSumLocal(SST_Vec3d* RESTRICT _X, const double _x, const SST_Vec3d* RESTRICT _Y, const double _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
	_X->v[0] = _x * _X->v[0] + _y * _Y->v[0];
	_X->v[1] = _x * _X->v[1] + _y * _Y->v[1];
	_X->v[2] = _x * _X->v[2] + _y * _Y->v[2];

}

/******************************************************************************/

bool SST_Math_Vec3dEquals(const SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b, const double _tolerance)
{
	SST_Vec3d tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_Vec3dSubtract(_a,_b,&tmp);
	for(i=0;i<3;i++)
	{
		returncode = (fabs(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			

/******************************************************************************/

double SST_Math_Vec3dMax(const SST_Vec3d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];

	return tmp;
}

/******************************************************************************/

double SST_Math_Vec3dMin(const SST_Vec3d* RESTRICT _a)
{
	double tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec3dCross(const SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b, SST_Vec3d* RESTRICT _out)
				{
 
	_out->v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	_out->v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	_out->v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
}

/******************************************************************************/

void SST_Math_Vec3dCrossLocal(SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b)
{
	SST_Vec3d out;
	
	out.v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	out.v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	out.v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[1];
	_a->v[2] = out.v[2]; 
}

/******************************************************************************/

void SST_Math_Vec3dRotateAbout(const SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _about,double _theta, SST_Vec3d* RESTRICT _out)
{
					

	SST_Vec3d tmp;
	double scalar = (      1.0000000000000000-cos(_theta)) * SST_Math_Vec3dDot(_about,_a);
	SST_Math_Vec3dScale(_about,scalar,_out);
	SST_Math_Vec3dCross(_about,_a,&tmp);
	SST_Math_Vec3dScaleLocal(&tmp,sin(_theta));
	SST_Math_Vec3dAddLocal(_out,&tmp);
	SST_Math_Vec3dScale(_a,cos(_theta),&tmp);
	SST_Math_Vec3dAddLocal(_out,&tmp);
				
}

/******************************************************************************/

void SST_Math_Vec3dRotateAboutLocal(SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _about,double _theta)
{
	

	int i;
	SST_Vec3d tmp;
	SST_Vec3d tmp2;
	double scalar = (      1.0000000000000000-cos(_theta)) * SST_Math_Vec3dDot(_about,_a);
			
	SST_Math_Vec3dScale(_about,scalar,&tmp2);
	SST_Math_Vec3dCross(_about,_a,&tmp);
	SST_Math_Vec3dScaleLocal(&tmp,sin(_theta));
	SST_Math_Vec3dAddLocal(&tmp2,&tmp);
	SST_Math_Vec3dScale(_a,cos(_theta),&tmp);
	SST_Math_Vec3dAddLocal(&tmp2,&tmp);

	for(i = 0; i < 3; i++)
		_a->v[i] = tmp2.v[i];

					
}

/******************************************************************************/

void SST_Math_Vec3dRotate(const SST_Vec3d* RESTRICT _a,double _theta, SST_Vec3d* RESTRICT _out)
{
					

	SST_Vec3d tmp;
	SST_Vec3d about;
	double scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0; 
	scalar = (      1.0000000000000000-cos(_theta)) * SST_Math_Vec3dDot(&about,_a);
	SST_Math_Vec3dScale(&about,scalar,_out);
	SST_Math_Vec3dCross(&about,_a,&tmp);
	SST_Math_Vec3dScaleLocal(&tmp,sin(_theta));
	SST_Math_Vec3dAddLocal(_out,&tmp);
	SST_Math_Vec3dScale(_a,cos(_theta),&tmp);
	SST_Math_Vec3dAddLocal(_out,&tmp);
				
}

/******************************************************************************/

void SST_Math_Vec3dRotateLocal(SST_Vec3d* RESTRICT _a, double _theta)
{
	

	int i;
	SST_Vec3d tmp;
	SST_Vec3d tmp2;
	SST_Vec3d about;
	double scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0;
	scalar = (      1.0000000000000000-cos(_theta)) * SST_Math_Vec3dDot(&about,_a);
			
	SST_Math_Vec3dScale(&about,scalar,&tmp2);
	SST_Math_Vec3dCross(&about,_a,&tmp);
	SST_Math_Vec3dScaleLocal(&tmp,sin(_theta));
	SST_Math_Vec3dAddLocal(&tmp2,&tmp);
	SST_Math_Vec3dScale(_a,cos(_theta),&tmp);
	SST_Math_Vec3dAddLocal(&tmp2,&tmp);

	for(i = 0; i < 3; i++)
		_a->v[i] = tmp2.v[i];

					
}
void SST_Math_Vec3dNormalize(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	double scalar = 1.f/SST_Math_Vec3dMagnitude(_in);
	SST_Math_Vec3dScale(_in,scalar,_out);
}

/******************************************************************************/

void SST_Math_Vec3dNormalizeLocal(SST_Vec3d* _inout)
{
	double scalar = 1.f/SST_Math_Vec3dMagnitude(_inout);
	SST_Math_Vec3dScaleLocal(_inout,scalar);
}

/******************************************************************************/

void SST_Math_Vec3dRecipSqrt(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = 1/sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dRecipSqrtLocal(SST_Vec3d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = 1/sqrt(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dSqrt(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = sqrt(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dSqrtLocal(SST_Vec3d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = sqrt(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec3dMagnitude(const SST_Vec3d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _a->v[i];
	return sqrt(sum);
}

/******************************************************************************/

void SST_Math_Vec3dAbs(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = fabs(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dAbsLocal(SST_Vec3d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = fabs(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dNegate(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dNegateLocal(SST_Vec3d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dRecip(const SST_Vec3d* RESTRICT _in, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec3dRecipLocal(SST_Vec3d* RESTRICT _a)
{
	int i;
	for(i = 0; i < 3; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

double SST_Math_Vec3dDot(const SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b)
{
	double sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

double SST_Math_Vec3dMagnitudeSquared(const SST_Vec3d* RESTRICT _a)
{
	double sum = 0;
	int i;
	for(i = 0; i < 3; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec3dProject(const SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b, SST_Vec3d* RESTRICT _out)
{
	double scalar = SST_Math_Vec3dDot(_a,_b) / SST_Math_Vec3dDot(_b,_b);
	SST_Math_Vec3dScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec3dProjectLocal(SST_Vec3d* RESTRICT _a, const SST_Vec3d* RESTRICT _b)
{
	double scalar = SST_Math_Vec3dDot(_a,_b) / SST_Math_Vec3dDot(_b,_b);
	SST_Math_Vec3dScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec3dBias(const SST_Vec3d* RESTRICT _a, const double _bias, SST_Vec3d* RESTRICT _out)
{
	int i;
	for(i = 0; i < 3; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec3dBiasLocal(SST_Vec3d* RESTRICT _a, const double _bias)
{
	int i;
	for(i = 0; i < 3; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

