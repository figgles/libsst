/*
	AUTOMATICALLY GENERATED FILE - DO NOT EDIT!
	Please change MatrixNxN.py and re-run it
*/
/* Generated with n = 2, TYPE = float */

#include <float.h>
#include <pstdbool.h>
#include <stdio.h>
#include <math.h> /* for sqrt functions */
#include <stdlib.h> /* for the abs/labs functions */
#include <SST/SST_Build.h>

#include <SST/SST_Mat22.h>
#include <SST/SST_Vec2.h>
void SST_Math_Mat22fAdd(const SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B, SST_Mat22f* RESTRICT _out)
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

void SST_Math_Mat22fAddLocal(SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] += _B->v[0];
	 _A->v[1] += _B->v[1];
	 _A->v[2] += _B->v[2];
	 _A->v[3] += _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22fSubtract(const SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B, SST_Mat22f* RESTRICT _out)
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

void SST_Math_Mat22fSubtractLocal(SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] -= _B->v[0];
	 _A->v[1] -= _B->v[1];
	 _A->v[2] -= _B->v[2];
	 _A->v[3] -= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22fMultiplyElementwise(const SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B, SST_Mat22f* RESTRICT _out)
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

void SST_Math_Mat22fMultiplyElementwiseLocal(SST_Mat22f* RESTRICT _A, const SST_Mat22f* RESTRICT _B)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_B,16);

	 _A->v[0] *= _B->v[0];
	 _A->v[1] *= _B->v[1];
	 _A->v[2] *= _B->v[2];
	 _A->v[3] *= _B->v[3];
}

/******************************************************************************/

void SST_Math_Mat22fMultiplyScalar(const SST_Mat22f* RESTRICT _A, const float k,  SST_Mat22f* RESTRICT _out)
{
	SST_ASSUME_ALIGNED(_A,16);
	SST_ASSUME_ALIGNED(_out,16);

	 _out->v[0] = _A->v[0] * k;
	 _out->v[1] = _A->v[1] * k;
	 _out->v[2] = _A->v[2] * k;
	 _out->v[3] = _A->v[3] * k;
}

/******************************************************************************/

void SST_Math_Mat22fMultiplyScalarLocal(SST_Mat22f* RESTRICT _A, const float k)
{
	SST_ASSUME_ALIGNED(_A,16);

	 _A->v[0] *= k;
	 _A->v[1] *= k;
	 _A->v[2] *= k;
	 _A->v[3] *= k;
}

/******************************************************************************/


void SST_Math_Mat22fMultiplyMatrix(const SST_Mat22f* _A, const SST_Mat22f*  RESTRICT _B, SST_Mat22f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 2]*_B->v[ 1];
_out->v[ 2] = _A->v[ 0]*_B->v[ 2]+_A->v[ 2]*_B->v[ 3];
_out->v[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1];
_out->v[ 3] = _A->v[ 1]*_B->v[ 2]+_A->v[ 3]*_B->v[ 3];
}
void SST_Math_Mat22fMultiplyMatrixLocal(SST_Mat22f*  RESTRICT _A, const SST_Mat22f*  RESTRICT _B)
{
	float tmp[4];
	SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_B,16);
tmp[ 0] = _A->v[ 0]*_B->v[ 0]+_A->v[ 2]*_B->v[ 1];
tmp[ 2] = _A->v[ 0]*_B->v[ 2]+_A->v[ 2]*_B->v[ 3];
_A->v[0] = tmp[0];
_A->v[2] = tmp[2];


