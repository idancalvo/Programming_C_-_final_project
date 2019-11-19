		#include "enc_label.h"

extern s_List head_s_List;
extern err_List head_err_List;

/*a_ האם קיים תוית*/					
bool exists_label (char *lineBuf)
{
	int i;
	for (i=0; lineBuf[i]!='\0'&&lineBuf[i]!='\n'&&lineBuf[i]!=':'&&lineBuf[i] !='\"'; i++);

	if (lineBuf[i]==':')
	{

		return true;
	}

	return false;
}

/*a_ מעבד תוית*/
char *processing_label(char *lineBuf)
{
	
	char *l_name;
	type_errors statosErr = E_ALL_GOOD;

	l_name = label_name(lineBuf);					/*a_מחזיק את שם התוית */
	lineBuf = clear_label(lineBuf);

	
	
	if (l_name==NULL)
	{
		err_enqueue (&head_err_List,"(null)",get_linefile (),E_label_name_character);
	}
	else
	{	
		if((statosErr=is_label_name(l_name))==E_ALL_GOOD)		/*a_ האם שם תוית תקין*/
		{
			/*a_ תוית תקינה*/
			turnOn (F_LABEL);					/*a_ הדלק דגל של תוית*/
			set_storage_label(l_name);

		}
		else								/*a_ שם תוית לא תקין*/
		{
			/*a_ הוספת שגיאה שם לא תקין*/
			err_enqueue (&head_err_List,l_name,get_linefile (),statosErr);		
		}
	}
	free(l_name);
	
	return 	lineBuf;	
	
}


char *label_name(char *lineBuf)
{
	int i,j,k;
	char *l_name;
	

	if (lineBuf)	
	{
		for(i=0;lineBuf[i]==' '||lineBuf[i]=='\t';i++);

		for (j=i;lineBuf[j]!=':'&&lineBuf[j]!='\0'&&lineBuf[j]!='\n';j++);

		for(;lineBuf[j]==':'||lineBuf[j]==' '||lineBuf[j]=='\t';j--);
		j++;

		if(j>i)
		{
			l_name = (char*)malloc(j-i+1);

			for (k=0;i<j&&lineBuf[i]!='\0'&&lineBuf[i]!='\n';i++)
			{
				l_name[k]=lineBuf[i];
				k++; 
			}
			l_name[k]='\0';

			return l_name;
		}
	}
	return NULL;
}




/*a_ מקבל סטרינג מנקה ממנו את התוית ושומר את התוית במקום ידוע (קובץ משתנים)*/
char *clear_label(char *lineBuf)
{
	int i;
	;
	
	for (i=0;lineBuf[i]!=':';i++);
	for (;lineBuf[i]==' '||lineBuf[i]=='\t'||lineBuf[i]==':';i++);
	
	return (lineBuf+i);
}


		
/*a_ האם השם של התוית תקין*/
type_errors is_label_name (char *label)
{	
	type_errors statosErr;
	 
	statosErr = is_macro_name(label);		/*a_ חוקיות תוים היא כמו של מקרו*/
	
	if (statosErr==E_ALL_GOOD)			/*a_ הכל תקין*/
	{
	return E_ALL_GOOD;
	
	}
	
	return  (statosErr + E_MACRO_TO_LABEL);		/*a_ הייסט משגיאות של מקרו*/
}








