#include<stdio.h>
#include<string.h>
#include<ctype.h>
typedef struct machine_opcode_table
{
char pnemonic[10];
int length;
}mot;
typedef struct symbol_table
{
char name[10],ra;
int lcval;
}st;
typedef struct base_table
{
int br;
int bv;
}bt;
void main()
{
	int lc=0,i,j,num,n=0,ind=0,p=0,loc[20],dflag,symval,min,diff,content,temp,offset;
	char label[10],opcode[10],operand1[10],operand2[30];
	char pot[8][6]={"DROP","END","START","USING","BALR","EQU","DS","DC"};
	char imperative[6][4]={"L","A","ST","SR","BCT","BR"};
	char declarative[2][3] = {"DC","DS"};
	mot m[15];
	st s[10];
	bt b[5];
	strcpy(m[0].pnemonic,"L")  ; m[0].length=4;
	strcpy(m[1].pnemonic,"A")  ; m[1].length=4;
	strcpy(m[2].pnemonic,"ST") ; m[2].length=4;
	strcpy(m[3].pnemonic,"SR") ; m[3].length=2;
	strcpy(m[4].pnemonic,"BR") ; m[4].length=4;
	strcpy(m[5].pnemonic,"BCT"); m[5].length=4;
	strcpy(m[6].pnemonic,"LR") ; m[6].length=2;
	strcpy(m[7].pnemonic,"LH") ; m[7].length=4;
	strcpy(m[8].pnemonic,"BNE"); m[8].length=4;
	strcpy(m[9].pnemonic,"C")  ; m[9].length=4;
	strcpy(m[10].pnemonic,"AR")  ; m[10].length=2;
	FILE *f1;
	loc[p]=lc; 
	f1=fopen("input.txt","r"); 
	fscanf(f1,"%s%s%s%s",label,opcode,operand1,operand2);
	while(!(feof(f1)))
	{
	printf("\n%s\t%s\t%s\t%s\t\t%d\n",label,opcode,operand1,operand2,loc[p]);
	p++;
	dflag=0;
	for(i=0;i<8;i++)
	{
	if(strcmp(pot[i],opcode)==0)
	{
		for(i=0;i<2;i++)
		{
			if(strcmp(declarative[i],opcode)==0)
			{
				dflag=1;
				strcpy(s[n].name,label); 
				s[n].lcval = lc;
				s[n].ra='R';
				n++;
			if(strcmp(operand1,"F")==0)
			{
				lc = lc+4; 
			}
			else if(strcmp(operand1,"H")==0)
			{
				lc = lc+2; 
			}
			else
			{
			num = atoi(operand1); 
			if(strcmp(operand2,"F")==0)
			{
				lc = lc+(4*num); 
			}
			else if(strcmp(operand2,"H")==0)
			{
				lc = lc+(2*num);
			}
			} 
			
			break;
			}
		}
		if(strcmp(opcode,"EQU")==0)
			{
				strcpy(s[n].name,label);
				s[n].lcval = atoi(operand1);
				s[n].ra='A';
				n++;
			}
		else if(strcmp(opcode,"START")==0)
			{
				lc= atoi(operand1);
			}
		else if(strcmp(opcode,"USING")==0)
			{
				b[ind].br = atoi(operand2);
				if(strcmp(operand1,"*")==0)
				{
					b[ind].bv = lc;
				}
				else
				{
					b[ind].bv = atoi(operand1);
				}
			ind++;
			}
			
		else 
		{
			if((strcmp(label,"?")==0) || (strcmp(opcode,"START")==0) || dflag==1)
				break;
			else
			{
				strcpy(s[n].name,label); 
				s[n].lcval = lc;
				s[n].ra='R';
				n++;
			}
		}
	break;
	}
	}//for
	for(i=0;i<6;i++)
	{
		if(strcmp(m[i].pnemonic,opcode)==0)
		{
		if(strcmp(label,"?")==0) 
			{;}
		else
		{
			strcpy(s[n].name,label); 
			s[n].lcval = lc;
			n++;
		}
		lc = lc+m[i].length;
		}
	}
	loc[p]=lc; 
	fscanf(f1,"%s%s%s%s",label,opcode,operand1,operand2);
	}//while
	printf("\nSYMBOL TABLE\nNAME\t\tLC VALUE\tREL/ABS\n");
	for(i=0;i<n;i++)
	{
	printf("%s\t\t%d\t\t%c\n",s[i].name,s[i].lcval,s[i].ra);
	}
	printf("\nBASE TABLE\nBASE REGISTER\tBASE VALUE\n");
	for(i=0;i<ind;i++)
	{
	printf("%d\t\t%d\n",b[i].br,b[i].bv);
	}
}
/*
INPUT FILE:
JOHN START 0 ?
? USING * 15
? L 1 FIVE
? A 1 FOUR
? ST 1 TEMP
FOUR DC F '4' 
FIVE DC F '5'
TEMP DS 1 F 

OUTPUT:
JOHN	START	0	?		0

?	USING	*	15		0

?	L	1	FIVE		0

?	A	1	FOUR		4

?	ST	1	TEMP		8

FOUR	DC	F	'4'		12

FIVE	DC	F	'5'		16

TEMP	DS	1	F		20

SYMBOL TABLE
NAME		LC VALUE	REL/ABS
FOUR		12		R
FIVE		16		R
TEMP		20		R

BASE TABLE
BASE REGISTER	BASE VALUE
15		0
*/