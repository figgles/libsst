#!/usr/bin/env python
from scipy import *
from numpy import *
import re
import sys

if len(sys.argv) < 3:
    sys.exit("Please provide both the number of elements (2-4) and the type of element (float, int, double) at the command line")
	
if len(sys.argv) == 3:
	DEBUG_PRINT = False
	CODE_TYPE = ''

else:
	DEBUG_PRINT = True
	CODE_TYPE = sys.argv[3]

N = int(sys.argv[1])
TYPE = sys.argv[2]

COMMBREAK = '/******************************************************************************/'

'''
/* Vec3f (3D float Vector) Routines */
 
/* f:R3 -> R3 */
void SST_Math_Vec3fAbs(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fAbsLocal(SST_Vec3f* a);
void SST_Math_Vec3fNegate(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fNegateLocal(const SST_Vec3f* a);
void SST_Math_Vec3fNormalize(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fNormalizeLocal(SST_Vec3f* a);
void SST_Math_Vec3fRecip(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fRecipLocal(SST_Vec3f* a);
void SST_Math_Vec3fRecipEst(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fRecipEstLocal(SST_Vec3f* a);
void SST_Math_Vec3fRecipSqrt(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fRecipSqrtLocal(SST_Vec3f* a);
void SST_Math_Vec3fRecipSqrtEst(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fRecipSqrtEstLocal(const SST_Vec3f* a);
void SST_Math_Vec3fSqrt(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fSqrtLocal(SST_Vec3f* a);
void SST_Math_Vec3fSqrtEst(const SST_Vec3f* a, SST_Vec3f* out);
void SST_Math_Vec3fSqrtEstLocal(SST_Vec3f* a);

/* f:R3 -> R */
float SST_Math_Vec3fL1Norm(const SST_Vec3f* a);
float SST_Math_Vec3fMagnitude(const SST_Vec3f* a);
float SST_Math_Vec3fMagnitudeSquared(const SST_Vec3f* a);
float SST_Math_Vec3fRecipMagnitude(const SST_Vec3f* a);

/* f:R3xR3 -> R */
float SST_Vector3f_Dot(const SST_Vec3f* a, const SST_Vec3f* b);

/* f:R3xR3 -> R3 */
void SST_Math_Vec3fAdd(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fAddLocal(SST_Vec3f* a, const SST_Vec3f* b);
void SST_Math_Vec3fCross(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fCrossLocal(SST_Vec3f* a, const SST_Vec3f* b);
void SST_Math_Vec3fDivide(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fDivideLocal(SST_Vec3f* a, const SST_Vec3f* b);
void SST_Math_Vec3fMultiply(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fMultiplyLocal(SST_Vec3f* a, const SST_Vec3f* b);
void SST_Math_Vec3fProject(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fProjectLocal(SST_Vec3f* a, const SST_Vec3f* b);
void SST_Math_Vec3fSubtract(const SST_Vec3f* a, const SST_Vec3f* b, SST_Vec3f* out);
void SST_Math_Vec3fSubtractLocal(SST_Vec3f* a, const SST_Vec3f* b);

/* f:R3xR -> R3 */
void SST_Math_Vec3fBias(const SST_Vec3f* a, const float bias, SST_Vec3f* out); 
void SST_Math_Vec3fBiasLocal(SST_Vec3f* a, const float bias);
void SST_Math_Vec3fScale(const SST_Vec3f* a, const float scale, SST_Vec3f* out); 
void SST_Math_Vec3fScaleLocal(SST_Vec3f* a, const float scale);

/* f:R3xR3xR -> R3 */
void SST_Math_Vec3fRotate(const SST_Vec3f* a, const SST_Vec3f* axis, float theta, SST_Vec3f* out);
void SST_Math_Vec3fRotateLocal(SST_Vec3f* a, const SST_Vec3f* axis, float theta);'''


#C function table
fabs = {'double' : 'fabs', 'float' : 'fabsf', 'int' : 'abs', 'unsigned int' : 'abs'}
cstyle = {'double' : '%24.16f', 'float' : '%ff', 'int' : '%d' , 'unsigned int' : '%u' }
fp_epsilon = {'double' : 'DBL_EPSILON' , 'float' : 'FLT_EPSILON' , 'int' : '0', 'unsigned int' : '0'}
size_t = {'double' : 64, 'float' : 32, 'int' : 32, 'unsigned int' : 32}
DTYPE = {'double' : float64 , 'float' : float32 , 'int' : int32 , 'unsigned int' : uint32}
COS   = {'double' : 'cos', 'float' : 'cosf', 'int' : '(int)cosf', 'unsigned int' : None}
SIN   = {'double' : 'sin', 'float' : 'sinf', 'int' : '(int)sinf', 'unsigned int' : None}
SQRT  = {'double' : 'sqrt', 'float' : 'sqrtf', 'int' : '(int)sqrtf', 'unsigned int' : None}

def levi_civita(i,j,k):
    indict = { (1,2,3): 1,
            (3,1,2): 1,
            (2,3,1): 1,
            (1,3,2):-1,
            (2,1,3):-1,
            (3,2,1):-1}
    return indict.get((i,j,k),0)

def kronecker(i,j):
    if(i==j):
        return 1
    else:
        return 0

def cprintf(name,N,M,explode_flag):
		if(DEBUG_PRINT):
				if(explode_flag):
						print('fprintf(stdout,"'+name+'\");')
						for i in r_[0:N]:
								for j in r_[0:M]:
										print('fprintf(stdout,"' + name + '[%d][%d]' % (i,j) + '='+cstyle[TYPE]+'",' + name  + '[%d]' % (N*i+j) + ');')
								print('fprintf(stdout,"\");')
				else:
						print('fprintf(stdout,"'+name+'\");')
						for i in r_[0:N]:
								for j in r_[0:M]:
										print('fprintf(stdout,"'+cstyle[TYPE]+' ",' + name  + '[%d]' % (N*i+j) + ');')
								print('fprintf(stdout,"\");')
		else:
				'''N+1 #it gets angry if this isn't here	'''

def A_op_B(op):
    for i in range(N):
        print('\t _A->v[%d] %s _B->v[%d];' % (i, op, i))

def A_op_K(op):
    for i in range(N):
        print('\t _A->v[%d] %s k;' % (i, op))

def A_op_B_eq_Out(op):
    for i in range(N):
        print('\t _out->v[%d] = _A->v[%d] %s _B->v[%d];' % (i, i, op, i))

