/*
* @Author: 1uci3n
* @Date:   2018-05-21 12:37:19
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-05-22 12:25:19
*/
#include "LDPCCode.h"

using namespace std;

static vector<double> vNodes;

void sPrint(){
	vNodes.insert(vNodes.end(), 1);
	cout << "succeed" << endl;
	cout << vNodes[0] << endl;
}