#include "BasicFunc.h"

	extern s_List head_s_List;
	extern err_List head_err_List;
	

/*a_ בודק האם השורה היא הערה*/
bool is_comment (char *lineBuf) 
{
	if (*lineBuf==';')				/*a_ בודר האם השורה מתחילה ב;*/
		return true;
	return false;
}


/*a_ בודק האם השורה היא שורה רייקה(תוים לבנים)*/
bool is_empty_line (char *lineBuf)
{
	char *p;
	p=lineBuf;
	while(*p != '\n')				/*a_ עובר על כל השורה */
	{
		if (((*p)!=' ')&&((*p)!='\t')) 		/*a_ מספיק שמצא תו אחד שהוא לא לבן מחזיר שקר*/
			return false;
		p++;
	}

	return true;
}

/*a_ האם הסטרינג מורכב רק מאותיות ומספרים*/
bool is_num_and_letters(char *word)
{
	char *p;
	p=word;
	
	while (*p)
	{
		if(!isalnum(*p)&&(*p!='\n'))
		{
			return false;
		}
		p++;
	}
	return true;
}


int str_to_int (char *word)
{
	
	/*int ans;*/
	char *p1=word;
	char *p2=word;
	
	
	while (*p1==' ' || *p1=='\t')
	{
		p1++;
	}
	p2=p2;
	while (*p2!='\0' && *p2!='\n')
	{
		p2++;
	}
	while (*p2==' ' || *p2=='\t'||*p2=='\0' || *p2=='\n')
	{
		p2--;
	}
	p2++;
	*p2='\0';
	
	return atoi(p1);
}





