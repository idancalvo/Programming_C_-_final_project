#include "enc_instructions.h"

extern s_List head_s_List;
extern err_List head_err_List;


/*a_ פונקצית פיענוח משפט הוראה*/
void processing_instructions(char *lineBuf)
{
	char *cmd = NULL;
	char *ope1 = NULL;
	char *ope2= NULL;
	int nomOfOperator = 0;
	tableCommands command = _NOTEXIST;
	addressing adOpe1 = _NON;
	addressing adOpe2 = _NON;
	type_errors statosErr = E_ALL_GOOD;	
	
	cmd = processing_command (&lineBuf);
	ope1 = processing_ope1 (&lineBuf);
	ope2 = processing_ope2 (&lineBuf);
	nomOfOperator = num_of_operator (cmd,ope1,ope2);
	
	printf("\n\ncmd:%s\n",cmd);
	printf("operator1:%s\n",ope1);
	printf("operator2:%s\n",ope2);
	printf("nomOfOperator:%d\n\n",nomOfOperator);
	
	
	if(cmd)
	command	= word_to_Commands (cmd);
	
	if (command==_NOTEXIST)						/*a_ בעיה בפקודה*/
	{
		err_enqueue (&head_err_List,cmd,get_linefile (),E_cmd_not_exist);		
	}	
	else
	{
		if (ope1)
		{
			adOpe1 = word_to_addressing (ope1);	/*a_ מחזיר שיטת מיעון לאופרנד 1*/
		}
		
		if (ope2)
		{
			adOpe2 = word_to_addressing (ope2);	/*a_ מחזיר שיטת מיעון לאופרנד 2*/
		}
		else 
		{
			ope2=ope1;
			adOpe2 = adOpe1;
			ope1=NULL;
			adOpe1 = _NON;
		}

		printf("adOpe1:%d\n",adOpe1);
		printf("adOpe2:%d\n",adOpe2);	
		
		
		statosErr = is_operand1(command,adOpe1);	/*a_ בדיקת תקינות האופרנד1*/

		if (statosErr == E_ALL_GOOD)
		{
			statosErr = is_operand2(command,adOpe2);	/*a_ בדיקת תקינות האופרנד2*/

			if (statosErr == E_ALL_GOOD)
			{
				add_instructions(command,ope1,adOpe1,ope2,adOpe2);
			}
			else
			{
				err_enqueue (&head_err_List,ope2,get_linefile (),statosErr);
			}
		}
		else
		{
			err_enqueue (&head_err_List,ope1,get_linefile (),statosErr);
		}
	}
	
	printf("instructions\n");
}






char *processing_command (char **lineBuf)
{
	int i;
	char *cmd;
		
	for(i=0;(*lineBuf)[i]==' '||(*lineBuf)[i]=='\t';i++);
	(*lineBuf)+=i;
	cmd = (*lineBuf);

	for(i=0;(*lineBuf)[i]!=' '&&(*lineBuf)[i]!='\t'&&(*lineBuf)[i]!='\n'&&(*lineBuf)[i]!='\0';i++);
	
	
	
	if ((*lineBuf)[i]==' '||(*lineBuf)[i]=='\t')
	{
		cmd[i]='\0';
		i++;
	}
	else
	{
		cmd[i]='\0';
	}

	(*lineBuf)+=i;
	
	return cmd;
}



char *processing_ope1 (char **lineBuf)
{
	int i;
	char *templine = *lineBuf;
	char *ope1;
		
	for(i=0;templine[i]==' '||templine[i]=='\t';i++);
	templine+=i;
	ope1 = templine;
	
	if (*ope1 == '\0' || *ope1 =='\n')
	{
		ope1 = NULL;
	}
	else
	{
		for(i=0;templine[i]!=','&&templine[i]!='\n'&&templine[i]!='\0';i++);
		if (templine[i]==',')
		{
			i++;
		}			
		templine+=i;
		
		for(i=-1;templine[i]==','||templine[i]==' '||templine[i]=='\t';i--);
		i++;
		templine[i]='\0';
	}

	(*lineBuf) = templine;
	return ope1;
}




char *processing_ope2 (char **lineBuf)
{
	int i;
	char *templine = *lineBuf;
	char *ope2;
		
	for(i=0;templine[i]==' '||templine[i]=='\t';i++);
	templine+=i;
	ope2 = templine;
	
	if (*ope2 == '\0' || *ope2 =='\n')
	{
		ope2 = NULL;
	}
	else
	{
		for(i=0;templine[i]!=' '&&templine[i]!='\t'&&templine[i]!='\n'&&templine[i]!='\0';i++);
		templine+=i;
		
		ope2[i]='\0';
		templine+=i;
	}

	(*lineBuf) = templine;
	return ope2;
}


