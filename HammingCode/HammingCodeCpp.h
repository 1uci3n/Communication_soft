#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <iostream>
#include "VectorTools.h"

#define MAX 1000000
#define TEST 0
#define SIGNAL_ZERO 1
#define SIGNAL_ONE -1

static std::vector<std::vector<int> > keySet;
static std::map<std::vector<int>, std::vector<int> > encodeMap;

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
std::vector<int> decodeMLD(std::vector<double> block, int msgLength, std::map<std::vector<int>, std::vector<int> > encodeMap);

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

std::vector<int> encode(std::vector<int> message, int msgLength){
	//计算块的大小
	int blockLength = getBlockLengthByMsgLength(msgLength);
	//块大小的调试信息
	if (TEST == 1){
		printf("%d\n", blockLength);
	}
	//计算纠错位的长度
	int checkbitLength = blockLength - msgLength;
	//初始化纠错位的位置
	int checkbitPosition[checkbitLength];
	getCheckbitPositionByCheckbitLength(checkbitPosition, checkbitLength);
	//纠错位位置的调试信息
	if (TEST == 1){
		for (int i = 0; i < checkbitLength; ++i){
			printf("%d ", checkbitPosition[i]);
		}
		printf("\n");
	}
	//产生临时编码块
	std::vector<int> tempBlock(blockLength, 0);
	//当前的纠错位序号
	int checkbitIndex = 0;
	//当前的数据位序号
	int msgbitIndex = 0;
	//对纠错位进行搜索
	for (int i = 0; i < blockLength; ++i){
		//判断当前位是否为纠错位
		if (i == checkbitPosition[checkbitIndex]){
			// //是纠错位,计算纠错位的数据
			// for(int j = checkbitPosition[checkbitIndex]; j < blockLength; ++j){
			// 	tempBlock[i] = 
			// }
			//temp将纠错位标记为X
			tempBlock[i] = 2;
			//将纠错位序号调整至下一个
			checkbitIndex++;
		} else {
			//不是纠错位,将当前数据存入其中
			tempBlock[i] = message[msgbitIndex];
			//将数据位序号调整至下一位
			msgbitIndex++;
		}
	}
	//纠错位连续计数器
	int nowNumber = 0;
	//临时数据
	int tempData = 0;
	//纠错位序号初始化
	checkbitIndex = 0;
	//纠错位内层循环子
	int j;
	//纠错位的计算
	//纠错位计算开始的调试信息
	if (TEST == 1){
		printf("开始纠错位计算\n");
	}
	for (int i = 0; i < blockLength; ++i)
	{
		//判断当前位是否为纠错位
		if (tempBlock[i] == 2)
		{
			//如果为纠错位，计算纠错位数据，配偶原则
			//内层循环因子初始化，计算纠错位数据，从当前的纠错位开始，与之前的位无关
			j = i;
			//连续标记，用来标记同一组内连续的数据位的序数
			nowNumber = 0;
			//纠错位计算分组的调试信息
			if (TEST == 1){
				printf("checkbitPosition[checkbitIndex] %d\n", checkbitPosition[checkbitIndex]);
			}
			//当内层循环因子小于块的长度时，循环继续
			while(j < blockLength){
				//纠错位计算的调试信息
				if (TEST == 1){
					printf("s %d 第%d位\n", tempBlock[j],j + 1);
				}
				//为了跳过分组中的第一位，对当前操作位进行判断是否位该组的第一位
				if (j != i){
					//若当前操作位不为当前组的第一位，进行累加计算
					tempData = tempData + tempBlock[j];
				}
				//连续标记自加
				nowNumber++;
				//对连续标记与当前纠错位的位置加一进行比较
				if (nowNumber < checkbitPosition[checkbitIndex] + 1){
					//当连续标记小于纠错位的位置加一，j自加，即j的下一位也在当前的分组中
					j++;
				} else {
					//当连续标记大于等于纠错位的位置加一，j“指针”需要跳到下一段连续数据
					j= j + checkbitPosition[checkbitIndex] + 2;
					//将连续标记重置为零
					nowNumber = 0;
				}
			}
			if (TEST == 1){
				printf("%d\n",tempData);
			}
			if ((tempData % 2) == 0){
				tempBlock[i] = 0;
			} else {
				tempBlock[i] = 1;
			}
			//每次循环完成后，对一些每次循环需要用到的数据进行初始化
			tempData = 0;
			//
			nowNumber = 0;
			//纠错位序号加一
			checkbitIndex++;
		}
	}
	//临时编码块纠错位置标记的调试信息
	if (TEST == 1)
	{
		//printf("%s\n", tempBlock);
	}
	return tempBlock;
}

