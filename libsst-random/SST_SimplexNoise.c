#include <SST/SST_SimplexNoise.h>

#include <time.h>
#include <math.h>
#include <stdlib.h>

#include <pstdint.h>
#include <string.h> /* memcpy() */

static const int grad3[][3] =
{
	{1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
	{1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
	{0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

static const int grad4[][4] =
{
	{0,1,1,1},	{0,1,1,-1},		{0,1,-1,1},		{0,1,-1,-1},
	{0,-1,1,1},	{0,-1,1,-1},	{0,-1,-1,1},	{0,-1,-1,-1},
	{1,0,1,1},	{1,0,1,-1},		{1,0,-1,1},		{1,0,-1,-1},
	{-1,0,1,1},	{-1,0,1,-1},	{-1,0,-1,1},	{-1,0,-1,-1},
	{1,1,0,1},	{1,1,0,-1},		{1,-1,0,1},		{1,-1,0,-1},
	{-1,1,0,1},	{-1,1,0,-1},	{-1,-1,0,1},	{-1,-1,0,-1},
	{1,1,1,0},	{1,1,-1,0},		{1,-1,1,0},		{1,-1,-1,0},
	{-1,1,1,0},	{-1,1,-1,0},	{-1,-1,1,0},	{-1,-1,-1,0}
};

static const int p[] =
{
	151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,
	225,140,36,103,30,69,142,8,99,37,240,21,10,23,190,6,
	148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,
	11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,
	168, 68,175,74,165,71,134,139,48,27,166,77,146,158,
	231,83,111,229,122,60,211,133,230,220,105,92,41,55,
	46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,
	209,76,132,187,208, 89,18,169,200,196,135,130,116,188,
	159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,
	123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
	47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,
	2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,
	39,253, 19,98,108,110,79,113,224,232,178,185,112,104,
	218,246,97,228,251,34,242,193,238,210,144,12,191,179,
	162,241, 81,51,145,235,249,14,239,107,49,192,214,31,
	181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,
	254, 138,236,205,93,222,114,67,29,24,72,243,141,128,195,
	78,66,215,61,156,180
};

/*
A lookup table to traverse the simplex around a given point in 4D.
Details can be found where this table is used, in the 4D noise method.
*/
static const int simplex[][4] =
{
	{0,1,2,3},{0,1,3,2},{0,0,0,0},{0,2,3,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,0},
	{0,2,1,3},{0,0,0,0},{0,3,1,2},{0,3,2,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,3,2,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{1,2,0,3},{0,0,0,0},{1,3,0,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,3,0,1},{2,3,1,0},
	{1,0,2,3},{1,0,3,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,3,1},{0,0,0,0},{2,1,3,0},
	{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
	{2,0,1,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,0,1,2},{3,0,2,1},{0,0,0,0},{3,1,2,0},
	{2,1,0,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,1,0,2},{0,0,0,0},{3,2,0,1},{3,2,1,0}
};

typedef struct
{
	int perm[512];
} SST_Simplex_Data_t;

static int fastfloor(const double x)
{
	return (int) floor(x);
}
static double dot2(const int* g, const double x, const double y)
{
	return g[0]*x + g[1]*y;
}

static double dot3(const int* g, const double x, const double y, const double z)
{
	return g[0]*x + g[1]*y + g[2]*z;
}
static double dot4(const int* g, const double x, const double y, const double z, const double w)
{
	return g[0]*x + g[1]*y + g[2]*z + g[3]*w;
}

SST_SimplexNoise SST_Random_CreateSimplexNoise()
{
	return SST_Random_CreateSimplexNoiseFromSeed((uint32_t) time(NULL));
}

SST_SimplexNoise SST_Random_CreateSimplexNoiseFromSeed(uint32_t _seed)
{
	SST_Simplex_Data_t* ret = (SST_Simplex_Data_t *)calloc(sizeof(SST_Simplex_Data_t), 1);
	size_t i;

	if (ret == NULL)
		return NULL;

	for(i = 0; i < 512; i++)
		ret->perm[i] = p[i & 255];

	SST_Random_ReseedSimplexNoise(ret, _seed);

	return (SST_SimplexNoise) ret;
}

void SST_Random_ReseedSimplexNoise(SST_SimplexNoise _source, uint32_t _seed)
{
	SST_Simplex_Data_t* temp = (SST_Simplex_Data_t *) _source;
	int i;

	/* reseeding here currently means shifting around the values */
	for(i = 0; i < 512; i++)
		temp->perm[i] = p[ ( (i + _seed) % 256) & 255];
}

SST_SimplexNoise SST_Random_CloneSimplexNoise(SST_SimplexNoise _source)
{
	SST_Simplex_Data_t* ret;

	if (_source == NULL)
		return NULL;
	
	ret = (SST_Simplex_Data_t*)calloc(sizeof(SST_Simplex_Data_t), 1);
	
	memcpy(ret,(SST_Simplex_Data_t*)_source, sizeof(SST_Simplex_Data_t));

	return (SST_SimplexNoise) ret;
}

void SST_Random_DestroySimplexNoise(SST_SimplexNoise _instance)
{
	free(_instance);
}

float SST_Random_MapSimplexNoise1D( SST_SimplexNoise _instance, float _x)
{
	/* HACKHACK */
	return SST_Random_MapSimplexNoise2D(_instance,_x,0);	
}

void SST_Random_MapSimplexNoise1DFromArray( SST_SimplexNoise _instance, float* _destination, float* _sourceX, size_t _numElements)
{
	size_t i;

	if (_destination == NULL || _sourceX == NULL)
		return;

	for (i = 0; i < _numElements; i++)
		_destination[i] = SST_Random_MapSimplexNoise1D(_instance, _sourceX[i]);
}

float SST_Random_MapSimplexNoise2D( SST_SimplexNoise _instance, float _x, float _y)
{
	int* perm;

	int i, j;
	int i1, j1; /* Offsets for second (middle) corner of simplex in (i,j) coords */
	double n0, n1, n2; /* Noise contributions from the three corners */
	double s, t,x0,X0,y0,Y0;
	double x1,y1,x2,y2;
	double t0,t1,t2;
	int ii, jj, gi0, gi1, gi2;

	/* Skew the input space to determine which simplex cell we're in */
	const double F2 = 0.5*(sqrtf(3.0)-1.0);
	const double G2 = (3.0-sqrtf(3.0))/6.0;
	s = (_x+_y)*F2; // Hairy factor for 2D
	i = fastfloor(_x+s);
	j = fastfloor(_y+s);

	t = (i+j)*G2;
	X0 = i-t; /* Unskew the cell origin back to (x,y) space */
	Y0 = j-t;
	x0 = _x-X0; /* The x,y distances from the cell origin */
	y0 = _y-Y0;

	/*
	For the 2D case, the simplex shape is an equilateral triangle.
	Determine which simplex we are in.
	*/
	perm = ((SST_Simplex_Data_t*)_instance)->perm;

	if(x0>y0)
	{
		i1=1;
		j1=0;
	} /* lower triangle, XY order: (0,0)->(1,0)->(1,1) */
	else
	{
		i1=0;
		j1=1;
	} /* upper triangle, YX order: (0,0)->(0,1)->(1,1) */

	/*
	A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	c = (3-sqrt(3))/6
	*/
	x1 = x0 - i1 + G2; /* Offsets for middle corner in (x,y) unskewed coords */
	y1 = y0 - j1 + G2;
	x2 = x0 - 1.0 + 2.0 * G2; /* Offsets for last corner in (x,y) unskewed coords */
	y2 = y0 - 1.0 + 2.0 * G2;

	/* Work out the hashed gradient indices of the three simplex corners */
	ii = i & 255;
	jj = j & 255;
	gi0 = perm[ii+perm[jj]] % 12;
	gi1 = perm[ii+i1+perm[jj+j1]] % 12;
	gi2 = perm[ii+1+perm[jj+1]] % 12;

	/* Calculate the contribution from the three corners */
	t0 = 0.5 - x0*x0-y0*y0;
	if(t0<0)
		n0 = 0.0;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * dot2(grad3[gi0], x0, y0); /* (x,y) of grad3 used for 2D gradient */
	}
	t1 = 0.5 - x1*x1-y1*y1;
	if(t1<0)
		n1 = 0.0;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * dot2(grad3[gi1], x1, y1);
	}

	t2 = 0.5 - x2*x2-y2*y2;
	if (t2<0)
		n2 = 0.0;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * dot2(grad3[gi2], x2, y2);
	}

	/*
	Add contributions from each corner to get the final noise value.
	The result is scaled to return values in the interval [-1,1].
	TODO check accuracy of this
	*/
	return (float) (70.0 * (n0 + n1 + n2));
}

void SST_Random_MapSimplexNoise2DFromArray( SST_SimplexNoise _instance, float* _destination, float* _sourceX, float* _sourceY, size_t _numElements)
{
	size_t i;

	if (_destination == NULL || _sourceX == NULL || _sourceY == NULL)
		return;

	for (i = 0; i < _numElements; i++)
		_destination[i] = SST_Random_MapSimplexNoise2D(_instance, _sourceX[i], _sourceY[i]);
}

float SST_Random_MapSimplexNoise3D( SST_SimplexNoise _instance, float _x, float _y,  float _z)
{
	double n0, n1, n2, n3; /* Noise contributions from the four corners */

	/* Skew the input space to determine which simplex cell we're in */
	const double F3 = 1.0/3.0;
	const double G3 = 1.0/6.0; /* Very nice and simple unskew factor, too */
	double s = (_x+_y+_z)*F3; /* Very nice and simple skew factor for 3D */
	int i = (int)floor(_x+s);
	int j = (int)floor(_y+s);
	int k = (int)floor(_z+s);

	double t = (i+j+k)*G3;
	double X0 = i-t; /* Unskew the cell origin back to (x,y,z) space */
	double Y0 = j-t;
	double Z0 = k-t;
	double x0 = _x-X0; /* The x,y,z distances from the cell origin */
	double y0 = _y-Y0;
	double z0 = _z-Z0;

	double x1,y1,z1,x2,y2,z2,x3,y3,z3;
	double t0,t1,t2,t3;

	/*
	For the 3D case, the simplex shape is a slightly irregular tetrahedron.
	Determine which simplex we are in.
	*/
	int i1, j1, k1; /* Offsets for second corner of simplex in (i,j,k) coords */
	int i2, j2, k2; /* Offsets for third corner of simplex in (i,j,k) coords */
	int ii,jj,kk,gi0,gi1,gi2,gi3;

	int* perm = ((SST_Simplex_Data_t*)_instance)->perm;

	if(x0>=y0)
	{
		if(y0>=z0)
		{
			i1=1;
			j1=0;
			k1=0;
			i2=1;
			j2=1;
			k2=0;
		} /* X Y Z order */
		else if(x0>=z0)
		{
			i1=1;
			j1=0;
			k1=0;
			i2=1;
			j2=0;
			k2=1;
		} /* X Z Y order */
		else
		{
			i1=0;
			j1=0;
			k1=1;
			i2=1;
			j2=0;
			k2=1;
		} /* Z X Y order */
	}
	else
	{ /* x0<y0 */
		if(y0<z0)
		{
			i1=0;
			j1=0;
			k1=1;
			i2=0;
			j2=1;
			k2=1;
		} /* Z Y X order */
		else if(x0<z0)
		{
			i1=0;
			j1=1;
			k1=0;
			i2=0;
			j2=1;
			k2=1;
		} /* Y Z X order */
		else
		{
			i1=0;
			j1=1;
			k1=0;
			i2=1;
			j2=1;
			k2=0;
		} /* Y X Z order */
	}
	/*
	A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
	a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
	c = 1/6
	*/
	x1 = x0 - i1 + G3; /* Offsets for second corner in (x,y,z) coords */
	y1 = y0 - j1 + G3;
	z1 = z0 - k1 + G3;
	x2 = x0 - i2 + 2.0*G3; /* Offsets for third corner in (x,y,z) coords */
	y2 = y0 - j2 + 2.0*G3;
	z2 = z0 - k2 + 2.0*G3;
	x3 = x0 - 1.0 + 3.0*G3; /* Offsets for last corner in (x,y,z) coords */
	y3 = y0 - 1.0 + 3.0*G3;
	z3 = z0 - 1.0 + 3.0*G3;

	/* Work out the hashed gradient indices of the four simplex corners */
	ii = i & 255;
	jj = j & 255;
	kk = k & 255;
	gi0 = perm[ii+perm[jj+perm[kk]]] % 12;
	gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1]]] % 12;
	gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2]]] % 12;
	gi3 = perm[ii+1+perm[jj+1+perm[kk+1]]] % 12;

	/* Calculate the contribution from the four corners */
	t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
	if(t0<0)
		n0 = 0.0;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * dot3(grad3[gi0], x0, y0, z0);
	}
	t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
	if(t1<0) n1 = 0.0;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * dot3(grad3[gi1], x1, y1, z1);
	}
	t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
	if(t2<0)
		n2 = 0.0;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * dot3(grad3[gi2], x2, y2, z2);
	}
	t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
	if(t3<0)
		n3 = 0.0;
	else
	{
		t3 *= t3;
		n3 = t3 * t3 * dot3(grad3[gi3], x3, y3, z3);
	}
	/*
	Add contributions from each corner to get the final noise value.
	The result is scaled to stay just inside [-1,1]
	*/
	return (float)(32.0*(n0 + n1 + n2 + n3));
}

