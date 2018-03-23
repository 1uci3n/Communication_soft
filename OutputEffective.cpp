#include <map>
#include <vector>
#include "HammingCodeCpp.h"
#include "RandomTools.h"
#include "GaussianChannel.h"
#include "OutputTools.h"

//信噪比最小值
#define MINI_S_N_R 0
//信噪比最大值
#define MAX_S_N_R 10
//测试信噪比的间隔
#define S_N_R_INTERVAL 0.1
//每个信道测试的循环次数
#define COUNT 1000
// //信噪比
// #define S_N_R 6;

int main(int argc, char const *argv[])
{
	//最终输出的数据map
	std::map<double, std::vector<double> > resultMap;
	//数据map的keySet
	std::vector<double> keySet;
	//用来储存每一轮结果的容器,[0]存储硬解码失败率，[1]存储最大似然度解码失败率
	std::vector<double> resultV(2);
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
	//硬解码失败计数器
	int hFailCount;
	//最大似然度解码失败计数器
	int mFailCount;
	//设置随机函数需要用到的盐值
	srand((unsigned)time(NULL));
	//设置最大似然解码方式需要用到的编码表
	setEncodeMapByMsgLength(4);
	//不同信道测试的循环
	for (double snr = MINI_S_N_R; snr <= MAX_S_N_R; snr += S_N_R_INTERVAL)
	{
		//初始化失败计数器
		hFailCount = 0;
		mFailCount = 0;
		//每个信道测试的循环体
		for (int i = 0; i < COUNT; ++i)
		{
			//获得随机消息
			msg = getRandomMsg(4);
			//将消息编码
			block = encode(msg, msg.size());
			//将块放入模拟的高斯信道传输
			clientBlock = Gaussian_channel(block, getN0ByDbSNR(snr));
			//硬解码
			tempHR = decodeHard(clientBlock, 7);
			//最大似然解码
			tempMR = decodeMLD(clientBlock, 4);
			//对解码结果进行判断
			if(tempHR != msg){
				hFailCount++;
			}
			if(tempMR != msg){
				mFailCount++;
			}
		}
		//计算失败率并记入容器
		resultV[0] = hFailCount / (double) COUNT;
		resultV[1] = mFailCount / (double) COUNT;
		//将结果的容器存入Map中
		resultMap.insert(std::pair<double, std::vector<double> >(snr, resultV));
		//将Key存入keySet中
		keySet.insert(keySet.end(), snr);
	}
	//输出测试结果至文件
	char fileName[] = "data.txt";
	outputMap(resultMap, keySet, fileName);
	return 0;
}