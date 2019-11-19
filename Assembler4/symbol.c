#include "symbol.h"



#define MAX_NAME 20



typedef struct s_node *ptr;

typedef struct s_node {
	char *s_name; 		/*שם הסמל*/
	properties s_prope;	/*a_מאפיינים = מקרו/קוד/דאטה*/
	int s_value; 		/*a_ערך סמל*/
	ptr next; 		/*איבר הבא ברשימה*/
	}s_node;


void set_s_List(s_List *head_l)
{
	head_l->first=NULL;
	head_l->last=NULL;
	head_l->num_of_item=0;

}	


/*a_ מוסיף מילה לסוף הרשימה*/
void s_add (s_List *head_l, char* s_name, properties s_prope, int s_value)
{
	ptr tempNode;
	tempNode = (ptr) malloc (sizeof(s_node));

	if (!tempNode)			
	{
		printf ("\n cannot allocate memory \n");
		exit(0);
	}

	tempNode->s_name = (char*) malloc (MAX_NAME*sizeof(char));
	strcpy(tempNode->s_name,s_name);
	tempNode->s_prope = s_prope;
	tempNode->s_value=s_value;
	tempNode->next = NULL;
	
	if (head_l->first==NULL)					/*a_ רשימה רייקה*/
	{
		head_l->first=tempNode;
		head_l->last=tempNode;
		head_l->num_of_item=0;
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

/*a_ s_valueמחפש שם בטבלה אם נמצא מחזיר אמת ואת הערך ב*/
bool s_search (s_List *head_l,char* s_name,int *s_value)
{
	ptr tempNode; 
	tempNode = head_l->first;
	
	if (head_l->first!=NULL)					/*a_ רשימה לא רייקה*/
	{
		while (tempNode->next)
		{
			if (!strcmp(tempNode->s_name,s_name))		/*אם המחרוזות זהות*/
			{
				*s_value=tempNode->s_value;
				return true;
			}
			tempNode = tempNode->next;
		}
		if (!strcmp(tempNode->s_name,s_name))			/*אם המחרוזות זהות*/
		{
			*s_value=tempNode->s_value;
			return true;
		}
	}
	return false;
}



int s_delete_macro (s_List *head_l)
{
	int ans = 0;
	ptr p1,p2;
	p2 = head_l->first;
	p1 = p2->next;
	

	while (p2->s_prope==MACRO)
	{
		head_l->first=p2->next;
		free(p2->s_name);
		free(p2);
		head_l->num_of_item--;
		ans++;	
		p2 = p1;
		p1 = p2->next;
	}
	while (p1)
	{
		if (p1->s_prope==MACRO)
		{
			p2->next= p1->next;
			free(p1->s_name);
			free(p1);
			p1=p2->next;
			head_l->num_of_item--;
			ans++;			
		}
		else
		{
		p2 = p1;
		p1 = p2->next;
		}
	}
	
	return ans;
}





/*a_ מדפיס את המילים*/
void s_printlist(s_List *head_l, FILE *fd)
{
	ptr tempNode;
	tempNode = head_l->first;
	while (tempNode->next)
	{
		fprintf(fd,"%s\t%d\n",tempNode->s_name,tempNode->s_value);
		tempNode = tempNode->next;
		
	}
	fprintf(fd,"%s\t%d\n",tempNode->s_name,tempNode->s_value);

}


void s_freelist (s_List *head_l)
{
	ptr p1;
	
	if (head_l->first)
	{
		p1 = head_l->first;
		while (p1)
		{
			head_l->first = p1->next;
			free(p1->s_name);
			free(p1);
			p1 = head_l->first;
			head_l->num_of_item--;
		}
		head_l->last =NULL;
	}  
}



/*a_ האם קיימות שגיאות?*/
bool any_symbol (s_List *head_l)
{
	if(head_l->num_of_item==0)
	{
		return false;
	}
	return true;	
}



/*a_ עדכון בטבלת סמלים כתובות ל+100*/
/*void update_data_address(s_List *head_l) 
{
	ptr p1;
	
	if (head_l->first)
	{
		p1 = head_l->first;
		while (p1)
		{
			if (p1->s_prope==DATA)
			{
				  p1->s_value+=get_ic()+START_ADRESS_DATA;
			}
			else
			{
				if (p1->s_prope==)
			
			}
			
			
			free();
			free(p1);
			p1 = head_l->first;
			head_l->num_of_item--;
		}
	}



}*/

/*---------------------------------------------------------------------------------------------*/


