
#include <MKL25Z4.h>
#include "CNNCortex.h"

void gating_LED()
	{
		SystemCoreClockUpdate();
		SIM_SCGC5 |= 1<<10; 
		
		PORTB_PCR18 |= 1<<8; 
		
	        GPIOB_PDDR  |=1<<18;  
		
		
		GPIOB_PSOR  |= 1<<18;   
		
	}

void glow_LED()
	{	
		
		GPIOB_PCOR  |= 1<<18;   //Resetting the Pin to 0 to switch on the LED
	
	}
void switchoff_LED()
	{
		GPIOB_PSOR  |= 1<<18;	
	}

int main(){
	
	int Array1[1][2][2];
	int Array2[1][2][2];
	int Answer[1][2][2];
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
	
	for( i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<2;k++){
				Array1[i][j][k]=i;
				Array2[i][j][k]=j;
				Answer[i][j][k]=i*j;
			}
		}
	}
	
	packedArray1 = matrixPacker((int *)Array1,1,2,2);
	packedArray2 = matrixPacker((int *)Array2,1,2,2);
	
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
	for( i=0;i<1;i++){
		for(j=0;j<2;j++){
			for(k=0;k<2;k++){
				if(Answer[i][j][k]!=myArrayElementWiseProduct[i][j][k]){
					flag = 0;
					break;
				}
			}
		}
	}

	if(flag==0){
		glow_LED();
	}
	else{
		switchoff_LED();
	}
	
	return 1;
}
