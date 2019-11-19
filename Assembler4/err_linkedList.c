#include "err_linkedList.h"



char *Errors[] = {
		/*0*/	"no errore",
			
		/*1*/	"invalid macro name, the firs character must be a letter",
		/*2*/	"invalid macro name, icon with that name already exists",
		/*3*/	"invalid macro name, it is the name of the keywords",
		/*4*/	"invalid macro name, the name is too long",
		/*5*/	"invalid macro name, invalid character",
		/*6*/	"invalid macro value",

		/*7*/	"invalid label name, the firs character must be a letter",
		/*8*/	"invalid label name, icon with that name already exists",
		/*9*/	"invalid label name, it is the name of the keywords",
		/*10*/	"invalid label name, the name is too long",
		/*11*/	"invalid label name, invalid character",

		/*12*/	"directive \".data\" is empty",
		/*13*/	"directive \".data\" too much comma",
		
		/*14*/	"directive \".string\" is empty",
		/*15*/	"directive \".string\"  not define well",	
		
		/*16*/	"there is no source operand",	
		/*17*/	"addressing source operand is illegel",
		/*18*/	"there is no destination operand",
		/*19*/	"addressing destination operand is illegel",
		/*20*/	"the command not exist",	
		
		
		/*21*/
		/*22*/
		/*23*/
		/*24*/
		/*25*/
		/*26*/
		/*27*/	
		


		};
			

/*a_רשימה מקושרת של שגיאות*/


#define MAX_WORD 20

typedef struct err_node *ptr;

typedef struct err_node {
	char *err_word;
	int err_line; /*מה השורת שגיאה*/
	int err_key;/*a_ איזו סוג שגיאה יש*/
	ptr next; /*איבר הבא ברשימה*/
	}err_item;



void set_err_List (err_List *head_l)
{
	head_l->first=NULL;
	head_l->last=NULL;
	head_l->num_of_item=0;
}



void print_1_err(FILE *fd ,char* name_file,ptr tempNode);

	


/*a_ מוסיף שגיאה לסוף הרשימה*/
void err_enqueue (err_List *head_l, char* err_word, int err_line, int err_key)
{
	ptr tempNode;
	tempNode = (ptr) malloc (sizeof(err_item));

	if (!tempNode)			
	{
		printf ("\n cannot allocate memory \n");
		exit(0);
	}
	
	tempNode->err_word=NULL;
	if (err_word)
	{
	tempNode->err_word=(char*) malloc (strlen(err_word));
	strcpy(tempNode->err_word,err_word);
	}
	
	
	tempNode->err_line = err_line;
	tempNode->err_key = err_key;
	tempNode->next = NULL;
	
	if (head_l->first==NULL)/*a_ רשימה רייקה*/
	{
		head_l->first=tempNode;
		head_l->last=tempNode;
	}	
	else
	{
		ptr temp_p;
		temp_p = head_l->last;
		temp_p->next = tempNode;
		head_l->last = tempNode;
	
	}

	head_l->num_of_item++;
}



/*a_ מדפיס את השגיאות מהסוף להתחלה*/
void err_printlist(err_List *head_l, FILE *fd)
{
	ptr tempNode;
	tempNode = head_l->first;
	
	while (tempNode->next)
	{
		
		print_1_err(fd,head_l->name_file,tempNode);
		tempNode = tempNode->next;
	}
	
	print_1_err(fd,head_l->name_file,tempNode);
	
	fprintf (fd,"num of error = %d \n",head_l->num_of_item);	
	
	
}

void print_1_err(FILE *fd ,char* name_file,ptr tempNode)
{

		fprintf(fd,"in file: %s, ",name_file);

		fprintf(fd,"line:%d\n",tempNode->err_line);
		
		fprintf(fd,"error: \"%s\", %s\n\n",tempNode->err_word,Errors[tempNode->err_key]);

}


void err_freelist (err_List *head_l)
{
	ptr p1;
	
	if (head_l->first)
	{
		p1 = head_l->first;
		while (p1)
		{
			head_l->first = p1->next;
			free(p1->err_word);
			free(p1);
			p1 = head_l->first;
			head_l->num_of_item--;
		}
		head_l->last =NULL;
	}  
}


/*a_ האם קיימות שגיאות?*/
bool any_err (err_List *head_l)
{
	if(head_l->num_of_item==0)
	{
		return false;
	}
	return true;	
}



/*---------------------------------------------------------------------------------------------*/


