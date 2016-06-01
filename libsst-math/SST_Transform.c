
#include <math.h>		/* tanf() */
#include <string.h>		/* memset() */
#include <SST/SST_Math.h>

/* Will form the 4x4 identity matrix.
 * Remember that you can save operations by 
 * simply zeroing what you're not going to fill in yourself */
void SST_Math_Mat33fCreateIdentity(SST_Mat33f* Mat)
{
	memset(Mat, 0, sizeof(SST_Mat33f));
	Mat->v[0] = 1.f;
	Mat->v[4] = 1.f;
	Mat->v[8] = 1.f;
}

void SST_Math_Mat33fFromVec3f(SST_Mat33f* Mat, const SST_Vec3f* v, const int column)
{
	Mat->v[0+3*column] = v->v[0];
	Mat->v[1+3*column] = v->v[1];
	Mat->v[2+3*column] = v->v[2];
}

void SST_Math_Mat44fFromVec4f(SST_Mat44f* Mat, const SST_Vec4f* v, const int column)
{
	Mat->v[0+4*column] = v->v[0];
	Mat->v[1+4*column] = v->v[1];
	Mat->v[2+4*column] = v->v[2];
	Mat->v[3+4*column] = v->v[3];
}
void SST_Math_Mat33dFromVec3d(SST_Mat33d* Mat, const SST_Vec3d* v, const int column)
{
	Mat->v[0+3*column] = v->v[0];
	Mat->v[1+3*column] = v->v[1];
	Mat->v[2+3*column] = v->v[2];
}
void SST_Math_Mat44dFromVec4d(SST_Mat44d* Mat, const SST_Vec4d* v, const int column)
{
	Mat->v[0+4*column] = v->v[0];
	Mat->v[1+4*column] = v->v[1];
	Mat->v[2+4*column] = v->v[2];
	Mat->v[3+4*column] = v->v[3];
}
/* Will form the 4x4 identity matrix.
 * Remember that you can save operations by 
 * simply zeroing what you're not going to fill in yourself */
void SST_Math_Mat44fCreateIdentity(SST_Mat44f* Mat)
{
	memset(Mat, 0, sizeof(SST_Mat44f));
	Mat->v[0] = 1.f;
	Mat->v[5] = 1.f;
	Mat->v[10] = 1.f;
	Mat->v[15] = 1.f;
}
void SST_Math_Mat33fApplyTransforms(SST_Vec3f** Vecs, SST_Mat33f* Transforms, const int num_Vecs)
{
	int i;
	for(i=0; i < num_Vecs; i++)
		SST_Math_Mat33fMultiplyVectorLocal(Transforms, Vecs[i]);
}
void SST_Math_Mat33fCreateTranslation(SST_Mat33f* Mat, const float x, const float y)
{
	memset(Mat, 0, sizeof(SST_Mat33f));
	Mat->v[0] = 1.f;
	Mat->v[4] = 1.f;

	Mat->v[6] = x;
	Mat->v[7] = y;
	Mat->v[8] = 1.f;
}
void SST_Math_Mat44fCreateTranslation(SST_Mat44f* Mat, const float x, const float y, const float z)
{
	memset(Mat, 0, sizeof(SST_Mat44f));
	Mat->v[0]  = 1.f;
	Mat->v[5]  = 1.f;
	Mat->v[10] = 1.f;

	Mat->v[12] = x;
	Mat->v[13] = y;
	Mat->v[14] = z;
	Mat->v[15] = 1.f;
}
/* Forms the matrix to rotate around the X-axis some angle (RADIANS)*/
void SST_Math_Mat44fCreateEulerX(SST_Mat44f* Mat, const float angle)
{
		Mat->v[0]  = 1.f;
		Mat->v[1]  = 0.f;
		Mat->v[2]  = 0.f;
		Mat->v[3]  = 0.f;

		Mat->v[4]  = 0.f;
		Mat->v[5]  = cosf(angle); 
		Mat->v[6]  = sinf(angle);
		Mat->v[7]  = 0.f;

		Mat->v[8]  = 0.f;
		Mat->v[9]  = -sinf(angle);
		Mat->v[10] = cosf(angle);
		Mat->v[11] = 0.f;

		Mat->v[12] = 0.f;
		Mat->v[13] = 0.f;
		Mat->v[14] = 0.f;
		Mat->v[15] = 1.f;
}
/* Forms the matrix to rotate around the X-axis some angle(RADIANS)
 * and applies it to the given Mat */
