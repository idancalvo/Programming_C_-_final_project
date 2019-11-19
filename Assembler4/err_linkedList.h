#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
/*end my header file 		--------------------------------------------*/



#define MAX_FILENAME 100


#ifndef ERR_LIST_H
#define ERR_LIST_H
typedef struct err_list {
	void* first;
	void* last;
	int num_of_item;
	char name_file [MAX_FILENAME];
	} err_List;
#endif /*ERR_LIST_H*/





/*FUNCTION PROTOTYPE		--------------------------------------------*/
void set_err_List (err_List *head_l);
void err_enqueue (err_List *head_l, char* word, int err_id, int err_key);
void err_printlist(err_List *head_l, FILE *fd);
void err_freelist (err_List *head_l);
bool any_err (err_List *head_l);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/




/*---------------------------------------------------------------------------------------------*/
/*a_ טבלאות שגיאות*/
#ifndef Errors_H
#define Errors_H

#define E_MACRO_TO_LABEL 6 


typedef enum  
	{
		E_ALL_GOOD=0, 			/* no errore */

		E_macro_name_firs=1,		/*invalid macro name, the firs character must be a letter*/
		E_macro_name_double=2,		/*invalid macro name, icon with that name already exists*/
		E_macro_name_keywords=3,	/*invalid macro name, it is the name of the keywords */
		E_macro_name_len=4,		/*invalid macro name, the name is too long*/
		E_macro_name_character=5,	/*invalid macro name, invalid character*/
		E_macro_value=6,		/*invalid macro value*/
		
		E_label_name_firs=7,		/*invalid label name, the firs character must be a letter*/
		E_label_name_double=8,		/*invalid label name, icon with that name already exists*/
		E_label_name_keywords=9,	/*invalid label name, it is the name of the keywords */
		E_label_name_len=10,		/*invalid label name, the name is too long*/
		E_label_name_character=11,	/*invalid label name, invalid character*/

		E_dir_data_empty=12,		/*directive ".data" is empty */
		E_dir_data_comma=13,		/*directive ".data" too much comma */
		
		E_dir_string_empty=14,		/*directive ".string" is empty */
		E_dir_string_defined=15,	/*directive ".string"  not define well*/

		E_non_operand_src=16,		/*there is no source operand*/		
		E_addressing_src_illegel=17,	/*addressing source operand is illegel*/
		E_non_operand_dst=18,		/*there is no destination operand*/
		E_addressing_dst_illegel=19,	/*addressing destination operand is illegel*/
		E_cmd_not_exist=20,		/*the command not exist*/
		


		

		
	}type_errors;



#endif /*Errors_H*/
/*---------------------------------------------------------------------------------------------*/


