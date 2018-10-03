/*
* @Author: 1uci3n
* @Date:   2018-09-21 15:54:36
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-10-01 20:23:02
*/
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