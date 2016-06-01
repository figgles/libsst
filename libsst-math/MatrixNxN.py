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

N  = int(sys.argv[1])
N2 = N * N
TYPE = sys.argv[2]


tab = 4*' '
COMMBREAK = '/******************************************************************************/'



#C function table
fabs = {'double' : 'fabs', 'float' : 'fabsf', 'int' : 'abs', 'unsigned int' : ''}
cstyle = {'double' : '%24.15lf', 'float' : '%ff', 'int' : '%d', 'unsigned int' : '%u' }
fp_epsilon = {'double' : 'DBL_EPSILON' , 'float' : 'FLT_EPSILON' , 'int' : '0' , 'unsigned int' : '0'}
size_t = {'double' : 64, 'float' : 32, 'int' : 32, 'unsigned int' : 32}
DTYPE = {'double' : float64 , 'float' : float32 , 'int' : int32 , 'unsigned int' : uint32}

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
										print('fprintf(stdout,"' + name + '[%d][%d]' % (i,j) + '='+cstyle[TYPE]+'",' + name  + '.v[%d]' % (i+N*j) + ');')
								print('fprintf(stdout,"\");')
				else:
						print('fprintf(stdout,"'+name+'\");')
						for j in r_[0:M]:
								for i in r_[0:N]:
										print('fprintf(stdout,"'+cstyle[TYPE]+' ",' + name  + '.v[%d]' % (i+N*j) + ');')
								print('fprintf(stdout,"\");')
		else:
				'''N+1 #it gets angry if this isn't here	'''

def A_op_B(op):
    for i in range(N2):
        print('\t _A->v[%d] %s _B->v[%d];' % (i, op, i))

def A_op_K(op):
    for i in range(N2):
        print('\t _A->v[%d] %s k;' % (i, op))

def A_op_B_eq_Out(op):
    for i in range(N2):
        print('\t _out->v[%d] = _A->v[%d] %s _B->v[%d];' % (i, i, op, i))

def A_op_K_eq_Out(op):
    for i in range(N2):
        print('\t _out->v[%d] = _A->v[%d] %s k;' % (i, i, op))

def commbreak():
    print('\n' + COMMBREAK + '\n');

# Generates: out = A op B
def ThreeMatrixFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name+'(const %s* RESTRICT _A, const %s* RESTRICT _B, %s* RESTRICT _out)\n{' % (MTXTYPE, MTXTYPE, MTXTYPE))

    #Alignment assumptions
    print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_B,16);\n\tSST_ASSUME_ALIGNED(_out,16);\n')

    #Generate operation
    A_op_B_eq_Out(op)

    print("}");
    commbreak();

# Generates: A op= B
def TwoMatrixFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name+'(%s* RESTRICT _A, const %s* RESTRICT _B)\n{' % (MTXTYPE, MTXTYPE))

    #Alignment assumptions
    print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_B,16);\n')

    #Generate operation
    A_op_B(op)

    print("}");
    commbreak();

# Generates: A op= K
def MatrixScalarFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name +'(%s* RESTRICT _A, const %s k)\n{' % (MTXTYPE, TYPE))

    #Alignment assumptions
    print('\tSST_ASSUME_ALIGNED(_A,16);\n')

    #Generate operation
    A_op_K(op)

    print("}");
    commbreak();

# Generates: out = A op K
def TwoMatrixScalarFunc(Name, op):
    # Function header
    print(function_preamble+function_suffix+Name+'(const %s* RESTRICT _A, const %s k,  %s* RESTRICT _out)\n{' % (MTXTYPE, TYPE, MTXTYPE))

    #Alignment assumptions
    print('\tSST_ASSUME_ALIGNED(_A,16);\n\tSST_ASSUME_ALIGNED(_out,16);\n')

    #Generate operation
    A_op_K_eq_Out(op)

    print("}");
    commbreak();

rows = r_[0:N]
columns = r_[0:N]

# FLAGS for use in this generator
PIVOTING_FLAG = True
SINGULAR_FLAG = False
TIMING_CHECK = False
# End of FLAGS

function_preamble = 'void SST_Math_'
function_suffix = 'Mat%d%d%s' % (N,N,TYPE[0])
function_call = 'SST_Math_Mat%d%d%s' % (N,N,TYPE[0])
MTXTYPE = 'SST_Mat%d%d%s' % (N,N,TYPE[0])
VTXTYPE = 'SST_Vec%d%s' % (N,TYPE[0])

