/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 4, TYPE = int */

#include <float.h>
#include <math.h>
#include <pstdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SST/SST_Build.h>
#include <SST/SST_Vec4.h>

void SST_Math_Vec4iAdd(const SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B, SST_Vec4i* RESTRICT _out)
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

void SST_Math_Vec4iAddLocal(SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4iSubtract(const SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B, SST_Vec4i* RESTRICT _out)
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

void SST_Math_Vec4iSubtractLocal(SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4iMultiply(const SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B, SST_Vec4i* RESTRICT _out)
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

void SST_Math_Vec4iMultiplyLocal(SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Vec4iScale(const SST_Vec4i* RESTRICT _A,  const int k, SST_Vec4i* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Vec4iScaleLocal(SST_Vec4i* RESTRICT _A, const int k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/

void SST_Math_Vec4iDivide(const SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B, SST_Vec4i* RESTRICT _out)
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

void SST_Math_Vec4iDivideLocal(SST_Vec4i* RESTRICT _A, const SST_Vec4i* RESTRICT _B)
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


void SST_Math_Vec4iAddMult(const SST_Vec4i* RESTRICT _X, const int _x, const SST_Vec4i* RESTRICT _Y, SST_Vec4i* RESTRICT _Z)
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


void SST_Math_Vec4iAddMultLocal(SST_Vec4i* RESTRICT _X, const int _x, const SST_Vec4i* RESTRICT _Y)
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


void SST_Math_Vec4iLerp(const SST_Vec4i* RESTRICT _X, const SST_Vec4i* RESTRICT _Y, const int _y, SST_Vec4i* RESTRICT _Z)
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

void SST_Math_Vec4iLerpLocal(SST_Vec4i* RESTRICT _X, const SST_Vec4i* RESTRICT _Y, const int _y)
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


void SST_Math_Vec4iWeightedSum(const SST_Vec4i* RESTRICT _X, const int _x, const SST_Vec4i* RESTRICT _Y, const int _y, SST_Vec4i* RESTRICT _Z)
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

void SST_Math_Vec4iWeightedSumLocal(SST_Vec4i* RESTRICT _X, const int _x, const SST_Vec4i* RESTRICT _Y, const int _y)
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

bool SST_Math_Vec4iEquals(const SST_Vec4i* RESTRICT _a, const SST_Vec4i* RESTRICT _b)
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

int SST_Math_Vec4iMax(const SST_Vec4i* RESTRICT _a)
{
	int tmp = _a->v[0];
	if(tmp < _a->v[1]) tmp = _a->v[1];
	if(tmp < _a->v[2]) tmp = _a->v[2];
	if(tmp < _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

int SST_Math_Vec4iMin(const SST_Vec4i* RESTRICT _a)
{
	int tmp = _a->v[0];
	if(tmp > _a->v[1]) tmp = _a->v[1];
	if(tmp > _a->v[2]) tmp = _a->v[2];
	if(tmp > _a->v[3]) tmp = _a->v[3];

	return tmp;
}

/******************************************************************************/

void SST_Math_Vec4iAbs(const SST_Vec4i* RESTRICT _in, SST_Vec4i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = abs(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4iAbsLocal(SST_Vec4i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = abs(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4iNegate(const SST_Vec4i* RESTRICT _in, SST_Vec4i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = -(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4iNegateLocal(SST_Vec4i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = -(_a->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4iRecip(const SST_Vec4i* RESTRICT _in, SST_Vec4i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
		_out->v[i] = 1/(_in->v[i]);
}

/******************************************************************************/

void SST_Math_Vec4iRecipLocal(SST_Vec4i* RESTRICT _a)
{
	int i;
	for(i = 0; i < 4; i++)
		_a->v[i] = 1/(_a->v[i]);
}

/******************************************************************************/

int SST_Math_Vec4iDot(const SST_Vec4i* RESTRICT _a, const SST_Vec4i* RESTRICT _b)
{
	int sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}

/******************************************************************************/

int SST_Math_Vec4iMagnitudeSquared(const SST_Vec4i* RESTRICT _a)
{
	int sum = 0;
	int i;
	for(i = 0; i < 4; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}

/******************************************************************************/

void SST_Math_Vec4iProject(const SST_Vec4i* RESTRICT _a, const SST_Vec4i* RESTRICT _b, SST_Vec4i* RESTRICT _out)
{
	int scalar = SST_Math_Vec4iDot(_a,_b) / SST_Math_Vec4iDot(_b,_b);
	SST_Math_Vec4iScale(_b, scalar, _out);
}
		

/******************************************************************************/

void SST_Math_Vec4iProjectLocal(SST_Vec4i* RESTRICT _a, const SST_Vec4i* RESTRICT _b)
{
	int scalar = SST_Math_Vec4iDot(_a,_b) / SST_Math_Vec4iDot(_b,_b);
	SST_Math_Vec4iScale(_b, scalar, _a);
}
		

/******************************************************************************/

void SST_Math_Vec4iBias(const SST_Vec4i* RESTRICT _a, const int _bias, SST_Vec4i* RESTRICT _out)
{
	int i;
	for(i = 0; i < 4; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		

/******************************************************************************/

void SST_Math_Vec4iBiasLocal(SST_Vec4i* RESTRICT _a, const int _bias)
{
	int i;
	for(i = 0; i < 4; i++)
	_a->v[i] += _bias;
}
		

/******************************************************************************/

