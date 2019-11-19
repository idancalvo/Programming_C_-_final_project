#include <stdio.h>
#include <string.h>


/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "cleariputline.h"		/*a_ מסדר שורת לצורה סטנדרטית*/

#include "enc_instructions.h"		/*a_ משפטי הוראה*/	
#include "enc_label.h"			/*a_ תויות*/	
#include "enc_directive.h"		/*a_ משפטי החיה*/
#include "enc_macro.h"			/*a_ מקרו*/

#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "BasicFunc.h"			/*a_ פונקציות בסיסיות*/
#include "variables.h"			/*a_ משתנים וקבועים חשובים*/
#include "keywords.h"			/*a_ מילים שמורות ופיענוח שלהם*/

#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/





#define FOLDER_ADDRES  "input/"




/*FUNCTION PROTOTYPE		--------------------------------------------*/
void Works_file (FILE *fd);
void first_processing(FILE *fd);
void second_processing(FILE * fd);
void work_line (char *wordBuf);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/



void clear_obj ();





