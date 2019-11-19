#include "enc_macro.h"


extern s_List head_s_List;
extern err_List head_err_List;


/*a_ האם זה מקרו*/
bool is_macro(char *lineBuf)
{
	char *strmacro =".define ";
	if ( !strncmp(lineBuf,strmacro,strlen(strmacro)))	/*a_ בודק האם המילה הראשונה היא .define*/
	{
		return true;
	}
	return false;
}



/*a_    מטפל שבורת מקרות בדיקה, הוספה, שגיאה*/
void processing_macro(char *lineBuf)
{
	char *m_name;
	char *m_value;
	type_errors statosErr = E_ALL_GOOD;
	
	m_name = macro_name(lineBuf);					/*a_מחזיק את שם המקרו*/
	m_value = macro_value(lineBuf);					/*a_מחזיק את ערך המקרו*/
	
	if (m_value==NULL||m_name==NULL)
	{
		err_enqueue (&head_err_List,"(null)",get_linefile (),E_macro_name_character);	
	}
	else
	{	
		if((statosErr=is_macro_name(m_name))==E_ALL_GOOD)		/*a_ האם שם מקרו תקין*/
		{
			if( (statosErr=is_macro_value (m_value)) ==E_ALL_GOOD)	/*a_ האם ערך מקרו תקין*/
			{
				/*a_ הוספת מקרו לטבלת סמלים*/
				s_add (&head_s_List,m_name,MACRO,str_to_int(m_value));	
			}	
			else							/*a_ ערך מקרו לא תקין*/
			{
				/*a_ הוספת שגיאה ערך לא תקין*/
				err_enqueue (&head_err_List,m_value,get_linefile (),statosErr);
			}
		}
		else								/*a_ שם מקרו לא תקין*/
		{
			/*a_ הוספת שגיאה שם לא תקין*/
			err_enqueue (&head_err_List,m_name,get_linefile (),statosErr);		
		}
	}
	free(m_name);
	free(m_value);
	
}


/*a_ האם השם של המקרו תקין*/
type_errors is_macro_name (char *m_name)
{
	int i;
	
	if(!isalpha(*m_name)) 				/*a_ תו ראשון הוא לא אות*/
	{
		return E_macro_name_firs;
	}
	if(s_search (&head_s_List,m_name,&i)) 		/*a_ לבדוק שלא קיים סמל בשם הזה*/
	{
		return E_macro_name_double;
	}
	if (is_keywords(m_name))			/*a_ לבדוק שזה לא מילה שמורה*/
	{
		return E_macro_name_keywords;
	}
	if (strlen(m_name)>MAX_LEN_LABEL) 		/*a_ שם ארוך מידי*/
	{
		return E_macro_name_len;
	}	
	if (!is_num_and_letters(m_name))		/*a_ מספרים ואותיות תוית חוקית*/
	{
		return E_macro_name_character;
	}
			
	return E_ALL_GOOD;					
}


/*a_ האם הערך של המקרו תקין*/
type_errors is_macro_value (char *value)
{
	
	char *p;

	if (value==NULL)
	{
		return E_macro_value;
	}
	
	p=value;
	if(*p!='+'&&*p!='-'&&!isdigit(*p))	/*a_ תו ראשון הוא או מספר או + או- */	
	{
		return E_macro_value;
	}
	p++;
	while (*p)
	{
		if(!isdigit(*p))		/*a_ יתר התוים חייבים להיות מספרים*/	
		{
			return E_macro_value;
		}
		p++;
	}
	return E_ALL_GOOD;
}


/*a_ בידוד שם המקרו משורת הפקודה*/
char *macro_name (char *lineBuf)
{
	int i,j,k;
	char *m_name;
	
	if (lineBuf)	
	{
		for (i=0;lineBuf[i]!=' '&&lineBuf[i]!='\t'&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++);
		for(;lineBuf[i]==' '||lineBuf[i]=='\t';i++);

		for (j=i;lineBuf[j]!='='&&lineBuf[j]!='\0'&&lineBuf[j]!='\n';j++);
		for(;lineBuf[j]=='='||lineBuf[j]==' '||lineBuf[j]=='\t';j--);
		j++;

		if(j>i)
		{
			m_name=(char*)malloc(j-i+1);

			for (k=0;i<j&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++)
			{
				m_name[k]=lineBuf[i];
				k++; 
			}
			m_name[k]='\0';
			return m_name;
		}
	}
	return NULL;
}

/*a_ בידוד ערך המקרו משורת הפקודה*/
char *macro_value (char *lineBuf)
{
int i,j,k;
	char *m_value;
	
	if (lineBuf)	
	{
		for (i=0;lineBuf[i]!='='&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++);
		for(;lineBuf[i]=='='||lineBuf[i]==' '||lineBuf[i]=='\t';i++);

		for (j=i;lineBuf[j]!='\0'&&lineBuf[j]!='\n';j++);
		j--;
		for(;lineBuf[j]==' '||lineBuf[j]=='\t';j--);
		j++;

		if(j>i)
		{
			m_value=(char*)malloc(j-i+1);

			for (k=0;i<j&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++)
			{
				m_value[k]=lineBuf[i];
				k++; 
			}
			m_value[k]='\0';
			return m_value;
		}
	}
	return NULL;
}






