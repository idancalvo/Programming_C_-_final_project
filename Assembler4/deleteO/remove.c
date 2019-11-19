#include <stdio.h>

char *str [] = {"Assembler4.o", "variables.o", "BasicFunc.o", "cleariputline.o", "symbol.o", "err_linkedList.o", "keywords.o", "enc_directive.o", "enc_instructions.o", "enc_label.o", "enc_macro.o","arrays.o","Assembler4"};

void clear_obj ();



int main ()
{

 clear_obj ();

return 0;
}



void clear_obj ()
{
	
	int i;
	
	for (i=0;i<13;i++)
	{
		remove(str[i]);
	}
}






