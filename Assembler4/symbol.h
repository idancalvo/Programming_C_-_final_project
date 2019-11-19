#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
/*end my header file 		--------------------------------------------*/



#ifndef PROPERTIES_H
#define PROPERTIES_H
typedef enum  {MACRO = 0, CODE=1, DATA=2, ENTRY=3} properties; /*a_ מאפיינים*//*a_מאפיינים = מקרו/קוד/דאטה*/
#endif /*PROPERTIES_H*/


#ifndef S_LIST_H
#define S_LIST_H
typedef struct s_List {
	void* first;
	void* last;
	int num_of_item;
	} s_List;
#endif /*S_LIST_H*/






/*FUNCTION PROTOTYPE		--------------------------------------------*/
void set_s_List(s_List *head_l);
void s_add (s_List *head_l, char* s_name, properties s_prope, int s_value);
bool s_search (s_List *head_l,char* s_name,int *s_value);
void s_printlist(s_List *head_l, FILE *fd);
void s_freelist (s_List *head_l);
int s_delete_macro (s_List *head_l);
bool any_symbol (s_List *head_l);
/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
