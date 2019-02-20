#ifndef CNNCortex_H_
#define CNNCortex_H_  
//the above construct is to ensure that this header file contents are only added once

#include<stdlib.h>
//#include<math.h>
//#include<rt_fp.h>



__asm void floatAdd(void){
	IMPORT __aeabi_fadd;
	MOV r2, lr
	PUSH { r2 }
	BL __aeabi_fadd;
	POP { r2 }
	MOV lr, r2
	BX lr;
}


/*
__asm void import(void){
	IMPORT __aeabi_fadd;
	BX lr;
}
*/


/*Insert Documentation*/
int * matrixPacker(int * inputMatrix, unsigned int height, unsigned int numberOfRows, unsigned int numberOfColumns ){
	int i=3;
	int * packedMatrix;
	int sizeOfArray=(numberOfRows*numberOfColumns*height + 3)*sizeof(int);
	packedMatrix=malloc(sizeOfArray);
	packedMatrix[0]=height;
	packedMatrix[1]=numberOfRows;
	packedMatrix[2]=numberOfColumns;
	int length=numberOfRows*numberOfColumns*height;
	for(i=0;i<length;i++){
	packedMatrix[i+3]=inputMatrix[i];
	}	
	return packedMatrix;
}

/*Insert Documentation*/
float * matrixFloatPacker(float * inputMatrix, unsigned int height, unsigned int numberOfRows, unsigned int numberOfColumns ){
	int i=3;
	float * packedMatrix;
	int sizeOfArray=(numberOfRows*numberOfColumns*height + 3)*sizeof(float);
	packedMatrix=malloc(sizeOfArray);
	
	int length=numberOfRows*numberOfColumns*height;
	for(i=0;i<length;i++){
	packedMatrix[i+3]=inputMatrix[i];
	}	
	*(int *)(packedMatrix)=height;
	*(int *)(packedMatrix+1)=numberOfRows;
	*(int *)(packedMatrix+2)=numberOfColumns;
	return packedMatrix;
}

/*Insert Documentation*/
int * matrixShape(int * inputMatrix){
	int * outShape;
	outShape=malloc(sizeof(int)*3);
	
	outShape[0]=inputMatrix[0];
	outShape[1]=inputMatrix[1];
	outShape[2]=inputMatrix[2];
	return outShape;
}



/*Insert Documentation*/
int matrixLength(int * inputMatrix){
	unsigned int length=inputMatrix[0];
	unsigned int rows=inputMatrix[1];
	unsigned int columns=inputMatrix[2];
	
	
	__asm{ 
		MULS length, rows
		MULS length, columns
	}

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
		MULS length, rows
		MULS length, columns
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

float * matrixFloatSum(float * inputMatrix){
	float * result;
	result=malloc(sizeof(float));
	
	unsigned float sum=0;
	 int height=*(int *)(inputMatrix);
	 int rows=*(int *)(inputMatrix+1);
	 int columns=*(int *)(inputMatrix+2);
	
	 int length=height; //*rows*columns;
	
	__asm{ 
		MULS length, rows
		MULS length, columns
	}
	
	//BL foo, { r0=expression1, r1=expression2, r2 }
	//BL foo, { }, { result1=r0, r1 }
	//BL       __aeabi_fadd
	
	unsigned int location=(unsigned int)(inputMatrix+3);
	unsigned int counter =0;
	unsigned int readInFromMemory=0;
	__asm{	
		LDR sum, [location] // Might be a problem
		loop1:	
		ADDS counter, 0x1
		CMP counter, length
		BEQ exit1
		ADDS location, 0x4
		LDR readInFromMemory, [location]
		//ADDS sum, readInFromMemory
		BL floatAdd, {r0=sum, r1=readInFromMemory},{sum=r0}
		B loop1
		exit1:
	}
	* (float *)result = sum;

	return result;
}


/*Insert Documentation*/
int * matrixElementwiseMul( int * inputMatrixOne, int * inputMatrixTwo){
	//ToDo: add sanity check to the size of the matrix
	int * result;
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
	return result;
}

//end if for the singleton header inclusion
#endif
