#include "arrays.h"

unsigned int instArray [LEN_INST_ARRY]; /*מערך ההוראות*/
unsigned int dataArray [LEN_DATA_ARRY];	/*מערך נתונים*/


void add_inst_frs (int dstoperand, int srcoperand, int opcode)
{
	frsWord tempWord;
	unsigned int *tempInt;
	tempInt =(unsigned int *)(&tempWord);
	*tempInt = 0;

	tempWord.ARE = 0;		
	tempWord.dstOperand = dstoperand;
	tempWord.srcOperand = srcoperand;
	tempWord.opcode = opcode;
	
	instArray [get_ic()] = *tempInt;
	enc_ic();	
}	
	

void add_inst_sec (int ARE , int value)
{
	secWord tempWord;
	unsigned int *tempInt;
	tempInt =(unsigned int *)(&tempWord);
	*tempInt = 0;

	tempWord.ARE = ARE;		
	tempWord.value = value;
	
	instArray [get_ic()] = *tempInt;
	enc_ic();	
}


void add_inst_reg (int dstRegister, int srcRegister)
{
	registerWord tempWord;
	unsigned int *tempInt;
	tempInt =(unsigned int *)(&tempWord);
	*tempInt = 0;

	tempWord.ARE = 0;		
	tempWord.dstRegister = dstRegister;
	tempWord.srcRegister = srcRegister;
	
	instArray [get_ic()] = *tempInt;
	enc_ic();	
}




void add_data (int value)
{
	dataWord tempWord;
	unsigned int *tempInt;
	tempInt =(unsigned int *)(&tempWord);
	*tempInt = 0;
	
	tempWord.value = value;	
	*tempInt = tempWord.value;
	
	dataArray[get_dc()] = *tempInt;
	enc_dc();	
}


int get_data (int index)
{
	return dataArray[index];
} 


int get_inst (int index)
{
	return instArray[index];
} 



void print_all_arry()
{
	int k,i;
	
	if ((k = get_ic())!=0)
	{
		printf("instArray:\n");
		for (i=0;i<k;i++)	
		{
			printf("%d, ",instArray[i]);	
		}
		printf("\n");
	}
	
	
	if ((k=get_dc())!=0)	
	{
		printf("dataArray:\n");
		for (i=0;i<k;i++)	
		{
			printf("%d, ",dataArray[i]);	
		}
		printf("\n");
	}


}








