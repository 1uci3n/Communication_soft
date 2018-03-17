#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>

#define chartonumber(x) (x-'0')
#define MAX 1000000
#define TEST 0

using namespace std;

/**
 * 汉明码编码
 * 
 * @param  message   源消息(字符数组)
 * @param  msgLength 消息长度
 * @return           返回编码后的字符数组的首地址(malloc)，注意复制后释放地址(free)
 */
char* encode(char message[], int msgLength);

/**
 * 汉明码解码
 * 
 * @param  block       需要解码的块(字符数组)
 * @param  blockLength 块的长度
 * @return             返回解码后的字符数组的首地址(malloc)，注意复制后释放地址(free)
 */
char* decode(char block[], int blockLength);

/**
 * 根据消息长度计算目标块大小
 * 
 * @param  msgLength 原消息大小
 * @return           返回目标块大小
 */
int getBlockLengthByMsgLength(int msgLength);

/**
 * 根据纠错位位数计算纠错位位置
 * 
 * @param checkbitPosition 用来保存纠错位的数组
 * @param checkbitLength   纠错位位数
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
 * 将字符数组转换为vector容器
 */
vector<int> transCharArrayToIntVector(char* charArray, int arrayLenth);

/**
 * 汉明码编码(返回值为范性为int的vector容器)
 */
vector<int> encodeReturnVector(char message[], int msgLength);

char* encode(char message[], int msgLength){
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
		for (int i = 0; i < checkbitLength; i++){
			printf("%d ", checkbitPosition[i]);
		}
		printf("\n");
	}
	//产生临时编码块
	char tempBlock[blockLength];
	//当前的纠错位序号
	int checkbitIndex = 0;
	//当前的数据位序号
	int msgbitIndex = 0;
	//对纠错位进行搜索
	for (int i = 0; i < blockLength; ++i){
		//判断当前位是否为纠错位
		if (i == checkbitPosition[checkbitIndex]){
			// //是纠错位,计算纠错位的数据
			// for(int j = checkbitPosition[checkbitIndex]; j < blockLength; j++){
			// 	tempBlock[i] = 
			// }
			//temp将纠错位标记为X
			tempBlock[i] = 'X';
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
		if (tempBlock[i] == 'X')
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
					printf("s %c 第%d位\n", tempBlock[j],j + 1);
				}
				//为了跳过分组中的第一位，对当前操作位进行判断是否位该组的第一位
				if (j != i){
					//若当前操作位不为当前组的第一位，进行累加计算
					tempData = tempData + chartonumber(tempBlock[j]);
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
				tempBlock[i] = '0';
			} else {
				tempBlock[i] = '1';
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
		printf("%s\n", tempBlock);
	}
	char *block = NULL;
	//生成最终的编码块并返回
	block = (char *) malloc(blockLength * sizeof(char));
	if (block != NULL){
		snprintf(block, sizeof(tempBlock) + 1, tempBlock);
		return block;
	} else {
		return NULL;
	}
}

char* decode(char block[], int blockLength){
	//计算纠错位位数
	int checkbitLength = getCheckbitLengthByBlockLength(blockLength);
	//计算纠错位位置
	int checkbitPosition[checkbitLength];
	getCheckbitPositionByCheckbitLength(checkbitPosition, checkbitLength);
	//进行纠错校验
	//每组校验的结果数组
	int result[checkbitLength];
	//最终结果的储存器
	int target;
	//连续计数器
	int count = 0;
	for (int i = 0; i < checkbitLength; ++i)
	{
		for (int j = i; j < blockLength; ++j)
		{
			result[i] += chartonumber(block[i]);
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
		if (block[target] == '1'){
			block[target] = '0';
		} else {
			block[target] = '1';
		}
	}
	//去除纠错位解码
	char tempMsg[blockLength - checkbitLength];
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
	char *msg = NULL;
	msg = (char *) malloc((blockLength - checkbitLength) * sizeof(char));
	if (msg != NULL){
		snprintf(msg, sizeof(tempMsg) + 1, tempMsg);
		return msg;
	} else {
		return NULL;
	}
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

vector<int> transCharArrayToIntVector(char* charArray, int arrayLenth){
	vector<int> v(arrayLenth, 0);
	for (int i = 0; i < arrayLenth; ++i)
	{
		v[i] = chartonumber(charArray[i]);
	}
	free(charArray);
	return v;
}

vector<int> encodeReturnVector(char message[], int msgLength){
	return transCharArrayToIntVector(encode(message, msgLength), getBlockLengthByMsgLength(msgLength));
}
