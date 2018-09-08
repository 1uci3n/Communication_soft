/*
* @Author: 1uci3n
* @Date:   2018-05-21 13:00:51
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-08 21:36:16
*/
#include "LDPCCode.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//设置随机函数需要用到的盐值
	srand((unsigned)time(NULL));
	cout << "test" << endl;
	vector<int> msg;
	msg.insert(msg.end(), 1);
	msg.insert(msg.end(), 1);
	msg.insert(msg.end(), 0);
	msg.insert(msg.end(), 1);
	vector<int> xBlock = encode(msg, 4);
	cout << "源码:";
	printVector(msg);
	cout << "传递的码:";
	printVector(xBlock);
	double sigmaSquare = getVarianceBySNRdB(3);
	vector<double> yBlock = BPSK_AWGNC(xBlock, sigmaSquare);
	cout << "接收码:";
	printVector(yBlock);
	vector<vector<int> > parityCheckMatrix = setHammingCheckMatrix();
	vector<int> result = doSumproduct(yBlock, parityCheckMatrix, sigmaSquare);
	cout << "解码结果:";
	printVector(result);
	return 0;
}