void SST_Math_Mat44fCreateEulerY(SST_Mat44f* Mat, const float angle)
{
		Mat->v[0] = cosf(angle);
		Mat->v[1] = 0.f;
		Mat->v[2] = -sinf(angle);
		Mat->v[3] = 0.f;

		Mat->v[4] = 0.f;
		Mat->v[5] = 1.f;
		Mat->v[6] = 0.f;
		Mat->v[7] = 0.f;

		Mat->v[8]  =  sinf(angle);
		Mat->v[9]  = 0.f;
		Mat->v[10] =  cosf(angle);
		Mat->v[11] = 0.f;

		Mat->v[12] = 0.f;
		Mat->v[13] = 0.f;
		Mat->v[14] = 0.f;
		Mat->v[15] = 1.f;
}
void SST_Math_Mat33fRAT(SST_Mat33f* _mat,const SST_Vec2f* _about, const SST_Vec2f* _translation, const float angle)
{
		const float cosa = cosf(angle);
		const float sina = sinf(angle);

		_mat->v[0]  = cosa;
		_mat->v[1]  = sina;
		_mat->v[2]  = 0.f;

		_mat->v[3]  = -sina;
		_mat->v[4]  = cosa; 
		_mat->v[5]  = 0.f;

		_mat->v[6]  = -cosa * _about->v[0] +  sina * _about->v[1] + _about->v[0] + _translation->v[0];
		_mat->v[6]  = -sina * _about->v[0] + -cosa * _about->v[1] + _about->v[1] + _translation->v[1];
		_mat->v[8]  = 1.f;

}
void SST_Math_Mat33fCreateEulerZ(SST_Mat33f* Mat, const float angle)
{
		const float cosa = cosf(angle);
		const float sina = sinf(angle);

		Mat->v[0]  = cosa;
		Mat->v[1]  = sina;
		Mat->v[2]  = 0.f;

		Mat->v[3]  = -sina;
		Mat->v[4]  = cosa; 
		Mat->v[5]  = 0.f;

		Mat->v[6]  = 0.f;
		Mat->v[7]  = 0.f;
		Mat->v[8]  = 1.f;
}

void SST_Math_Mat44fCreateEulerZ(SST_Mat44f* Mat, const float angle)
{
		const float cosa = cosf(angle);
		const float sina = sinf(angle);
		Mat->v[0]  =  cosa;
		Mat->v[1]  = sina;
		Mat->v[2]  = 0.f;
		Mat->v[3]  = 0.f;

		Mat->v[4]  = -sina;
		Mat->v[5]  = cosa; 
		Mat->v[6]  = 0.f;
		Mat->v[7]  = 0.f;

		Mat->v[8]  = 0.f;
		Mat->v[9]  = 0.f;
		Mat->v[10] = 1.f;
		Mat->v[11] = 0.f;

		Mat->v[12] = 0.f;
		Mat->v[13] = 0.f;
		Mat->v[14] = 0.f;
		Mat->v[15] = 1.f;
}
/* The chained forms are designed so that they can be chained if desired, e.g.:
  float Original[16];
  Original = SST_Math_Mat33fCreateEulerZ(-30, SST_Math_Mat33fCreateEulerX(-45, SST_Math_Mat33fCreateEulerY(30, Original)));
  --Charles
 */
/* Forms the matrix to rotate around the X-axis some angle (RADIANS)*/
/* Much faster to do this than Create and then multiply */
void SST_Math_Mat44fCreateEulerXC(SST_Mat44f* Mat, const float angle)
{
#define Mat(i,j) Mat->v[i+4*j]
		float cosv = cosf(angle);
		float sinv = sinf(angle);
		float nsinv = -sinv;
		float t[8];
		int i;
		t[0] = nsinv*Mat(2,0);
		t[1] = nsinv*Mat(2,1);
		t[2] = nsinv*Mat(2,2);
		t[3] = nsinv*Mat(2,3);

		t[4] = sinv*Mat(1,0);
		t[5] = sinv*Mat(1,1);
		t[6] = sinv*Mat(1,2);
		t[7] = sinv*Mat(1,3);
		//If this fails, it's probably the next two lines,and the offset of t[];

		for(i=0;i<4;i++)
				Mat(1,i)= cosv*Mat(1,i)+t[i];
		for(i=0;i<4;i++)
				Mat(2,i)= cosv*Mat(2,i)+t[i+4];

#undef Mat
}
/* Forms the matrix to rotate around the X-axis some angle(RADIANS)
 * and applies it to the given Mat */