def A_op_K_eq_Out(op):
    for i in range(N):
        print('\t _out->v[%d] = _A->v[%d] %s k;' % (i, i, op))

def commbreak():
    print('\n' + COMMBREAK + '\n');

# Generates: out = A op B
def ThreeVectorFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name +'(const %s* RESTRICT _A, const %s* RESTRICT _B, %s* RESTRICT _out)\n{' % (VECTYPE, VECTYPE, VECTYPE))

    #Alignment assumptions
    if(N == 3) or (N == 4):
		print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_B,16);\n\tSST_ASSUME_ALIGNED(_out,16);\n')

    #Generate operation
    A_op_B_eq_Out(op)

    print("}");
    commbreak();


# Generates: out = function(A, B)
def ThreeVectorWithFunctionFunc(Name, func):
    # Function header
    print(function_preamble+function_suffix+Name +'(const %s* RESTRICT _A, const %s* RESTRICT _B, %s* RESTRICT _out)\n{' % (VECTYPE, VECTYPE, VECTYPE))

    #Alignment assumptions
    if(N == 3) or (N == 4):
		print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_B,16);\n\tSST_ASSUME_ALIGNED(_out,16);\n')

    #Generate operation
    A_op_B_eq_Out(op)

    print("}");
    commbreak();


# Generates: A op= B
def TwoVectorFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name +'(%s* RESTRICT _A, const %s* RESTRICT _B)\n{' % (VECTYPE, VECTYPE))

    #Alignment assumptions
    if(N == 3) or (N == 4):
		print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_B,16);\n')

    #Generate operation
    A_op_B(op)

    print("}");
    commbreak();

# Generates: A op= K
def VectorScalarFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name +'(%s* RESTRICT _A, const %s k)\n{' % (VECTYPE, TYPE))

    #Alignment assumptions
    if(N == 3) or (N == 4):
        print('\tSST_ASSUME_ALIGNED(_A,16);\n')

    #Generate operation
    A_op_K(op)

    print("}");
    commbreak();


# Generates: out = A op K
def TwoVectorScalarFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name +'(const %s* RESTRICT _A,  const %s k, %s* RESTRICT _out)\n{' % (VECTYPE, TYPE, VECTYPE ))

    #Alignment assumptions
    if(N == 3) or (N == 4):
        print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_out,16);\n')

    #Generate operation
    A_op_K_eq_Out(op)

    print("}");
    commbreak();




rows = r_[0:N]
columns = r_[0:N]

# FLAGS for use in this generator
DEBUG_PRINT=False
DEBUG_FLAG = False
PIVOTING_FLAG = True
SINGULAR_FLAG = False
TIMING_CHECK = False
# End of FLAGS

function_preamble = 'void SST_Math_'
function_suffix = 'Vec%d%s' % (N,TYPE[0])
function_call = 'SST_Math_Vec%d%s' % (N,TYPE[0])
VECTYPE = 'SST_Vec%d%s' % (N,TYPE[0])

if(CODE_TYPE == ''):
		# HEADER
		print('/*')
		print('\tAUTOMATICALLY GENERATED FILE - DO NOT EDIT!')
		print('\tPlease change MatrixNxN.py and re-run it')
		print('*/')
		print('/* Generated with n = %d, TYPE = %s */\n' % (N,TYPE))

		print('#include <float.h>')
		print('#include <math.h>')
		print('#include <pstdbool.h>')
		print('#include <stdio.h>')
		print('#include <stdlib.h>')
		print('#include <SST/SST_Build.h>')
		print('#include <SST/%s.h>\n' % (VECTYPE[0:-1]))

		#Add()
		ThreeVectorFunc("Add", "+")

		#AddLocal()
		TwoVectorFunc("AddLocal", "+=")

		#Sub()
		ThreeVectorFunc("Subtract", "-")

		#SubLocal()
		TwoVectorFunc("SubtractLocal", "-=")

		#Mult()
		ThreeVectorFunc("Multiply", "*")

		#MultLocal()
		TwoVectorFunc("MultiplyLocal", "*=")

		#Scale()
		TwoVectorScalarFunc("Scale", "*")

		#ScaleLocal()
		VectorScalarFunc("ScaleLocal", "*=")

		#Divide()
		ThreeVectorFunc("Divide","/")

		#DivideLocal()
		TwoVectorFunc("DivideLocal","/=")

		commbreak()

		#AddMult()
		listnums = list(range(0,N)*3); listnums.sort()
		opstr = "\t_Z->v[%d] = _x * _X->v[%d] + _Y->v[%d];\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sAddMult(const %s* RESTRICT _X, const %s _x, const %s* RESTRICT _Y, %s* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* _Z = _x * _X + _Y */
%s
}
''' % (function_suffix, VECTYPE, TYPE, VECTYPE, VECTYPE,opstr))

		#AddMultLocal()
		listnums = list(range(0,N)*3); listnums.sort()
		opstr = "\t_X->v[%d] = _x * _X->v[%d] + _Y->v[%d];\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sAddMultLocal(%s* RESTRICT _X, const %s _x, const %s* RESTRICT _Y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* _X = _x * _X + _Y */
%s
}
''' % (function_suffix, VECTYPE, TYPE, VECTYPE, opstr))

		commbreak()

		#Lerpolate()
		listnums = list(range(0,N)*4); listnums.sort()
		opstr = "\t_Z->v[%d] = _X->v[%d] + (_Y->v[%d] - _X->v[%d]) * _y ;\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sLerp(const %s* RESTRICT _X, const %s* RESTRICT _Y, const %s _y, %s* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
%s
}''' % (function_suffix, VECTYPE, VECTYPE, TYPE, VECTYPE,opstr))

		#LerpolateLocal()
		listnums = list(range(0,N)*4); listnums.sort()
		opstr = "\t_X->v[%d] = _X->v[%d] + (_Y->v[%d] - _X->v[%d]) * _y ;\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sLerpLocal(%s* RESTRICT _X, const %s* RESTRICT _Y, const %s _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
%s
}''' % (function_suffix, VECTYPE, VECTYPE, TYPE, opstr))

		del opstr

		commbreak()
		#Lerpolate()
		listnums = list(range(0,N)*3); listnums.sort()
		opstr = "\t_Z->v[%d] = _x * _X->v[%d] + _y * _Y->v[%d];\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sWeightedSum(const %s* RESTRICT _X, const %s _x, const %s* RESTRICT _Y, const %s _y, %s* RESTRICT _Z)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	SST_ASSUME_ALIGNED(_Z,16);
	/* Z = x*X + y*Y */
