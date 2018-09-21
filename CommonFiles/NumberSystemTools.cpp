#include "CommonFiles.h"

vector<int> decimalIntToBinaryVector(int decimal,int msgLength){
	vector<int> binary(msgLength, 0);
	int remain = decimal;
	for (int i = msgLength - 1; i >= 0; --i)
	{
		binary[msgLength - i - 1] = remain / pow(2, i);
		remain = remain - (binary[msgLength - i - 1] * pow(2, i));
	}
	return binary;
}