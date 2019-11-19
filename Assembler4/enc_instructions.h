#include <stdio.h>

/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "variables.h"			/*a_ משתנים וקבועים חשובים*/
#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/

















/*FUNCTION PROTOTYPE		--------------------------------------------*/
void processing_instructions(char *lineBuf);
char *processing_command (char **lineBuf);
char *processing_ope1 (char **lineBuf);
char *processing_ope2 (char **lineBuf);
int num_of_operator (char *cmd,char *operator1,char *operator2);

void add_instructions(tableCommands command,char *ope1,addressing adOpe1,char *ope2,addressing adOpe2);
type_errors is_operand1 (tableCommands command, addressing adOpe1);
type_errors is_operand2 (tableCommands command, addressing adOpe2);

/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
