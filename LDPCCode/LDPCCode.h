#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <math.h>

#define MAX_LOOP_NUMBER 1000

using namespace std;

vector<int> doSumproduct(vector<double> receivedBlock, vector<vector<int> > parityCheckMatrix, double sigmaSquare);

/**
 * initialization decoder(for BI-AWGN channel)
 * @param receivedBlock [description]
 * @param sigmaSquare   [description]
 */
void initialization(vector<double> receivedBlock, double sigmaSquare);

void checkNodesUpdate();

void variableNodesUpdate();

void lLRTotal();

bool stoppingCriteria(int loopCounter);

void clearAllStatic();

//SumproductTools.cpp

double calcuBIAWGNChannelLLR(double sigmaSquare, double input);

map<int, int> lTotalChanger(map<int, double> lTotal);

vector<int> transMapToVector(map<int, int> map);

vector<vector<int> > setHammingCheckMatrix();

vector<int> cutBlockForHamming(vector<int> longBlock);
//
//
//
/**
 * 汉明码编码(hamming encode function)
 * 
 * @param  message   源消息(source message)
 * @param  msgLength 消息长度(message's length)
 * @return           返回编码后的块(the code block after encode)
 */
std::vector<int> encode(std::vector<int> message, int msgLength);

/**
 * 汉明码解码(hamming decode function)
 * 
 * @param  block       需要解码的块(the block which need decode)
 * @return             返回解码后的消息(the block after decode)
 */
std::vector<int> decode(std::vector<int> block);

/**
 * 汉明码解码(硬解码)(hamming hard decode function)
 * 
 * @param  block       需要解码的块(the block which need decode)
 * @param  blockLength 块的长度(the length of block)
 * @return             返回解码后的消息(the block after decode)
 */
std::vector<int> decodeHard(std::vector<double> block, int blockLength);

/**
 * 汉明码解码(最大似然度解码Maximum Likelihood Decode)
 * 
 * @param  block       需要解码的块(the block which need decode)
 * @param  blockLength 块的长度(the length of block)
 * @return             返回解码后的消息(the block after decode)
 */
std::vector<int> decodeMLD(std::vector<double> block, int msgLength);

/**
 * 根据消息长度计算目标块大小(Calculate target block size based on message length)
 * 
 * @param  msgLength 原消息大小(message's length)
 * @return           返回目标块大小(the size of target block)
 */
int getBlockLengthByMsgLength(int msgLength);

/**
 * 根据纠错位位数计算纠错位位置(Calculate the error correction bit position based on the number of error correction bits)
 * 
 * @param checkbitPosition 用来保存纠错位的数组(the array which hold error correction bits)
 * @param checkbitLength   纠错位位数(the number of error correction bits)
 */
void getCheckbitPositionByCheckbitLength(int *checkbitPosition, int checkbitLength);

/**
 * 根据块大小计算纠错位位数
 * 
 * @param  blockLength 块长度
 * @return             返回纠错位位数
 */
int getCheckbitLengthByBlockLength(int blockLength);

/**
 * [setEncodeMapByMsgLength description]
 * @param  msgLength [description]
 * @return           [description]
 */
void setEncodeMapByMsgLength(int msgLength);

/**
 * [decimalIntToBinaryVector description]
 * @param  decimal   [description]
 * @param  msgLength [description]
 * @return           [description]
 */
std::vector<int> decimalIntToBinaryVector(int decimal,int msgLength);
/**
 * [getEulerDistance description]
 * @param  block1 [description]
 * @param  block2 [description]
 * @return        [description]
 */
double getEulerDistance(std::vector<double> block1,std::vector<int> block2);

/**
 * [transSymbol description]
 * @param  originBlock [description]
 * @return             [description]
 */
std::vector<int> transSymbol(std::vector<int> originBlock);

//
void printVector(std::vector<int> v);

void printVector(std::vector<char> v);

void printVector(std::vector<double> v);


double getVarianceBySNR(double SNR);

double getVarianceBySNRdB(double SNRdB);

vector<double> BPSK_AWGNC(vector<int> input, double variance);

std::vector<int> getRandomMsg(int msgLength);

bool outputMap(std::map<double, double> map, std::vector<double> keySet, char filename[]);

bool outputMap(std::map<double, std::vector<double> > map, std::vector<double> keySet, char filename[]);

bool outputMap(std::map<double, double> map, std::vector<double> keySet);

bool outputMap(std::map<double, std::vector<double> > map, std::vector<double> keySet);