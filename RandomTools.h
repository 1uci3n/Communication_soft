#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int* getRandomIntArray(int length, int unitLength){
	int array[lenght];
	srand(time(NULL));
	int randomTool = pow(10, unitLength);
	for(int i = 0; i < length; i++){
		array[i] = rand() % (pow(10, randomTool);
	}
	return array;
}
