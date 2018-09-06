/*
* @Author: 1uci3n
* @Date:   2018-05-22 12:31:47
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-09-06 14:42:52
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

// vector analysisEdge(vector<vector<int> > parityCheckMatrix){

// }