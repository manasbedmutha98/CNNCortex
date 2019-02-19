#ifndef CNNCortex_H_
#define CNNCortex_H_  
//the above construct is to ensure that this header file contents are only added once

#include<stdlib.h>


/*Insert Documentation*/
int * matrixPacker(int * inputMatrix, int height, int numberOfRows, int numberOfColumns ){
	int * packedMatrix;
	int sizeOfArray=(numberOfRows*numberOfColumns*height + 3)*sizeof(int);
	packedMatrix=malloc(sizeOfArray);
	packedMatrix[0]=height;
	packedMatrix[1]=numberOfRows;
	packedMatrix[2]=numberOfColumns;
	memcpy((void *)(packedMatrix+3), (const void *) inputMatrix,(unsigned) sizeOfArray);
	
	return packedMatrix;
}

/*Insert Documentation*/
void matrixShape(int * inputMatrix, int * outShape){
	outShape=malloc(sizeof(int)*3);
	
	outShape[0]=inputMatrix[0];
	outShape[1]=inputMatrix[1];
	outShape[2]=inputMatrix[2];
	
}

/*Insert Documentation*/
int matrixLength(int * inputMatrix){
	int length=inputMatrix[2];
	//ToDo: Logic here
	
	return length;
}

/*Insert Documentation*/
int matrixSum(int * inputMatrix){
	int sum=0;
	int height=inputMatrix[0];
	int rows=inputMatrix[1];
	int columns=inputMatrix[2];
	
	int length=height; //*rows*columns;
	
	__asm{ 
		MULS length,rows
		MULS length,columns
	}
	
	int r0=(int)(inputMatrix+3);
	int counter =0;
	int readInFromMemory=0;
	__asm{		
		LDR sum, [r0]
		loop1:	
		ADDS counter, 0x1
		CMP counter, length
		BEQ exit1
		ADDS r0, 0x4
		LDR readInFromMemory, [r0]
		ADDS sum, readInFromMemory
		B loop1
		exit1:
	}
	return sum;
}

/*Insert Documentation*/
void matrixElementwiseMul(int * result, int * inputMatrixOne, int * inputMatrixTwo){
	//ToDo: add sanity check to the size of the matrix
	int height=inputMatrix[0];
	int rows=inputMatrix[1];
	int columns=inputMatrix[2];
	
	int length=height; //*rows*columns;
	
	__asm{ 
		MULS length,rows
		MULS length,columns
	}
	
	
}

//end if for the singleton header inclusion
#endif