void SST_Math_Mat44fCreateEulerYC(SST_Mat44f* Mat, const float angle)
{
#define Mat(i,j) Mat->v[i+4*j]
		float cosv = cosf(angle);
		float sinv = sinf(angle);
		float t[8];
		int i;
		t[0] = sinv*Mat(2,0);
		t[1] = sinv*Mat(2,1);
		t[2] = sinv*Mat(2,2);
		t[3] = sinv*Mat(2,3);

		t[4] = -sinv*Mat(0,0);
		t[5] = -sinv*Mat(0,1);
		t[6] = -sinv*Mat(0,2);
		t[7] = -sinv*Mat(0,3);

		for(i=0;i<4;i++)
				Mat(0,i) = cosv*Mat(0,i)+t[i];
		for(i=0;i<4;i++)
				Mat(2,i) = cosv*Mat(2,i)+t[i+4];
#undef Mat
}
void SST_Math_Mat44fCreateEulerZC(SST_Mat44f* Mat, const float angle)
{
#define Mat(i,j) Mat->v[i+4*j]
		float cosv = cosf(angle);
		float sinv = sinf(angle);
		float t[8];
		int i;
		t[0] = -sinv*Mat(1,0);
		t[1] = -sinv*Mat(1,1);
		t[2] = -sinv*Mat(1,2);
		t[3] = -sinv*Mat(1,3);

		t[4] = sinv*Mat(0,0);
		t[5] = sinv*Mat(0,1);
		t[6] = sinv*Mat(0,2);
		t[7] = sinv*Mat(0,3);

		for(i=0;i<4;i++)
				Mat(0,i) = cosv*Mat(0,i)+t[i];
		for(i=0;i<4;i++)
				Mat(1,i) = cosv*Mat(1,i)+t[i+4];
#undef Mat
}
/* Forms the Shear Mat described as:
 * X' = M * X
 * where M = I + ShearX + ShearY + ShearZ
 * shearing[0:1] -- x in y, x in z
 * shearing[2:3] -- y in x, y in z
 * shearing[4:5] -- z in x, z in y
 */
void SST_Math_Mat44fCreateShear(SST_Mat44f* Mat, const float x_in_y, const float x_in_z, const float y_in_x, const float y_in_z, const float z_in_x, const float z_in_y)
{
#define Mat(i,j) Mat->v[i+4*j]
		Mat(0,0) = 1.0;
		Mat(1,0) = y_in_x;
		Mat(2,0) = z_in_x;
		Mat(3,0) = 0.0;

		Mat(0,1) = x_in_y;
		Mat(1,1) = 1.0;
		Mat(2,1) = z_in_y;
		Mat(3,1) = 0.0;

		Mat(0,2) = x_in_z;
		Mat(1,2) = y_in_z;
		Mat(2,2) = 1.0;
		Mat(3,2) = 0.0;

		Mat(0,3) = 0.0;
		Mat(1,3) = 0.0;
		Mat(2,3) = 0.0;
		Mat(3,3) = 1.0;
#undef Mat
}
/* Forms the Free Transform Mat described as:
 * X' = M * X
 * where M = ScaleM + Shear_forX + Shear_forY + Shear_forZ
 * scale[0:2] -- scale x,y,z
 * shearing[0:1] -- x in y, x in z
 * shearing[2:3] -- y in x, y in z
 * shearing[4:5] -- z in x, z in y
 */
void SST_Math_Mat44fCreateFreeTransform(SST_Mat44f* Mat,const float scale_x, const float scale_y, const float scale_z, const float x_in_y, const float x_in_z, const float y_in_x, const float y_in_z, const float z_in_x, const float z_in_y)
{
#define Mat(i,j) Mat->v[i+4*j]
		Mat(0,0) = scale_x;
		Mat(1,0) = y_in_x;
		Mat(2,0) = z_in_x;
		Mat(3,0) = 0.0;

		Mat(0,1) = x_in_y;
		Mat(1,1) = scale_y;
		Mat(2,1) = z_in_y;
		Mat(3,1) = 0.0;

		Mat(0,2) = x_in_z;
		Mat(1,2) = y_in_z;
		Mat(2,2) = scale_z;
		Mat(3,2) = 0.0;

		Mat(0,3) = 0.0;
		Mat(1,3) = 0.0;
		Mat(2,3) = 0.0;
		Mat(3,3) = 1.0;
#undef Mat
}

