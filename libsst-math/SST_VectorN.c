#include <SST/SST_VectorN.h>
#include <math.h>
#include <string.h>

float  SST_VectorNf_Magnitude(const int N, const float* _in)
{
		int i;
	float sum = 0.f;
	for(i = 0; i < N; i++)
			sum += _in[i] * _in[i];
	return sqrt(sum);
}

float  SST_VectorNf_MagnitudeSquared(const int N, const float* _in)
{
		int i;
	float sum = 0.f;
	for(i = 0; i < N; i++)
			sum += _in[i] * _in[i];
	return sum;
}

float  SST_VectorNf_L1Norm(const int N, const float* _in)
{
		int i;
	float sum = 0.f;
	for(i = 0; i < N; i++)
			sum += _in[i];
	return sum;
}

float  SST_VectorNf_Dot(const int N, const float* _a, const float* _b)
{
		int i;
	float sum = 0.f;
	for(i = 0; i < N; i++)
			sum += _a[i]*_b[i];
	return sum;
}

float* SST_VectorNf_Normalize(const int N, const float* _in, float* _out)
{
	float scalar = 1.f/SST_VectorNf_Magnitude(N,_in);
	return SST_VectorNf_Scale(N,_in,scalar,_out);
}

float* SST_VectorNf_NormalizeLocal(const int N,  float* _inout)
{
	float scalar = 1.f/SST_VectorNf_Magnitude(N,_inout);
	return SST_VectorNf_ScaleLocal(N,_inout,scalar);
}

float* SST_VectorNf_Add(const int N, const float* _a, const float* _b, float* _out)
{
	int i;
	for(i = 0; i < N; i++)
			_out[i] = _a[i]+_b[i];
	return _out;
}

float* SST_VectorNf_Subtract(const int N, const float* _a, const float* _b, float* _out)
{
		int i;
	for(i = 0; i < N; i++)
			_out[i] = _a[i]-_b[i];
	return _out;
}

float* SST_VectorNf_AddLocal(const int N, float* _a, const float* _b)
{
		int i;
	for(i = 0; i < N; i++)
			_a[i]+=_b[i];
	return _a;
}

