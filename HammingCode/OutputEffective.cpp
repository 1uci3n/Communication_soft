/*
* @Author: 1uci3n
* @Date:   2018-04-25 23:40:28
* @Last Modified by:   1uci3n
* @Last Modified time: 2018-06-06 17:22:04
*/
#include <map>
#include <vector>
#include "HammingCodeCpp.h"
#include "RandomTools.h"
//#include "GaussianChannel.h"
#include "GaussianChannel2nd.h"
#include "OutputTools.h"

//信噪比最小值
#define MINI_S_N_R 0.1
//信噪比最大值
#define MAX_S_N_R 10
//测试信噪比的间隔
#define S_N_R_INTERVAL 0.1
//每个信道测试的循环次数
#define COUNT 1000
// //信噪比
// #define S_N_R 6;

/**
 * compare two Bolck's bit
 * 
 * @param  block1 the one block
 * @param  block2 another block
 * @return        the count of different bit's
 */
int compareBolckBit(std::vector<int> block1, std::vector<int> block2);

int main(int argc, char const *argv[])
{
	//最终输出的数据map
	std::map<double, std::vector<double> > resultMap;
	//数据map的keySet
	std::vector<double> keySet;
	//用来储存每一轮结果的容器,[0]存储硬解码位错误率,[1]存储硬解码词错误率
	//[2]存储最大似然度位错误率,[3]存储最大似然度词错误率
	std::vector<double> resultV(4);
	//消息储存器
	std::vector<int> msg;
	//编码后的块储存器
	std::vector<int> block;
	//接收端的块存储器
	std::vector<double> clientBlock;
	//内层循环每次硬解码的结果临时存储器
	std::vector<int> tempHR;
	//内层循环每次最大似然解码的结果临时存储器
	std::vector<int> tempMR;
	//硬解码错误词计数器
	int hWErrorCount;
	//最大似然度解码错误词计数器
	int mWErrorCount;
	//硬解码错误位计数器
	int hBErrorCount;
	//最大似然度解码错误位计数器
	int mBErrorCount;
	//设置随机函数需要用到的盐值
	srand((unsigned)time(NULL));
	//设置最大似然解码方式需要用到的编码表
	setEncodeMapByMsgLength(4);
	//不同信道测试的循环
	for (double snr = MINI_S_N_R; snr <= MAX_S_N_R; snr += S_N_R_INTERVAL)
	{
		//初始化错误计数器
		hWErrorCount = 0;
		mWErrorCount = 0;
		hBErrorCount = 0;
		mBErrorCount = 0;
		//每个信道测试的循环体
		for (int i = 0; i < COUNT; ++i)
		{
			//获得随机消息
			msg = getRandomMsg(4);
			//将消息编码
			block = encode(msg, msg.size());
			//将块放入模拟的高斯信道传输
			//clientBlock = Gaussian_channel(block, getN0ByDbSNR(snr));
			clientBlock = BPSK_AWGNC(block, getVarianceBySNRdB(snr));
			//硬解码
			tempHR = decodeHard(clientBlock, 7);
			//最大似然解码
			tempMR = decodeMLD(clientBlock, 4);
			//对解码结果进行判断
			if(tempHR != msg){
				hWErrorCount++;
				hBErrorCount += compareBolckBit(msg, tempHR);
			}
			if(tempMR != msg){
				mWErrorCount++;
				mBErrorCount += compareBolckBit(msg, tempMR);
			}
		}
		//计算块失败率并记入容器
		//[0]存储硬解码位错误率,[1]存储硬解码词错误率
		//[2]存储最大似然度位错误率,[3]存储最大似然度词错误率
		resultV[0] = hBErrorCount / ((double) COUNT * 4);
		resultV[1] = hWErrorCount / (double) COUNT;
		resultV[2] = mBErrorCount / ((double) COUNT * 4);
		resultV[3] = mWErrorCount / (double) COUNT;
		//将结果的容器存入Map中
		resultMap.insert(std::pair<double, std::vector<double> >(snr, resultV));
		//将Key存入keySet中
		keySet.insert(keySet.end(), snr);
	}
	//输出测试结果至文件
	char fileName[] = "result.dat";
	outputMap(resultMap, keySet, fileName);
	return 0;
}

int compareBolckBit(std::vector<int> block1, std::vector<int> block2){
	int diffCount = 0;
	for (int i = 0; i < block1.size(); ++i)
	{
		if (block1[i] != block2[i])
		{
			diffCount++;
		}
	}
	return diffCount;
}