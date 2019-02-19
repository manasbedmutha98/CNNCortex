
#include <MKL25Z4.h>
#include "CNNCortex.h"

int main(){
	
	int myArray[3][10][10];
	int i,j,k; 
	int * packedMyArray;
	int myArrayLength;
	int myArraySum;
	int * myArrayElementWiseProduct;
	
	int * shapeOfMyMatrix;
	
	for( i=0;i<3;i++){
		for(j=0;j<10;j++){
			for(k=0;k<10;k++){
				myArray[i][j][k]=j;
			}
		}
	}
	
	packedMyArray = matrixPacker((int *)myArray,3,10,10);
	
	matrixShape(packedMyArray,shapeOfMyMatrix);
	
	myArrayLength=matrixLength(packedMyArray);
	
	myArraySum=matrixSum(packedMyArray);
	
	matrixElementwiseMul(myArrayElementWiseProduct,packedMyArray,packedMyArray);
	
	
	
	
	
	return 1;
}