if(DEBUG_PRINT != True):
		# HEADER
		print('/*')
		print('\tAUTOMATICALLY GENERATED FILE - DO NOT EDIT!')
		print('\tPlease change MatrixNxN.py and re-run it')
		print('*/')
		print('/* Generated with n = %d, TYPE = %s */\n' % (N,TYPE))

		print('#include <float.h>')
		print('#include <pstdbool.h>')
		print('#include <stdio.h>')
		print('#include <math.h> /* for sqrt functions */')
		print('#include <stdlib.h> /* for the abs/labs functions */')
		print('#include <SST/SST_Build.h>\n')
		print('#include <SST/%s.h>' % MTXTYPE[0:-1])
		print('#include <SST/%s.h>' % VTXTYPE[0:-1])

		#Add()
		ThreeMatrixFunc("Add", "+")

		#AddLocal()
		TwoMatrixFunc("AddLocal", "+=")

		#Sub()
		ThreeMatrixFunc("Subtract", "-")

		#SubLocal()
		TwoMatrixFunc("SubtractLocal", "-=")

		#MultElem()
		ThreeMatrixFunc("MultiplyElementwise", "*")

		#MultElemLocal()
		TwoMatrixFunc("MultiplyElementwiseLocal", "*=")

		#MultScalar()
		TwoMatrixScalarFunc("MultiplyScalar", "*")

		#MultScalarLocal()
		MatrixScalarFunc("MultiplyScalarLocal", "*=")

		function_preamble = function_preamble+function_suffix
		print('\n'+function_preamble+'MultiplyMatrix(const %s* _A, const %s*  RESTRICT _B, %s*  RESTRICT _out)\n{' % (MTXTYPE,MTXTYPE,MTXTYPE) )
		print('SST_ASSUME_ALIGNED(_A,16);\nSST_ASSUME_ALIGNED(_B,16);\nSST_ASSUME_ALIGNED(_out,16);')
		for i in rows:
			for j in columns:
				for k in r_[0:N]:
					if(k==0):
						outstr ='_out->v[%2d] = _A->v[%2d]*_B->v[%2d]' % (i+N*j,i+N*k,k+N*j)
					else:
						outstr +='+_A->v[%2d]*_B->v[%2d]' % (i+N*k,k+N*j)
				print(outstr+';')

		print('}\n'+function_preamble+'MultiplyMatrixLocal(%s*  RESTRICT _A, const %s*  RESTRICT _B)\n{' % (MTXTYPE,MTXTYPE) )
		print('\t%s tmp[%d];' % (TYPE,N*N))
		print('\tSST_ASSUME_ALIGNED(_A,16);\nSST_ASSUME_ALIGNED(_B,16);')
		for i in rows:
			for j in columns:
				for k in r_[0:N]:
					if(k==0):
						outstr ='tmp[%2d] = _A->v[%2d]*_B->v[%2d]' % (i+N*j,i+N*k,k+N*j)
					else:
						outstr +='+_A->v[%2d]*_B->v[%2d]' % (i+N*k,k+N*j)
				print(outstr+';')
			for j in columns:
				print('_A->v[%d] = tmp[%d];' % (i+N*j,i+N*j))
			print('\n')

		print('}\n'+function_preamble+'MultiplyVector(const %s*  RESTRICT _A, const %s*  RESTRICT _v, %s*  RESTRICT _out)\n{' % (MTXTYPE,VTXTYPE,VTXTYPE) )
		print('SST_ASSUME_ALIGNED(_A,16);\nSST_ASSUME_ALIGNED(_v,16);\nSST_ASSUME_ALIGNED(_out,16);')
		for i in r_[0:N]:
			outstr='_out->v[%2d] = _A->v[%2d]*_v->v[0]' % (i,i)
			for j in r_[1:N]:
				outstr+='+_A->v[%2d]*_v->v[%d]' % (i+N*j,j)
			outstr+=';'
			print(outstr)

		print('}\n'+function_preamble+'MultiplyVectorLocal(const %s*  RESTRICT _A, %s*  RESTRICT _v)\n{' % (MTXTYPE,VTXTYPE) )
		print('%s tmp[%d];' % (TYPE,N))
		print('SST_ASSUME_ALIGNED(_A,16);\nSST_ASSUME_ALIGNED(_v,16);')
		for i in r_[0:N]:
			outstr='tmp[%2d] = _A->v[%2d]*_v->v[0]' % (i,i)
			for j in r_[1:N]:
				outstr+='+_A->v[%2d]*_v->v[%d]' % (i+N*j,j)
			outstr+=';'
			print(outstr)
		for i in r_[0:N]:
			print('_v->v[%d] = tmp[%d];' % (i,i));
		print('}\n'+function_preamble+'Transpose(const %s*  RESTRICT _A, %s*  RESTRICT _out)\n{' % (MTXTYPE,MTXTYPE) )
		print('SST_ASSUME_ALIGNED(_A,16);\nSST_ASSUME_ALIGNED(_out,16);')
		for i in r_[0:N]:
			for j in r_[0:N]:
				print('_out->v[%2d] = _A->v[%2d];' % (j+N*i,i+N*j))

		print('}\n'+function_preamble+'TransposeLocal(%s*  RESTRICT _A)\n{' % (MTXTYPE) )
		print('%s tmp[%d];' % (TYPE,N))
		print('SST_ASSUME_ALIGNED(_A,16);')
		for i in r_[0:N]:
			for j in r_[i:N]:
				if(i!=j):
					print('tmp[%d] = _A->v[%2d];' % (j,i+N*j))
					print('_A->v[%2d] = _A->v[%2d];' % (i+N*j,j+N*i))
					print('_A->v[%2d] = tmp[%d];' % (j+N*i,j))

		if((TYPE != 'unsigned int')):
				print('}\n'+re.sub(r"void",'bool',function_preamble)+'CheckOrthonormal(const %s* _A)\n{' % (MTXTYPE) )
				'''trans(M)*M = I if its Orthonormal'''
				outstr  ='((%s(' % fabs[TYPE]+ ('%s' % cstyle[TYPE]) % (N)
				outstr2 ='((%s(' % fabs[TYPE]
				outstr3 ='const %s diag =' % TYPE
				outstr4 ='const %s odiag =' % TYPE
				for i in rows:
					for j in columns:
						for k in r_[0:N]:
							if(i==j):
								outstr3  +=' -_A->v[%d]*_A->v[%d]' % (k+N*i,k+N*j)
							else:
								outstr4 +='+ _A->v[%d]*_A->v[%d]' % (k+N*i,k+N*j)

				outstr3+=';'
				outstr4=re.sub("=\+",'=',outstr4)+';'
				outstr+='+diag)) <= 100*%s) &' % fp_epsilon[TYPE]
				outstr2+='odiag)) <= 100*%s);' % fp_epsilon[TYPE]
				print(outstr3)
				print(outstr4)
				#print('fprintf(stdout,"diag = '+('%s' % cstyle[TYPE])+'\\n",%d+diag);' % (N))
				#print('fprintf(stdout,"odiag = '+('%s' % cstyle[TYPE])+'\\n",odiag);')
				print('SST_ASSUME_ALIGNED(_A,16);')
				print('return ')
				print(outstr)
				print(outstr2)
				print('\n')

				print('}\n'+re.sub(r"void",TYPE,function_preamble)+'Determinant(const %s* _A)\n{' % (MTXTYPE) )
				# we're just going to use the first row... though I have an idea for an algo
				# that might actually make the determinant feasibly useful for later calcs.
				# A couple properties to remember:
				#        det(A) = det(LU) = det(L)det(U) = det(U) | det(L) ~ O(n) operations
				#                         (L or U will have 1s on the diagonal)
				#
				if(N==2):
					print('\tconst %s result = _A->v[0]*_A->v[3]-_A->v[1]*_A->v[2];' % (TYPE))
					print('\tSST_ASSUME_ALIGNED(_A,16);')
					print('\treturn result;')
				if(N==3):
					print('\tconst %s result = _A->v[0]*(_A->v[4]*_A->v[8]-_A->v[5]*_A->v[7])-_A->v[1]*(_A->v[3]*_A->v[8]-_A->v[6]*_A->v[5])+_A->v[2]*(_A->v[3]*_A->v[7]-_A->v[6]*_A->v[4]);' % (TYPE))
					print('\tSST_ASSUME_ALIGNED(_A,16);')
					print('\treturn result;')
					# [[0  1  2   3]
					#  [4  5  6   7]
					#  [8  9  10 11]
					#  [12 13 14 15]]
					#
					# [[0  4  8  12]
					#  [1  5  9  13]
					#  [2  6  10 14]
					#  [3  7  11 15]]
					#
				if(N==4):
					print('\tconst %s a10151411 = _A->v[10]*_A->v[15]-_A->v[11]*_A->v[14];' % TYPE)
					print('\tconst %s a9151311  =  _A->v[6]*_A->v[15]-_A->v[7]*_A->v[14];' % TYPE)
					print('\tconst %s a9141310  =  _A->v[6]*_A->v[11]-_A->v[7]*_A->v[10];' % TYPE)
					print('\tconst %s a8151112  =  _A->v[2]*_A->v[15]-_A->v[14]*_A->v[3];' % TYPE)
					print('\tconst %s a8141210  =  _A->v[2]*_A->v[11]-_A->v[3]*_A->v[10];' % TYPE)
					print('\tconst %s a813129   =  _A->v[2]*_A->v[7]-_A->v[3]*_A->v[6];'  % TYPE)
					print('\tconst %s result = _A->v[0]*(_A->v[5]*a10151411-_A->v[9]*a9151311+_A->v[13]*a9141310)' % (TYPE)
							+'-_A->v[4]*(_A->v[1]*a10151411-_A->v[9]*a8151112+_A->v[13]*a8141210)'
							+'+_A->v[8]*(_A->v[1]*a9151311 -_A->v[5]*a8151112+_A->v[13]*a813129)'
							+'-_A->v[12]*(_A->v[1]*a9141310 -_A->v[5]*a8141210+_A->v[9]*a813129);' )
					print('\tSST_ASSUME_ALIGNED(_A,16);')
					print('\treturn result;')


		if((TYPE != 'int') & (TYPE != 'unsigned int')):
				print('}\n'+function_preamble+'Invert(const %s*  RESTRICT _A, %s*  RESTRICT _out)\n{' % (MTXTYPE,MTXTYPE) )
				if(N==2):
					print('/* Analytical Invert for 2x2 */')
					print('const %s aij = (%s) / (_A->v[0]*_A->v[3]-_A->v[1]*_A->v[2]);' % (TYPE,cstyle[TYPE] % (1)))
					print('SST_ASSUME_ALIGNED(_A,16);')
					print('_out->v[0] =  aij*_A->v[3];\n_out->v[1] = -aij*_A->v[1];\n_out->v[2] = -aij*_A->v[2];\n_out->v[3] =  aij*_A->v[0];\n')
				else:
					# Gauss elimination
						print('/* Gaussian Elimination */')
						print('#define _A(i,j) _A->v[i+%d*j]' % (N))
						print('#define _out(i,j) _out->v[i+%d*j]' % (N))
						print('#define Pinv(i,j) Pinv.v[i+%d*j]' % (N))
						print('%s aij;' % TYPE)
						print('%s  norm_aij;' % (TYPE))
						print('%s Pinv;' % (MTXTYPE))
						print('SST_ASSUME_ALIGNED(_A,16);')
						print('/* Set _out to the identity */')

						for j in r_[0:N]:
								for i in r_[0:N]:
									print('_out(%d,%d) = ' % (i,j) + (cstyle[TYPE] % (kronecker(i,j))) + ';')

						print("/* Set _Pinv to _A so we don't overwrite it */")
						for i in r_[0:N*N]:
								print('Pinv.v[%d] = _A->v[%d];' % (i,i))

						cprintf('_out',N,N,False)
						cprintf('Pinv',N,N,False)

						print('/* Put in Reduced Row Echelon form */')
						print('/* Note that we can set the entry to 0, or just calculate it. \n The latter will be helpful when recognizing that these are all simple vector moves */')
						for i in r_[0:N]:
								for k in r_[i+1:N]:
									print('/* Sort if need be */')
									print('aij = -Pinv(%d,%d) / Pinv(%d,%d) ;' % (k,i,i,i))
									for j in r_[0:N]:
										print('Pinv(%d,%d) += aij*Pinv(%d,%d) ;' % (k,j,i,j))
									cprintf('Pinv',N,N,False)
									for j in r_[0:N]:
										print('_out(%d,%d) += aij*_out(%d,%d) ;' % (k,j,i,j))
									cprintf('_out',N,N,False)

						print('/* Backsubstitution */')
						for k in r_[(N-1):-1:-1]:
								print('norm_aij = %s / Pinv(%d,%d) ;' % ((cstyle[TYPE] % (1)),k,k))
								print('Pinv(%d,%d) = %s;' % (k,k,(cstyle[TYPE] % (1))))
								for l in r_[0:N]:
										print('_out(%d,%d) *= norm_aij;' % (k,l))
								for i in r_[0:k]:
										print('aij = -Pinv(%d,%d);' % (i,k))
										for j in r_[0:N]:
												print('Pinv(%d,%d) += aij*Pinv(%d,%d);' % (i,j,k,j))
												cprintf('Pinv',N,N,False)
										for j in r_[0:N]:
												print('_out(%d,%d) += aij*_out(%d,%d);' % (i,j,k,j))
												cprintf('_out',N,N,False)
						print('#undef _A')
						print('#undef _out')
						print('#undef Pinv')


				print('}\n'+function_preamble+'InvertLocal(%s* RESTRICT _A)\n{' % (MTXTYPE) )
				if(N==2):
						print('/* Analytical Invert for 2x2 */')
						print('const %s aij = (%s) / (_A->v[0]*_A->v[3]-_A->v[1]*_A->v[2]);' % (TYPE,cstyle[TYPE] % (1)))
						print('const %s tmp = _A->v[0];' % (TYPE))
						print('SST_ASSUME_ALIGNED(_A,16);')
						print('_A->v[0] =  aij*_A->v[3];\n_A->v[1] *= -aij;\n_A->v[2] *= -aij;\n_A->v[3] =  aij*tmp;\n')
				else:
					# Gauss elimination
						print('/* Gaussian Elimination */')
						print('#define _A(i,j) _A->v[i+%d*j]' % (N))
						print('#define out(i,j) out->v[i+%d*j]' % (N))
						print('#define Pinv(i,j) Pinv.v[i+%d*j]' % (N))
						print('%s aij;' % TYPE)
						print('%s  norm_aij;' % (TYPE))
						print('%s Pinv;' % (MTXTYPE))
						print('SST_ASSUME_ALIGNED(_A,16);')
						print('/* Set _out to the identity */')

						print("/* Set _Pinv to _A so we don't overwrite it */")
						for i in r_[0:N*N]:
								print('Pinv.v[%d] = _A->v[%d];' % (i,i))

						for j in r_[0:N]:
								for i in r_[0:N]:
									print('_A(%d,%d) = ' % (i,j) + (cstyle[TYPE] % (kronecker(i,j))) + ';')


						cprintf('_A',N,N,False)
						cprintf('Pinv',N,N,False)

						print('/* Put in Reduced Row Echelon form */')
						print('/* Note that we can set the entry to 0, or just calculate it. \n The latter will be helpful when recognizing that these are all simple vector moves */')
						for i in r_[0:N]:
								for k in r_[i+1:N]:
									print('/* Sort if need be */')
									print('aij = -Pinv(%d,%d) / Pinv(%d,%d) ;' % (k,i,i,i))
									for j in r_[0:N]:
										print('Pinv(%d,%d) += aij*Pinv(%d,%d) ;' % (k,j,i,j))
									cprintf('Pinv',N,N,False)
									for j in r_[0:N]:
										print('_A(%d,%d) += aij*_A(%d,%d) ;' % (k,j,i,j))
									cprintf('_A',N,N,False)

						print('/* Backsubstitution */')
						for k in r_[(N-1):-1:-1]:
								print('norm_aij = %s / Pinv(%d,%d) ;' % ((cstyle[TYPE] % (1)),k,k))
								print('Pinv(%d,%d) = %s;' % (k,k,(cstyle[TYPE] % (1))))
								for l in r_[0:N]:
										print('_A(%d,%d) *= norm_aij;' % (k,l))
								for i in r_[0:k]:
										print('aij = -Pinv.v[%d];' % (i+N*k))
										for j in r_[0:N]:
												print('Pinv.v[%d] += aij*Pinv.v[%d];' % (i+N*j,k+N*j))
												cprintf('Pinv',N,N,False)
										for j in r_[0:N]:
												print('_A->v[%d] += aij*_A->v[%d];' % (i+N*j,k+N*j))
												cprintf('_A',N,N,False)



				print('}\n'+function_preamble+'CreateLU(const %s* RESTRICT _A, %s* RESTRICT _LU)\n{' % (MTXTYPE,MTXTYPE) )
				print('#define _A(i,j) _A->v[i+%d*j]' % (N))
				print('#define _LU(i,j) _LU->v[i+%d*j]' % (N))
				print(tab+'int i,j,k;')
				print(tab+TYPE+' sum;')
				print('SST_ASSUME_ALIGNED(_A,16);')
				print('SST_ASSUME_ALIGNED(_LU,16);')
				for i in rows:
						print(tab+'_LU(%d,0) = _A(%d,0);' % (i,i))
						for j in r_[i+1:N]:
								print(tab+'_LU(%d,%d) = 0;' % (i,j))

				for i in rows:
						print(tab+'/* _U(%d,%d) = ' % (i,i) + (('%s; */' % cstyle[TYPE]) % (1)) )

				for i in r_[1:N]:
						print(tab+'_LU(0,%d) = _A(0,%d) / _LU(0,0);' % (i,i))

				print((tab+'for(i=1; i < %d; i++) {\n') %(N))
				print(2*tab+'for(j=1; j <= i; j++) {')
				print(3*tab+'sum = '+('%s;' % cstyle[TYPE]) % (0))
				print(3*tab+'for(k=0; k < j; k++)')
				print(4*tab+'sum += -_LU(i,k)*_LU(k,j);')
				print(3*tab+'_LU(i,j) = _A(i,j) + sum;\n%s}' % (2*tab))
				print(2*tab+'for(j=i+1; j < %d; j++) {' % (N))
				print(3*tab+'sum = '+('%s;' % cstyle[TYPE]) % (0))
				print(3*tab+'for(k=0; k < i; k++)')
				print(4*tab+'sum += -_LU(i,k)*_LU(k,j);')
				print(3*tab+'_LU(i,j) = (_A(i,j) + sum) / _LU(i,i);\n%s}' % (2*tab))
				print(tab+'}')
				print('#undef _A')
				print('#undef _LU')
				
				print('}\n'+function_preamble+'ApplyLUMat(const %s* _LU, const %s* _A, %s* _out)\n{\n ' % (MTXTYPE,MTXTYPE,MTXTYPE) )
				print('#define _LU(i,j) _LU->v[i+%d*j]' % (N))
				print('#define _A(i,j) _A->v[i+%d*j]' % (N))
				print('#define _out(i,j) _out->v[i+%d*j]' % (N))

				print(tab+'int i, j, col;')
				print(tab+'%s sum;' % TYPE);
				print('SST_ASSUME_ALIGNED(_A,16);')
				print('SST_ASSUME_ALIGNED(_LU,16);')
				print('SST_ASSUME_ALIGNED(_out,16);')
				print(tab+'for(col = 0; col < %d; col++) {' % (N))
				for k in r_[0:N]:
						print(tab+tab+'_out(%d,col) = _A(%d,col);' % (k,k) )
				print(tab+tab+'/* Forward Substitution for Ly = v */')
				print(tab+tab+'for(i = 0; i < %d; i++) {' % (N))
				print(2*tab+tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+tab+'for(j = 0; j < i; j++)' )
				print(3*tab+tab+'sum += _LU(i,j) * _out(j,col);') 
				print(2*tab+tab+'_out(i,col) = (_out(i,col) - sum) / _LU(i,i) ;')
				print(tab+tab + '}' )
				print('/* Backwards Substitution for Uw = y */')
				print(tab+tab+'for(i = %d; i >=0; i--) {' % (N-1))
				print(2*tab+tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+tab+'for(j = i+1; j < %d; j++)' %(N) )
				print(3*tab+tab+'sum += _LU(i,j) * _out(j,col);') 
				print(2*tab+tab+'_out(i,col) = (_out(i,col) - sum) ; /* divide by U(i,i)=1 */')
				print(tab+tab + '}' )
				print(tab + '}' )

				print('#undef _LU /* (i,j) _LU->v[i+%d*j] */' % (N))
				print('#undef _A /* (i,j) _A->v[i+%d*j] */' % (N))
				print('#undef _out /* (i,j) _out->v[i+%d*j] */' % (N))

				print('}\n'+function_preamble+'ApplyLUMatLocal(const %s* _LU,%s* _A)\n{\n ' % (MTXTYPE,MTXTYPE) )
				print('#define _LU(i,j) _LU->v[i+%d*j]' % (N))
				print('#define _A(i,j)  _A->v[i+%d*j]' % (N))
				print(tab+'int i, j, col;')
				print(tab+'%s sum;' % TYPE);
				print(tab+'for(col = 0; col < %d; col++) {' % (N))
				print(tab+tab+'/* Forward Substitution for Ly = v */')
				print(tab+tab+'for(i = 0; i < %d; i++) {' % (N))
				print(2*tab+tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+tab+'for(j = 0; j < i; j++)' )
				print(3*tab+tab+'sum += _LU(i,j) * _A(j,col);') 
				print(2*tab+tab+'_A(i,col) = (_A(i,col) - sum) / _LU(i,i) ;')
				print(tab+tab + '}' )
				print('/* Backwards Substitution for Uw = y */')
				print(tab+tab+'for(i = %d; i >=0; i--) {' % (N-1))
				print(2*tab+tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+tab+'for(j = i+1; j < %d; j++)' %(N) )
				print(3*tab+tab+'sum += _LU(i,j) * _A(j,col);') 
				print(2*tab+tab+'_A(i,col) = (_A(i,col) - sum) ; /* U is 1s along the diagonal */')
				print(tab+tab + '}' )
				print(tab + '}' )

				print('}\n'+function_preamble+'ApplyLUVec(const %s* _LU, const %s* _v,%s* _w)\n{\n ' % (MTXTYPE,VTXTYPE,VTXTYPE) )
				print('#define _LU(i,j) _LU->v[i+%d*j]' % (N))
				print(tab+'int i, j;')
				print(tab+'%s sum;' % TYPE);
				for k in r_[0:N]:
						print(tab+'_w->v[%d] = _v->v[%d];' % (k,k) )
				print(tab+'/* Forward Substitution for Ly = v */')
				print(tab+'for(i = 0; i < %d; i++) {' % (N))
				print(2*tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+'for(j = 0; j < i; j++)' )
				print(3*tab+'sum += _LU(i,j) * _w->v[j];') 
				print(2*tab+'_w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;')
				print(tab + '}' )
				print('/* Backwards Substitution for Uw = y */')
				print(tab+'for(i = %d; i >= 0; i--) {' % (N-1))
				print(2*tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+'for(j = i+1; j < %d; j++)' %(N) )
				print(3*tab+'sum += _LU(i,j) * _w->v[j];') 
				print(2*tab+'/*_w->v[i] = (_w->v[i] - sum) ;*/')
				print(2*tab+'_w->v[i] = (_w->v[i] - sum) ;')
				print(tab + '}' )
				print('#undef _LU /* (i,j) _LU->v[i+%d*j] */' % (N))

				print('}\n'+function_preamble+'ApplyLUVecLocal(const %s* _LU,%s* _w)\n{\n ' % (MTXTYPE,VTXTYPE) )
				print('#define _LU(i,j) _LU->v[i+%d*j]' % (N))
				print(tab+'int i, j;')
				print(tab+'%s sum;' % TYPE);
				print(tab+'/* Forward Substitution for Ly = v */')
				print(tab+'for(i = 0; i < %d; i++) {' % (N))
				print(2*tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+'for(j = 0; j < i; j++)' )
				print(3*tab+'sum += _LU(i,j) * _w->v[j];') 
				print(2*tab+'_w->v[i] = (_w->v[i] - sum) / _LU(i,i) ;')
				print(tab + '}' )
				print('/* Backwards Substitution for Uw = y */')
				print(tab+'for(i = %d; i >= 0; i--) {' % (N-1))
				print(2*tab+'sum = %s;' % (cstyle[TYPE] % (0)) )
				print(2*tab+'for(j = i+1; j < %d; j++)' %(N) )
				print(3*tab+'sum += _LU(i,j) * _w->v[j];') 
				print(2*tab+'/*_w->v[i] = (_w->v[i] - sum) ;*/')
				print(2*tab+'_w->v[i] = (_w->v[i] - sum) ;')
				print(tab + '}' )
				print('#undef _LU /* (i,j) _LU->v[i+%d*j] */' % (N))

				print('}\n'+function_preamble+'CreateLULocal(%s* RESTRICT _A)\n{\n /* Note this code stores both L and U inside of A */' % (MTXTYPE) )
				print(' /* For A in R[n x m] we say that for n = m there is an LU = A decomposition [In our decomp, diag[L] = I. Furthermore there is an LU=PA decomposition, where P is a permutation matrix\n Step 1:  U(i,i:m) = A(i,i:m) \n Step 2: L(i+1:n,i) = -A(i+1:n,i) \n Step 3: ??? \n Step 4: Profit */ ')
				print('#define _A(i,j) _A->v[i+%d*j]' % (N))
				print(tab+'int i,j,k;')
				print(tab+TYPE+' sum;')
				
				print('/* These entries are the same as before in the algorithm. This is left in for purposes of clarity and completeness ')
				for i in rows:
						print('_L(%d,0) = _A(%d,0);' % (i,i))
				print('These entries are understood to be 1 in this storage format. This is left in for purposes of clarity and completeness ')
				for i in rows:
						print('_U(%d,%d) = ' % (i,i) + (('%s;' % cstyle[TYPE]) % (1)) )
				print('*/')

				for i in r_[1:N]:
						print('_A(0,%d) = _A(0,%d) / _A(0,0);' % (i,i))


				print((tab+'for(i=1; i < %d; i++) {\n') %(N))
				print(2*tab+'for(j=0; j <= i; j++) {')
				print(3*tab+'sum = '+('%s;' % cstyle[TYPE]) % (0))
				print(3*tab+'for(k=0; k < j; k++) sum += -_A(i,k)*_A(k,j);')
				print(3*tab+'_A(i,j) = _A(i,j) + sum;\n%s}' % (2*tab))
				print(2*tab+'for(j=i+1; j < %d; j++) {' % (N))
				print(3*tab+'sum = '+('%s;' % cstyle[TYPE]) % (0))
				print(3*tab+'for(k=0; k < i; k++) sum += -_A(i,k)*_A(k,j);')
				print(3*tab+'_A(i,j) = (_A(i,j) + sum) / _A(i,i);\n%s}' % (2*tab))
				print(tab+'}')
				print('#undef _A')

		print('}')