std::vector<int> decode(std::vector<int> block){
	int blockLength = block.size();
	//计算纠错位位数
	int checkbitLength = getCheckbitLengthByBlockLength(blockLength);
	//计算纠错位位置
	int checkbitPosition[checkbitLength];
	getCheckbitPositionByCheckbitLength(checkbitPosition, checkbitLength);
	//进行纠错校验
	//每组校验的结果数组
	int result[checkbitLength];
	//最终结果的储存器
	int target = 0;
	//连续计数器
	int count = 0;
	for (int i = 0; i < checkbitLength; ++i)
	{
		result[i] = 0;
		for (int j = i; j < blockLength; ++j)
		{
			result[i] += block[i];
			//连续计数器计数
			count ++;
			if (count >= checkbitPosition[i] + 1){
				//当连续计数器数值大于等于纠错位的位置加一，j“指针”需要跳到下一段连续数据
				j= j + checkbitPosition[i] + 1;
				//将连续计数器重置为零
				count = 0;
			}
		}
		target += (result[i] % 2) * pow(2, i);
	}
	//判断纠错
	if (target != -1){
		//发生错误,进行纠错
		if (block[target] == 1){
			block[target] = 0;
		} else {
			block[target] = 1;
		}
	}
	//去除纠错位解码
	std::vector<int> tempMsg(blockLength - checkbitLength, 0);
	int checkIndex = 0;
	int msgIndex = 0;
	for (int i = 0; i < blockLength; ++i)
	{
		if (i != checkbitPosition[checkIndex])
		{
			tempMsg[msgIndex] = block[i];
			msgIndex++;
		} else {
			checkIndex++;
		}
	}
	//生成最终的编码块并返回
	return tempMsg;
}

std::vector<int> decodeHard(std::vector<double> block, int blockLength){
	std::vector<int> newBlock(blockLength, 0);
	for (int i = 0; i < blockLength; ++i)
	{
		if (fabs(block[i] - SIGNAL_ONE) <= fabs(block[i] - SIGNAL_ZERO)){
			newBlock[i] = 1;
		} else {
			newBlock[i] = 0;
		}
	}
	if(TEST == 1){
		printVector(newBlock);
	}
	return decode(newBlock);
}


std::vector<int> decodeMLD(std::vector<double> block, int msgLength){
	double dis;
	double minDis;
	std::vector<int> key;
	minDis = getEulerDistance(block, keySet[0]);
	key = keySet[0];
	for (int i = 1; i < pow(2, msgLength); ++i)
	{
		dis = getEulerDistance(block, keySet[i]);
		if(dis < minDis){
			minDis = dis;
			key = keySet[i];
		}
	}
	return encodeMap.at(key);
}

int getBlockLengthByMsgLength(int msgLength){
	for (int i = 2; i < MAX; ++i){
		if(pow(2,i) >= i + msgLength + 1){
			return i + msgLength;
		}
	}
	return 0;
}

void getCheckbitPositionByCheckbitLength(int *checkbitPosition, int checkbitLength){
	for (int i = 0; i < checkbitLength; ++i){
		checkbitPosition[i] = (int) pow(2, i) - 1;
	}
}

int getCheckbitLengthByBlockLength(int blockLength){
	for (int i = 1; i <= blockLength; ++i)
	{
		if(pow(2, i) >= blockLength + 1){
			return i;
		}
	}
	return 0;
}

void setEncodeMapByMsgLength(int msgLength){
	std::vector<int> msg;
	std::vector<int> block;
	std::vector<std::vector <int> >::iterator iter=keySet.end();
	for (int i = 0; i < pow(2, msgLength); ++i)
	{
		msg = decimalIntToBinaryVector(i, msgLength);
		block = encode(msg, msgLength);
		block = transSymbol(block);
		keySet.insert(iter, block);
		iter = keySet.end();
		//printVector(keySet[i]);
		encodeMap.insert(std::pair<std::vector<int>, std::vector<int> >(block, msg));
	}
}

std::vector<int> decimalIntToBinaryVector(int decimal,int msgLength){
	std::vector<int> binary(msgLength, 0);
	int remain = decimal;
	for (int i = msgLength - 1; i >= 0; --i)
	{
		binary[msgLength - i - 1] = remain / pow(2, i);
		remain = remain - (binary[msgLength - i - 1] * pow(2, i));
	}
	return binary;
}


double getEulerDistance(std::vector<double> block1,std::vector<int> block2){
	double result;
	for (int i = 0; i < block1.size(); ++i)
	{
		result += fabs(block1[i] - block2[i]);
	}
	return result;
}

std::vector<int> transSymbol(std::vector<int> block){
	for (int i = 0; i < block.size(); ++i)
	{
		if (block[i] == 1)
		{
			block[i] = SIGNAL_ONE;
		} else {
			block[i] = SIGNAL_ZERO;
		}
	}
	return block;
}
