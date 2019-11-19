#include "enc_directive.h"

#define NUM_OF_TYPE_DIR 4

extern s_List head_s_List;
extern err_List head_err_List;


/*a_ האם זה משפט הנחיה */
bool is_directive(char *lineBuf)
{
	int dir_type;
	char *dir_name;	

	dir_name =(char*)malloc(strlen(lineBuf));
	dir_name = strcpy(dir_name,lineBuf);
	dir_name = strtok(dir_name," \n\t,");
	dir_type = directives_to_int(dir_name);
	
	if (dir_type != _NOTEXIST && dir_type != _DEFINE)/*a_ בודק האם המילה הראשונה היא של משפט הוראה */
	{
		turnOn (dir_type);
		set_storage_Directive (dir_type);
		free(dir_name);
		return true;
	}

	free(dir_name);
	return false;
}


			
/*a_ פונקצית פיענוח משפט הנחיה*/
void processing_directive(char *lineBuf)
{
	
	switch (get_storage_Directive())
	{
		case _DATA:							/*a_ נתונים*/
			processing_data(lineBuf);	
        		break;
        	
        	case _STRING:							/*a_ סטרינג*/
			processing_string(lineBuf);
        		break;
 
        	case _ENTRY:							/*a_ יצוא משתנה*/
			processing_entry(lineBuf);	
        		break;
   
        	case _EXTERN:							/*a_יבוא משתנה חיצוני*/
			processing_extern(lineBuf);	
        		break;
		
		default:							/*a_ הנחיה לא תקינה*/
			err_enqueue (&head_err_List,"סטרינג- מילה בעייתית",get_linefile (),0/*סוג שגיאה*/); 
			
        }
	printf("directive\n");
}


/*------------------------------------------------------------------------------------------------

processing directive .data

------------------------------------------------------------------------------------------------*/


void processing_data(char *lineBuf)
{
	
	int i;
	int numOfComma=1;
	int NumOfData=0;
 					
	char *nextValue;
	type_errors statosErr = E_ALL_GOOD;
	
	
	for(i=0;lineBuf[i]!=' '&&lineBuf[i]!='\t'&&lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++);
	i++;
	lineBuf+=i;						/*a_ תחילת הערכים*/
	
	for (i=0;lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++)	/*a_ להגיע לסוף ולספור את כמות הערכים*/
	{
		if(lineBuf[i]==',')
		{
			numOfComma++;
		}
	}


	while (lineBuf && *lineBuf)
	{
		nextValue = next_data_value (&lineBuf);			/*a_ מפריד ערך בסטרינג*/
		
		if ((statosErr=is_macro_value (nextValue))==E_ALL_GOOD) /*a_ בודר האם זה ערך תקין*/
		{

			if (state_flag (F_LABEL)) 	/*a_ להוסיף את התוית לטבלת סמלים בתור דטה*/
			{
				 s_add (&head_s_List,get_storage_label(),DATA,get_dc());
				 turnOff (F_LABEL);
			}
			add_data (str_to_int(nextValue));		/*a_ מוסיף ערך לטבלת הנתונים*/
		}
		else 
		{
			/*a_ עדכון שגיאה שתתאים לדטה ולא למקרו*/
			err_enqueue (&head_err_List,nextValue,get_linefile (),statosErr);
		}
		NumOfData++;
		free(nextValue); 
	}
	

	if (NumOfData!=numOfComma)
	{
		statosErr = (NumOfData==0)? E_dir_data_empty:E_dir_data_comma;
		err_enqueue (&head_err_List,"(null)",get_linefile (),statosErr);
	}
	printf("data\n");
}



/*a_ בידוד ערך המקרו משורת הפקודה*/
char *next_data_value (char **P_lineBuf)
{
	int i,j,k;
	char *nextValue;
	char *lineBuf = *P_lineBuf;
	
	if (lineBuf)	
	{
		for (i=0; lineBuf[i]==' ' || lineBuf[i]=='\t';i++);
		
		for (j=i;lineBuf[j]!=','&&lineBuf[j]!='\0'&&lineBuf[j]!='\n';j++);
		
		*P_lineBuf = (lineBuf+j);
		if(**P_lineBuf==',')
		{
			(*P_lineBuf)++;
			while (**P_lineBuf==' '||**P_lineBuf=='\t')
			{
				(*P_lineBuf)++;
			}
		
		}
		
		j--;
		for(;lineBuf[j]==' '||lineBuf[j]=='\t';j--);
		j++;
		
		if(j>i)
		{
			nextValue=(char*)malloc(j-i+1);

			for (k=0;i<j&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++)
			{
				nextValue[k]=lineBuf[i];
				k++; 
			}
			nextValue[k]='\0';
			return nextValue;
		}
	}
	return NULL;
}


/*------------------------------------------------------------------------------------------------

processing directive .string

------------------------------------------------------------------------------------------------*/

void processing_string(char *lineBuf)
{
	int i,j;			
	type_errors statosErr = E_ALL_GOOD;
	
	for(i=0;lineBuf[i]!=' '&&lineBuf[i]!='\t'&&lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++);
	for(;lineBuf[i]==' '||lineBuf[i]=='\t';i++);
	lineBuf+=i;	
	
	for(i=0;lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++);
	for(;lineBuf[i]==' '||lineBuf[i]=='\t'||lineBuf[i]=='\n'||lineBuf[i]=='\0';i--);
	
	
	
	if (*lineBuf=='\"' && lineBuf[i]=='\"' && i!=0)
	{	
		if (state_flag(F_LABEL))
		{

			s_add (&head_s_List,get_storage_label(),DATA,get_dc());
			turnOff (F_LABEL);

		}
		for (j=1;j<i;j++)
		{
			add_data (lineBuf[j]);
		
		}
	}
	else
	{
		statosErr = (i==0)? E_dir_string_empty:E_dir_string_defined;
		err_enqueue (&head_err_List,lineBuf,get_linefile (),statosErr);
	}

	printf("string\n");
}




/*------------------------------------------------------------------------------------------------

processing directive .entry

------------------------------------------------------------------------------------------------*/
void processing_entry(char *lineBuf)
{
	/*type_errors statosErr = E_ALL_GOOD;*/
	printf("entry\n");
}

/*------------------------------------------------------------------------------------------------

processing directive .extern

------------------------------------------------------------------------------------------------*/
void processing_extern(char *lineBuf)
{

	int i;			
	type_errors statosErr = E_ALL_GOOD;
	
	for(i=0;lineBuf[i]!=' '&&lineBuf[i]!='\t'&&lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++);
	for(;lineBuf[i]==' '||lineBuf[i]=='\t';i++);
	lineBuf+=i;	
	
	for(i=0;lineBuf[i]!='\n'&&lineBuf[i]!='\0';i++);
	for(;lineBuf[i]==' '||lineBuf[i]=='\t'||lineBuf[i]=='\n'||lineBuf[i]=='\0';i--);
	i++;
	lineBuf[i]='\0';


	if((statosErr=is_macro_name(lineBuf))==E_ALL_GOOD)		/*a_ האם שם תוית תקין*/
	{
		s_add (&head_s_List,lineBuf,ENTRY,0);	

	}
	else	/*a_ תוית לא תקינה*/
	{
		err_enqueue (&head_err_List,lineBuf,get_linefile (),statosErr);
	}
	

	printf("extern\n");
}

/*------------------------------------------------------------------------------------------------*/






