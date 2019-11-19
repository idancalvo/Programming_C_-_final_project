#include <stdio.h>
#include <ctype.h>


/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "variables.h"			/*a_ משתנים וקבועים חשובים*/
#include "BasicFunc.h"			/*a_ פונקציות בסיסיות*/
#include "enc_macro.h"			/*a_ מקרו*/

#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/























/*FUNCTION PROTOTYPE		--------------------------------------------*/
bool exists_label (char *lineBuf);
type_errors is_label_name (char *label);
char *processing_label(char *lineBuf);
char *label_name(char *lineBuf);
char *clear_label(char *lineBuf);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
