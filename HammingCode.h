#include<stdio.h>
#include<math.h>

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
	for(int i = 0; i < checkbitLength; i++){
		printf("%d ", checkbitPosition[i]);
	}
	printf("\n");
	//生成最终的编码块并返回
	static char block[blockLength] = "11110";
	return block;
}

int getBlockLength(int msgLength){
	for (int i = 2; i < 1000; ++i){
		if(pow(2,i) >= i + msgLength + 1){
			return i + msgLength;
		}
	}
	return 0;
}

void getCheckbitPosition(int *checkbitPosition, int checkbitLength){
	for(int i = 0; i < checkbitLength; i++){
		checkbitPosition[i] = (int) pow(2, i);
	}
}