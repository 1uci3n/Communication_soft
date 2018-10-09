/*
* @Author: 1uci3n
* @Date:   2018-10-01 19:02:14
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-10-09 17:12:12
*/

#include "OutputHammingCodeSample.h"



int main(int argc, char const *argv[])
{
	int sampleCount = pow(2, CODE_BIT_LENGTH);
	vector<int> msg, block;
	vector<vector<int> > msgOutPutList;
	vector<vector<int> > blockOutPutList;
	vector<vector <int> >::iterator msgIter = msgOutPutList.end();
	vector<vector <int> >::iterator blockIter = blockOutPutList.end();
	for (int i = 0; i < sampleCount; ++i)
	{
		msg = decimalIntToBinaryVector(i, 11);
		printVector(msg);
		block = encode(msg);
		printVector(block);
		msgOutPutList.insert(msgIter, msg);
		blockOutPutList.insert(blockIter, block);
		msgIter = msgOutPutList.end();
		blockIter = blockOutPutList.end();
	}
	char labelFileName[] = "label.dat";
	outputList(msgOutPutList, labelFileName);
	char blockFileName[] = "block.dat";
	outputList(blockOutPutList, blockFileName);
	return 0;
}