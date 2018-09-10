#include"LDPCCode.h"

std::vector<int> getRandomMsg(int msgLength){
	std::vector<int> msg;
	//srand(time(NULL));
	int intMsg = rand() % ((int) pow(2, msgLength) - 1);
	msg = decimalIntToBinaryVector(intMsg, msgLength);
	return msg;
}



