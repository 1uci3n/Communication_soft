#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>


using namespace std;


//				NumberSystemTools.cpp
/**
 * 将十进制数转化为二进制,并用Vector存储,Vector每一个维度代表一个二进制位
 * (10進数を2進数に変換してVectorに格納する。Vectorの各次元は2進ビットを表す)
 * [decimalIntToBinaryVector description]
 * @param  decimal   十进制数(10進数)
 * @param  msgLength 返回的Vector长度(返されたベクトルの長さ)
 * @return           目标Vector(ターゲットベクター)
 */
vector<int> decimalIntToBinaryVector(int decimal,int msgLength);