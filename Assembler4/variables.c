#include "variables.h"

s_List head_s_List;
err_List head_err_List;

static int IC;
static int DC;
static int linefile;


int get_ic () 
{ return IC;}

int get_dc ()
{return DC;}

int get_linefile ()
{return linefile;}

void reset_ic ()
{IC=0;}

void reset_dc () 
{DC=0;}

void reset_linefile () 
{linefile=0;}

void enc_ic() 
{IC++;}

void enc_dc() 
{DC++;}

void enc_linefile() 
{linefile++;}


/*---------------------------*/

char storageLabel [MAX_LEN_LABEL];
dirOptions storageDirective;


static statusFlag label_flag;
static statusFlag directive_flag;
static statusFlag comma_flag;


statusFlag state_flag (oFlags flag)
{
	bool ans;	
	
	switch (flag)
	{
		case F_LABEL:
			ans = label_flag;
        	break;
        	
        	case F_DIRECTIVE:
			ans = directive_flag;
        	break;
		case F_COMMA:
			ans = comma_flag;
        	break;

	default:;
        
	}
        return ans;
}


void turnOn (oFlags flag)
{

	switch (flag)
	{
		case F_LABEL:
			label_flag = ON;
        	break;
        	
        	case F_DIRECTIVE:
			directive_flag = ON;
        	break;
		case F_COMMA:
			comma_flag = ON;
        	break;
		default:;

        }
}


void turnOff (oFlags flag)
{
	switch (flag)
	{
		case F_ALL:
			turnOff (F_LABEL);
			turnOff (F_DIRECTIVE);
			turnOff (F_COMMA);
        	break;

		case F_LABEL:
			label_flag = OFF;
			clear_storageLabel ();
        	break;
        	
		case F_DIRECTIVE:
			directive_flag = OFF;
        	break;
		
		case F_COMMA:
			comma_flag = OFF;
        	break;

	}
}


/*a_ לשמור מה ההוראה*/
void set_storage_Directive (dirOptions direc)
{
	storageDirective=direc;
}

/*a_ לקבל מה ההוראה חזרה*/
dirOptions get_storage_Directive ()
{
	return storageDirective;
}

/*a_ לשמור את התוית*/
void set_storage_label(char* Label)
{
	int i;
	clear_storageLabel ();
	for(i=0;Label[i]!='\0';i++)
	{
		storageLabel[i]=Label[i];
	}
	storageLabel[i]='\0';
}

/*a_ לקבל את התוית חזרה*/
char *get_storage_label ()
{
	return storageLabel;
}


void clear_storageLabel ()
{
	int i;
	for(i=0;i<strlen(storageLabel);i++)
	{
		storageLabel[i]='\0';
	}
}