tmp[ 1] = _A->v[ 1]*_B->v[ 0]+_A->v[ 3]*_B->v[ 1];
tmp[ 3] = _A->v[ 1]*_B->v[ 2]+_A->v[ 3]*_B->v[ 3];
_A->v[1] = tmp[1];
_A->v[3] = tmp[3];


}
void SST_Math_Mat22fMultiplyVector(const SST_Mat22f*  RESTRICT _A, const SST_Vec2f*  RESTRICT _v, SST_Vec2f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
_out->v[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
}
void SST_Math_Mat22fMultiplyVectorLocal(const SST_Mat22f*  RESTRICT _A, SST_Vec2f*  RESTRICT _v)
{
float tmp[2];
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_v,16);
tmp[ 0] = _A->v[ 0]*_v->v[0]+_A->v[ 2]*_v->v[1];
tmp[ 1] = _A->v[ 1]*_v->v[0]+_A->v[ 3]*_v->v[1];
_v->v[0] = tmp[0];
_v->v[1] = tmp[1];
}
void SST_Math_Mat22fTranspose(const SST_Mat22f*  RESTRICT _A, SST_Mat22f*  RESTRICT _out)
{
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_out,16);
_out->v[ 0] = _A->v[ 0];
_out->v[ 1] = _A->v[ 2];
_out->v[ 2] = _A->v[ 1];
_out->v[ 3] = _A->v[ 3];
}
void SST_Math_Mat22fTransposeLocal(SST_Mat22f*  RESTRICT _A)
{
float tmp[2];
SST_ASSUME_ALIGNED(_A,16);
tmp[1] = _A->v[ 2];
_A->v[ 2] = _A->v[ 1];
_A->v[ 1] = tmp[1];
}
bool SST_Math_Mat22fCheckOrthonormal(const SST_Mat22f* _A)
{
const float diag = -_A->v[0]*_A->v[0] -_A->v[1]*_A->v[1] -_A->v[2]*_A->v[2] -_A->v[3]*_A->v[3];
const float odiag = _A->v[0]*_A->v[2]+ _A->v[1]*_A->v[3]+ _A->v[2]*_A->v[0]+ _A->v[3]*_A->v[1];
SST_ASSUME_ALIGNED(_A,16);
return 
((fabsf(2.000000f+diag)) <= 100*FLT_EPSILON) &
((fabsf(odiag)) <= 100*FLT_EPSILON);


}
float SST_Math_Mat22fDeterminant(const SST_Mat22f* _A)
{
	const float result = _A->v[0]*_A->v[3]-_A->v[1]*_A->v[2];
	SST_ASSUME_ALIGNED(_A,16);
	return result;
}
void SST_Math_Mat22fInvert(const SST_Mat22f*  RESTRICT _A, SST_Mat22f*  RESTRICT _out)
{
/* Analytical Invert for 2x2 */
const float aij = (1.000000f) / (_A->v[0]*_A->v[3]-_A->v[1]*_A->v[2]);
SST_ASSUME_ALIGNED(_A,16);
_out->v[0] =  aij*_A->v[3];
_out->v[1] = -aij*_A->v[1];
_out->v[2] = -aij*_A->v[2];
_out->v[3] =  aij*_A->v[0];

}
void SST_Math_Mat22fInvertLocal(SST_Mat22f* RESTRICT _A)
{
/* Analytical Invert for 2x2 */
const float aij = (1.000000f) / (_A->v[0]*_A->v[3]-_A->v[1]*_A->v[2]);
const float tmp = _A->v[0];
SST_ASSUME_ALIGNED(_A,16);
_A->v[0] =  aij*_A->v[3];
_A->v[1] *= -aij;
_A->v[2] *= -aij;
_A->v[3] =  aij*tmp;

}
void SST_Math_Mat22fCreateLU(const SST_Mat22f* RESTRICT _A, SST_Mat22f* RESTRICT _LU)
{
#define _A(i,j) _A->v[i+2*j]
#define _LU(i,j) _LU->v[i+2*j]
    int i,j,k;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
    _LU(0,0) = _A(0,0);
    _LU(0,1) = 0;
    _LU(1,0) = _A(1,0);
    /* _U(0,0) = 1.000000f; */
    /* _U(1,1) = 1.000000f; */
    _LU(0,1) = _A(0,1) / _LU(0,0);
    for(i=1; i < 2; i++) {

        for(j=1; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 2; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++)
                sum += -_LU(i,k)*_LU(k,j);
            _LU(i,j) = (_A(i,j) + sum) / _LU(i,i);
        }
    }
#undef _A
#undef _LU
}
void SST_Math_Mat22fApplyLUMat(const SST_Mat22f* _LU, const SST_Mat22f* _A, SST_Mat22f* _out)
{
 
#define _LU(i,j) _LU->v[i+2*j]
#define _A(i,j) _A->v[i+2*j]
#define _out(i,j) _out->v[i+2*j]
    int i, j, col;
    float sum;
SST_ASSUME_ALIGNED(_A,16);
SST_ASSUME_ALIGNED(_LU,16);
SST_ASSUME_ALIGNED(_out,16);
    for(col = 0; col < 2; col++) {
        _out(0,col) = _A(0,col);
        _out(1,col) = _A(1,col);
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 2; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 1; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 2; j++)
                sum += _LU(i,j) * _out(j,col);
            _out(i,col) = (_out(i,col) - sum) ; /* divide by U(i,i)=1 */
        }
    }
