#include<stdio.h>
#include<math.h>


char* encode(char message[], int msgLength){
	//计算块的大小
	int blockLength = getBlockLength(msgLength);
	//计算纠错位的长度
	int checkbitLength = blockLength - msgLength;
        //
        int checkbitPosition[checkbitLength];
 	getCheckbitPosition(checkbitPosition, checkbitLength);
        for(int i = 0; i < checkbitLength; i++){
		printf("%d ", checkbitPosition[i]);
	}
	printf("\n");
	char block[blockLength];
	printf("%d\n", blockLength);
	return block;
}

int getBlockLength(int msgLength){
	for (int i = 2; i < 1000; ++i)
	{
		if(pow(2,i) >= i + msgLength + 1){
			return i + msgLength;
		}
	}
	return 0;
}

void getCheckbitPosition(int* checkbitPosition, int checkbitLength){
        for(int i = 0; i < checkbitLength; i++){
		checkbitPosition[i] = (int) pow(2, i);
	}
}