float* SST_VectorNf_Cross(const int N, const float* _a, const float* _b, float* _out)
{
		if(N==2) {
				_out[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				_out[0] =  _a[1]*_b[2] - _a[2]*_b[1];
				_out[1] =-(_a[0]*_b[2] - _a[2]*_b[0]);
				_out[2] =  _a[0]*_b[1] - _a[1]*_b[0];

		} else {
				/* do nothing */
		}
		return _out;
}

float* SST_VectorNf_CrossLocal(const int N, float* _a, const float* _b)
{
		if(N==2) {
				_a[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				float tmp[3] = {

				  _a[1]*_b[2] - _a[2]*_b[1],
				-(_a[0]*_b[2] - _a[2]*_b[0]),
				  _a[0]*_b[1] - _a[1]*_b[0]};

				_a[0]=tmp[0];
				_a[1]=tmp[1];
				_a[2]=tmp[2];

		} else {
				/* do nothing */
		}
		return _a;
}

float* SST_VectorNf_Scale(const int N, const float* _a, const float _scale, float* _out)
{
		int i;
	for(i = 0; i < N; i++)
			_out[i]= _scale * _a[i];
	return _out;
}

float* SST_VectorNf_ScaleLocal(const int N, float* _a, const float _scale)
{
		int i;
	for(i = 0; i < N; i++)
			_a[i]*=_scale;
	return _a;
}

float* SST_VectorNf_RotateAbout(const int N, const float* _a, const float* _about,float _theta, float* _out)
{
		if(N==2) {
				_out[0] = _a[0];
				_out[1] = _a[1];

		} else if(N==3){
				float tmp[4] = {_about[0],_about[1],_about[2],0};
				float scalar = (1.0-cos(_theta)) * SST_VectorNf_Dot(3,_about,_a);
				SST_VectorNf_Scale(3,tmp,scalar,_out);
				SST_VectorNf_Cross(3,_about,_a,tmp);
				SST_VectorNf_ScaleLocal(3,tmp,sin(_theta));
				SST_VectorNf_AddLocal(3,_out,tmp);
				SST_VectorNf_Scale(3,_a,cos(_theta),tmp);
				SST_VectorNf_AddLocal(3,_out,tmp);
		} else {
				int i;
				for(i = 0; i < N; i++)
						_out[i] = _a[i];
		}
		return _out;
}

float*  SST_VectorNf_Project(const int N, const float* _a, const float* _b, float* _out)
{
		float scalar = SST_VectorNf_Dot(N,_a,_b) / SST_VectorNf_Dot(N,_b,_b);
		SST_VectorNf_Scale(N, _b, scalar, _out);
		return _out;
}

float*  SST_VectorNf_ProjectLocal(const int N, float* _a, const float* _b)
{
		float scalar = SST_VectorNf_Dot(N,_a,_b) / SST_VectorNf_Dot(N,_b,_b);
		SST_VectorNf_Scale(N, _b, scalar, _a);
		return _a;
}

float* SST_VectorNf_Bias(const int N, const float* a, const float bias, float* out)
{
		int i;
		for(i = 0; i < N; i++)
				out[i] = a[i]+bias;
		return out;
}

float* SST_VectorNf_RotateAboutLocal(const int N, float* _a, const float* _about,float _theta)
{
		int i;
		float tmp2[N];
		if(N==2) {
				tmp2[0] = _a[0];
				tmp2[1] = _a[1];
		} else if(N==3){
				float tmp[4] = {_about[0],_about[1],_about[2],0};
				float scalar = (1.0-cos(_theta)) * SST_VectorNf_Dot(3,_about,_a);
				SST_VectorNf_Scale(3,tmp,scalar,tmp2);
				SST_VectorNf_Cross(3,_about,_a,tmp);
				SST_VectorNf_ScaleLocal(3,tmp,sin(_theta));
				SST_VectorNf_AddLocal(3,tmp2,tmp);
				SST_VectorNf_Scale(3,_a,cos(_theta),tmp);
				SST_VectorNf_AddLocal(3,tmp2,tmp);
		} else {
				for(i = 0; i < N; i++)
						tmp2[i] = _a[i];
		}
		for(i = 0; i < N; i++)
				_a[i] = tmp2[i];

		return _a;
}

double  SST_VectorNd_Magnitude(const int N, const double* _in)
{
		int i;
	double sum = 0.0;
	for(i = 0; i < N; i++)
			sum += _in[i] * _in[i];
	return sqrt(sum);
}

double  SST_VectorNd_MagnitudeSquared(const int N, const double* _in)
{
		int i;
	double sum = 0.0;
	for(i = 0; i < N; i++)
			sum += _in[i] * _in[i];
	return sum;
}

double  SST_VectorNd_L1Norm(const int N, const double* _in)
{
		int i;
	double sum = 0.0;
	for(i = 0; i < N; i++)
			sum += _in[i];
	return sum;
}

double  SST_VectorNd_Dot(const int N, const double* _a, const double* _b)
{
	int i;
	double sum = 0.0;
	for(i = 0; i < N; i++)
			sum += _a[i]*_b[i];
	return sum;
}

double* SST_VectorNd_Normalize(const int N, const double* _in, double* _out)
{
	double scalar = 1.0/SST_VectorNd_Magnitude(N,_in);
	return SST_VectorNd_Scale(N,_in,scalar,_out);
}

double* SST_VectorNd_NormalizeLocal(const int N,  double* _inout)
{
	double scalar = 1.0/SST_VectorNd_Magnitude(N,_inout);
	return SST_VectorNd_ScaleLocal(N,_inout,scalar);
}

double* SST_VectorNd_Add(const int N, const double* _a, const double* _b, double* _out)
{
		int i;
	for(i = 0; i < N; i++)
			_out[i] = _a[i]+_b[i];
	return _out;
}

double* SST_VectorNd_Subtract(const int N, const double* _a, const double* _b, double* _out)
{
		int i;
	for(i = 0; i < N; i++)
			_out[i] = _a[i]-_b[i];
	return _out;
}

double* SST_VectorNd_AddLocal(const int N, double* _a, const double* _b)
{
	int i;
	for(i = 0; i < N; i++)
			_a[i]+=_b[i];
	return _a;
}

double* SST_VectorNd_Cross(const int N, const double* _a, const double* _b, double* _out)
{
		if(N==2) {
				_out[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				_out[0] =  _a[1]*_b[2] - _a[2]*_b[1];
				_out[1] =-(_a[0]*_b[2] - _a[2]*_b[0]);
				_out[2] =  _a[0]*_b[1] - _a[1]*_b[0];
		} else {
				/* do nothing */
		}
		return _out;
}

double* SST_VectorNd_CrossLocal(const int N, double* _a, const double* _b)
{
		if(N==2) {
				_a[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				double tmp[3] = {
						_a[1]*_b[2] - _a[2]*_b[1],
				-(_a[0]*_b[2] - _a[2]*_b[0]),
				  _a[0]*_b[1] - _a[1]*_b[0]};
				_a[0]=tmp[0];
				_a[1]=tmp[1];
				_a[2]=tmp[2];
		} else {
				/* do nothing */
		}
		return _a;
}

double* SST_VectorNd_Scale(const int N, const double* _a, const double _scale, double* _out)
{
		int i;
	for(i = 0; i < N; i++)
			_out[i]= _scale * _a[i];
	return _out;
}

double* SST_VectorNd_ScaleLocal(const int N, double* _a, const double _scale)
{
		int i;
	for(i = 0; i < N; i++)
			_a[i]*=_scale;
	return _a;
}

double* SST_VectorNd_RotateAbout(const int N, const double* _a, const double* _about,double _theta, double* _out)
{
		if(N==3) {
				double  tmp[4] = {_about[0],_about[1],_about[2],0};
				double scalar = (1.0-cos(_theta)) * SST_VectorNd_Dot(3,_about,_a);
				SST_VectorNd_Scale(3,tmp,scalar,_out);
				SST_VectorNd_Cross(3,_about,_a,tmp);
				SST_VectorNd_ScaleLocal(3,tmp,sin(_theta));
				SST_VectorNd_AddLocal(3,_out,tmp);
				SST_VectorNd_Scale(3,_a,cos(_theta),tmp);
				SST_VectorNd_AddLocal(3,_out,tmp);
		} else {
				memset(_out,0,N*sizeof(double));
		}
		return _out;
}

double* SST_VectorNd_RotateAboutLocal(const int N, double* _a, const double* _about,double _theta)
{
		int i;
		double tmp2[N];
		if(N==2) {
				tmp2[0] = _a[0];
				tmp2[1] = _a[1];
		} else if(N==3){
				double tmp[4] = {_about[0],_about[1],_about[2],0};
				double scalar = (1.0-cos(_theta)) * SST_VectorNd_Dot(3,_about,_a);
				SST_VectorNd_Scale(3,tmp,scalar,tmp2);
				SST_VectorNd_Cross(3,_about,_a,tmp);
				SST_VectorNd_ScaleLocal(3,tmp,sin(_theta));
				SST_VectorNd_AddLocal(3,tmp2,tmp);
				SST_VectorNd_Scale(3,_a,cos(_theta),tmp);
				SST_VectorNd_AddLocal(3,tmp2,tmp);
		} else {
				for(i = 0; i < N; i++)
						tmp2[i] = _a[i];
		}
		for(i = 0; i < N; i++)
				_a[i] = tmp2[i];

		return _a;
}

int  SST_VectorNi_MagnitudeSquared(const int N, const int* _in)
{
	int i;
	int sum = 0;
	for(i = 0; i < N; i++)
			sum=_in[i]*_in[i];
	return sum;
}

int  SST_VectorNi_Dot(const int N, const int* _a, const int* _b)
{
	int i;
	int sum = 0;
	for(i = 0; i < N; i++)
			sum=_a[i]*_b[i];
	return sum;
}

int*  SST_VectorNi_Add(const int N, const int* _a, const int* _b, int* _out)
{
	int i;
	for(i = 0; i < N; i++)
			_out[i]=_a[i]+_b[i];
	return _out;
}

int*  SST_VectorNi_Subtract(const int N, const int* _a, const int* _b, int* _out)
{
	int i;
	for(i = 0; i < N; i++)
			_out[i]=_a[i]-_b[i];
	return _out;
}

int*  SST_VectorNi_AddLocal(const int N, int* _a, const int* _b)
{
	int i;
	for(i = 0; i < N; i++)
			_a[i]+=_b[i];
	return _a;
}

int*  SST_VectorNi_Cross(const int N, const int* _a, const int* _b, int* _out)
{
		if(N==2) {
				_out[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				_out[0] =  _a[1]*_b[2] - _a[2]*_b[1];
				_out[1] =-(_a[0]*_b[2] - _a[2]*_b[0]);
				_out[2] =  _a[0]*_b[1] - _a[1]*_b[0];

		} else {
				/* do nothing */
		}
		return _out;
}

int*  SST_VectorNi_CrossLocal(const int N, int* _a, const int* _b)
{
		if(N==2) {
				_a[0] = _a[0]*_b[1] - _a[1]*_b[0];
		} else if(N==3) {
				int tmp[3] = {
				  _a[1]*_b[2] - _a[2]*_b[1],
				-(_a[0]*_b[2] - _a[2]*_b[0]),
				  _a[0]*_b[1] - _a[1]*_b[0]};
				_a[0]=tmp[0];
				_a[1]=tmp[1];
				_a[2]=tmp[2];
		} else {
				/* do nothing */
		}
		return _a;
}

int*  SST_VectorNi_Scale(const int N, const int* _a, const int _scale, int* _out)
{
		int i;
		for(i = 0; i < N; i++)
				_out[i] = _scale * _a[i];
		return _out;
}

int*  SST_VectorNi_ScaleLocal(const int N, int* _a, const int _scale)
{
		int i;
		for(i = 0; i < N; i++)
				_a[i]*=_scale;
		return _a;
}
