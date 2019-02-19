
#include <MKL25Z4.h>
#include "CNNCortex.h"

int main(){
	
	int Array1[2][2][1];
	int Array2[2][2][1];
	int Answer[2][2][1];
	int i,j,k; 
	int * packedArray1;
	int * packedArray2;
	int Array1Length;
	int Array2Length;
	int Array1Sum;
	int Array2Sum;

	int * myArrayElementWiseProduct;
	
	int * shapeOfMyMatrix;

	gating_LED();
	
	for( i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=0;k<1;k++){
				Array1[i][j][k]=i;
				Array2[i][j][k]=j;
				Answer[i][j][k]=i*j;
			}
		}
	}
	
	packedArray1 = matrixPacker((int *)Array1,2,2,1);
	packedArray2 = matrixPacker((int *)Array2,2,2,1);
	
	matrixShape(Array1,shapeOfMyMatrix);
	matrixShape(Array2,shapeOfMyMatrix);
	
	//myArrayLength=matrixLength(packedMyArray);
	Array1Length=matrixLength(Array1);
	Array2Length=matrixLength(Array2);
	
	//myArraySum=matrixSum(packedMyArray);
	Array1Sum=matrixSum(packedArray1);
	Array2Sum=matrixSum(packedArray2);
	
	matrixElementwiseMul(myArrayElementWiseProduct,packedArray1,packedArray2);

	int flag = 1;
	for( i=0;i<2;i++){
		for(j=0;j<2;j++){
			for(k=0;k<1;k++){
				if(Answer[i][j][k]!=myArrayElementWiseProduct[i][j][k]){
					glow_LED();
				}
			}
		}
	}

	
	return 1;
}