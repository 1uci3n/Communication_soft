#include<stdio.h>
#include<math.h>

char* encode(char message[], int msgLength){
	int blockLength = getBlockLength(msgLength);
	int 
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