def resetMats():
		if(TYPE=='unsigned int'):
				low = 0
				high = 40
		else:
				low = -20
				high = 20

		v = array(random.randint(low,high,N),dtype=DTYPE[TYPE])
		X = asfortranarray(random.randint(low,high,(N,N)),dtype=DTYPE[TYPE])
		Y = asfortranarray(random.randint(low,high,(N,N)),dtype=DTYPE[TYPE])

		print('/* Resetting test vectors / mats */')
		'''print('/* v')
		print(v)
		print('*/')'''
		for i in rows:
				print(tab+'v.v[%d] = ' % i + ('%s' % cstyle[TYPE]) % (v[i])+';')
		'''print('/* X')
		print(X)
		print('*/')'''
		for j in columns:
				for i in rows:
						print(tab+'X.v[%d] = ' %(i+N*j) + (('%s' % cstyle[TYPE]) % (X[i,j]))+';')

		'''print('/* Y')
		print(Y)
		print('*/')'''
		for j in columns:
				for i in rows:
						print(tab+'Y.v[%d] = ' %(i+N*j) + (('%s' % cstyle[TYPE]) % (Y[i,j]))+';')

		return v,X,Y

def Equals(str1,str2):
    if((TYPE=='int') | (TYPE=='unsigned int')):
        return '('+str1+')==('+str2+')'
    else:
        return '%s((' % fabs[TYPE] + str1+')-('+str2+')) <=100*%s /* yes this is bad */' % (fp_epsilon[TYPE])

