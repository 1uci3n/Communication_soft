/*
* @Author: 1uci3n
* @Date:   2018-05-21 13:00:51
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-08 20:33:39
*/
#include "LDPCCode.h"

using namespace std;

vector<vector<int> > setCheckMatrix(){
	vector<int> j(7);
	vector<vector<int> > matrix;
	j[0] = 1, j[1] = 0, j[2] = 1, j[3] = 0, j[4] = 1, j[5] = 0, j[6] = 1;
	matrix.insert(matrix.end(), j);
	j[0] = 1, j[1] = 1, j[2] = 1, j[3] = 0, j[4] = 0, j[5] = 1, j[6] = 1;
	matrix.insert(matrix.end(), j);
	j[0] = 0, j[1] = 0, j[2] = 0, j[3] = 1, j[4] = 1, j[5] = 1, j[6] = 1;
	matrix.insert(matrix.end(), j);
	return matrix;
}

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
	vector<vector<int> > parityCheckMatrix = setCheckMatrix();
	doSumproduct(yBlock, parityCheckMatrix, sigmaSquare);
	// initialization(yBlock, sigmaSquare);
	return 0;
}

