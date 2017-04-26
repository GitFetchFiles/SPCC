#include<stdio.h>
#include<string.h>
void main () 
{
char l;
char b[5],a[5];
char r[10];
int i=0,j=0; 
printf("Enter the left production\n");
scanf("%c",&l);
printf("Enter the right production\n");
scanf("%s",r);
printf("\n Grammar is:\n %c->%s",l,r);

if(l==r[i])
{
 a[j]=r[i+1];
 j++;
 printf("\nGrammar is left recursive.\n");
 while(r[i]!=0 && r[i]!='|')
 {
  i++;
  if(r[i+1]=='|') 	
      break;
  else
  {
   a[j]=r[i+1];
   j++;
  }
 }
 i++;
 a[j]=0;
 j=0;
 if(r[i]!=0) {
  {
   b[j]=r[i+1];
   j++; 
   }
 while(r[i]!=0)
  {
   i++;
   b[j]=r[i+1];
   j++;
  }
 b[j]=0;
 printf("\nGrammar without left recursion:\n");
 printf("%c->%s%c\'",l,b,l);
 printf("\n%c\'->%s%c\'|E\n",l,a,l);
 }
 else
  printf("Grammar can't be reduced\n");
}
else
 printf("Grammar is not left recursive.\n");
}
/*
OUTPUT:

c413@c413-OptiPlex-390:~$ ./a.out
Enter the left production
E
Enter the right production
E+T|T

 Grammar is:
 E->E+T|T
Grammar is left recursive.

Grammar without left recursion:
E->TE'
E'->+TE'|E*/