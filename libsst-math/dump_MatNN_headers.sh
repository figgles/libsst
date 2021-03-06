#!/bin/sh
HEADERPATH=../Lib/Include/SST
echo "/*  NEXT FILE  */
/* This is an AUTOGENERATED FILE generated from the bash script 'dumpheader.sh', last generated on `date`  */
#ifndef __SST_MAT22_H__
#define __SST_MAT22_H__
#include <SST/SST_Build.h>
#include <SST/SST_Vec2.h>
#include <pstdbool.h>
#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(disable:4201)
#endif
#ifdef __cplusplus
extern \"C\" {
#endif
		typedef SST_ALIGN_PREFIX(16) union SST_Mat22f
		{
				float v[4];
				struct { float a11, a21, a12, a22; };
		} SST_ALIGN_SUFFIX(16) SST_Mat22f;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat22d
		{
				double v[4];
				struct { double a11, a21, a12, a22; };
		} SST_ALIGN_SUFFIX(16) SST_Mat22d;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat22i
		{
				int v[4];
				struct { int a11, a21, a12, a22; };
		} SST_ALIGN_SUFFIX(16) SST_Mat22i;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat22u
		{
				unsigned int v[4];
				struct { unsigned int a11, a21, a12, a22; };
		} SST_ALIGN_SUFFIX(16) SST_Mat22u;" > $HEADERPATH/SST_Mat22.h
		echo "
		/*##########################################################
		##  float 
		##########################################################*/" >> $HEADERPATH/SST_Mat22.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat22f.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat22.h
		echo "
		/*##########################################################
		##  double 
		##########################################################*/" >> $HEADERPATH/SST_Mat22.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat22d.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat22.h
		echo "
		/*##########################################################
		##  int 
		##########################################################*/" >> $HEADERPATH/SST_Mat22.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat22i.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat22.h
		echo "
		/*##########################################################
		##  unsigned int
		##########################################################*/" >> $HEADERPATH/SST_Mat22.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat22u.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat22.h
echo "#ifdef __cplusplus
}
#endif
#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(default:4201)
#endif
#endif" >> $HEADERPATH/SST_Mat22.h
echo "/*  NEXT FILE  */
/* This is an AUTOGENERATED FILE generated from the bash script 'dumpheader.sh', last generated on `date` */
#ifndef __SST_MAT33_H__
#define __SST_MAT33_H__
#include <SST/SST_Build.h>
#include <SST/SST_Vec3.h>
#include <pstdbool.h>

#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(disable:4201)
#endif
#ifdef __cplusplus
extern \"C\" {
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
#undef PAD" > $HEADERPATH/SST_Mat33.h
		echo "
		/*##########################################################
		##  float 
		##########################################################*/" >> $HEADERPATH/SST_Mat33.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat33f.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat33.h
		echo "
		/*##########################################################
		##  double 
		##########################################################*/" >> $HEADERPATH/SST_Mat33.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat33d.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat33.h
		echo "
		/*##########################################################
		##  int 
		##########################################################*/" >> $HEADERPATH/SST_Mat33.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat33i.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat33.h
		echo "
		/*##########################################################
		##  unsigned int
		##########################################################*/" >> $HEADERPATH/SST_Mat33.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat33u.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat33.h
echo "#ifdef __cplusplus
}
#endif
#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(default:4201)
#endif
#endif" >> $HEADERPATH/SST_Mat33.h
echo "/*  NEXT FILE  */
/* This is an AUTOGENERATED FILE generated from the bash script 'dumpheader.sh', last generated on `date` */
#ifndef __SST_MAT44_H__
#define __SST_MAT44_H__
#include <SST/SST_Build.h>
#include <SST/SST_Vec4.h>
#include <pstdbool.h>

#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(disable:4201)
#endif
#ifdef __cplusplus
extern \"C\" {
#endif

		typedef SST_ALIGN_PREFIX(16) union SST_Mat44f
		{
				float v[16];
				struct { float a11, a21, a31, a41,
						a12, a22, a32, a42,
						a13, a23, a33, a43,
						a14, a24, a34, a44; };
		} SST_ALIGN_SUFFIX(16) SST_Mat44f;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat44d
		{
				double v[16];
				struct { double a11, a21, a31, a41,
						a12, a22, a32, a42,
						a13, a23, a33, a43,
						a14, a24, a34, a44; };
		} SST_ALIGN_SUFFIX(16) SST_Mat44d;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat44i
		{
				int v[16];
				struct { int a11, a21, a31, a41,
						a12, a22, a32, a42,
						a13, a23, a33, a43,
						a14, a24, a34, a44; };
		} SST_ALIGN_SUFFIX(16) SST_Mat44i;

		typedef SST_ALIGN_PREFIX(16) union SST_Mat44u
		{
				unsigned int v[16];
				struct { unsigned int a11, a21, a31, a41,
						a12, a22, a32, a42,
						a13, a23, a33, a43,
						a14, a24, a34, a44; };
		} SST_ALIGN_SUFFIX(16) SST_Mat44u;" > $HEADERPATH/SST_Mat44.h
		echo "
		/*##########################################################
		##  float 
		##########################################################*/" >> $HEADERPATH/SST_Mat44.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat44f.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat44.h
		echo "
		/*##########################################################
		##  double 
		##########################################################*/" >> $HEADERPATH/SST_Mat44.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat44d.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat44.h
		echo "
		/*##########################################################
		##  int 
		##########################################################*/" >> $HEADERPATH/SST_Mat44.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat44i.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat44.h
		echo "
		/*##########################################################
		##  unsigned int
		##########################################################*/" >> $HEADERPATH/SST_Mat44.h
grep -h "^[bvfdiu][Boln][iouts].* SST_Math_Mat" SST_Mat44u.c | sed -e "s/$/;/" -e "s/^/		/" >> $HEADERPATH/SST_Mat44.h
echo "#ifdef __cplusplus
}
#endif
#if SST_COMPILER == SST_COMPILER_MSVC
#pragma warning(default:4201)
#endif
#endif" >> $HEADERPATH/SST_Mat44.h
