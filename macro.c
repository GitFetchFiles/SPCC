#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MNT
{
	char MacroName[10];
	int MDTp;
}MNTob[10];

struct MDT
{
	char MacroDefinition[50];
}MDTob[10];

struct ALA
{
	char DummyArg[10];
	int Index;
}ALAob[5]; 

int main()
{
	 
	char ch,inst[20];
	
	FILE *fp;
	fp = fopen("macroip.txt", "r");
	
	printf("\n**************\nFile Contents:-\n\n");
	while( (ch=fgetc(fp)) != EOF)
   		printf("%c",ch);
   		
   	rewind(fp);
   	
	int mn=0,md=0,alap=0,z,i,flag=0;
   	while(fscanf(fp, "%s", inst)!=EOF)
   	{
   		if(strcmp(inst,"MACRO")==0)
   		{
   			fscanf(fp,"%s",inst);
   			strcpy(MNTob[mn].MacroName,inst);
   			MNTob[mn].MDTp=md;
   			mn++;
   			fscanf(fp,"%s",inst);
   			while(strcmp(inst,"1234")!=0)
   			{
   				ALAob[alap].Index=alap;
   				strcpy(ALAob[alap].DummyArg,inst);
   				alap++;
   				fscanf(fp,"%s",inst);
   			}
   			fscanf(fp,"%s",inst);
   			while(strcmp(inst,"MEND")!=0)
   			{
   				for(i=0;i<alap;i++)
				{
					if(strcmp(inst,ALAob[i].DummyArg)==0)
					{
						flag=1;
						if(i==0)
						strcpy(MDTob[md].MacroDefinition,"#0");
						else if(i==1)
						strcpy(MDTob[md].MacroDefinition,"#1");
						break;
					}
					else
					{
						flag=0;
					}
				}
				if(flag==0)
				{	
					strcpy(MDTob[md].MacroDefinition,inst);
				}
				md++;
   				fscanf(fp,"%s",inst);
   			}
			strcpy(MDTob[md].MacroDefinition,inst);	
		}
		
   	}
	
	int j;
	
	printf("\n\n**************\nMNT:-\n\nMacro Name\t\tMdtp\n\n");
	for(j=0;j<mn;j++)
		printf(" %s\t\t\t%d\n",MNTob[j].MacroName,MNTob[j].MDTp);
		
	printf("\n**************\nMDT:-\n\nMacro Definition\n\n");
	for(j=0;j<=md;j++)
	{
		if( strcmp(MDTob[j].MacroDefinition,"1234")==0)
		{
			printf("\n");
		}
		else
			printf("%s ",MDTob[j].MacroDefinition);
	}
		
	printf("\n\n**************\nALA:-\n\nIndex\t\tDummy Arguments\n\n");
	for(j=0;j<alap;j++)
		printf(" %d\t\t\t%s\n",ALAob[j].Index,ALAob[j].DummyArg);
	
		
	printf("**************\n");
	rewind(fp);

//for printing ala of pass 2
printf("\n\n**************\nALA:-\n\nIndex\t\tActual Arguments\n\n");
	int mdtp;
	FILE *fpw;

	fpw=fopen("MacroOutput.txt","w");
	while(fscanf(fp, "%s", inst)!=EOF)
   	{
		if(strcmp(inst,"MACRO")==0)
		{
			while(strcmp(inst,"MEND")!=0)
				fscanf(fp,"%s",inst);
			fscanf(fp,"%s",inst);
		}
		
		
		flag=0,j=0;
		for(i=0;i<mn;i++)
		{
			if(strcmp(inst,MNTob[i].MacroName)==0)
			{	
				mdtp=MNTob[i].MDTp;
				for(j=0;j<alap;j++)
				{
					fscanf(fp,"%s",inst);
					strcpy(ALAob[j].DummyArg,inst); //copying data1 and data2 in originbal ALA
					//strcpy(ALAob2[j].actualArg,ALAob[j].DummyArg);
					printf(" %d\t\t\t%s\n",ALAob[j].Index,ALAob[j].DummyArg);
					
				}
				
				while(strcmp(MDTob[mdtp].MacroDefinition,"MEND")!=0)
				{
					if(strcmp(MDTob[mdtp].MacroDefinition,"1234")==0)
						fprintf(fpw,"\n");
					else if(strcmp(MDTob[mdtp].MacroDefinition,"#0")==0)
						fprintf(fpw,"%s",ALAob[0].DummyArg);
					else if(strcmp(MDTob[mdtp].MacroDefinition,"#1")==0)
						fprintf(fpw,"%s",ALAob[1].DummyArg);
						
					else
						fprintf(fpw,"%s ",MDTob[mdtp].MacroDefinition);

					mdtp++;
				}
				flag=1;
				break;
			}
			else
			{
				flag=0;
			}
		}
		if(flag==0)
		{
			if(strcmp(inst,"1234")==0)
				fprintf(fpw,"\n");
			else
				fprintf(fpw,"%s ",inst);
		}
	}

	fclose(fpw);
	fpw =fopen("MacroOutput.txt","r");
	
	printf("\n**************\nFile Contents after pass2 of macro processor:-\n\n");
	while( (ch=fgetc(fpw)) != EOF)
   		printf("%c",ch);

	printf("\n************\n");
	return 0;
}

/*  Output:
c404@c404-OptiPlex-390:~/Desktop$ gcc Macrop.c
c404@c404-OptiPlex-390:~/Desktop$ ./a.out

**************
File Contents:-

MACRO
	INCR &ARG1 &ARG2
1234	L 1 &ARG1
1234	A 1 =F'5'
1234	ST 1 &ARG2
1234 	MEND

		L 1 =F'5'
1234	A 2 =F'2'
1234	INCR DATA1 DATA2
1234	DATA1 DC F '5'
1234	DATA2 DC F '10'
1234 END


**************
MNT:-

Macro Name		Mdtp

 INCR			0

**************
MDT:-

Macro Definition

L 1 #0 
A 1 =F'5' 
ST 1 #1 
MEND 

**************
ALA:-

Index		Dummy Arguments

 0			&ARG1
 1			&ARG2
**************


**************
ALA:-

Index		Actual Arguments

 0			DATA1
 1			DATA2

**************
File Contents after pass2 of macro processor:-

L 1 =F'5' 
A 2 =F'2' 
L 1 DATA1
A 1 =F'5' 
ST 1 DATA2

DATA1 DC F '5' 
DATA2 DC F '10' 
END 
************
c404@c404-OptiPlex-390:~/Desktop$ 
*/
