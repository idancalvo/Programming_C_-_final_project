#include <stdio.h>



/*my header file 		--------------------------------------------*/
#include "variables.h"

/*end my header file 		--------------------------------------------*/


#define LEN_DATA_ARRY 150
#define LEN_INST_ARRY 150


#ifndef INST_TYPE_H
#define INST_TYPE_H
typedef enum {FRSWORD, SECWORD, REGISTERWORD,NON} instType ;
#endif /* INST_TYPE_H */

/*מילה ר אשונהבפקודה*/
typedef struct { /*10 BIT*/
	unsigned int ARE:2;
	unsigned int dstOperand:2;
	unsigned int srcOperand:2;
	unsigned int opcode:4;
	unsigned int :0;
	}frsWord;

/*12bit כתובת/ערך מספרי (מיעון מידי או ישיר)*/
typedef struct { /*8 BIT*/
	unsigned int ARE:2;
	unsigned int value:12;
	}secWord;
	
/*מילים עם רגיסטרים1 או2*/
typedef struct  {	/*8 BIT*/
	unsigned int ARE:2;
	unsigned int dstRegister:3;
	unsigned int srcRegister:3;
	}registerWord;
	
/*גנריות*/
typedef union {
	frsWord frs_word;
	secWord Immediate_word;
	registerWord register_word;
	
	}instWord;
	
	
/*מילה המחזיקה דטה */
typedef struct  { /*14 BIT*/
	unsigned int value:14;
	}dataWord;



void add_inst_frs (int dstoperand, int srcoperand, int opcode);
void add_inst_sec (int ARE , int value);
void add_inst_reg (int ARE , int dstoperand, int srcoperand);
void add_data (int value);
int get_data (int index);
int get_inst (int index);


void print_all_arry();





