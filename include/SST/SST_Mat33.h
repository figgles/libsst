/*  NEXT FILE  */
/* This is an AUTOGENERATED FILE generated from the bash script 'dumpheader.sh', last generated on Fri Apr 18 19:06:56 CDT 2014 */
#ifndef __SST_MAT33_H__
#define __SST_MAT33_H__
#include <SST/SST_Build.h>
#include <SST/SST_Vec3.h>
#include <pstdbool.h>

#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(disable:4201)
#endif
#ifdef __cplusplus
extern "C" {
#endif
#define PAD 3 /* spaces it out to 4 * T for better alignment */
		typedef SST_ALIGN_PREFIX(16) union SST_Mat33f
		{
				float v[9+PAD];
				struct { float a11, a21, a31,
						a12, a22, a32,
						a13, a23, a33; };
		} SST_ALIGN_SUFFIX(16) SST_Mat33f;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat33d
		{
				double v[9+PAD];
				struct { double a11, a21, a31, 
						a12, a22, a32,
						a13, a23, a33; };
		} SST_ALIGN_SUFFIX(16) SST_Mat33d;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat33u
		{
				unsigned int v[9+PAD];
				struct { unsigned int a11, a21, a31, 
						a12, a22, a32,
						a13, a23, a33; };
		} SST_ALIGN_SUFFIX(16) SST_Mat33u;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat33i
		{
				int v[9+PAD];
				struct { int a11, a21, a31, 
						a12, a22, a32,
						a13, a23, a33; };
		} SST_ALIGN_SUFFIX(16) SST_Mat33i;
#undef PAD

		/*##########################################################
		##  float 
		##########################################################*/
		void SST_Math_Mat33fAdd(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out);
		void SST_Math_Mat33fAddLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B);
		void SST_Math_Mat33fSubtract(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out);
		void SST_Math_Mat33fSubtractLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B);
		void SST_Math_Mat33fMultiplyElementwise(const SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B, SST_Mat33f* RESTRICT _out);
		void SST_Math_Mat33fMultiplyElementwiseLocal(SST_Mat33f* RESTRICT _A, const SST_Mat33f* RESTRICT _B);
		void SST_Math_Mat33fMultiplyScalar(const SST_Mat33f* RESTRICT _A, const float k,  SST_Mat33f* RESTRICT _out);
		void SST_Math_Mat33fMultiplyScalarLocal(SST_Mat33f* RESTRICT _A, const float k);
		void SST_Math_Mat33fMultiplyMatrix(const SST_Mat33f* _A, const SST_Mat33f*  RESTRICT _B, SST_Mat33f*  RESTRICT _out);
		void SST_Math_Mat33fMultiplyMatrixLocal(SST_Mat33f*  RESTRICT _A, const SST_Mat33f*  RESTRICT _B);
		void SST_Math_Mat33fMultiplyVector(const SST_Mat33f*  RESTRICT _A, const SST_Vec3f*  RESTRICT _v, SST_Vec3f*  RESTRICT _out);
		void SST_Math_Mat33fMultiplyVectorLocal(const SST_Mat33f*  RESTRICT _A, SST_Vec3f*  RESTRICT _v);
		void SST_Math_Mat33fTranspose(const SST_Mat33f*  RESTRICT _A, SST_Mat33f*  RESTRICT _out);
		void SST_Math_Mat33fTransposeLocal(SST_Mat33f*  RESTRICT _A);
		bool SST_Math_Mat33fCheckOrthonormal(const SST_Mat33f* _A);
		float SST_Math_Mat33fDeterminant(const SST_Mat33f* _A);
		void SST_Math_Mat33fInvert(const SST_Mat33f*  RESTRICT _A, SST_Mat33f*  RESTRICT _out);
		void SST_Math_Mat33fInvertLocal(SST_Mat33f* RESTRICT _A);
		void SST_Math_Mat33fCreateLU(const SST_Mat33f* RESTRICT _A, SST_Mat33f* RESTRICT _LU);
		void SST_Math_Mat33fApplyLUMat(const SST_Mat33f* _LU, const SST_Mat33f* _A, SST_Mat33f* _out);
		void SST_Math_Mat33fApplyLUMatLocal(const SST_Mat33f* _LU,SST_Mat33f* _A);
		void SST_Math_Mat33fApplyLUVec(const SST_Mat33f* _LU, const SST_Vec3f* _v,SST_Vec3f* _w);
		void SST_Math_Mat33fApplyLUVecLocal(const SST_Mat33f* _LU,SST_Vec3f* _w);
		void SST_Math_Mat33fCreateLULocal(SST_Mat33f* RESTRICT _A);

		/*##########################################################
		##  double 
		##########################################################*/
		void SST_Math_Mat33dAdd(const SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B, SST_Mat33d* RESTRICT _out);
		void SST_Math_Mat33dAddLocal(SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B);
		void SST_Math_Mat33dSubtract(const SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B, SST_Mat33d* RESTRICT _out);
		void SST_Math_Mat33dSubtractLocal(SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B);
		void SST_Math_Mat33dMultiplyElementwise(const SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B, SST_Mat33d* RESTRICT _out);
		void SST_Math_Mat33dMultiplyElementwiseLocal(SST_Mat33d* RESTRICT _A, const SST_Mat33d* RESTRICT _B);
		void SST_Math_Mat33dMultiplyScalar(const SST_Mat33d* RESTRICT _A, const double k,  SST_Mat33d* RESTRICT _out);
		void SST_Math_Mat33dMultiplyScalarLocal(SST_Mat33d* RESTRICT _A, const double k);
		void SST_Math_Mat33dMultiplyMatrix(const SST_Mat33d* _A, const SST_Mat33d*  RESTRICT _B, SST_Mat33d*  RESTRICT _out);
		void SST_Math_Mat33dMultiplyMatrixLocal(SST_Mat33d*  RESTRICT _A, const SST_Mat33d*  RESTRICT _B);
		void SST_Math_Mat33dMultiplyVector(const SST_Mat33d*  RESTRICT _A, const SST_Vec3d*  RESTRICT _v, SST_Vec3d*  RESTRICT _out);
		void SST_Math_Mat33dMultiplyVectorLocal(const SST_Mat33d*  RESTRICT _A, SST_Vec3d*  RESTRICT _v);
		void SST_Math_Mat33dTranspose(const SST_Mat33d*  RESTRICT _A, SST_Mat33d*  RESTRICT _out);
		void SST_Math_Mat33dTransposeLocal(SST_Mat33d*  RESTRICT _A);
		bool SST_Math_Mat33dCheckOrthonormal(const SST_Mat33d* _A);
		double SST_Math_Mat33dDeterminant(const SST_Mat33d* _A);
		void SST_Math_Mat33dInvert(const SST_Mat33d*  RESTRICT _A, SST_Mat33d*  RESTRICT _out);
		void SST_Math_Mat33dInvertLocal(SST_Mat33d* RESTRICT _A);
		void SST_Math_Mat33dCreateLU(const SST_Mat33d* RESTRICT _A, SST_Mat33d* RESTRICT _LU);
		void SST_Math_Mat33dApplyLUMat(const SST_Mat33d* _LU, const SST_Mat33d* _A, SST_Mat33d* _out);
		void SST_Math_Mat33dApplyLUMatLocal(const SST_Mat33d* _LU,SST_Mat33d* _A);
		void SST_Math_Mat33dApplyLUVec(const SST_Mat33d* _LU, const SST_Vec3d* _v,SST_Vec3d* _w);
		void SST_Math_Mat33dApplyLUVecLocal(const SST_Mat33d* _LU,SST_Vec3d* _w);
		void SST_Math_Mat33dCreateLULocal(SST_Mat33d* RESTRICT _A);

		/*##########################################################
		##  int 
		##########################################################*/
		void SST_Math_Mat33iAdd(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out);
		void SST_Math_Mat33iAddLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B);
		void SST_Math_Mat33iSubtract(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out);
		void SST_Math_Mat33iSubtractLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B);
		void SST_Math_Mat33iMultiplyElementwise(const SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B, SST_Mat33i* RESTRICT _out);
		void SST_Math_Mat33iMultiplyElementwiseLocal(SST_Mat33i* RESTRICT _A, const SST_Mat33i* RESTRICT _B);
		void SST_Math_Mat33iMultiplyScalar(const SST_Mat33i* RESTRICT _A, const int k,  SST_Mat33i* RESTRICT _out);
		void SST_Math_Mat33iMultiplyScalarLocal(SST_Mat33i* RESTRICT _A, const int k);
		void SST_Math_Mat33iMultiplyMatrix(const SST_Mat33i* _A, const SST_Mat33i*  RESTRICT _B, SST_Mat33i*  RESTRICT _out);
		void SST_Math_Mat33iMultiplyMatrixLocal(SST_Mat33i*  RESTRICT _A, const SST_Mat33i*  RESTRICT _B);
		void SST_Math_Mat33iMultiplyVector(const SST_Mat33i*  RESTRICT _A, const SST_Vec3i*  RESTRICT _v, SST_Vec3i*  RESTRICT _out);
		void SST_Math_Mat33iMultiplyVectorLocal(const SST_Mat33i*  RESTRICT _A, SST_Vec3i*  RESTRICT _v);
		void SST_Math_Mat33iTranspose(const SST_Mat33i*  RESTRICT _A, SST_Mat33i*  RESTRICT _out);
		void SST_Math_Mat33iTransposeLocal(SST_Mat33i*  RESTRICT _A);
		bool SST_Math_Mat33iCheckOrthonormal(const SST_Mat33i* _A);
		int SST_Math_Mat33iDeterminant(const SST_Mat33i* _A);

		/*##########################################################
		##  unsigned int
		##########################################################*/
		void SST_Math_Mat33uAdd(const SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B, SST_Mat33u* RESTRICT _out);
		void SST_Math_Mat33uAddLocal(SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B);
		void SST_Math_Mat33uSubtract(const SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B, SST_Mat33u* RESTRICT _out);
		void SST_Math_Mat33uSubtractLocal(SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B);
		void SST_Math_Mat33uMultiplyElementwise(const SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B, SST_Mat33u* RESTRICT _out);
		void SST_Math_Mat33uMultiplyElementwiseLocal(SST_Mat33u* RESTRICT _A, const SST_Mat33u* RESTRICT _B);
		void SST_Math_Mat33uMultiplyScalar(const SST_Mat33u* RESTRICT _A, const unsigned int k,  SST_Mat33u* RESTRICT _out);
		void SST_Math_Mat33uMultiplyScalarLocal(SST_Mat33u* RESTRICT _A, const unsigned int k);
		void SST_Math_Mat33uMultiplyMatrix(const SST_Mat33u* _A, const SST_Mat33u*  RESTRICT _B, SST_Mat33u*  RESTRICT _out);
		void SST_Math_Mat33uMultiplyMatrixLocal(SST_Mat33u*  RESTRICT _A, const SST_Mat33u*  RESTRICT _B);
		void SST_Math_Mat33uMultiplyVector(const SST_Mat33u*  RESTRICT _A, const SST_Vec3u*  RESTRICT _v, SST_Vec3u*  RESTRICT _out);
		void SST_Math_Mat33uMultiplyVectorLocal(const SST_Mat33u*  RESTRICT _A, SST_Vec3u*  RESTRICT _v);
		void SST_Math_Mat33uTranspose(const SST_Mat33u*  RESTRICT _A, SST_Mat33u*  RESTRICT _out);
		void SST_Math_Mat33uTransposeLocal(SST_Mat33u*  RESTRICT _A);
#ifdef __cplusplus
}
#endif
#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(default:4201)
#endif
#endif
