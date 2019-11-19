#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*my header file 		--------------------------------------------*/
#include "bool.h"			/*a_ הגדרת משתנה בוליאני*/
#include "keywords.h"			/*a_ מילים שמורות ופיענוח שלהם*/
#include "err_linkedList.h"		/*a_ מנהל שגיאות*/
#include "symbol.h"			/*a_ טבלת סמלים*/
/*end my header file 		--------------------------------------------*/


#define MAX_LEN_LABEL 31 /*a_ אורך מקסימלי של תוית*/
#define MAX_LEN_LINE 100 /*a_ אורך מקסימלי של שורת פקודה אחת*/
#define START_ADRESS_DATA 100

#ifndef STATUS_FLAG_H
#define STATUS_FLAG_H
typedef enum {ON=1, OFF=0} statusFlag;
#endif /* STATUS_FLAG_H */

#ifndef OFLAGS_H
#define OFLAGS_H
typedef enum {F_ALL=0,F_LABEL=1, F_DIRECTIVE=2,F_COMMA=3} oFlags;
#endif /* OFLAGS_H*/




/*FUNCTION PROTOTYPE		--------------------------------------------*/
int get_ic (); 
int get_dc ();
int get_linefile ();
void reset_ic ();
void reset_dc (); 
void reset_linefile (); 
void enc_ic();
void enc_dc();
void enc_linefile();

void set_storage_label(char* str);
char *get_storage_label ();

void set_storage_Directive (dirOptions direc);
dirOptions get_storage_Directive ();

statusFlag state_flag (oFlags flag);
void turnOn (oFlags flag);
void turnOff (oFlags flag);

void clear_storageLabel ();

/*end - FUNCTION PROTOTYPE 	--------------------------------------------*/
