#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define chartonumber(x) (x-'0')
#define MAX 1000000

char* encode(char message[], int msgLength);
int getBlockLength(int msgLength);
void getCheckbitPosition(int *checkbitPosition, int checkbitLength);

char* encode(char message[], int msgLength){
	//计算块的大小
	int blockLength = getBlockLength(msgLength);
	//块大小的调试信息
	printf("%d\n", blockLength);
	//计算纠错位的长度
	int checkbitLength = blockLength - msgLength;
	//初始化纠错位的位置
	int checkbitPosition[checkbitLength];
	getCheckbitPosition(checkbitPosition, checkbitLength);
	//纠错位位置的调试信息
	for (int i = 0; i < checkbitLength; i++){
		printf("%d ", checkbitPosition[i]);
	}
	printf("\n");
	//产生临时编码块
	char tempBlock[blockLength];
	//当前的纠错位序号
	int checkbitIndex = 0;
	//当前的数据位序号
	int msgbitIndex = 0;
	//储存临时的纠错信息

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
	int j;
	//纠错位的计算
	printf("开始纠错位计算\n");
	for (int i = 0; i < blockLength; ++i)
	{
		//判断当前位是否为纠错位
		if (tempBlock[i] == 'X')
		{
			//如果为纠错位，计算纠错位数据，配偶原则
			j = i;
			nowNumber = 0;
			printf("checkbitPosition[checkbitIndex] %d\n", checkbitPosition[checkbitIndex]);
			while(j < blockLength){
				printf("s %c 第%d位\n", tempBlock[j],j + 1);
				if (j != i){
					tempData = tempData + chartonumber(tempBlock[j]);
				}
				nowNumber++;
				if (nowNumber < checkbitPosition[checkbitIndex] + 1){
					j++;
				} else {
					j= j + checkbitPosition[checkbitIndex] + 2;
					nowNumber = 0;
				}
			}
			printf("%d\n",tempData);
			if ((tempData % 2) == 0){
				tempBlock[i] = '0';
			} else {
				tempBlock[i] = '1';
			}
			tempData = 0;
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

// char* decode(char block[], int blockLength){
// 	return null;
// }

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