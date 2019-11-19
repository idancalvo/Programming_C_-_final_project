#include <stdio.h>
#include <string.h>
#include <ctype.h>


/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/

#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/










/*FUNCTION PROTOTYPE		--------------------------------------------*/
bool is_comment (char*);			/**/
bool is_empty_line (char*);			/**/
bool is_num_and_letters(char *word);		/**/
int str_to_int (char *word);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/






