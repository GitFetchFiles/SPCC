#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	int i,n,j,k,l,g=0,count1=0,vcount=0,vcount3=0,vcount4=0,vcount1=0,count2=0,count3=0,y,flag=0,count4=0,count5=0,count6=0,flag1=0,flag3=0,flag4=0;
	n=15;
	k=0;
	l=0;
	FILE *fp;
	char word[90],d[10][10],b[10][10];
	char keyword[15][15]={"while","int","if","break","void","main","#include","for","else","printf","scanf"};
	char header[10][10]={"<stdio.h>","<stdlib.h>"};
	char operator[15][15]={"+","=","*","-","/","%d","%s","{","}",";","(",")",","};
	char relop[10][10]={"<",">","<=",">=",};
	char logical[10][10]={"AND","NOR","NOT","NAND","EXOR"};
	char constant[15][10]={"1","2","3","4","5","6","7","8","9","0"};
	char identifier[15][10]={"1a","b","c","d","e","f","g","h","i","j","a1","a2","a"};
	char c;
	char usedi[10][10]={" "};
	char usedo[15][15]={" "};
	int flo=0;
	int valid[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	printf("phase 1\n\n");
	fp=fopen("input.c","r");
	do
	{
		c=fscanf(fp,"%s",word);
		for(i=0;i<n;i++)
		{
			if(!strcmp(word,keyword[i]))
			{
				printf("keyword=%s\n",word);
				count1++;
			}
		}	

		for(i=0;i<n;i++)
		{
			if(!strcmp(word,operator[i]))
			{	
				for(y=0;y<15;y++)
				{
					if(usedo[y][0]==operator[i][0])
					{
						flag1=1;
					}


				}
				if(flag1==0)
				{
					printf("operator =%s\n",word);
					count5++;
					usedo[k][0]=operator[i][0];
					k++;
				}
				flag1=0;
			}
		}
		for(i=0;i<n;i++)
		{
			if(!strcmp(word,constant[i]))
			{
				printf("constant=%s\n",word);
				count4++;
			}
		}
		for(i=0;i<n;i++)
		{
			if(!strcmp(word,relop[i]))
			{
				printf("relopt=%s\n",word);
				count6++;
			}
		}	
		for(i=0;i<n;i++)
		{
			if(!strcmp(word,header[i]))
			{
				printf("header=%s\n",word);
				count2++;
			}
		}
		for(i=0;i<n;i++)
		{
			if(!strcmp(word,identifier[i]))
			{
				for(y=0;y<8;y++)
				{
					if(usedi[y][0]==identifier[i][0])
					{
						flag=1;
					}
				}
				if(flag==0)
				{
					printf("identifier=%s\n",word);
					count3++;


					usedi[l][0]=identifier[i][0];
					if(isdigit(identifier[i][0]))
						{
						valid[i]=1;

						}
					l++;
					
				}
				flag=0;
			}
		}
	}

	while(c!=EOF);
	printf("\ntotal keywords %d\n",count1);
	printf("\ntotal headers %d\n",count2);
	printf("\ntotal identifiers %d\n",count3);
	printf("\ntotal constants %d\n",count4);
	printf("\ntotal operators %d\n",count5);
	printf("\ntotal relational operators %d\n",count6);
	for(i=0;i<15;i++)
	{
	if(valid[i]==1)
		{
		printf("invalid identifier detected at %d",i);
	 	flo=1;
		}
	}
	if(flo=0)
		printf("all valid identifier detected");
	fclose(fp);
}


/*
Output:
c404@c404-OptiPlex-390:~$ gcc lexical.c


c404@c404-OptiPlex-390:~$ ./a.out
phase 1
keyword=#include
header=<stdio.h>
keyword=#include
header=<stdlib.h>
keyword=void

keyword=main
operator =(
operator =)
operator ={
keyword=int
identifier=1a
operator =;
keyword=int
identifier=b
keyword=int
identifier=c
operator ==
constant=9
operator =*
keyword=printf
operator =%d
operator =,
operator =}
total keywords 8
total headers 2
total identifiers 3
total constants 1
total operators 9
total relational operators 0
invalid identifier detected at 0*/