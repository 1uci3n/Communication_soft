#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define chartonumber(x) (x-'0')
#define MAX 1000000
#define TEST 0

char* encode(char message[], int msgLength);
char* decode(char block[], int blockLength);
int getBlockLength(int msgLength);
void getCheckbitPosition(int *checkbitPosition, int checkbitLength);

char* encode(char message[], int msgLength){
	//计算块的大小
	int blockLength = getBlockLength(msgLength);
	//块大小的调试信息
	if (TEST == 1){
		printf("%d\n", blockLength);
	}
	//计算纠错位的长度
	int checkbitLength = blockLength - msgLength;
	//初始化纠错位的位置
	int checkbitPosition[checkbitLength];
	getCheckbitPosition(checkbitPosition, checkbitLength);
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
	printf("%s\n", tempBlock);
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
	//判断错位位置
	//计算新纠错位数值
	//判断纠错
	//去除纠错位解码
	return NULL;
}

int getBlockLength(int msgLength){
	for (int i = 2; i < MAX; ++i){
		if(pow(2,i) >= i + msgLength + 1){
			return i + msgLength;
		}
	}
	return 0;
}

void getCheckbitPosition(int *checkbitPosition, int checkbitLength){
	for (int i = 0; i < checkbitLength; i++){
		checkbitPosition[i] = (int) pow(2, i) - 1;
	}
}
