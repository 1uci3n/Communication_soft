/*
* @Author: 1uci3n
* @Date:   2018-05-22 12:31:47
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-08 20:06:53
*/
#include "LDPCCode.h"

/**
 * [calcuBIAWGNChannelLLR description]
 * @param  sigmaSquare [description]
 * @param  input x = 1 v = 0;x = -1 v = 1
 * @return       [description]
 */
double calcuBIAWGNChannelLLR(double sigmaSquare, double input){
	return (2 * input) / sigmaSquare;
}

map<int, int> lTotalChanger(map<int, double> lTotal){
	map<int, int> result;
	int key;
	double value;
	map<int, double>::iterator itForlTotal;
	itForlTotal = lTotal.begin();
	while(itForlTotal != lTotal.end())
	{
		key = itForlTotal->first;
		value = itForlTotal -> second;
		if(value < 0){
			result[key] = 1;
		} else {
			result[key] = 0;
		}
		itForlTotal++;
	}
	return result;
}

// vector analysisEdge(vector<vector<int> > parityCheckMatrix){

// }