def ZUnitTestPair( testname , additional_endchars = ','):
		print('{ "%-45s" , %-45s }' %(testname,testname)+additional_endchars)

# Variable Setup
def VariableSetup():
		print(tab+'int i;')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s B; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		print(tab+'SST_Vec%s w; /* %d vector */' % (MTXTYPE[-2::],N))

def EndTest():
		print(tab+'return ZTEST_SUCCESS;\n}')

#Generate Unit Test code
if(CODE_TYPE == 'unittest'):
		print('#include "ZUnitTest.hpp"')
		print('#include <float.h>')
		print('#include <math.h>')
		print('#include <stdlib.h>')
		print('#include <stdio.h>')
		print('#include <SST/%s.h>' % MTXTYPE[0:-1])
		print('#include <SST/%s.h>' % VTXTYPE[0:-1])
		print('\n\n\n')

		unittest_preamble = 'static const char* test'
		print(unittest_preamble+function_call+'Add();')
		print(unittest_preamble+function_call+'AddLocal();')
		print(unittest_preamble+function_call+'Subtract();')
		print(unittest_preamble+function_call+'SubtractLocal();')
		print(unittest_preamble+function_call+'MultiplyElementwise();')
		print(unittest_preamble+function_call+'MultiplyElementwiseLocal();')
		print(unittest_preamble+function_call+'MultiplyScalar();')
		print(unittest_preamble+function_call+'MultiplyScalarLocal();')
		print(unittest_preamble+function_call+'MultiplyMatrix();')
		print(unittest_preamble+function_call+'MultiplyMatrixLocal();')
		print(unittest_preamble+function_call+'MultiplyVector();')
		print(unittest_preamble+function_call+'MultiplyVectorLocal();')
		print(unittest_preamble+function_call+'Transpose();')
		print(unittest_preamble+function_call+'TransposeLocal();')
		if((TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Determinant();')
				print(unittest_preamble+function_call+'CheckOrthonormal();')
		if((TYPE!='int') & (TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'Invert();')
				print(unittest_preamble+function_call+'InvertLocal();')
				print(unittest_preamble+function_call+'CreateLU();')
				print(unittest_preamble+function_call+'CreateLULocal();')
				print(unittest_preamble+function_call+'ApplyLUMat();')
				print(unittest_preamble+function_call+'ApplyLUMatLocal();')
				print(unittest_preamble+function_call+'ApplyLUVec();')
				print(unittest_preamble+function_call+'ApplyLUVecLocal();')

		print('// List of unit tests ')
		print('ZUnitTest '+function_call+'UnitTests[] = \n{')
		ZUnitTestPair('test'+function_call+'Add')
		ZUnitTestPair('test'+function_call+'AddLocal')
		ZUnitTestPair('test'+function_call+'Subtract')
		ZUnitTestPair('test'+function_call+'SubtractLocal')
		ZUnitTestPair('test'+function_call+'MultiplyElementwise')
		ZUnitTestPair('test'+function_call+'MultiplyElementwiseLocal')
		ZUnitTestPair('test'+function_call+'MultiplyScalar')
		ZUnitTestPair('test'+function_call+'MultiplyScalarLocal')
		ZUnitTestPair('test'+function_call+'MultiplyMatrix')
		ZUnitTestPair('test'+function_call+'MultiplyMatrixLocal')
		ZUnitTestPair('test'+function_call+'MultiplyVector')
		ZUnitTestPair('test'+function_call+'MultiplyVectorLocal')
		if((TYPE!='unsigned int')):
				ZUnitTestPair('test'+function_call+'Determinant')
				ZUnitTestPair('test'+function_call+'CheckOrthonormal')
		if((TYPE!='int') & (TYPE!='unsigned int')):
				ZUnitTestPair('test'+function_call+'Invert')
				ZUnitTestPair('test'+function_call+'InvertLocal')
				ZUnitTestPair('test'+function_call+'CreateLU')
				ZUnitTestPair('test'+function_call+'CreateLULocal')
				ZUnitTestPair('test'+function_call+'ApplyLUMat')
				ZUnitTestPair('test'+function_call+'ApplyLUMatLocal')
				ZUnitTestPair('test'+function_call+'ApplyLUVec')
				ZUnitTestPair('test'+function_call+'ApplyLUVecLocal')
		ZUnitTestPair('test'+function_call+'Transpose')
		ZUnitTestPair('test'+function_call+'TransposeLocal','\n};')

		print('DECLARE_ZTESTBLOCK('+function_call+')')

		commbreak()

		print(unittest_preamble+function_call+'Add(){')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X+Y)
		print('*/')
		print(tab+function_call+'Add(&X,&Y,&A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]+Y[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()

		commbreak()

		print(unittest_preamble+function_call+'AddLocal(){')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))

		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X+Y)
		print('*/')
		print(tab+function_call+'AddLocal(&X,&Y); /* for accuracy */')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]+Y[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1)+');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Subtract(){')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X-Y)
		print('*/')
		print(tab+function_call+'Subtract(&X,&Y,&A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]-Y[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1)+');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'SubtractLocal(){')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X-Y)
		print('*/')
		print(tab+function_call+'SubtractLocal(&X,&Y); /* for accuracy */')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]-Y[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1)+');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyElementwise(){')
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X*Y)
		print('*/')
		print(tab+function_call+'MultiplyElementwise(&X, &Y, &A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (Y[i,j]*X[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyElementwiseLocal(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X*Y)
		print('*/')
		print(tab+function_call+'MultiplyElementwiseLocal(&X,&Y);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (Y[i,j]*X[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyScalar(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(2*X)
		print('*/')
		print(tab+function_call+'MultiplyScalar(&X,'+('%s'%cstyle[TYPE])%(2)+',&A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (2*X[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyScalarLocal(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(2*X)
		print('*/')
		print(tab+function_call+'MultiplyScalarLocal(&X,'+('%s'%cstyle[TYPE]%2)+');')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (2*X[i,j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyMatrix(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		A = dot(reshape(X,(N,N)),reshape(Y,(N,N)))
		print('/*')
		print('X')
		print(reshape(X,(N,N)))
		print('Y')
		print(reshape(Y,(N,N)))
		print(A)
		print('*/')
		print(tab+function_call+'MultiplyMatrix(&X,&Y,&A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i][j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyMatrixLocal(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		A = dot(reshape(X,(N,N)),reshape(Y,(N,N)))
		print('/*')
		print('X')
		print(reshape(X,(N,N)))
		print('Y')
		print(reshape(Y,(N,N)))
		print('X')
		print(A)
		print('*/')
		print(tab+function_call+'MultiplyMatrixLocal(&X,&Y);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i][j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyVector(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		print(tab+'SST_Vec%s w; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		w = dot(reshape(X,(N,N)),v)
		print('/*')
		print('X')
		print(X)
		print('v')
		print(v)
		print('w')
		print(w)
		print('*/')
		print(tab+function_call+'MultiplyVector(&X,&v,&w);')
		for i in rows:
				print(tab+'TASSERT('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (w[i]))+',"Entry .v[%d] failed!"' % (i) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'MultiplyVectorLocal(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print('/*')
		print('X')
		print(X)
		print('v')
		print(v)
		v = dot(reshape(X,(N,N)),v)
		print('v')
		print(v)
		print('*/')
		print(tab+function_call+'MultiplyVectorLocal(&X,&v);')
		for i in rows:
				print(tab+'TASSERT('+Equals('v.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (v[i]))+',"Entry .v[%d] failed!"' % (i) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'Transpose(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print(tab+function_call+'Transpose(&X,&A);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[j,i]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()

		print(unittest_preamble+function_call+'TransposeLocal(){')
		
		print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		v,X,Y = resetMats()
		print(tab+function_call+'TransposeLocal(&X);')
		for i in rows:
				for j in columns:
						print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[j,i]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
		EndTest()
		
		commbreak()


		if((TYPE!='unsigned int')):
				print(unittest_preamble+function_call+'CheckOrthonormal(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
				v,X,Y = resetMats()
				# QR Decomposition - the first n independent columns of matrix X will result in the first n columns of Q being orthonormal basis
				Q,R = linalg.qr(reshape(X,(N,N)))
				QTQ = dot(Q.T,Q)
				if((TYPE=='int') | (TYPE=='unsigned int')):
						for j in columns:
								for i in rows:
										print('X.v[%d] = ' % (i+N*j) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (kronecker(i,j))+';')
						for j in columns:
								for i in rows:
										print('Y.v[%d] = ' % (i+N*j) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (kronecker(i,j))+';')
						print('Y.v[%d] = ' % (N-1) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (1)+'; /* Will cause Y to be fail */')
				else:
						print('/*')
						print(Q)
						print(QTQ)
						print('*/')
						print('/* Set X to orthogonal matrix Q */')
						for j in columns:
								for i in rows:
										print(tab+'X.v[%d] = ' % (i+N*j) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (Q[i][j])+';')
						
				print('/* Check Positive Test */')
				print(tab+'TASSERT('+function_call+'CheckOrthonormal(&X),"CheckOrthonormal failed when it should have passed");')
				print('/* Check Negative Test */')
				print(tab+'TASSERT(!'+function_call+'CheckOrthonormal(&Y),"CheckOrthonormal succeeded when it should have failed");')

				EndTest()
				
				commbreak()

				print(unittest_preamble+function_call+'Determinant(){')
				
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
				v,X,Y = resetMats()
				print('/* det(X) = ')
				print(linalg.det(X))
				print(' */')
				print(tab+TYPE+' result = '+function_call+'Determinant(&X);')
				print(tab+'TASSERT(%s( (result)/(%s) - %s ) <= 100*%s' % (fabs[TYPE],cstyle[TYPE] % (linalg.det(X)),cstyle[TYPE] % (1), fp_epsilon[TYPE] )+',"Determinant failed!");')
				#print(tab+'TASSERT('+Equals('result ',('%s' % cstyle[TYPE]) % (linalg.det(X)))+',"Determinant failed!");')
				EndTest()
				
				commbreak()

		if((TYPE != 'int') & (TYPE != 'unsigned int')):
				print(unittest_preamble+function_call+'Invert(){')
				
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s B; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
				v,X,Y = resetMats()
				B = linalg.inv(reshape(X,(N,N)))
				print('/*')
				print(B)
				print('*/')
				print(tab+function_call+'Invert(&X,&B);')
				for j in columns:
						for i in rows:
								'''print('fprintf(stdout,"B[%d][%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,%d,B.v[%d]);' % (i,j,i+N*j))'''

				for j in columns:
						for i in rows:
								print(tab+'TASSERT('+Equals('B.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i][j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')
				EndTest()
		
				commbreak()

				print(unittest_preamble+function_call+'InvertLocal(){')
				
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
				v,X,Y = resetMats()
				B = linalg.inv(reshape(X,(N,N)))
				print('/*')
				print(B)
				print('*/')
				print(tab+function_call+'InvertLocal(&X);')
				for j in columns:
						for i in rows:
								print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i][j]))+',"Entry _a%d%d failed!"' % (i+1,j+1) + ');')

				EndTest()
		
				commbreak()

				print(unittest_preamble+function_call+'CreateLU(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s LU; /* %d x %d matrix */' % (MTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				print(tab+function_call+'CreateLU(&X,&LU);')

				if(N==2):
						L = array([[2,0],[-3,-.5]],order='F')
						U = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						L = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						U = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						L = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						U = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')
				print('/*')
				print(X)
				print('*/')
				print('/*')
				print(L)
				print('*/')
				print('/*')
				print(U)
				print('*/')
				for i in rows:
						for j in r_[0:i+1]:
								print(tab+'TASSERT('+Equals('LU.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (L[i,j]))+',"L:Entry A_a%d%d failed!"' % (i+1,j+1) + ');')
						for j in r_[i+1:N]:
								print(tab+'TASSERT('+Equals('LU.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (U[i,j]))+',"U:Entry B_a%d%d failed!"' % (i+1,j+1) + ');')

				EndTest()
				print(unittest_preamble+function_call+'CreateLULocal(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				print(tab+function_call+'CreateLULocal(&X);')

				if(N==2):
						A = array([[2,0],[-3,-.5]],order='F')
						B = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						A = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						B = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						A = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						B = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')

				for i in rows:
						for j in r_[0:i+1]:
								print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i,j]))+',"L:Entry A_a%d%d failed!"' % (i+1,j+1) + ');')
						for j in r_[i+1:N]:
								print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i,j]))+',"U:Entry B_a%d%d failed!"' % (i+1,j+1) + ');')

				EndTest()

				print(unittest_preamble+function_call+'ApplyLUMat(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s LU; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s I; /* %d x %d matrix */' % (MTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				print(tab+function_call+'CreateLU(&X,&LU);')

				if(N==2):
						L = array([[2,0],[-3,-.5]],order='F')
						U = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						L = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						U = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						L = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						U = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')
				print('/*')
				print(X)
				print('*/')
				print('/*')
				print(L)
				print('*/')
				print('/*')
				print(U)
				print('*/')

				for i in rows:
						for j in r_[0:i+1]:
								print(tab+'TASSERT('+Equals('LU.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (L[i,j]))+',"L:Entry A_a%d%d failed!"' % (i+1,j+1) + ');')
						for j in r_[i+1:N]:
								print(tab+'TASSERT('+Equals('LU.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (U[i,j]))+',"U:Entry B_a%d%d failed!"' % (i+1,j+1) + ');')

				print(tab+function_call+'ApplyLUMat(&LU,&X,&I);')
				for j in columns:
						for i in rows: 
								print(tab+'TASSERT('+Equals('I.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (kronecker(i,j)))+',"I:Entry I_a%d%d failed!"' % (i+1,j+1) + ');')
				EndTest()

				print(unittest_preamble+function_call+'ApplyLUMatLocal(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s Xinv; /* %d x %d matrix */' % (MTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				for j in columns:
						for i in rows:
								print(tab+('Xinv.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				print(tab+function_call+'CreateLULocal(&X);')

				if(N==2):
						A = array([[2,0],[-3,-.5]],order='F')
						B = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						A = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						B = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						A = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						B = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')

				for i in rows:
						for j in r_[0:i+1]:
								print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i,j]))+',"L:Entry A_a%d%d failed!"' % (i+1,j+1) + ');')
						for j in r_[i+1:N]:
								print(tab+'TASSERT('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i,j]))+',"U:Entry B_a%d%d failed!"' % (i+1,j+1) + ');')

				print(tab+function_call+'ApplyLUMatLocal(&X,&Xinv);')
				for j in columns:
						for i in rows: 
								print(tab+'TASSERT('+Equals('Xinv.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (kronecker(i,j)))+',"Xinv:Entry Xinv_a%d%d failed!"' % (i+1,j+1) + ');')
				
				EndTest()

				print(unittest_preamble+function_call+'ApplyLUVec(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s LU; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s b; /* %d x %d vector */' % (VTXTYPE,N,N))
				print(tab+'%s x; /* %d x %d vector */' % (VTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
						b = array([2,-1])
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
						b = array([2,-1,1])
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')
						b = array([2,-1,1,1])

				x = dot(linalg.inv(reshape(X,(N,N))),b)

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				for j in columns:
						print(tab+('b.v[%d] = %s;' % (j,cstyle[TYPE])) % (b[j]))

				print(tab+function_call+'CreateLU(&X,&LU);')

				if(N==2):
						L = array([[2,0],[-3,-.5]],order='F')
						U = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						L = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						U = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						L = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						U = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')

				print(tab+function_call+'ApplyLUVec(&LU,&b,&x);')
				for j in columns:
						print(tab+'TASSERT('+Equals('x.v[%d]' % (j), ('%s' % cstyle[TYPE]) % (x[j]))+',"x:Entry x_a%d failed!"' % (j+1) + ');')
				
				EndTest()

				print(unittest_preamble+function_call+'ApplyLUVecLocal(){')
				print(tab+'%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s LU; /* %d x %d matrix */' % (MTXTYPE,N,N))
				print(tab+'%s b; /* %d x %d vector */' % (VTXTYPE,N,N))
				if(N==2):
						X = array([[2,-1],[-3,1]],order='F')
						b = array([2,-1])
				if(N==3):
						X = array([[2,-1,-1],[1,0,-1],[0,2,1]],order='F')
						b = array([2,-1,1])
				if(N==4):
						X = array([[2,-1,-1,1],[1,0,-1,2],[0,2,1,1],[4,2,0,0]],order='F')
						b = array([2,-1,1,1])

				x = dot(linalg.inv(reshape(X,(N,N))),b)

				for j in columns:
						for i in rows:
								print(tab+('X.v[%d] = %s;' % (i+N*j,cstyle[TYPE])) % (X[i,j]))

				for j in columns:
						print(tab+('b.v[%d] = %s;' % (j,cstyle[TYPE])) % (b[j]))

				print(tab+function_call+'CreateLU(&X,&LU);')

				if(N==2):
						L = array([[2,0],[-3,-.5]],order='F')
						U = array([[1,-.5],[0,1]], order='F')

				if(N==3):
						L = array([[2,0,0],[1,.5,0],[0,2,3]],order='F')
						U = array([[1,-.5,-.5],[0,1,-1],[0,0,1]],order='F')

				if(N==4):
						L = array([[2,0,0,0],[1,.5,0,0],[0,2,3,0],[4,4,6,-4]],order='F')
						U = array([[1,-.5,-.5,.5],[0,1,-1,3],[0,0,1,-1.66666666666667],[0,0,0,1]],order='F')

				print(tab+function_call+'ApplyLUVecLocal(&LU,&b);')
				for j in columns:
						print(tab+'TASSERT('+Equals('b.v[%d]' % (j), ('%s' % cstyle[TYPE]) % (x[j]))+',"x:Entry x_a%d failed!"' % (j+1) + ');')
				
				EndTest()


# Generates the test code
if(CODE_TYPE == 'benchmark'):
		print('#include <float.h>')
		print('#include <math.h>')
		print('#include <stdlib.h>')
		print('#include <stdio.h>')
		print('#include <assert.h>')
		print('#include <xmmintrin.h>')
		print('#include <SST/SST_Timer_x86.h>')
		print('#include <SST/%s.h>' % MTXTYPE[0:-1])
		print('#include <SST/%s.h>' % VTXTYPE[0:-1])
		print('\n\n\n')
		print('int '+function_call+'_test_fxns()\n{')
# Variable Setup
		print('const int NTESTS = 10;')
		print('int i;')
		print('uint64_t t0,t1;')
		print('%s X; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print('%s Y; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print('%s A; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print('%s B; /* %d x %d matrix */' % (MTXTYPE,N,N))
		print('SST_Vec%s v; /* %d vector */' % (MTXTYPE[-2::],N))
		print('SST_Vec%s w; /* %d vector */' % (MTXTYPE[-2::],N))
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
# Initial array / matrix values
		v,X,Y = resetMats()
# Function Tests
		print(function_call+'Add(&X,&Y,&A); /* clear out the initial finding of object */')
		print('/* Clear out the rdtsc register */')
		print('fprintf(stdout,"'+function_call+'Add(X,Y,A)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'Add(&X,&Y,&A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('/*')
		print(X)
		print(Y)
		print(X+Y)
		print('*/')
		for i in rows:
				for j in columns:
						print('assert('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]+Y[i,j]))+');')

# Unit test for Add equals
		print('/*')
		print(X)
		print(Y)
		print(X+Y)
		print('*/')
		print('fprintf(stdout,"'+function_call+'AddLocal(A,Y)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'AddLocal(&A,&Y);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		# have to check for accuracy as well as for timing
		print(function_call+'AddLocal(&X,&Y); /* for accuracy */')
		for i in rows:
				for j in columns:
						print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[i,j]+Y[i,j]))+');')

		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(2*X)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyScalar(X,t,Y)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyScalar(&X,'+('%s'%cstyle[TYPE])%(2)+',&A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		for i in rows:
				for j in columns:
						print('assert('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (2*X[i,j]))+');')

		print('/*')
		print(X)
		print(2*X)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyScalarLocal(A,t)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyScalarLocal(&A,'+('%s'%cstyle[TYPE]%2)+');')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print(function_call+'MultiplyScalarLocal(&X,'+('%s'%cstyle[TYPE]%2)+');')
		for i in rows:
				for j in columns:
						print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (2*X[i,j]))+');')

		v,X,Y = resetMats()
		print('/*')
		print(X)
		print(Y)
		print(X*Y)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyElementwise(X,Y,A)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyElementwise(&X, &Y, &A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		for i in rows:
				for j in columns:
						print('assert('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (Y[i,j]*X[i,j]))+');')

		print('/*')
		print(X)
		print(Y)
		print(X*Y)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyElementwiseLocal(X,Y)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyElementwiseLocal(&A,&Y);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print(function_call+'MultiplyElementwiseLocal(&X,&Y);')
		for i in rows:
				for j in columns:
						print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (Y[i,j]*X[i,j]))+');')

		v,X,Y = resetMats()
		A = dot(reshape(X,(N,N)),reshape(Y,(N,N)))
		print('/*')
		print('X')
		print(reshape(X,(N,N)))
		print('Y')
		print(reshape(Y,(N,N)))
		print(A)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyMatrix(X,Y,A)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyMatrix(&X,&Y,&A);')
		print('t1 = rdtsc();')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		for i in rows:
				for j in columns:
						print('assert('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i][j]))+');')

		print('/*')
		print('X')
		print(reshape(X,(N,N)))
		print('Y')
		print(reshape(Y,(N,N)))
		print('X')
		print(A)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyMatrixLocal(X,Y)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyMatrixLocal(&A,&Y);')
		print('t1 = rdtsc();')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print(function_call+'MultiplyMatrixLocal(&X,&Y);')
		for i in rows:
				for j in columns:
						print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (A[i][j]))+');')

		v,X,Y = resetMats()
		w = dot(reshape(X,(N,N)),v)
		print('/*')
		print('X')
		print(X)
		print('v')
		print(v)
		print('w')
		print(w)
		print('*/')
		print('i=0;')
		print('fprintf(stdout,"'+function_call+'MultiplyVector(X,v,w)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyVector(&X,&v,&w);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		'''for i in rows:
		for j in columns:
			print('fprintf(stdout,"X[%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,X[%d]);' % (N*i+j,N*i+j))
		for i in rows:
		print('fprintf(stdout,"v[%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,v[%d]);' % (i,i))
		for i in rows:
		print('fprintf(stdout,"w[%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,w[%d]);' % (i,i)) '''
		for i in rows:
				print('assert('+Equals('w.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (w[i]))+');')

		print('/*')
		print('X')
		print(X)
		print('v')
		print(v)
		v = dot(reshape(X,(N,N)),v)
		print('v')
		print(v)
		print('*/')
		print('fprintf(stdout,"'+function_call+'MultiplyVectorLocal(X,v)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyVectorLocal(&X,&w);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print(function_call+'MultiplyVectorLocal(&X,&v);')
		for i in rows:
				print('assert('+Equals('v.v[%d]' % (i), ('%s' % cstyle[TYPE]) % (v[i]))+');')

		v,X,Y = resetMats()
		print('fprintf(stdout,"'+function_call+'Transpose(X,A)\");')
		print('t0 = rdtsc();')
		print(function_call+'Transpose(&X,&A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		for i in rows:
				for j in columns:
						print('assert('+Equals('A.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[j,i]))+');')

		print('fprintf(stdout,"'+function_call+'TransposeLocal(X)\");')
		print('for(i = 0; i < NTESTS; i++) { ')
		print('t0 = rdtsc();')
		print(function_call+'TransposeLocal(&A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('}')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print(function_call+'TransposeLocal(&X);')
		for i in rows:
				for j in columns:
						print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (X[j,i]))+');')

# QR Decomposition - the first n independent columns of matrix X will result in the first n columns of Q being orthonormal basis
		Q,R = linalg.qr(reshape(X,(N,N)))
		QTQ = dot(Q.T,Q)
		print('/*')
		print(Q)
		print(QTQ)
		print('*/')
		for i in rows:
				for j in columns:
						print('X.v[%d] = ' % (i+N*j) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (Q[i][j])+';')

		print('fprintf(stdout,"'+function_call+'Transpose(X,A)\");')
		print('t0 = rdtsc();')
		print(function_call+'Transpose(&X,&A);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		print('fprintf(stdout,"'+function_call+'MultiplyMatrix(A,X,B)\");')
		print('t0 = rdtsc();')
		print(function_call+'MultiplyMatrix(&A,&X,&B);')
		print('t1 = rdtsc();')
		print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
		for i in rows:
				for j in columns:
						#print('fprintf(stdout,"B[%d][%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,%d,B[%d]);' % (i,j,N*i+j))
						''' '''

		if(TYPE != 'unsigned int'):
			if(TYPE != 'int'):
				print('/* Check Negative Test */')
				print('assert(!'+function_call+'CheckOrthonormal(&X));')
				for i in rows:
						for j in columns:
								print('X.v[%d] = ' % (i+N*j) +('(%s)' % TYPE) + ('%s' % cstyle[TYPE]) % (kronecker(i,j))+';')
				print('/* Check Positive Test */')
				print('assert('+function_call+'CheckOrthonormal(&X));')
			else:
				print('/* Check Positive Test */')
				print('assert('+function_call+'CheckOrthonormal(&X));')
				print('/* Check Negative Test */')
				print('assert(!'+function_call+'CheckOrthonormal(&Y));')

		if((TYPE != 'int') & (TYPE != 'unsigned int')):
				v,X,Y = resetMats()
				B = linalg.inv(reshape(X,(N,N)))
				print('/*')
				print(B)
				print('*/')
				print('fprintf(stdout,"'+function_call+'Invert(X,B)\\n");')
				print('t0 = rdtsc();')
				print(function_call+'Invert(&X,&B);')
				print('t1 = rdtsc();')
				print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
				for i in rows:
						for j in columns:
								print('fprintf(stdout,"B[%d][%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,%d,B.v[%d]);' % (i,j,N*i+j))
								''' '''
				for i in rows:
						for j in columns:
								print('assert('+Equals('B.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i][j]))+');')

				v,X,Y = resetMats()
				B = linalg.inv(reshape(X,(N,N)))
				print('/*')
				print(B)
				print('*/')
				print('fprintf(stdout,"'+function_call+'Invert(X,B)\\n");')
				for i in rows:
						for j in columns:
								#print('fprintf(stdout,"X[%d][%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,%d,X[%d]);' % (i,j,N*i+j))
								''' '''
				print('fflush(stdout);')
				print('fprintf(stdout,"'+function_call+'InvertLocal(X,B)\\n");')
				print('t0 = rdtsc();')
				print(function_call+'InvertLocal(&X);')
				print('t1 = rdtsc();')
				print('fprintf(stdout," timing:%llu\\n",(long long unsigned int)(t1-t0));')
				for i in rows:
						for j in columns:
								#print('fprintf(stdout,"X[%d][%d] = '+('%s' % cstyle[TYPE])+'\\n",%d,%d,X[%d]);' % (i,j,N*i+j))
								''' '''
				print('fflush(stdout);')
				for i in rows:
						for j in columns:
								print('assert('+Equals('X.v[%d]' % (i+N*j), ('%s' % cstyle[TYPE]) % (B[i][j]))+');')

		print('fprintf(stdout,"\\n==== '+function_call+'test_fxn COMPLETE ====\\n");')
		print('return 0;\n}')

if(TIMING_CHECK):
		NUM_TESTS = 1000
		print('#include <assert.h>')
		print('#include <stdlib.h>')
		print('#include <stdio.h>')
		print('#include <SST/SST_Timer_x86.h>')
		print('int '+function_call+'timing_fxns()\n{')
# Variable Setup
		print('%s *X,*Y,*A,*B,*v,*w;' % TYPE)
		print('int i;')
		print('const int NUM_TESTS = %d;' % (NUM_TESTS))
		print('X = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N*N,TYPE))
		print('Y = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N*N,TYPE))
		print('A = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N*N,TYPE))
		print('B = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N*N,TYPE))
		print('v = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N,TYPE))
		print('w = (%s*) calloc(%d,sizeof(%s));' % (TYPE,N,TYPE))
		print('for(i=0;i<NUM_TESTS;i++){}')

		print('free(X);')
		print('free(Y);')
		print('free(A);')
		print('free(B);')
		print('free(v);')
		print('free(w);')
		print('fprintf(stdout,"==== '+function_call+'timing_fxn COMPLETE ====\");')
		print('return 0;\n}')

