#include "keywords.h"


/*---------------------------------------------------------------------------------------------------*/

#define NUM_OF_REGISTER 8
#define NUM_OF_DIRECTIVES 5
#define NUM_OF_CMD 16
#define LEBEL_LEN_MAX 31



char *tableCmd[]= {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

char *registers[] = {"r0","r1","r2","r3","r4","r5","r6","r7"};

char *directives[] = {".data",".string",".entry",".extern",".define"};

			

bool is_keywords (char *str)
{
	if (word_to_Commands(str)!=_NOTEXIST)
	{
		return true;
	}
	if (register_to_int(str)!=_NOTEXIST)
	{
		return true;
	}
	if (directives_to_int(str)!=_NOTEXIST)
	{
		return true;
	}
	return false;
}

/*a_ מתרגם הנחיה לאינט*/
int directives_to_int (char * str_d)
{
	int i;
	for (i=0;i<NUM_OF_DIRECTIVES;i++)
	{
		if (!strcmp(directives[i],str_d))
		{
			return i;
		}
	}
	return _NOTEXIST;
}

/*a_ מתרגם רגיסטר לאינט*/
int register_to_int (char * str_r)
{
	int i;
	for (i=0;i<NUM_OF_REGISTER;i++)
	{
		if (!strcmp(registers[i],str_r))
		{
			return i;
		}
	}
	return _NOTEXIST;
}



/*a_ מתרגם פקודה לאינט*/
tableCommands word_to_Commands (char *word)
{
	int i;
	for (i=0;i<NUM_OF_CMD;i++)
	{
		if (!strcmp(tableCmd[i],word))
		{
			return i;
		}
	}
	return _NOTEXIST;
}


/*---------------------------------------------------------------------------------------*/








addressing word_to_addressing (char *word)
{
	if (*word == '#')				/*a_מיעון מיידי*/
	{
		return _IMMEDIATE;
	}	
	else
	{
		/*a_ רגיסטר*/
		if ((*word=='r')&&(atoi((word+1))>=0)&&(atoi((word+1))<NUM_OF_REGISTER)&&*(word+2)=='\0')
		{
			return _REGISTER;
		}
		else
		{
			if (is_index_addressing(word))	/*a_ אינדקס*/
			{
				return _INDEX;
			}
			else				/*a_ ישיר*/
			{
				return _DIRECT;
			}
		}
	}
}




bool is_index_addressing (char * word)
{

	int i;	
	for(i=0;word[i]==' '||word[i]=='\t';i++);
	word+=i;

	for(i=0;word[i]!='[' && word[i]!='\0'&& word[i]!='\n';i++);
	word+=i;

	for(i=0;word[i]!=']' && word[i]!='\0'&& word[i]!='\n';i++);
	
	if (word[i]=='[')
	{
		return true;	
	}
	
	return false;
}



