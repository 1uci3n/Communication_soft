/*
* @Author: 1uci3n
* @Date:   2018-05-21 12:37:19
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-09 17:28:03
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
//使用map方便插值与更新,vector需要区分插值和更新
static map<int, double> lTotalJ;
static map<int, double> preLTotalJ;

static map<int, int> vJ;

/**
 * doSumproduct (for BI-AWGN channel)
 * @param  receivedBlock     [description]
 * @param  parityCheckMatrix [description]
 * @param  sigmaSquare       [description]
 * @return                   [description]
 */
vector<int> doSumproduct(vector<double> receivedBlock, vector<vector<int> > parityCheckMatrix, double sigmaSquare){
	sPCMatrix = parityCheckMatrix;
	initialization(receivedBlock, sigmaSquare);
	int loopCounter = 0;
	do{
		checkNodesUpdate();
		variableNodesUpdate();
		lLRTotal();
		loopCounter++;
	} while(!stoppingCriteria(loopCounter));
	vector<int> result = transMapToVector(vJ);
	result = cutBlockForHamming(result);
	clearAllStatic();
	return result;
}

void initialization(vector<double> receivedBlock, double sigmaSquare){
	//1
	vector<double>::iterator iter = lJ.end();
	for (int i = 0; i < receivedBlock.size(); ++i)
	{
		lJ.insert(iter, calcuBIAWGNChannelLLR(receivedBlock[i], sigmaSquare));
		iter = lJ.end();
	}
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
}

void checkNodesUpdate(){
	vector<int> keyForJI;
	vector<int> keyForIJ;
	double totalProduct = 1;
	double tempResult;
	for (int i = 0; i < sPCMatrix.size(); ++i)
	{
		for (int j = 0; j < sPCMatrix[0].size(); ++j)
		{
			if (sPCMatrix[i][j] == 1)
			{
				for (int k = 0; k < sPCMatrix[0].size(); ++k)
				{
					keyForJI.insert(keyForJI.end(), k);
					keyForJI.insert(keyForJI.end(), i);
					if(lJI[keyForJI] != 0){
						totalProduct *= tanh(lJI[keyForJI] / 2);
					}
					keyForJI.clear();
				}
				keyForJI.insert(keyForJI.end(), j);
				keyForJI.insert(keyForJI.end(), i);
				totalProduct /= tanh(lJI[keyForJI] / 2);
				keyForJI.clear();
				tempResult = 2 * atanh(totalProduct);
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
	vector<int> keyForIJ;
	vector<int> keyForJI;
	double summation = 0;
	double tempResult;
	for (int j = 0; j < sPCMatrix[0].size(); ++j)
	{
		for (int i = 0; i < sPCMatrix.size(); ++i)
		{
			if (sPCMatrix[i][j] == 1)
			{
				for (int k = 0; k < sPCMatrix.size(); ++k)
				{
					keyForIJ.insert(keyForIJ.end(), k);
					keyForIJ.insert(keyForIJ.end(), j);
					summation += lIJ[keyForIJ];
					keyForIJ.clear();
				}
				keyForIJ.insert(keyForIJ.end(), i);
				keyForIJ.insert(keyForIJ.end(), j);
				summation -= lIJ[keyForIJ];
				keyForIJ.clear();
				tempResult = lJ[j] + summation;
				keyForJI.insert(keyForJI.end(), j);
				keyForJI.insert(keyForJI.end(), i);
				lJI[keyForJI] = tempResult;
				keyForJI.clear();
				summation = 0;
			}
		}
	}
}

void lLRTotal(){
	vector<int> keyForIJ;
	double tempSummation = 0;
	for (int j = 0; j < sPCMatrix[0].size(); ++j)
	{
		for (int i = 0; i < sPCMatrix.size(); ++i)
		{
			keyForIJ.insert(keyForIJ.end(), i);
			keyForIJ.insert(keyForIJ.end(), j);
			tempSummation += lIJ[keyForIJ];
			keyForIJ.clear();
		}
		lTotalJ[j] = lJ[j] + tempSummation;
		tempSummation = 0;
	}
}

bool stoppingCriteria(int loopCounter){
	if(loopCounter < MAX_LOOP_NUMBER){
		vJ = lTotalChanger(lTotalJ);
		if (lTotalJ == preLTotalJ)
		{
			return true;
		}
		preLTotalJ = lTotalJ;
		return false;
	} else {
		return true;
	}
}

void clearAllStatic(){
	variableNodes.clear();
	checkNodes.clear();
	sPCMatrix.clear();
	lJ.clear();
	lJI.clear();
	lIJ.clear();
	lTotalJ.clear();
	preLTotalJ.clear();
	vJ.clear();
}