void SST_Random_MapSimplexNoise3DFromArray( SST_SimplexNoise _instance, float* _destination, float* _sourceX, float* _sourceY, float* _sourceZ, size_t _numElements)
{
	size_t i;

	if (_destination == NULL || _sourceX == NULL || _sourceY == NULL || _sourceZ == NULL)
		return;

	for (i = 0; i < _numElements; i++)
		_destination[i] = SST_Random_MapSimplexNoise3D(_instance, _sourceX[i], _sourceY[i], _sourceZ[i]);
}

float SST_Random_MapSimplexNoise4D( SST_SimplexNoise _instance, float _x, float _y,  float _z, float _w)
{
	/* The skewing and unskewing factors are hairy again for the 4D case */
	const double F4 = (sqrtf(5.0)-1.0)/4.0;
	const double G4 = (5.0-sqrtf(5.0))/20.0;
	double n0, n1, n2, n3, n4; /* Noise contributions from the five corners */
	
	/* Skew the (x,y,z,w) space to determine which cell of 24 simplices we're in */
	double s = (_x + _y + _z + _w) * F4; /* Factor for 4D skewing */
	int i = fastfloor(_x + s);
	int j = fastfloor(_y + s);
	int k = fastfloor(_z + s);
	int l = fastfloor(_w + s);
	double t = (i + j + k + l) * G4; /* Factor for 4D unskewing */
	double X0 = i - t; /* Unskew the cell origin back to (x,y,z,w) space */
	double Y0 = j - t;
	double Z0 = k - t;
	double W0 = l - t;
	double x0,x1,x2,x3,x4,y0,y1,y2,y3,y4,z0,z1,z2,z3,z4,w0,w1,w2,w3,w4;
	int c,c1,c2,c3,c4,c5,c6;
	double t0,t1,t2,t3,t4;
	int i1, j1, k1, l1; /* The integer offsets for the second simplex corner */
	int i2, j2, k2, l2; /* The integer offsets for the third simplex corner */
	int i3, j3, k3, l3; /* The integer offsets for the fourth simplex corner */
	int ii,jj,kk,ll,gi0,gi1,gi2,gi3,gi4;
	int* perm = ((SST_Simplex_Data_t*)_instance)->perm;

	x0 = _x - X0; /* The x,y,z,w distances from the cell origin */
	y0 = _y - Y0;
	z0 = _z - Z0;
	w0 = _w - W0;

	/*
	For the 4D case, the simplex is a 4D shape I won't even try to describe.
	To find out which of the 24 possible simplices we're in, we need to
	determine the magnitude ordering of x0, y0, z0 and w0.
	The method below is a good way of finding the ordering of x,y,z,w and
	then find the correct traversal order for the simplex we�re in.
	First, six pair-wise comparisons are performed between each possible pair
	of the four coordinates, and the results are used to add up binary bits
	for an integer index.
	*/
	c1 = (x0 > y0) ? 32 : 0;
	c2 = (x0 > z0) ? 16 : 0;
	c3 = (y0 > z0) ? 8 : 0;
	c4 = (x0 > w0) ? 4 : 0;
	c5 = (y0 > w0) ? 2 : 0;
	c6 = (z0 > w0) ? 1 : 0;
	c = c1 + c2 + c3 + c4 + c5 + c6;

	/*
	simplex[c] is a 4-vector with the numbers 0, 1, 2 and 3 in some order.
	Many values of c will never occur, since e.g. x>y>z>w makes x<z, y<w and x<w
	impossible. Only the 24 indices which have non-zero entries make any sense.
	We use a thresholding to set the coordinates in turn from the largest magnitude.
	The number 3 in the "simplex" array is at the position of the largest coordinate.
	*/
	i1 = simplex[c][0]>=3 ? 1 : 0;
	j1 = simplex[c][1]>=3 ? 1 : 0;
	k1 = simplex[c][2]>=3 ? 1 : 0;
	l1 = simplex[c][3]>=3 ? 1 : 0;

	/* The number 2 in the "simplex" array is at the second largest coordinate. */
	i2 = simplex[c][0]>=2 ? 1 : 0;
	j2 = simplex[c][1]>=2 ? 1 : 0;
	k2 = simplex[c][2]>=2 ? 1 : 0;
	l2 = simplex[c][3]>=2 ? 1 : 0;

	/* The number 1 in the "simplex" array is at the second smallest coordinate. */
	i3 = simplex[c][0]>=1 ? 1 : 0;
	j3 = simplex[c][1]>=1 ? 1 : 0;
	k3 = simplex[c][2]>=1 ? 1 : 0;
	l3 = simplex[c][3]>=1 ? 1 : 0;

	/* The fifth corner has all coordinate offsets = 1, so no need to look that up. */
	x1 = x0 - i1 + G4; /* Offsets for second corner in (x,y,z,w) coords */
	y1 = y0 - j1 + G4;
	z1 = z0 - k1 + G4;
	w1 = w0 - l1 + G4;
	x2 = x0 - i2 + 2.0*G4; /* Offsets for third corner in (x,y,z,w) coords */
	y2 = y0 - j2 + 2.0*G4;
	z2 = z0 - k2 + 2.0*G4;
	w2 = w0 - l2 + 2.0*G4;
	x3 = x0 - i3 + 3.0*G4; /* Offsets for fourth corner in (x,y,z,w) coords */
	y3 = y0 - j3 + 3.0*G4;
	z3 = z0 - k3 + 3.0*G4;
	w3 = w0 - l3 + 3.0*G4;
	x4 = x0 - 1.0 + 4.0*G4; /* Offsets for last corner in (x,y,z,w) coords */
	y4 = y0 - 1.0 + 4.0*G4;
	z4 = z0 - 1.0 + 4.0*G4;
	w4 = w0 - 1.0 + 4.0*G4;
	
	/* Work out the hashed gradient indices of the five simplex corners */
	ii = i & 255;
	jj = j & 255;
	kk = k & 255;
	ll = l & 255;
	gi0 = perm[ii+perm[jj+perm[kk+perm[ll]]]] % 32;
	gi1 = perm[ii+i1+perm[jj+j1+perm[kk+k1+perm[ll+l1]]]] % 32;
	gi2 = perm[ii+i2+perm[jj+j2+perm[kk+k2+perm[ll+l2]]]] % 32;
	gi3 = perm[ii+i3+perm[jj+j3+perm[kk+k3+perm[ll+l3]]]] % 32;
	gi4 = perm[ii+1+perm[jj+1+perm[kk+1+perm[ll+1]]]] % 32;
	
	/* Calculate the contribution from the five corners */
	t0 = 0.6 - x0*x0 - y0*y0 - z0*z0 - w0*w0;
	if(t0<0)
		n0 = 0.0;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * dot4(grad4[gi0], x0, y0, z0, w0);
	}
	t1 = 0.6 - x1*x1 - y1*y1 - z1*z1 - w1*w1;
	if(t1<0)
		n1 = 0.0;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * dot4(grad4[gi1], x1, y1, z1, w1);
	}
	t2 = 0.6 - x2*x2 - y2*y2 - z2*z2 - w2*w2;
	if(t2<0)
		n2 = 0.0;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * dot4(grad4[gi2], x2, y2, z2, w2);
	}

	t3 = 0.6 - x3*x3 - y3*y3 - z3*z3 - w3*w3;

	if(t3<0)
		n3 = 0.0;
	else
	{
		t3 *= t3;
		n3 = t3 * t3 * dot4(grad4[gi3], x3, y3, z3, w3);
	}
	t4 = 0.6 - x4*x4 - y4*y4 - z4*z4 - w4*w4;
	if(t4<0)
		n4 = 0.0;
	else
	{
		t4 *= t4;
		n4 = t4 * t4 * dot4(grad4[gi4], x4, y4, z4, w4);
	}

	/* Sum up and scale the result to cover the range [-1,1] */
	return (float)(27.0 * (n0 + n1 + n2 + n3 + n4));
}

void SST_Random_MapSimplexNoise4DFromArray( SST_SimplexNoise _instance, float* _destination, float* _sourceX, float* _sourceY, float* _sourceZ, float* _sourceW, size_t _numElements)
{
	size_t i;

	if (_destination == NULL || _sourceX == NULL || _sourceY == NULL || _sourceZ == NULL || _sourceW == NULL)
		return;

	for (i = 0; i < _numElements; i++)
		_destination[i] = SST_Random_MapSimplexNoise4D(_instance, _sourceX[i], _sourceY[i], _sourceZ[i], _sourceW[i]);
}