%s
}''' % (function_suffix, VECTYPE, TYPE, VECTYPE, TYPE, VECTYPE,opstr))

		#LerpolateLocal()
		listnums = list(range(0,N)*3); listnums.sort()
		opstr = "\t_X->v[%d] = _x * _X->v[%d] + _y * _Y->v[%d];\n"*N % (tuple(listnums));
		print('''
void SST_Math_%sWeightedSumLocal(%s* RESTRICT _X, const %s _x, const %s* RESTRICT _Y, const %s _y)
{
	SST_ASSUME_ALIGNED(_X,16);
	SST_ASSUME_ALIGNED(_Y,16);
	/* Z = x*X + y*Y */
%s
}''' % (function_suffix, VECTYPE, TYPE, VECTYPE, TYPE, opstr))

		del opstr

		commbreak()

		#Equals()
		if((TYPE == 'int') or (TYPE == 'unsigned int')):
			print('''bool SST_Math_%sEquals(const %s* RESTRICT _a, const %s* RESTRICT _b)
{
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;
	for(i=0;i<%d;i++)
	{
		returncode = (_a->v[i]==_b->v[i]) && returncode;
	}
	return returncode;
} 
			''' % (function_suffix, VECTYPE, VECTYPE, N))
		else:
			print('''bool SST_Math_%sEquals(const %s* RESTRICT _a, const %s* RESTRICT _b, const %s _tolerance)
{
	%s tmp;
	int i;
	bool returncode;
	SST_ASSUME_ALIGNED(_a,16);
	SST_ASSUME_ALIGNED(_b,16);
	returncode = 1;

	SST_Math_%sSubtract(_a,_b,&tmp);
	for(i=0;i<%d;i++)
	{
		returncode = (%s(tmp.v[i]) <= _tolerance) && returncode;
	}
	
	return returncode;
} 
			''' % (function_suffix, VECTYPE, VECTYPE, TYPE, VECTYPE, function_suffix, N, fabs[TYPE]))
			
			

		commbreak()
		# Comparisons
		indices = range(1,N)*2; indices.sort()
		print('''%s SST_Math_%sMax(const %s* RESTRICT _a)
{
	%s tmp = _a->v[0];
%s
	return tmp;
}'''  % (TYPE, function_suffix, VECTYPE, TYPE,'\tif(tmp < _a->v[%d]) tmp = _a->v[%d];\n'*(N-1) % (tuple(indices))))
		commbreak()
		print('''%s SST_Math_%sMin(const %s* RESTRICT _a)
{
	%s tmp = _a->v[0];
%s
	return tmp;
}'''  % (TYPE, function_suffix, VECTYPE, TYPE,'\tif(tmp > _a->v[%d]) tmp = _a->v[%d];\n'*(N-1) % (tuple(indices))))

		commbreak()

		if((TYPE != 'int') & (TYPE != 'unsigned int')):
			if(N != 4):
				#Cross
				print('''void SST_Math_%sCross(const %s* RESTRICT _a, const %s* RESTRICT _b, %s* RESTRICT _out)
				{''' % (function_suffix,VECTYPE,VECTYPE,VECTYPE))
				if (N==2):
					print('''
	_out->v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_out->v[1] = _out->v[0];''')
				if (N==3):
					print(''' 
	_out->v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	_out->v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	_out->v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];''')

				print('}')

				commbreak()
				#CrossLocal
				print('''void SST_Math_%sCrossLocal(%s* RESTRICT _a, const %s* RESTRICT _b)\n{
	%s out;'''% (function_suffix,VECTYPE,VECTYPE,VECTYPE))
				if(N==2):
					print('''	
	out.v[0] = _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[0];''')
				if(N==3):
					print('''	
	out.v[0] =  _a->v[1]*_b->v[2] - _a->v[2]*_b->v[1];
	out.v[1] =-(_a->v[0]*_b->v[2] - _a->v[2]*_b->v[0]);
	out.v[2] =  _a->v[0]*_b->v[1] - _a->v[1]*_b->v[0];
	_a->v[0] = out.v[0];
	_a->v[1] = out.v[1];
	_a->v[2] = out.v[2]; ''')

				print('}')

				commbreak()


			if( (N==3) or (N==2)):
				''' // This is a giant comment if you're not apython person. algorithm using other thigns. inlined it because the includes
				// got something horrid
						/*
						/* [sx 0 0; 0 sy 0; 0 0 1] */
						/* [cos(a)  sin(a)  0; -sin(a) cos(a) 0; 0 0 1] */
						/* T are translations */
						SST_Vec3%s X;
						SST_Mat33%s T; 
						SST_Mat33%s S;
						SST_Mat33%s R;

						X.x = _a->x;
						X.y = _a->y;
						X.z = 1.0f;

						SST_Math_Mat33%sCreateIdentity(&T);
						SST_Math_Mat33%sCreateTranslation(&S,_about->x,_about->y);
						SST_Math_Mat33%sCreateEulerZ(&R,_theta);
						SST_Math_Mat33%sMultiplyMatrixLocal(&S,&T);
						SST_Math_Mat33%sMultiplyMatrixLocal(&R,&T);
						SST_Math_Mat33%sCreateTranslation(&S,-_about->x,-_about->y);
						SST_Math_Mat33%sMultiplyMatrixLocal(&S,&T);

						/* X' = S^-1 * R * S * X  */
						/* See ApplyTransformations in SST_Transform */
						SST_Math_Mat33%sApplyTransforms(&T,&(&X),1); */
				'''
				#RotateAbout
				print('''void SST_Math_%sRotateAbout(const %s* RESTRICT _a, const %s* RESTRICT _about,%s _theta, %s* RESTRICT _out)\n{
					''' % (function_suffix,VECTYPE,VECTYPE,TYPE,VECTYPE))
				if (N==2):
					print('''
	const %s cosa = %s(_theta);
	const %s sina = %s(_theta);
	_out->x =  cosa * (_a->x-_about->x) + sina * (_a->y-_about->y) + _about->x;
	_out->y = -sina * (_a->x-_about->x) + cosa * (_a->y-_about->y) + _about->y;
					''' % (TYPE, COS[TYPE], TYPE, SIN[TYPE]))
				if (N==3):
					print('''
	%s tmp;
	%s scalar = (%s-%s(_theta)) * SST_Math_%sDot(_about,_a);
	SST_Math_%sScale(_about,scalar,_out);
	SST_Math_%sCross(_about,_a,&tmp);
	SST_Math_%sScaleLocal(&tmp,%s(_theta));
	SST_Math_%sAddLocal(_out,&tmp);
	SST_Math_%sScale(_a,%s(_theta),&tmp);
	SST_Math_%sAddLocal(_out,&tmp);
				''' % (VECTYPE,TYPE,cstyle[TYPE] % (1), COS[TYPE],function_suffix,function_suffix,function_suffix,function_suffix,SIN[TYPE],function_suffix,function_suffix,COS[TYPE],function_suffix))

				print('''}''')

				commbreak()

				#RotateAboutLocal
				print('''void SST_Math_%sRotateAboutLocal(%s* RESTRICT _a, const %s* RESTRICT _about,%s _theta)\n{
	''' % (function_suffix,VECTYPE,VECTYPE,TYPE))
				if (N==2):
					print('''
	%s tmp;
	const %s cosa = %s(_theta);
	const %s sina = %s(_theta);

	_a->x -= _about->x;
	_a->y -= _about->y;

	tmp =  cosa * (_a->x) + sina * (_a->y) + _about->x;
	_a->y = -sina * (_a->x) + cosa * (_a->y) + _about->y;
	_a->x = tmp;
					''' % (TYPE, TYPE, COS[TYPE], TYPE, SIN[TYPE]))

				if (N==3):
					print('''
	int i;
	%s tmp;
	%s tmp2;
	%s scalar = (%s-%s(_theta)) * SST_Math_%sDot(_about,_a);''' % (VECTYPE,VECTYPE,TYPE,cstyle[TYPE] % (1), COS[TYPE],function_suffix))
					print('''			
	SST_Math_%sScale(_about,scalar,&tmp2);
	SST_Math_%sCross(_about,_a,&tmp);
	SST_Math_%sScaleLocal(&tmp,%s(_theta));
	SST_Math_%sAddLocal(&tmp2,&tmp);
	SST_Math_%sScale(_a,%s(_theta),&tmp);
	SST_Math_%sAddLocal(&tmp2,&tmp);

	for(i = 0; i < %s; i++)
		_a->v[i] = tmp2.v[i];

					''' % (function_suffix,function_suffix,function_suffix,SIN[TYPE],function_suffix,function_suffix,COS[TYPE],function_suffix,N))
				print('''}''')

				commbreak()
				#Rotate
				print('''void SST_Math_%sRotate(const %s* RESTRICT _a,%s _theta, %s* RESTRICT _out)\n{
					''' % (function_suffix,VECTYPE,TYPE,VECTYPE))
				if (N==2):
					print('''
	const %s cosa = %s(_theta);
	const %s sina = %s(_theta);
	_out->x =  cosa * (_a->x) + sina * (_a->y);
	_out->y = -sina * (_a->x) + cosa * (_a->y);
					''' % (TYPE, COS[TYPE], TYPE, SIN[TYPE]))
				if (N==3):
					print('''
	%s tmp;
	%s about;
	%s scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0; 
	scalar = (%s-%s(_theta)) * SST_Math_%sDot(&about,_a);
	SST_Math_%sScale(&about,scalar,_out);
	SST_Math_%sCross(&about,_a,&tmp);
	SST_Math_%sScaleLocal(&tmp,%s(_theta));
	SST_Math_%sAddLocal(_out,&tmp);
	SST_Math_%sScale(_a,%s(_theta),&tmp);
	SST_Math_%sAddLocal(_out,&tmp);
				''' % (VECTYPE,VECTYPE,TYPE,cstyle[TYPE] % (1), COS[TYPE],function_suffix,function_suffix,function_suffix,function_suffix,SIN[TYPE],function_suffix,function_suffix,COS[TYPE],function_suffix))
				print('''}''')

				commbreak()

				#RotateLocal
				print('''void SST_Math_%sRotateLocal(%s* RESTRICT _a, %s _theta)\n{
	''' % (function_suffix,VECTYPE,TYPE))
				if (N==2):
					print('''
	const %s cosa = %s(_theta);
	const %s sina = %s(_theta);
	%s tmp;

	tmp =  cosa * (_a->x) + sina * (_a->y);
	_a->y = -sina * (_a->x) + cosa * (_a->y);
	_a->x = tmp;
					''' % (TYPE, COS[TYPE], TYPE, SIN[TYPE], TYPE))

				if (N==3):
					print('''
	int i;
	%s tmp;
	%s tmp2;
	%s about;
	%s scalar;
	about.x = 0.0;
	about.y = 0.0;
	about.z = 0.0;
	scalar = (%s-%s(_theta)) * SST_Math_%sDot(&about,_a);''' % (VECTYPE, VECTYPE, VECTYPE, TYPE,cstyle[TYPE] % (1), COS[TYPE],function_suffix))
					print('''			
	SST_Math_%sScale(&about,scalar,&tmp2);
	SST_Math_%sCross(&about,_a,&tmp);
	SST_Math_%sScaleLocal(&tmp,%s(_theta));
	SST_Math_%sAddLocal(&tmp2,&tmp);
	SST_Math_%sScale(_a,%s(_theta),&tmp);
	SST_Math_%sAddLocal(&tmp2,&tmp);

	for(i = 0; i < %s; i++)
		_a->v[i] = tmp2.v[i];

					''' % (function_suffix,function_suffix,function_suffix,SIN[TYPE],function_suffix,function_suffix,COS[TYPE],function_suffix,N))
				print('''}''')

			#Normalize
			print('''void SST_Math_%sNormalize(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	%s scalar = 1.f/SST_Math_%sMagnitude(_in);
	SST_Math_%sScale(_in,scalar,_out);
}''' % (function_suffix,VECTYPE,VECTYPE,TYPE,function_suffix,function_suffix))

			commbreak()

			#NormalizeLocal
			print('''void SST_Math_%sNormalizeLocal(%s* _inout)\n{
	%s scalar = 1.f/SST_Math_%sMagnitude(_inout);
	SST_Math_%sScaleLocal(_inout,scalar);
}''' % (function_suffix,VECTYPE,TYPE,function_suffix,function_suffix))

			commbreak()
			#RecipSqrt
			print('''void SST_Math_%sRecipSqrt(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
		_out->v[i] = 1/%s(_in->v[i]);
}''' % (function_suffix,VECTYPE,VECTYPE,N,SQRT[TYPE]))

			commbreak()
			#RecipSqrtLocal
			print('''void SST_Math_%sRecipSqrtLocal(%s* RESTRICT _a)\n{
	int i;
	for(i = 0; i < %d; i++)
		_a->v[i] = 1/%s(_a->v[i]);
}''' % (function_suffix,VECTYPE,N,SQRT[TYPE]))

			commbreak()
			#Sqrt
			print('''void SST_Math_%sSqrt(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
		_out->v[i] = %s(_in->v[i]);
}''' % (function_suffix,VECTYPE,VECTYPE,N,SQRT[TYPE]))

			commbreak()
			#SqrtLocal
			print('''void SST_Math_%sSqrtLocal(%s* RESTRICT _a)\n{
	int i;
	for(i = 0; i < %d; i++)
		_a->v[i] = %s(_a->v[i]);
}''' % (function_suffix,VECTYPE,N,SQRT[TYPE]))

			commbreak()
			#Magnitude
			print('''%s SST_Math_%sMagnitude(const %s* RESTRICT _a)\n{
	%s sum = 0;
	int i;
	for(i = 0; i < %d; i++)
		sum += _a->v[i] * _a->v[i];
	return %s(sum);
}''' % (TYPE,function_suffix,VECTYPE,TYPE,N,SQRT[TYPE]))

			commbreak()
		if(TYPE != 'unsigned int'):
			#Abs
			print('''void SST_Math_%sAbs(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
		_out->v[i] = %s(_in->v[i]);
}''' % (function_suffix,VECTYPE,VECTYPE,N,fabs[TYPE]))

			commbreak()
			#AbsLocal
			print('''void SST_Math_%sAbsLocal(%s* RESTRICT _a)\n{
	int i;
	for(i = 0; i < %d; i++)
		_a->v[i] = %s(_a->v[i]);
}''' % (function_suffix,VECTYPE,N,fabs[TYPE]))

			commbreak()
			#Negate
			print('''void SST_Math_%sNegate(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
		_out->v[i] = -(_in->v[i]);
}''' % (function_suffix,VECTYPE,VECTYPE,N))

			commbreak()
			#NegateLocal
			print('''void SST_Math_%sNegateLocal(%s* RESTRICT _a)\n{
	int i;
	for(i = 0; i < %d; i++)
		_a->v[i] = -(_a->v[i]);
}''' % (function_suffix,VECTYPE,N))

			commbreak()
			#Recip
			print('''void SST_Math_%sRecip(const %s* RESTRICT _in, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
		_out->v[i] = 1/(_in->v[i]);
}''' % (function_suffix,VECTYPE,VECTYPE,N))

			commbreak()
			#RecipLocal
			print('''void SST_Math_%sRecipLocal(%s* RESTRICT _a)\n{
	int i;
	for(i = 0; i < %d; i++)
		_a->v[i] = 1/(_a->v[i]);
}''' % (function_suffix,VECTYPE,N))

			commbreak()
		#Dot
		print('''%s SST_Math_%sDot(const %s* RESTRICT _a, const %s* RESTRICT _b)\n{
	%s sum = 0;
	int i;
	for(i = 0; i < %d; i++)
		sum += _a->v[i] * _b->v[i];
	return sum;
}''' % (TYPE,function_suffix,VECTYPE,VECTYPE,TYPE,N))

		commbreak()


		#MagnitudeSquared
		print('''%s SST_Math_%sMagnitudeSquared(const %s* RESTRICT _a)\n{
	%s sum = 0;
	int i;
	for(i = 0; i < %d; i++)
		sum += _a->v[i] * _a->v[i];
	return sum;
}''' % (TYPE,function_suffix,VECTYPE,TYPE,N))

		commbreak()

		print('''void SST_Math_%sProject(const %s* RESTRICT _a, const %s* RESTRICT _b, %s* RESTRICT _out)\n{
	%s scalar = SST_Math_%sDot(_a,_b) / SST_Math_%sDot(_b,_b);
	SST_Math_%sScale(_b, scalar, _out);
}
		''' % (function_suffix,VECTYPE,VECTYPE,VECTYPE,TYPE,function_suffix,function_suffix,function_suffix) )

		commbreak()

		print('''void SST_Math_%sProjectLocal(%s* RESTRICT _a, const %s* RESTRICT _b)\n{
	%s scalar = SST_Math_%sDot(_a,_b) / SST_Math_%sDot(_b,_b);
	SST_Math_%sScale(_b, scalar, _a);
}
		''' % (function_suffix,VECTYPE,VECTYPE,TYPE,function_suffix,function_suffix,function_suffix) )

		commbreak()

		print('''void SST_Math_%sBias(const %s* RESTRICT _a, const %s _bias, %s* RESTRICT _out)\n{
	int i;
	for(i = 0; i < %d; i++)
	_out->v[i] = _a->v[i] + _bias;
}
		''' % (function_suffix,VECTYPE,TYPE,VECTYPE,N) )

		commbreak()

		print('''void SST_Math_%sBiasLocal(%s* RESTRICT _a, const %s _bias)\n{
	int i;
	for(i = 0; i < %d; i++)
	_a->v[i] += _bias;
}
		''' % (function_suffix,VECTYPE,TYPE,N) )

		commbreak()
		'''
		/* Vec3f (3D float Vector) Routines */

		/* f:R3 -> R3 */
		/* f:R3 -> R */
		float SST_Math_Vec3fL1Norm(const SST_Vec3f* a);
		float SST_Math_Vec3fRecipMagnitude(const SST_Vec3f* a);

		'''
# End of SST_VecNT.c section
tab = '    '
def Equals(str1,str2):
    if((TYPE=='int') | (TYPE=='unsigned int')):
        return '('+str1+')==('+str2+')'
    else:
        return '%s((' % fabs[TYPE] + str1+')-('+str2+')) <=100*%s /* yes this is bad */' % (fp_epsilon[TYPE])

def ZUnitTestPair( testname , additional_endchars = ','):
		print('{ "%-45s" , %-45s }' %(testname,testname)+additional_endchars)

# Variable Setup
def VariableSetup(vars = ['x','y','w']):
		if( 'x' in vars ):
				print(tab+'%s x; /* %d vector */' % (VECTYPE,N))
		if( 'y' in vars ):
				print(tab+'%s y; /* %d vector */' % (VECTYPE,N))
		if( 'w' in vars ):
				print(tab+'%s w; /* %d vector */' % (VECTYPE,N))
		if( 'a' in vars ):
				print(tab+'%s a; /* scalar */' % (TYPE))

def resetVecs(vars = ['x','y','w']):
		low = -20
		high = 20
		if(TYPE=='unsigned int'):
				low = 0
				high = 40
		print('/* Resetting test vectors */')
		if( 'x' in vars ):
				x = array(random.randint(low,high,N),dtype=DTYPE[TYPE])
				'''print('/* x')
				print(x.dtype)
				print(x)
				print('*/')'''
				for i in rows:
						print(tab+'x.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (x[i])+';')
		if( 'y' in vars ):
				y = array(random.randint(low,high,N),dtype=DTYPE[TYPE])
				'''print('/* y')
				print(y.dtype)
				print(y)
				print('*/')'''
				for i in rows:
						print(tab+'y.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (y[i])+';')

		if( 'w' in vars ):
				w = zeros((N),dtype=DTYPE[TYPE])
				'''print('/* w')
				print(w.dtype)
				print(w)
				print('*/')'''
				for i in rows:
						print(tab+'w.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (w[i])+';')

		if (('w' in vars) & ('x' in vars) & ('y' in vars)):
				return x,y,w

		if (('x' in vars) & ('y' in vars)):
				return x,y

		if (('x' in vars) & ('w' in vars)):
				return x,w

		if ('x' in vars):
				return x

def resetVecsPositive(vars = ['x','y','w']):
		low =  1
		high = 40
		if(TYPE=='unsigned int'):
				low = 1
				high = 40
		print('/* Resetting test vectors */')
		if( 'x' in vars ):
				x = array(random.randint(low,high,N),dtype=DTYPE[TYPE])
				'''print('/* x')
				print(x.dtype)
				print(x)
				print('*/')'''
				for i in rows:
						print(tab+'x.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (x[i])+';')
		if( 'y' in vars ):
				y = array(random.randint(low,high,N),dtype=DTYPE[TYPE])
				'''print('/* y')
				print(y.dtype)
				print(y)
				print('*/')'''
				for i in rows:
						print(tab+'y.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (y[i])+';')

		if( 'w' in vars ):
				w = zeros((N),dtype=DTYPE[TYPE])
				'''print('/* w')
				print(w.dtype)
				print(w)
				print('*/')'''
				for i in rows:
						print(tab+'w.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (w[i])+';')

		if (('w' in vars) & ('x' in vars) & ('y' in vars)):
				return x,y,w

		if (('x' in vars) & ('y' in vars)):
				return x,y

		if (('x' in vars) & ('w' in vars)):
				return x,w

		if ('x' in vars):
				return x
def project(a,b):
		return b*(dot(a,b)/dot(b,b))
def EndTest():
		print(tab+'return ZTEST_SUCCESS;\n}')

entry = { 0 : 'x' , 1 : 'y' , 2 : 'z' , 3 : 'w' }

#Generate Unit Test code
if(CODE_TYPE == 'unittest'):
		print('#include "ZUnitTest.hpp"')
		print('#include <float.h>')
		print('#include <math.h>')
		print('#include <stdlib.h>')
		print('#include <stdio.h>')
		print('#include <SST/%s.h>' % VECTYPE[0:-1])
		print('\n\n\n')

		unittest_preamble = 'static const char* test'
		print(unittest_preamble+function_call+'Add();')
		print(unittest_preamble+function_call+'AddLocal();')
		print(unittest_preamble+function_call+'Subtract();')
		print(unittest_preamble+function_call+'SubtractLocal();')
		print(unittest_preamble+function_call+'Multiply();')
		print(unittest_preamble+function_call+'MultiplyLocal();')
		print(unittest_preamble+function_call+'Scale();')
		print(unittest_preamble+function_call+'ScaleLocal();')
		print(unittest_preamble+function_call+'Divide();')
		print(unittest_preamble+function_call+'DivideLocal();')
		if((TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Abs();')
				print(unittest_preamble+function_call+'AbsLocal();')
				print(unittest_preamble+function_call+'Negate();')
				print(unittest_preamble+function_call+'NegateLocal();')
				print(unittest_preamble+function_call+'Bias();')
				print(unittest_preamble+function_call+'BiasLocal();')
		if((TYPE!='int') & (TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Recip();')
				print(unittest_preamble+function_call+'RecipLocal();')
				print(unittest_preamble+function_call+'RecipSqrt();')
				print(unittest_preamble+function_call+'RecipSqrtLocal();')
				print(unittest_preamble+function_call+'Sqrt();')
				print(unittest_preamble+function_call+'SqrtLocal();')
				print(unittest_preamble+function_call+'Sqrt();')
				print(unittest_preamble+function_call+'SqrtLocal();')
				if((N==2) | (N==3)):
						print(unittest_preamble+function_call+'Cross();')
						print(unittest_preamble+function_call+'CrossLocal();')
				if(N==3):
						print(unittest_preamble+function_call+'RotateAbout();')
						print(unittest_preamble+function_call+'RotateAboutLocal();')
				print(unittest_preamble+function_call+'Project();')
				print(unittest_preamble+function_call+'ProjectLocal();')
				print(unittest_preamble+function_call+'Magnitude();')
				print(unittest_preamble+function_call+'Normalize();')
				print(unittest_preamble+function_call+'NormalizeLocal();')
		print(unittest_preamble+function_call+'MagnitudeSquared();')
		print(unittest_preamble+function_call+'Dot();')

		print('// List of unit tests ')
		print('ZUnitTest '+function_call+'UnitTests[] = \n{')
		ZUnitTestPair('test'+function_call+'Add')
		ZUnitTestPair('test'+function_call+'AddLocal')
		ZUnitTestPair('test'+function_call+'Subtract')
		ZUnitTestPair('test'+function_call+'SubtractLocal')
		ZUnitTestPair('test'+function_call+'Multiply')
		ZUnitTestPair('test'+function_call+'MultiplyLocal')
		ZUnitTestPair('test'+function_call+'Scale')
		ZUnitTestPair('test'+function_call+'ScaleLocal')
		ZUnitTestPair('test'+function_call+'Divide')
		ZUnitTestPair('test'+function_call+'DivideLocal')
		if((TYPE!='unsigned int')):
				ZUnitTestPair('test'+function_call+'Abs')
				ZUnitTestPair('test'+function_call+'AbsLocal')
				ZUnitTestPair('test'+function_call+'Negate')
				ZUnitTestPair('test'+function_call+'NegateLocal')
				ZUnitTestPair('test'+function_call+'Bias')
				ZUnitTestPair('test'+function_call+'BiasLocal')
		if((TYPE!='int') & (TYPE!='unsigned int')):
				ZUnitTestPair('test'+function_call+'Recip')
				ZUnitTestPair('test'+function_call+'RecipLocal')
				ZUnitTestPair('test'+function_call+'RecipSqrt')
				ZUnitTestPair('test'+function_call+'RecipSqrtLocal')
				ZUnitTestPair('test'+function_call+'Sqrt')
				ZUnitTestPair('test'+function_call+'SqrtLocal')
				ZUnitTestPair('test'+function_call+'Sqrt')
				ZUnitTestPair('test'+function_call+'SqrtLocal')
				ZUnitTestPair('test'+function_call+'Magnitude')
				ZUnitTestPair('test'+function_call+'Normalize')
				ZUnitTestPair('test'+function_call+'NormalizeLocal')
				if((N==2) | (N==3)):
						ZUnitTestPair('test'+function_call+'Cross')
						ZUnitTestPair('test'+function_call+'CrossLocal')
				if(N==3):
						ZUnitTestPair('test'+function_call+'RotateAbout')
						ZUnitTestPair('test'+function_call+'RotateAboutLocal')
				ZUnitTestPair('test'+function_call+'Project')
				ZUnitTestPair('test'+function_call+'ProjectLocal')
		ZUnitTestPair('test'+function_call+'MagnitudeSquared')
		ZUnitTestPair('test'+function_call+'Dot','\n};')
		print('DECLARE_ZTESTBLOCK('+function_call+')')

		commbreak()

		print(unittest_preamble+function_call+'Add()\n{')
		VariableSetup()
		x,y,w = resetVecs()
		print('/*')
		print(x)
		print(y)
		print(x+y)
		print('*/')
		print(tab+function_call+'Add(&x,&y,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]+y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'AddLocal()\n{')
		VariableSetup(['x','y'])
		x,y = resetVecs(['x','y'])
		print('/*')
		print(x)
		print(y)
		print(x+y)
		print('*/')
		print(tab+function_call+'AddLocal(&x,&y); /* for accuracy */')
		for i in rows:
				print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]+y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Subtract()\n{')
		VariableSetup()
		x,y,w = resetVecs()
		print('/*')
		print(x)
		print(y)
		print(x-y)
		print('*/')
		print(tab+function_call+'Subtract(&x,&y,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]-y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'SubtractLocal()\n{')
		VariableSetup(['x','y'])
		x,y = resetVecs(['x','y'])
		print('/*')
		print(x)
		print(y)
		print(x-y)
		print('*/')
		print(tab+function_call+'SubtractLocal(&x,&y); /* for accuracy */')
		for i in rows:
				print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]-y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Multiply()\n{')
		VariableSetup()
		x,y,w = resetVecs()
		print('/*')
		print(x)
		print(y)
		print(x*y)
		print('*/')
		print(tab+function_call+'Multiply(&x,&y,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]*y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'MultiplyLocal()\n{')
		VariableSetup(['x','y'])
		x,y = resetVecs(['x','y'])
		print('/*')
		print(x)
		print(y)
		print(x*y)
		print('*/')
		print(tab+function_call+'MultiplyLocal(&x,&y); /* for accuracy */')
		for i in rows:
				print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i]*y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()
		
		commbreak()
		
		print(unittest_preamble+function_call+'Divide()\n{')
		VariableSetup()
		x,y,w = resetVecsPositive()
		print('/*')
		print(x)
		print(y)
		print(x / y)
		print('*/')
		print(tab+function_call+'Divide(&x,&y,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i] / y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'DivideLocal()\n{')
		VariableSetup(['x','y'])
		x,y = resetVecsPositive(['x','y'])
		print('/*')
		print(x)
		print(y)
		print(x / y)
		print('*/')
		print(tab+function_call+'DivideLocal(&x,&y); /* for accuracy */')
		for i in rows:
				print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (x[i] / y[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Scale()\n{')
		VariableSetup(['x','w','a'])
		x,w = resetVecs(['x','w'])
		print(tab+'a = %s;' % cstyle[TYPE]%(2))
		print('/*')
		print(x)
		print(x*2)
		print('*/')
		print(tab+function_call+'Scale(&x,a,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (2 * x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'ScaleLocal()\n{')
		VariableSetup(['x','a'])
		x = resetVecs(['x'])
		print(tab+'a = %s;' % cstyle[TYPE]%(2))
		print('/*')
		print(x)
		print(2*x)
		print('*/')
		print(tab+function_call+'ScaleLocal(&x,a); /* for accuracy */')
		for i in rows:
				print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (2 * x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

		EndTest()
		
		commbreak()


		if((TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Abs()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecs(['x','w'])
				print('/*')
				print(x)
				print(abs(x))
				print('*/')
				print(tab+function_call+'Abs(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (abs(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'AbsLocal()\n{')
				VariableSetup(['x'])
				x = resetVecs(['x'])
				print('/*')
				print(x)
				print(abs(x))
				print('*/')
				print(tab+function_call+'AbsLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (abs(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Bias()\n{')
				VariableSetup(['x','w','a'])
				x,w = resetVecs(['x','w'])
				a = random.randint(-20,20,1)
				print(tab+'a = %s;' % cstyle[TYPE]%(a))
				print('/*')
				print(x)
				print(x*2)
				print('*/')
				print(tab+function_call+'Bias(&x,a,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (a + x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'BiasLocal()\n{')
				VariableSetup(['x','a'])
				x = resetVecs(['x'])
				a = random.randint(-20,20,1)
				print(tab+'a = %s;' % cstyle[TYPE]%(a))
				print('/*')
				print(x)
				print(2*x)
				print('*/')
				print(tab+function_call+'BiasLocal(&x,a); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (a + x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Negate()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecs(['x','w'])
				print('/*')
				print(x)
				print(-x)
				print('*/')
				print(tab+function_call+'Negate(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (-x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'NegateLocal()\n{')
				VariableSetup(['x'])
				x = resetVecs(['x'])
				print('/*')
				print(x)
				print(-x)
				print('*/')
				print(tab+function_call+'NegateLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (-x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

		if((TYPE!='int') & (TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Sqrt()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecsPositive(['x','w'])
				print('/*')
				print(x)
				print(sqrt(x))
				print('*/')
				print(tab+function_call+'Sqrt(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (sqrt(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'SqrtLocal()\n{')
				VariableSetup(['x'])
				x = resetVecsPositive(['x'])
				print('/*')
				print(x)
				print(sqrt(x))
				print('*/')
				print(tab+function_call+'SqrtLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (sqrt(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'RecipSqrt()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecsPositive(['x','w'])
				print('/*')
				print(x)
				print(1/sqrt(x))
				print('*/')
				print(tab+function_call+'RecipSqrt(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (1/sqrt(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'RecipSqrtLocal()\n{')
				VariableSetup(['x'])
				x = resetVecsPositive(['x'])
				print('/*')
				print(x)
				print(1/sqrt(x))
				print('*/')
				print(tab+function_call+'RecipSqrtLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (1/sqrt(x[i])))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Recip()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecsPositive(['x','w'])
				print('/*')
				print(x)
				print(1/x)
				print('*/')
				print(tab+function_call+'Recip(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (1/x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'RecipLocal()\n{')
				VariableSetup(['x'])
				x = resetVecsPositive(['x'])
				print('/*')
				print(x)
				print(1/sqrt(x))
				print('*/')
				print(tab+function_call+'RecipLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (1/x[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Normalize()\n{')
				VariableSetup(['x','w'])
				x,w = resetVecs(['x','w'])
				print('/*')
				print(x)
				print(x/sqrt(sum(x**2)))
				print('*/')
				print(tab+function_call+'Normalize(&x,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((x/sqrt(sum(x**2)))[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'NormalizeLocal()\n{')
				VariableSetup(['x'])
				x = resetVecs(['x'])
				print('/*')
				print(x)
				print(x/sqrt(sum(x**2)))
				print('*/')
				print(tab+function_call+'NormalizeLocal(&x); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((x/sqrt(sum(x**2)))[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Project()\n{')
				VariableSetup(['x','y','w'])
				x,y,w = resetVecs(['x','y','w'])
				w = project(x,y) 
				print('/*')
				print(x)
				print(y)
				print( w )
				print('*/')
				print(tab+function_call+'Project(&x,&y,&w);')
				for i in rows:
						print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()

				commbreak()

				print(unittest_preamble+function_call+'ProjectLocal()\n{')
				VariableSetup(['x','y','w'])
				x,y,w = resetVecs(['x','y','w'])
				w = project(x,y) 
				print('/*')
				print(x)
				print(y)
				print(w)
				print('*/')
				print(tab+function_call+'ProjectLocal(&x,&y); /* for accuracy */')
				for i in rows:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

				EndTest()
				
				commbreak()

				if(N==2):
						print(unittest_preamble+function_call+'Cross()\n{')
						VariableSetup(['x','y','w'])
						x,y,w = resetVecs(['x','y','w'])
						w = cross(x,y)
						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'Cross(&x,&y,&w);')
						for i in rows:
								print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()

						commbreak()

						print(unittest_preamble+function_call+'CrossLocal()\n{')
						VariableSetup(['x','y'])
						x,y = resetVecs(['x','y'])
						w = cross(x,y)
						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'CrossLocal(&x,&y); /* for accuracy */')
						for i in rows:
								print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()

				if(N==3):
						print(unittest_preamble+function_call+'Cross()\n{')
						VariableSetup(['x','y','w'])
						x,y,w = resetVecs(['x','y','w'])
						w = cross(x,y)
						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'Cross(&x,&y,&w);')
						for i in rows:
								print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()

						commbreak()

						print(unittest_preamble+function_call+'CrossLocal()\n{')
						VariableSetup(['x','y'])
						x,y = resetVecs(['x','y'])
						w = cross(x,y)
						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'CrossLocal(&x,&y); /* for accuracy */')
						for i in rows:
								print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()

						commbreak()

						print(unittest_preamble+function_call+'RotateAbout()\n{')
						VariableSetup(['x','y','w'])
						x = array([1,0,0],dtype=DTYPE[TYPE])
						y = array([0,0,1],dtype=DTYPE[TYPE])
						w = array([0,1,0],dtype=DTYPE[TYPE])
						for i in rows:
								print(tab+('x.v[%d] = %s;' % (i,cstyle[TYPE])) % (x[i]))

						for i in rows:
								print(tab+('y.v[%d] = %s;' % (i,cstyle[TYPE])) % (y[i]))

						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'RotateAbout(&x,&y,%s,&w);' % (cstyle[TYPE] % (pi/2)) )
						for i in rows:
								print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()

						commbreak()

						print(unittest_preamble+function_call+'RotateAboutLocal()\n{')
						VariableSetup(['x','y'])
						x = array([1,0,0],dtype=DTYPE[TYPE])
						y = array([0,0,1],dtype=DTYPE[TYPE])
						w = array([0,1,0],dtype=DTYPE[TYPE])
						for i in rows:
								print(tab+('x.v[%d] = %s;' % (i,cstyle[TYPE])) % (x[i]))

						for i in rows:
								print(tab+('y.v[%d] = %s;' % (i,cstyle[TYPE])) % (y[i]))

						print('/*')
						print(x)
						print(y)
						print(w)
						print('*/')
						print(tab+function_call+'RotateAboutLocal(&x,&y,%s);' % (cstyle[TYPE] % (pi/2)) )
						for i in rows:
								print(tab+'TASSERT('+Equals('x.v[%d]' % (i), ('%s' % cstyle[TYPE]) % ((w)[i]))+',"Entry _%s failed!"' % (entry[i]) + ');')

						EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Magnitude()\n{')
				VariableSetup(['x','a'])
				x = resetVecs(['x'])
				print('/*')
				print(x)
				print(sqrt(sum(x**2)))
				print('*/')
				print(tab+'a = '+function_call+'Magnitude(&x);')
				print(tab+'TASSERT('+Equals('a' , ('%s' % cstyle[TYPE]) % ((sqrt(sum(x**2)))))+',"Magnitude failed!");')

				EndTest()
				
				commbreak()

		print(unittest_preamble+function_call+'MagnitudeSquared()\n{')
		VariableSetup(['x','a'])
		x = resetVecs(['x'])
		print('/*')
		print(x)
		print(sum(x**2))
		print('*/')
		print(tab+'a = '+function_call+'MagnitudeSquared(&x);')
		print(tab+'TASSERT('+Equals('a' , ('%s' % cstyle[TYPE]) % (((sum(x**2)))))+',"MagnitudeSquared failed!");')

		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Dot()\n{')
		VariableSetup(['x','y','a'])
		x,y = resetVecs(['x','y'])
		a = dot(x,y)
		print('/*')
		print(x)
		print(dot(x,y))
		print('*/')
		print(tab+'a = '+function_call+'Dot(&x,&y);')
		print(tab+'TASSERT('+Equals('a' , ('%s' % cstyle[TYPE]) % (a))+',"Dot failed!");')

		EndTest()
		
		commbreak()
