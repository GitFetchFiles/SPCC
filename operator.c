#include<stdio.h>
#include<string.h>
#define max 50
int in=0,ip=0;
char str[50],tab[20][20],stack[100];
struct stack
{
    char st[max];
    int top;
}s;
void push(char);
char pop(void);
void main()
{
	s.top=-1;
	char ch,gram[50],ter[10];
	int i,j,n,row,column,p;
	
	printf("\nEnter the Grammar: ");	
	scanf("%s",gram);
	
	printf("Enter the number of Terminals in the Grammar: ");	
	scanf("%d",&n);
	printf("Enter the terminals\n");
	for(i=0;i<n;i++)
		scanf("%s",&ter[i]);
		
	printf("\nEnter the table:\n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%s",&tab[i][j]);
	printf("The Operator Precedence Table\n\t");
	for(i=0;i<n;i++)
		printf("%c\t",ter[i]);
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%c\t",ter[i]);
		for(j=0;j<n;j++)
			printf("%c\t",tab[i][j]);
		printf("\n");
	}
	
	printf("Enter the string: ");
	scanf("%s",str);
	
	ch = str[in]; //push $
	push(ch);
	in++;
	
	printf("%c\t",stack[0]);
	for(i=in;i<strlen(str);i++)
		printf("%c",str[i]);
	printf("\n");
	
	while(in <= strlen(str))
	{
		for(i=0;i<n;i++)
		{
			if(s.st[s.top]==ter[i])
			{
			row=i;
			break;
			}
		}
		for(j=0;j<n;j++)
		{
			if(str[in]==ter[j])
			{
			column=j;
			break;
			}
		}
		if((s.st[s.top]=='$') && (str[in]=='$'))
		{
			printf("\n\nVALID STRING\nACCEPTED\n");
			break;
		}
		else if(tab[row][column] == '<')
		{
			ch = tab[row][column];
			push(ch);
			ch = str[in];
			push(ch);
			in++; 
		}
		else
		{
			if(tab[row][column] == '>')
			{
				while(s.st[s.top] != '<')
				{
					ch = pop();
				}
				ch = pop();
			}
			else
			{
				printf("\n\nINVALID STRING\nNOT ACCEPTED\n");
				break;
			}
		}
		for(i=0;i<ip;i++)
			printf("%c",stack[i]);
		printf("\t");
		for(i=in;i<strlen(str);i++)
			printf("%c",str[i]);
		
		printf("\n");
	}
	
}


void push (char op)
{
	s.top = s.top + 1;
        s.st[s.top] = op;
        stack[ip] = op;
        ip++;
}
char pop(void)
{
char op;
        op = s.st[s.top] ;
        s.top = s.top - 1;
        ip--;
return op;
}

/*
OUTPUT:
dell@dell-Inspiron-3558:~$ gcc oper.c
dell@dell-Inspiron-3558:~$ ./a.out

Enter the Grammar: E->E+E|E-E|i
Enter the number of Terminals in the Grammar: 4
Enter the terminals
i
+
-
$

Enter the table:
-
>
>
>
<
>
>
>
<
>
>
>
<
<
<
-
The Operator Precedence Table
	i	+	-	$	
i	-	>	>	>	
+	<	>	>	>	
-	<	>	>	>	
$	<	<	<	-	
Enter the string: $i+i-i$
$	i+i-i$
$<i	+i-i$
$	+i-i$
$<+	i-i$
$<+<i	-i$
$<+	-i$
$	-i$
$<-	i$
$<-<i	$
$<-	$
$	$


VALID STRING
ACCEPTED
	
Enter the string: $i+i-i*i$
$	i+i-i*i$
$<i	+i-i*i$
$	+i-i*i$
$<+	i-i*i$
$<+<i	-i*i$
$<+	-i*i$
$	-i*i$
$<-	i*i$
$<-<i	*i$


INVALID STRING
NOT ACCEPTED
*/