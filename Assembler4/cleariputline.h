#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 100 /*a_ אורך מקסימלי של שורת פקודה אחת*/

/*	FUNCTION PROTOTYPE	*/
char *fix_comma (char *lineBuf);
void copy_string (char **pt1, char **pt2);
char *clear_white_char(char*);
