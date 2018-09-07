/*
* @Author: 1uci3n
* @Date:   2018-05-21 12:37:19
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-06 18:19:40
*/
#include "LDPCCode.h"

using namespace std;

static vector<double> variableNodes;
static vector<double> checkNodes;
//例7,4汉明码
//  1234567j
//  
//1 1010101
//2 0110011
//3 0001111
//i
static vector<vector<int> > sPCMatrix;

static vector<double> lJ;
static map<vector<int>, double> lJI;
static map<vector<int>, double> lIJ;



void sPrint(){
	variableNodes.insert(variableNodes.end(), 1);
	cout << "succeed" << endl;
	cout << variableNodes[0] << endl;
}

/**
 * doSumproduct (for BI-AWGN channel)
 * @param  receivedBlock     [description]
 * @param  parityCheckMatrix [description]
 * @param  sigmaSquare       [description]
 * @return                   [description]
 */
vector<int> doSumproduct(vector<double> receivedBlock, vector<vector<int> > parityCheckMatrix, double sigmaSquare){
	sPCMatrix = parityCheckMatrix;
	cout << "before ini" << endl;
	initialization(receivedBlock, sigmaSquare);
	// codeNodesUpdate();
	// variableNodesUpdate();
	vector<int> result;
	return result;
}

/**
 * initialization decoder(for BI-AWGN channel)
 * @param receivedBlock [description]
 */
void initialization(vector<double> receivedBlock, double sigmaSquare){
	cout << "before 1" << endl;
	//1
	vector<double>::iterator iter = lJ.end();
	cout << "after iter " << endl;
	for (int i = 0; i < receivedBlock.size(); ++i)
	{
		cout << "first loop " << endl;
		lJ.insert(iter, calcuBIAWGNChannelLLR(receivedBlock[i], sigmaSquare));
		iter = lJ.end();
	}
	cout << "before 2" << endl;
	//2
	vector<int> keyForJI;
	for (int i = 0; i < sPCMatrix.size(); ++i)
	{
		for (int j = 0; j < sPCMatrix[0].size(); ++j)
		{
			if (sPCMatrix[i][j] == 1)
			{
				keyForJI.insert(keyForJI.end(), j);
				keyForJI.insert(keyForJI.end(), i);
				lJI.insert(pair<vector<int>, double >(keyForJI, lJ[j]));
				keyForJI.clear();
			}
		}
	}
	keyForJI.insert(keyForJI.end(), 2);
	keyForJI.insert(keyForJI.end(), 1);
	cout << lJI[keyForJI] << endl;
}

void checkNodesUpdate(){
	vector<int> keyForJI;
	vector<int> keyForIJ;
	map<vector<int>, double>::iterator itForJIMap;
	double totalProduct = 1;
	double tempResult;
	for (int i = 0; i < sPCMatrix.size(); ++i)
	{
		for (int j = 0; j < sPCMatrix[0].size(); ++j)
		{
			if (sPCMatrix[i][j] == 1)
			{
				// itForJIMap = lJI.begin();
				// while(itForJIMap != lJI.end())
				// {
				// 	//it->first;
				// 	itForJIMap -> second;
				// 	totalProduct *= tanh();
				// 	itForJIMap++;
				// }
				for (int k = 0; k < sPCMatrix[0].size; ++k)
				{
					keyForJI.insert(keyForIJ.end(), k);
					keyForJI.insert(keyForIJ.end(), i);
					totalProduct *= tanh(lJI[keyForJI] / 2);
					keyForJI.clear();
				}
				keyForJI.insert(keyForIJ.end(), j);
				keyForJI.insert(keyForIJ.end(), i);
				totalProduct /= tanh(lJI[keyForJI] / 2);
				tempResult = 
				keyForIJ.insert(keyForIJ.end(), i);
				keyForIJ.insert(keyForIJ.end(), j);
				lIJ[keyForIJ] = tempResult;
				keyForIJ.clear();
				totalProduct = 1;
			}
		}
	}
}

void variableNodesUpdate(){

}

void lLRTotal(){

}