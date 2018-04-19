#include<time.h>
#include<math.h>
#define limit	1e-100
#define R 4/7
#define Es 1
#define _USE_MATH_DEFINES
using namespace std;

vector<double> Gaussian_channel(vector<int> code,double n0)
{
	unsigned int i;
	double u1,u0;
	double gaussnoise;

	vector<double> Gaussuanword(code.size(),0);
	
	for(i= 0; i<code.size(); ++i)
	{
		u0 = (double)(rand() + 1) / ((double)RAND_MAX + 2);
		u1 = (double)(rand() + 1) / ((double)RAND_MAX + 2);
	
		if( u0 < limit) 
		{
			u0 = limit;
		}
		gaussnoise = sqrt( n0*log(1./u0) )*cos( 2*M_PI*u1 );

		//cout << "gaussnoise = " << gaussnoise << endl;
		Gaussuanword[i]=(2*code[i]-1)+gaussnoise;	
	}

	return Gaussuanword;
}

double getN0BySNR(double SNR){
	return Es / (SNR * R);
}

double getN0ByDbSNR(double DbSNR){
	return getN0BySNR(pow(10,DbSNR/10));
}