void SST_Math_Mat44fConvertQuaternion(SST_Mat44f* Mat,const SST_Vec4f* q)
{
	/* From Wikipedia - 8/30/2012 */
#define Mat(i,j) Mat->v[i+4*j]
	Mat(0,0) =  q->x;
	Mat(1,0) = -q->y;
	Mat(2,0) = -q->z;
	Mat(3,0) = -q->w;

	Mat(0,1) =  q->y;
	Mat(1,1) =  q->x;
	Mat(2,1) =  q->w;
	Mat(3,1) = -q->z;

	Mat(0,2) =  q->z;
	Mat(1,2) = -q->w;
	Mat(2,2) =  q->x;
	Mat(3,2) =  q->y;

	Mat(0,3) =  q->w;
	Mat(1,3) =  q->z;
	Mat(2,3) = -q->y;
	Mat(3,3) =  q->x;
#undef Mat
}
void SST_Math_Mat44fCreateRotationFromQuaternion(SST_Mat44f* Mat,const SST_Vec4f* q)
{
	/* From Wikipedia - 8/30/2012 */
#define Mat(i,j) Mat->v[i+4*j]
	const float norm = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
	const float a = q->x / norm;
	const float b = q->y / norm;
	const float c = q->z / norm;
	const float d = q->w / norm;
	Mat(0,0) =  a*a + b*b - c*c - d*d;
	Mat(1,0) =  2.f * (b*c+a*d);
	Mat(2,0) =  2.f * (b*d-a*c);
	Mat(3,0) =  0.f;

	Mat(0,1) =  2.f * (b*c-a*d);
	Mat(1,1) =  a*a - b*b + c*c - d*d;
	Mat(2,1) =  2.f * (c*d-a*b);
	Mat(3,1) =  0.f;

	Mat(0,2) =  2.f * (b*d + a*c);
	Mat(1,2) =  2.f * (c*d - a*b);
	Mat(2,2) =  a*a-b*b-c*c+d*d;
	Mat(3,2) =  0.f;

	Mat(0,3) =  0.f;
	Mat(1,3) =  0.f;
	Mat(2,3) =  0.f;
	Mat(3,3) =  1.f;
#undef Mat
}

void SST_Math_Mat44fCreateScale(SST_Mat44f* Mat, const float scale_x, const float scale_y, const float scale_z)
{
	memset(Mat, 0, sizeof(SST_Mat44f));
	Mat->v[0]  = scale_x;	
	Mat->v[5]  = scale_y;	
	Mat->v[10] = scale_z;	
	Mat->v[15] = 1;
}


void SST_Math_Mat44fCreateLookAt(SST_Mat44f* Mat, const SST_Vec3f* eye,const SST_Vec3f* at, const SST_Vec3f* up)
{
#define Mat(i,j) Mat->v[i+4*j]
		int i;
		SST_Vec3f F;
		SST_Vec3f UP;
		SST_Vec3f s;
		SST_Vec3f u;
		SST_Mat44f tmp;

		SST_Math_Vec3fNormalize(up,&UP);
		SST_Math_Vec3fSubtract(at,eye,&F);
		SST_Math_Vec3fNormalizeLocal(&F);
		SST_Math_Vec3fCross(&F,&UP,&s);
		SST_Math_Vec3fCross(&s,&F,&u);

		for(i=0;i<3;i++)
		{
				Mat(0,i) = s.v[i];
				Mat(1,i) = u.v[i];
				Mat(2,i) = -F.v[i];
				Mat(3,i) = 0.0f;
		}


		Mat(0,3) = 0;
		Mat(1,3) = 0;
		Mat(2,3) = 0;
		Mat(3,3) = 1.f;

		/* Multiply by translation matrix */
		SST_Math_Mat44fCreateTranslation(&tmp, -eye->x, -eye->y, -eye->z);
		SST_Math_Mat44fMultiplyMatrixLocal(Mat, &tmp);


#undef Mat
}

