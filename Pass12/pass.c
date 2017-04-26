
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct mot
{
	int len;
	char inst[10];
}m[3];

struct pot
{
	char dir[20];
}p[5];

struct st
{
	char name[20];
	int val;
	int length;
	char reloc[5];
}s[10];

struct bt
{	
	char reg[10];
	int content;
}b[20];
	
struct Pass
{
	char c[10];
	int n;
	int offset;
	int index;
	int base;
}pass[10];

void main()
{
	char s1[10],s2[10],s3[10],s4[10];
	int lc=0,l=0;
	int i,j=0,k=0;
	int offset,index,base;

	strcpy(m[0].inst,"L");
	strcpy(m[1].inst,"A");
	strcpy(m[2].inst,"ST");

	m[0].len=4;
	m[1].len=4;
	m[2].len=4;

	strcpy(p[0].dir,"START");
	strcpy(p[1].dir,"END");
	strcpy(p[2].dir,"USING");
	strcpy(p[3].dir,"DC");
	strcpy(p[4].dir,"DS");
	

	printf("\nMOT \n\tMnemonics \tlength");
	for(i=0;i<3;i++)
		printf("\n\t%s\t\t%d",m[i].inst,m[i].len);
	
	printf("\nPOT \n\tDirectives\n");
	for(i=0;i<4;i++)
	{
		printf("\t%s",p[i].dir);
		printf("\n");
	}

	FILE *fp;
	fp=fopen("pass1.txt","r");

	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s",s1,s2,s3,s4);
		if(strcmp(s1,"*")!=0)
		{	
			strcpy(s[j].name,s1);
			s[j].val=lc;
			if((strcmp(s3,"F")==0) || (strcmp(s4,"F")==0))
			{
				s[j].length=4;
				strcpy(s[j].reloc,"R");
			}
			else
			{
				s[j].length=1;
				strcpy(s[j].reloc,"R");
			}
			j++;
		}
		for(i=0;i<4;i++)
		{
			if(strcmp(p[i].dir,s2)==0)
			{
				if(strcmp(s2,"USING")==0)
				{
					strcpy(b[k].reg,s4);
					b[k].content=lc;
					k++;
				}
			}
			else if(strcmp(m[i].inst,s2)==0)
				lc=lc+m[i].len;
		}
		if((strcmp(s3,"F")==0)|| (strcmp(s4,"F")==0))
			lc=lc+4;
	}
		printf("\nST \n\tsymbol\tlc value\tlength\trelocation\n");
		for(i=0;i<4;i++)
		{
			printf("\t%s\t%d\t\t%d\t%s",s[i].name,s[i].val,s[i].length,s[i].reloc);
			printf("\n");
		}
		printf("\nbase table \n\tbase register\tvalue\n");
		for(i=0;i<1;i++)
			printf("\t%s\t\t%d\n",b[i].reg,b[i].content);
	rewind(fp);
	
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s",s1,s2,s3,s4);
		for(i=0;i<3;i++)
		{
			if (strcmp(p[i].dir,s2)==0)
			{

			}
			else if(strcmp(m[i].inst,s2)!=0)
			{
				strcpy(pass[l].c,s2);
				if(atoi(s3)<15)
					pass[l].n=atoi(s3);
				for (j=0;j<4;j++)
				{
					if(strcmp(s4,s[j].name)==0)
					{
						offset=s[j].val;
						pass[l].offset=offset-0;
						pass[l].index=0;
						pass[l].base=15;
					}
				}
			}
		}
			l++;
	}
	printf("Pass 2\n");
	i=0;
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %s",s1,s2,s3,s4);
		if((strcmp(s2,"L")==0)||(strcmp(s2,"A")==0)||(strcmp(s2,"ST")==0))
		{
			printf("\t %s %d (%d,%d) \n",pass[i].c,pass[i].offset,pass[i].index,pass[i].base);
		}	
		i++;
	}

}


/*
Output:
c404@c404-OptiPlex-390:~$ gcc pass1.c
c404@c404-OptiPlex-390:~$ ./a.out

MOT 
	Mnemonics 	length
	L		4
	A		4
	ST		4
POT 
	Directives
	START
	END
	USING
	DC

ST 
	symbol	lc value	length	relocation
	JOHN	0		1	R
	FOUR	12		4	R
	FIVE	16		4	R
	TEMP	20		4	R

base table 
	base register	value
	15		0
Pass 2
	 L 16 (0,15) 
	 A 12 (0,15) 
	 ST 20 (0,15) 

*/