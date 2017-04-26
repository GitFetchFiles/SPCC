#include<stdio.h>
#include<ctype.h>
void FIRST(char[],char );
void addToResultSet(char[],char);
int numOfProductions;
char productionSet[10][10];
void main()
{
int i;
int choice; 
char c;
char result[20];
printf("Enter number of productions:");
scanf(" %d",&numOfProductions);
for(i=0;i<numOfProductions;i++)
{

        printf("Enter productions Number %d : ",i+1);
	scanf(" %s",productionSet[i]);
}
 do
{
printf("\n Find the FIRST of  :");
scanf(" %c",&c);
FIRST(result,c);
printf("\n FIRST(%c)= { ",c);
for(i=0;result[i]!='\0';i++)
printf(" %c ",result[i]);       
printf("}\n");
printf("press '1' to continue : ");
        scanf(" %d",&choice);

    }

    while(choice==1);

}
void FIRST(char* Result,char c)
{
int i,j,k;
char subResult[20];
int foundEpsilon;
subResult[0]='\0';
Result[0]='\0';
if(!(isupper(c)))
{
addToResultSet(Result,c);
return ;
}
for(i=0;i<numOfProductions;i++)
{
   if(productionSet[i][0]==c)
        {
	if(productionSet[i][2]=='$') addToResultSet(Result,'$');
	else
	{
	j=2;
	while(productionSet[i][j]!='\0')
	{
	foundEpsilon=0;
	FIRST(subResult,productionSet[i][j]);
	for(k=0;subResult[k]!='\0';k++)
	addToResultSet(Result,subResult[k]);
	for(k=0;subResult[k]!='\0';k++)
	if(subResult[k]=='$')
	{
	foundEpsilon=1;
	break;
	}
if(!foundEpsilon)
break;
j++;
	}
      }
   }
}
return ;
}
void addToResultSet(char Result[],char val)
{
int k;
for(k=0 ;Result[k]!='\0';k++)
if(Result[k]==val)
return;
Result[k]=val;
Result[k+1]='\0';
}
/* output
Enter number of productions:7
Enter productions Number 1 : X=YZ
Enter productions Number 2 : Z=0WY
Enter productions Number 3 : Z=Y1
Enter productions Number 4 : Y=$
Enter productions Number 5 : Y=+W1
Enter productions Number 6 : W=*
Enter productions Number 7 : W=z1

 Find the FIRST of  :*

 FIRST(*)= {  * }
press '1' to continue : 1

 Find the FIRST of  :+

 FIRST(+)= {  + }
press '1' to continue : 1

 Find the FIRST of  :1

 FIRST(1)= {  1 }
press '1' to continue : 1

 Find the FIRST of  :0

 FIRST(0)= {  0 }
press '1' to continue : 1

 Find the FIRST of  :Y

 FIRST(Y)= {  $  + }
press '1' to continue : 1

 Find the FIRST of  :Z

 FIRST(Z)= {  0  $  +  1 }
press '1' to continue : 1

 Find the FIRST of  :W

 FIRST(W)= {  *  z }
press '1' to continue : 1

 Find the FIRST of  :X

 FIRST(X)= {  $  +  0  1 }
press '1' to continue : 2
*/