void SST_Math_Mat44fCreateLookDir(SST_Mat44f* Mat, const SST_Vec3f* eye,const SST_Vec3f* dir, const SST_Vec3f* up)
{
#define Mat(i,j) Mat->v[i+4*j]
		int i;
		SST_Vec3f F;
		SST_Vec3f UP;
		SST_Vec3f s;
		SST_Vec3f u;
		SST_Vec3f at;
		SST_Mat44f tmp;

		SST_Math_Vec3fAdd(eye,dir,&at);
		SST_Math_Vec3fNormalize(up,&UP);
		SST_Math_Vec3fSubtract(&at,eye,&F);
		SST_Math_Vec3fNormalizeLocal(&F);
		SST_Math_Vec3fCross(&F,&UP,&s);
		SST_Math_Vec3fCross(&s,&F,&u);

		for(i=0;i<3;i++)
		{
				Mat(0,i) = s.v[i];
				Mat(1,i) = u.v[i];
				Mat(2,i) = -F.v[i];
				Mat(3,i) = 0.0f;
		}
		Mat(0,3) = 0;
		Mat(1,3) = 0;
		Mat(2,3) = 0;
		Mat(3,3) = 1.f;

		/* Multiply by translation matrix */
		SST_Math_Mat44fCreateTranslation(&tmp, -eye->x, -eye->y, -eye->z);
		SST_Math_Mat44fMultiplyMatrixLocal(Mat, &tmp);

#undef Mat
}

/* Extracts the 3x3 matrix most used from Geo routines from a 4x4 matrix */
void SST_Math_Mat33fCreateFromMat44f(const SST_Mat44f* Mat44, SST_Mat33f* Mat33)
{
#define Mat33(i,j) Mat33->v[i+3*j]
#define Mat44(i,j) Mat44->v[i+4*j]
	int i;
	for(i=0;i<3;i++)
	{
			Mat33(i,0) = Mat44(i,0);
			Mat33(i,1) = Mat44(i,1);
			Mat33(i,2) = Mat44(i,2);
	}
#undef Mat33
#undef Mat44
}
void SST_Math_Mat44fCreatePerspective(SST_Mat44f* Mat, const float FOV_in_y, const float aspect_in_x, const float zNear, const float zFar)
{
#define Mat(i,j) Mat->v[i + 4*j]
	const float f = tanf(((float)M_PI_2) - FOV_in_y * ((float)M_PI) / 360.f);
	memset(Mat, 0, sizeof(SST_Mat44f));
	Mat(0,0) = f/aspect_in_x;
	Mat(1,1) = f;
	Mat(2,2) = (zFar+zNear)/(zNear-zFar);
	Mat(3,2) = -1.f;
	Mat(2,3) = (2.f * zFar * zNear)/(zNear-zFar);
#undef Mat
}
void SST_Math_Mat44fCreateOrtho(SST_Mat44f* Mat, const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
{
#define Mat(i,j) Mat->v[i + 4*j]
	const float rl = right - left;
	const float tb = top - bottom;
	const float fn = farVal - nearVal;
	memset(Mat, 0, sizeof(SST_Mat44f));
	Mat(0,0) =  2.f/rl;
	Mat(1,1) =  2.f/tb;
	Mat(2,2) = -2.f/fn;

	Mat(0,3) = -(right+left)/rl;
	Mat(1,3) = -(top+bottom)/tb; 
	Mat(2,3) = -(farVal+nearVal)/fn; 
	Mat(3,3) =  1.f;
#undef Mat
}
void SST_Math_Mat33fHomogenousMultiplyAssumed(const SST_Mat33f* Mat,const SST_Vec2f* VecIn, SST_Vec2f* VecOut)
{
#define Mat(i,j) Mat->v[i + 3*j]
#define VI(i) VecIn->v[i]
	float recipz;
	recipz = 1.f / (Mat(2,0)*VI(0) + Mat(2,1) * VI(1) + Mat(2,2));
	VecOut->v[0] = recipz*(Mat(0,0)*VI(0) + Mat(0,1) * VI(1) + Mat(0,2));
	VecOut->v[1] = recipz*(Mat(1,0)*VI(0) + Mat(1,1) * VI(1) + Mat(1,2));
#undef Mat
#undef VI
}

void SST_Math_Mat33fHomogenousMultiplyAssumedLocal(const SST_Mat33f* Mat, SST_Vec2f* Vec)
{
#define Mat(i,j) Mat->v[i + 3*j]
#define VI(i) Vec->v[i]
	float tmp,tmp2,recipz;
	tmp = Mat(0,0)*VI(0) + Mat(0,1) * VI(1) + Mat(0,2);
	tmp2 = Mat(1,0)*VI(0) + Mat(1,1) * VI(1) + Mat(1,2);
	recipz = 1.f / (Mat(2,0)*VI(0) + Mat(2,1) * VI(1) + Mat(2,2));
	VI(0) = tmp * recipz;
	VI(1) = tmp2 * recipz;
#undef Mat
#undef VI
}
