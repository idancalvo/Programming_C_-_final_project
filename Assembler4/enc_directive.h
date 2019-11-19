#include <stdio.h>




/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "variables.h"			/*a_ משתנים וקבועים חשובים*/
#include "enc_macro.h"			/*a_ מקרו*/
#include "keywords.h"			/*a_ מילים שמורות ופיענוח שלהם*/
#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
#include "arrays.h"			/*a_ מערכי נתונים והוראות*/
/*end my header file 		--------------------------------------------*/

























/*FUNCTION PROTOTYPE		--------------------------------------------*/
bool is_directive(char *lineBuf);
void processing_directive(char *lineBuf);

void processing_data(char *lineBuf);
char *next_data_value (char **P_lineBuf);

void processing_string(char *lineBuf);

void processing_entry(char *lineBuf);

void processing_extern(char *lineBuf);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