int num_of_operator (char *cmd,char *ope1,char *ope2)
{
	if (cmd!=NULL)
	{
		if (ope1!=NULL)
		{
			if(ope2!=NULL)
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
		else
		{
		return 0;
		}
	}
	else
	{
		return -1;
	}
}



bool arry[16][2][4]= {
	/*0-mov*/{{1,1,1,1},{0,1,1,1}},		/*1-cmp*/{{1,1,1,1},{1,1,1,1}},
	/*2-add*/{{1,1,1,1},{0,1,1,1}},		/*3-sub*/{{1,1,1,1},{0,1,1,1}},
	/*4-not*/{{0,0,0,0},{0,1,1,1}},		/*5-clr*/{{0,0,0,0},{0,1,1,1}},
	/*6-lea*/{{0,1,1,0},{0,1,1,1}},		/*7-inc*/{{0,0,0,0},{0,1,1,1}},
	/*8-dec*/{{0,0,0,0},{0,1,1,1}},		/*9-jmp*/{{0,0,0,0},{0,1,0,1}},
	/*10-bne*/{{0,0,0,0},{0,1,0,3}},	/*11-red*/{{0,0,0,0},{0,1,1,1}},
	/*12-prn*/{{0,0,0,0},{1,1,1,1}},	/*13-jsr*/{{0,0,0,0},{0,1,0,1}},
	/*14-rts*/{{0,0,0,0},{0,0,0,0}},	/*15-stop*/{{0,0,0,0},{0,0,0,0}}
	};	


/*a_ בודק שיטות מיעון תואמות לפעולה*/	
type_errors is_operand1 (tableCommands command, addressing adOpe1)
{
	if (adOpe1==_NON)
	{
		int i;
		for (i=0;i<4;i++)
		{
			if(arry[command][0][i])
			{
				return E_non_operand_src;	/*a_ חסר אופרנד 1*/
			}	
		}
	}
	else
	{
		if (!arry[command][0][adOpe1])
		{
			return	E_addressing_dst_illegel;		/*a_אופרנד יעד לא מתאים לפקודה*/
		}
		else
		{
				
		
		
		}
		
		
		
		
	}
	
	return E_ALL_GOOD;
}


/*a_ בודק שיטות מיעון תואמות לפעולה*/	
type_errors is_operand2 (tableCommands command, addressing adOpe2)
{
	if (adOpe2==_NON)
	{
		int i;
		for (i=0;i<4;i++)
		{
			if(arry[command][1][i])
			{
				return E_non_operand_dst;	/*a_ חסר אופרנד 2*/
			}	
		}
	}
	else
	{
		if (!arry[command][1][adOpe2])
		{
			return	E_addressing_src_illegel; 		/*a_אופרנד מקור לא מתאים לפקודה*/
		}
	}
	
	return E_ALL_GOOD;
}



/*
type_errors is_immediate ()
{

}


type_errors is_direct ()
{

}


type_errors is_index ()
{

}


type_errors is_register ()
{

}

*/

/*_NON=-1,_IMMEDIATE=0, _DIRECT=1, _INDEX=2, _REGISTER=3*/


void add_instructions(tableCommands command,char *ope1, addressing adOpe1, char *ope2,addressing adOpe2)
{
	int i;
	int numOfLine = how_many_lines(adOpe1,adOpe2);
	int ARE [numOfLine-1];
	int value [numOfLine-1];
	
	
	
	/*a_ לסדר את המספרים והARE*/
	
	operand_to_int(ope1,value,&i);
	operand_to_int(ope2,value,&i);
	
	
	
	add_inst_frs (adOpe1,adOpe2,command);
	if(adOpe1==_REGISTER&&adOpe2==_REGISTER)			/*a_ שני גיסטרים*/
	{
		add_inst_reg (dstRegister,srcRegister);
	}
	else								/*a_ לפחות אחד הוא לא רגיסטר*/
	{
		if(adOpe1==_REGISTER)					/*a_ 1 הוא רגיסטר*/
		{
			add_inst_reg (0,srcRegister);
		}
		else
		{
			add_inst_sec (ARE,value_adOpe1);		/*1 לא רגיסטר*/
			if (adOpe1==_INDEX)				
		 	{
		 		add_inst_sec (ARE,value_adOpe1);	/*a_ 1 הוא אינדקס*/
			}
		}
		if(adOpe2==_REGISTER)					/*a_ 2 הוא רגיסטר*/
		{
			add_inst_reg (0,srcRegister);
		}
		else
		{
			add_inst_sec (ARE,value_adOpe2);		/*2 לא רגיסטר*/
			if (adOpe2==_INDEX)				
		 	{
		 		add_inst_sec (ARE,value_adOpe2);	/*a_ 2 הוא אינדקס*/
			}
		}
	 }	
}



int how_many_lines(addressing adOpe1,addressing adOpe2)
{
	int numOfLine;
	if (adOpe1==_REGISTER && adOpe2==_REGISTER)
	{
		numOfLine=2;
	}
	else
	{
		numOfLine = 3;
		if (adOpe1==_INDEX)
		{
		numOfLine++;
		}
		if (adOpe2==_INDEX)
		{
		numOfLine++;
		}
	}
	return numOfLine;
}



/**/
void operand_to_int(char *ope,int *value,int *i)
{
i אינדקס המערך
value מערך לשמור נתונים
ope מה לפענח


}














