#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
/*end my header file 		--------------------------------------------*/



#ifndef TABLECOMMANDS_H
#define TABLECOMMANDS_H
typedef enum  {
	_MOV=0,_CMP=1,_ADD=2,_SUB=3,
	_NOT=4,_CLR=5,_LEA=6,_INC=7,
	_DEC=8,JMP=9,_BNE=10,_RED=11,	
	_PRN=12,_JSR=13,_RTS=14,_STOP=15,
	_NOTEXIST=-1
	}tableCommands; /*a_ טבלת פקודות*/
#endif /*TABLECOMMANDS_H*/

#ifndef TABLECOMMANDS_H
#define TABLECOMMANDS_H
typedef enum  {
	_ONE=0,_TWO=1,_THREE=2
	}tableCommands; /*a_ טבלת פקודות*/
#endif /*TABLECOMMANDS_H*/



#ifndef DIR_OPTIONS_H
#define DIR_OPTIONS_H
typedef enum  {	
	_DATA=0,_STRING=1,_ENTRY=2,
	_EXTERN=3,_DEFINE=4
	}dirOptions;
#endif /*DIR_OPTIONS_H*/


#ifndef ADDRESSING_H
#define ADDRESSING_H
/*a_ באיזה מיעון מדובר*/
typedef enum { _NON=-1,_IMMEDIATE=0, _DIRECT=1, _INDEX=2, _REGISTER=3} addressing; /*a_ טבלת מיעונים*/
#endif /*ADDRESSING_H*/


/*FUNCTION PROTOTYPE		--------------------------------------------*/
bool is_keywords (char *str);
int directives_to_int (char * str_d);
int register_to_int (char * str_r);
tableCommands word_to_Commands (char *word);
bool is_index_addressing (char *word);
addressing word_to_addressing (char *word);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
