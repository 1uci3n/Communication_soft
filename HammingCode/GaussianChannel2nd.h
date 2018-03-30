//#include "channel.h"
//
#define ENCODE_R 4/7

using namespace std;

double gaussrand()
{
	double V1(0), V2(0), S(0);
	int phase = 0;
	double x(0);

	if (phase == 0)
	{
		do
		{
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;
			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		x = V1 * sqrt(-2 * log(S) / S);
	}
	else
		x = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	return x;
}

vector<double> BPSK_AWGNC(vector<int> input, double variance)
{
	vector<double> output;

	for (vector<int>::size_type i = 0; i != input.size(); ++i)
	{
		double t = (double)(1 - 2 * input[i]) + sqrt(variance) * gaussrand();
		output.push_back(t);
	}

	return output;
}

double getVarianceBySNR(double SNR){
	//cout << 1 / ((double) 2 * ENCODE_R * SNR) << endl;
	return 1 / ((double) 2 * ENCODE_R * SNR);
}

double getVarianceBySNRdB(double SNRdB){
	return getVarianceBySNR(pow(10, SNRdB / 10));
}
