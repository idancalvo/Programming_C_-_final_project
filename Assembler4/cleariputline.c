#include "cleariputline.h"



/*a_ מנקה תוים לבנים*/
char *clear_white_char(char *lineBuf)
{
	char *p1;
	char *p2;
	char newline [MAX_LINE];
	
	p1=lineBuf;
	p2=newline;
	
	while ( (*p1) && (isspace(*p1)) && (*p1!='\n') ) 	/*a_ דילוג על רווחים וטאבים לפני מילה ראשונה*/
	{
		p1++;
	}
	
	while ( (*p1) && (*p1!='\n') )				/*a_ כל עוד יש עוד תוים*/
	{
		while ( (*p1) && (!isspace(*p1))  )		/*a_ מעתיק תוים לא לבנים*/
		{			
			if((*p1=='"'))				/*a_ אם מתחיל סטרינג להעתיק הכל*/
			{
				copy_string (&p1,&p2);		/*a_ מעתיק את כל הסטרינג */	
			}
			else					/*a_ העתקת תוים רגילים*/
			{
				*p2=*p1;
				p1++;
				p2++;
			}
		}
		
		if ( (*p1) && (*p1!='\n') )			/*a_ הוספת רווח בודד בין מילים*/
		{
			*p2=' ';
			p2++;
		}
		
		/*a_ התגלה תו לבן*/
		
		while ( (*p1) && (isspace(*p1)) && (*p1!='\n') )	/*a_ דילוג על רווחים וטאבים*/
		{
			p1++;
		}	
	}
	
	*p2='\0';						/*a_ סגירת מחרוזת*/
	
	strcpy(newline,fix_comma(newline));			/*a_ סדר פסיקים*/
	lineBuf = strcpy(lineBuf,newline);			/*מחזיר לבאפר את המילה*/
	
	return lineBuf;
}



/*a_ מקבל מחרוזת ומנקה רווחים לפני פסיק ומוסיף רווח אחריו */
char *fix_comma (char *lineBuf)
{
	char *p1;
	char *p2;
	char newline [MAX_LINE];
	
	p1=lineBuf;
	p2=newline;
	
	while (*p1)						/*a_ כל עוד יש עוד תוים*/
	{
		if((*p1=='"'))					/*a_ אם מתחיל סטרינג להעתיק הכל*/
		{
			copy_string (&p1,&p2);			/*a_ מעתיק את כל הסטרינג */
		}
		
		if (*p1==',')					/*a_ אם התגלה פסיק */
		{
			while (*(p2-1)==' ')			/*a_ מחיקת כל הרווחים לפני הפסיק*/
			{
			p2--;
			}
			if ( (*(p1+1)) && *(p1+1)!=' ')		/*a_ אם אין רווח אחרי הפסיק מוסיף אחד*/
			{
				*p2=*p1;
				p2++;
				*p1=' ';
			}
		}
		*p2=*p1;
		p1++;
		p2++;
	}
	*p2=*p1;
	
	lineBuf = strcpy(lineBuf,newline);			/*a_ מחזיר לבאפר את המילה*/
	return lineBuf;
}


/*a_ מעתיק סטרינג כמו שהוא*/
void copy_string (char **p1, char **p2)
{

		
	(*(*p2))=*(*(p1));
	(*p1)++;
	(*p2)++;
	
	while ( (*(*p1)) && (*(*p1))!='"')			/*a_ כל עוד אין עוד " ואז נגמר הסטרינג*/
	{
		*(*p2)=*(*p1);
		(*p1)++;
		(*p2)++;
	}
	
	if((**p1=='"'))						/*a_ מעתיק את " האחרון אם יש*/
	{
		*(*p2)=*(*p1);
		(*p1)++;
		(*p2)++;
	}

}