#undef _LU /* (i,j) _LU->v[i+2*j] */
#undef _A /* (i,j) _A->v[i+2*j] */
#undef _out /* (i,j) _out->v[i+2*j] */
}
void SST_Math_Mat22fApplyLUMatLocal(const SST_Mat22f* _LU,SST_Mat22f* _A)
{
 
#define _LU(i,j) _LU->v[i+2*j]
#define _A(i,j)  _A->v[i+2*j]
    int i, j, col;
    float sum;
    for(col = 0; col < 2; col++) {
        /* Forward Substitution for Ly = v */
        for(i = 0; i < 2; i++) {
            sum = 0.000000f;
            for(j = 0; j < i; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) / _LU(i,i) ;
        }
/* Backwards Substitution for Uw = y */
        for(i = 1; i >=0; i--) {
            sum = 0.000000f;
            for(j = i+1; j < 2; j++)
                sum += _LU(i,j) * _A(j,col);
            _A(i,col) = (_A(i,col) - sum) ; /* U is 1s along the diagonal */
        }
    }
}
void SST_Math_Mat22fApplyLUVec(const SST_Mat22f* _LU, const SST_Vec2f* _v,SST_Vec2f* _w)
{
 
#define _LU(i,j) _LU->v[i+2*j]
    int i, j;
    float sum;
    _w->v[0] = _v->v[0];
    _w->v[1] = _v->v[1];
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 2; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 1; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 2; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+2*j] */
}
void SST_Math_Mat22fApplyLUVecLocal(const SST_Mat22f* _LU,SST_Vec2f* _w)
{
 
#define _LU(i,j) _LU->v[i+2*j]
    int i, j;
    float sum;
    /* Forward Substitution for Ly = v */
    for(i = 0; i < 2; i++) {
        sum = 0.000000f;
        for(j = 0; j < i; j++)
            sum += _LU(i,j) * _w->v[j];
        _w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;
    }
/* Backwards Substitution for Uw = y */
    for(i = 1; i >= 0; i--) {
        sum = 0.000000f;
        for(j = i+1; j < 2; j++)
            sum += _LU(i,j) * _w->v[j];
        /*_w->v[i] = (_w->v[i] - sum) ;*/
        _w->v[i] = (_w->v[i] - sum) ;
    }
#undef _LU /* (i,j) _LU->v[i+2*j] */
}
void SST_Math_Mat22fCreateLULocal(SST_Mat22f* RESTRICT _A)
{
 /* Note this code stores both L and U inside of A */
 /* For A in R[n x m] we say that for n = m there is an LU = A decomposition [In our decomp, diag[L] = I. Furthermore there is an LU=PA decomposition, where P is a permutation matrix
 Step 1:  U(i,i:m) = A(i,i:m) 
 Step 2: L(i+1:n,i) = -A(i+1:n,i) 
 Step 3: ??? 
 Step 4: Profit */ 
#define _A(i,j) _A->v[i+2*j]
    int i,j,k;
    float sum;
/* These entries are the same as before in the algorithm. This is left in for purposes of clarity and completeness 
_L(0,0) = _A(0,0);
_L(1,0) = _A(1,0);
These entries are understood to be 1 in this storage format. This is left in for purposes of clarity and completeness 
_U(0,0) = 1.000000f;
_U(1,1) = 1.000000f;
*/
_A(0,1) = _A(0,1) / _A(0,0);
    for(i=1; i < 2; i++) {

        for(j=0; j <= i; j++) {
            sum = 0.000000f;
            for(k=0; k < j; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = _A(i,j) + sum;
        }
        for(j=i+1; j < 2; j++) {
            sum = 0.000000f;
            for(k=0; k < i; k++) sum += -_A(i,k)*_A(k,j);
            _A(i,j) = (_A(i,j) + sum) / _A(i,i);
        }
    }
#undef _A
}
