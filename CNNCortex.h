#ifndef CNNCortex_H_
#define CNNCortex_H_  
//the above construct is to ensure that this header file contents are only added once

#include<stdlib.h>


/*Insert Documentation*/
int * matrixPacker(int * inputMatrix, unsigned int height, unsigned int numberOfRows, unsigned int numberOfColumns ){
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
	unsigned int height=inputMatrix[0];
	unsigned int rows=inputMatrix[1];
	unsigned int columns=inputMatrix[2];
	
	unsigned int length=height; //*rows*columns;
	
	__asm{ 
		MULS length,rows
		MULS length,columns
	}
	
	unsigned int r0=(unsigned int)(inputMatrix+3);
	unsigned int counter =0;
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
	unsigned int height=inputMatrixOne[0];
	unsigned int rows=inputMatrixOne[1];
	unsigned int columns=inputMatrixOne[2];
	
	int length=height; //*rows*columns;
	
	__asm{ 
		MULS length,rows
		MULS length,columns
	}
	
	result = malloc(length);
	
	result[0]=height;
	result[1]=rows;
	result[2]=columns;
	
	
	unsigned int r0=(unsigned int)(inputMatrixOne+3);
	unsigned int r1=(unsigned int)(inputMatrixTwo+3);
	unsigned int r2=(unsigned int)(result+3);
	unsigned int counter =0;
	
	int dataOne=0;
	int dataTwo=0;
	
	__asm{		
		
		loop1:	
		ADDS counter, 0x1
		CMP counter, length
		BGT exit1
		LDR dataOne, [r0]
		LDR dataTwo, [r1]
		MULS dataOne, dataTwo
		STR dataOne, [r2]		
		ADDS r0, 0x4
		ADDS r1, 0x4
		ADDS r2, 0x4
		B loop1
		exit1:
	}
	
}

//end if for the singleton header inclusion
#endif
