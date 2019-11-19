
# makefile for Assembler4

TARGET=Assembler4


OBJFILES =	Assembler4.o variables.o BasicFunc.o cleariputline.o symbol.o err_linkedList.o keywords.o enc_directive.o enc_instructions.o enc_label.o enc_macro.o arrays.o

HEDER = 	Assembler4.h variables.h BasicFunc.h cleariputline.h symbol.h err_linkedList.h keywords.h enc_directive.h enc_instructions.h enc_label.h enc_macro.h bool.h arrays.h


cc =gcc
CFLAGS =-g -ansi -Wall -pedantic
CFLAGS2 =-c -ansi -Wall -pedantic
LDFLAGS =-o



$(TARGET): $(OBJFILES) $(HEDER) 
	$(cc) $(CFLAGS) $(OBJFILES) $(LDFLAGS) $@


%.o: %.c %.h
	$(cc) $(CFLAGS2) $*.c $(LDFLAGS) $@ 







