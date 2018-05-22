/*
* @Author: 1uci3n
* @Date:   2018-05-21 12:37:19
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-05-22 14:46:06
*/
#include "LDPCCode.h"

using namespace std;

static vector<double> variableNodes;
static vector<double> checkNodes;
//内层为按行存储
static vector<vector<int> > sPCMatrix;


void sPrint(){
	variableNodes.insert(variableNodes.end(), 1);
	cout << "succeed" << endl;
	cout << variableNodes[0] << endl;
}

vector<int> doSumproduct(vector<double> receivedBlock, vector<vector<int> > parityCheckMatrix){
	sPCMatrix = parityCheckMatrix;
	initialization(receivedBlock);
	codeNodesUpdate();
	variableNodesUpdate();
	vector<int> result;
	return result;
}

void initialization(vector<double> receivedBlock){

	vector<double>::iterator iter = variableNodes.end();
}

void codeNodesUpdate(){

}

void variableNodesUpdate(){

}