/*a_
*
*
*
*
*
*/


#include "Assembler4.h"

	extern s_List head_s_List;
	extern err_List head_err_List;		

int main(int argc, char **argv)
{
	FILE *fd;
	int file_num =1;
	
	set_s_List(&head_s_List);
	set_err_List(&head_err_List);
	
	
	printf("-----------------------------------------------------\n");
	while (file_num<argc)
	{
		
		char *str;
		str = strcpy(str,FOLDER_ADDRES);
		strcat(str,argv[file_num]);
		strcpy((&head_err_List)->name_file,argv[file_num]);
		
		if (!(fd=fopen(str,"r")))		/*a_ אם יש בעיה לפתוח את הקובץ*/
		{
			fprintf(stderr,"cannot opern The file %s\n",argv[argc]);	
		}
		else						/*a_ אם פתיחת הקובץ הייתה תקינה*/
		{
		printf("stert working on file: %d.\"%s\"\n",file_num,argv[file_num]);
			
		Works_file (fd);				/*a_ פונקציית עיבוד הקובץ*/
		fclose(fd);					/*a_ סגירת הקובץ לפני מעבר לקובץ הבא*/
		
		printf("finish work on file: %d.\"%s\"\n",file_num,argv[file_num]);
		printf("-----------------------------------------------------\n");
		}
		
	file_num++;
	err_freelist (&head_err_List);
	s_freelist (&head_s_List);
	}
	return 0;
}



/*a_ מעבר על קובץ*/
void Works_file (FILE *fd)
{
	
	first_processing(fd);					/*a_ מעבר ראשון על הקובץ*/
	
	if (!any_err(&head_err_List))				/*a_ האם קיימות שגיאות*/
	{
		/*update_data_address();*/			/*a_ עדכון בטבלת סמלים כתובות ל+100*/
		rewind(fd);					/*a_ מחזיר סמן לתחילת הקובץ*/
		second_processing(fd); 				/*a_ מעבר שני על הקובץ*/
		
		if (!any_err(&head_err_List))			/*a_ האם קיימות שגיאות*/
		{
			/*a_ יצירת קבצי פלט לפי צורך*/
			/*a_ */

		}
		else
		{
			/*a_ הדפסת שגיאות*/
		}
	}
	else 							/*a_ נמצאו שגיאות במעבר ראשון*/
	{
	/*a_ הדפסת שגיאות*/
	}
}
	
	
void first_processing(FILE *fd)	
{	
	char lineBuf [MAX_LEN_LINE];				/*a_ באפר לשמירת שורת פקודה אחת בכל פעם*/
	reset_dc();						/*a_ מאתחל מונה נתונים  */
	reset_ic();						/*a_ מאתחל מונה הוראות*/
	reset_linefile();					/*a_ מאתחל מונה שורות בקובץ*/ 
	
	fgets(lineBuf,MAX_LINE-1,fd);				/*a_ קולט שורה מהקובץ*/
	while (!feof(fd))
	{	
		enc_linefile();					/*a_ מעלה ב1 את המונה שורה*/
		if (!is_comment(lineBuf))
		{
			work_line(lineBuf);			/*a_ עובד על שורה בקובץ*/
		}
		fgets(lineBuf,MAX_LINE-1,fd); 			/*a_ קולט שורה מהקובץ*/
		
	}
	printf("num of line in file: %d\n",get_linefile ()); 	/*a_ מדפיס את כמות השורות בקובץ*/
	
	
	if(any_symbol(&head_s_List))
	{
	printf("\n\ns_List:\n");
	s_printlist(&head_s_List,stdout);
	}
	
	if(any_err(&head_err_List))
	{
	printf("\nerr_List:\n");
	err_printlist(&head_err_List,stdout);
	}
	printf("\n\n");
	
	print_all_arry();
	
}


void second_processing(FILE * fd)
{


}



/*a_ מעבר על שורות בקובץ*/
void work_line (char *lineBuf)
{
	if (!(is_empty_line (lineBuf))) 				/*a_ האם זה משפט רייק*/
	{
		lineBuf = clear_white_char(lineBuf);			/*a_ מנקה תוים לבנים מיותרים*/
		printf("\nMM1.%s\n",lineBuf);		/*P*/
		if (is_macro(lineBuf)) 					/*a_ האם זה מקרו*/
		{
			processing_macro(lineBuf);			/*a_ עיבוד מקרו*/
		}
		else
		{
			if (exists_label(lineBuf))			/*a_ האם קיימת תוית*/	
			{

				lineBuf = processing_label(lineBuf); 	/*a_ עיבוד תוית והחזרת מילה בלי*/

			}
			
			printf("\nMM2.%s\n",lineBuf);	/*P*/

			if (is_directive(lineBuf))			/*a_ האם זה הנחיה*/
			{

					
				processing_directive (lineBuf);		/*a_ פונקצית פיענוח משפט הנחיה*/
			}
			else						/*a_  זה הוראה*/
			{
				processing_instructions(lineBuf);	/*a_ פונקצית פיענוח משפט הוראה*/
				
			}	
		}
	}
	turnOff (F_ALL);
	
}


