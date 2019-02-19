
//#include <MKL25Z4.h>
#include <stdio.h>
#include <stdlib.h>
#include "CNNCortex.h"

int main(){
	
	int myArray[1][1][2];
	float myFloatArray[1][1][2];
	int i,j,k; 
	int x=0;
	int * packedMyArray;
	float * packedMyFloatArray;
	int myArrayLength;
	int myArraySum;
	int * myArrayElementWiseProduct;
	float *myFloatArraySum;
	
	int * shapeOfMyMatrix;//=alloca(sizeof(int));
	
	myArray[0][0][0]=2;
	myArray[0][0][1]=2;
	myFloatArray[0][0][0]=2.0;
	myFloatArray[0][0][1]=2.0;
	
	packedMyArray = matrixPacker((int *)myArray,1,1,2);
	packedMyFloatArray = matrixFloatPacker((float *)myArray,1,1,2);
	
	shapeOfMyMatrix=matrixShape(packedMyArray);
	if(shapeOfMyMatrix[2] ==2){
		x = 0;
	}else{
		x =-1;
	}
	
	myArrayLength=matrixLength(packedMyArray);
	
	if(myArrayLength ==2){
		x = 0;
	}else{
		x =-1;
	}
	
	myArraySum=matrixSum(packedMyArray);
	
	if(myArraySum ==4){
		x = 0;
	}else{
		x =-1;
	}
		
	myArrayElementWiseProduct=matrixElementwiseMul(packedMyArray,packedMyArray);
	int data = myArrayElementWiseProduct[3];
		
	if(data==4){
		 x =0;
	}else{
		x = -1;
	}	
	
	/*
		myFloatArraySum=matrixFloatSum(packedMyFloatArray);
	int datax=*myFloatArraySum;
	if(datax ==4){
		x = 0;
	}else{
		x =-1;
	}
	*/
	
	return 1;
}
