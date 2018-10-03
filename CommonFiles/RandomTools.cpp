/*
* @Author: 1uci3n
* @Date:   2018-09-21 16:47:45
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-10-01 19:21:51
*/
#include "CommonFiles.h"

vector<int> getRandomMsg(int msgLength){
	vector<int> msg;
	//srand(time(NULL));
	int intMsg = rand() % ((int) pow(2, msgLength) - 1);
	msg = decimalIntToBinaryVector(intMsg, msgLength);
	return msg;
}



