#include <stdio.h>



/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "variables.h"			/*a_ משתנים וקבועים חשובים*/
#include "keywords.h"			/*a_ מילים שמורות ופיענוח שלהם*/
#include "BasicFunc.h"			/*a_ פונקציות בסיסיות*/

#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/
























/*FUNCTION PROTOTYPE		--------------------------------------------*/
bool is_macro(char *lineBuf);
void processing_macro(char *lineBuf);
type_errors is_macro_name (char *m_name);
type_errors is_macro_value (char *value);
char *macro_name (char *lineBuf);
char *macro_value (char *lineBuf);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
