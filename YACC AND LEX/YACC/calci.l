%{
   	#include "y.tab.h"
   	#include <stdio.h>
   	void yyerror(char *);
%}
%%
[0-9]+ { yylval=atoi(yytext);
     	return INTEGER;
   	}
[-+*/\n] {return *yytext;}
[ \t];
.   	yyerror("unknown character");
%%
int yywrap(void)
{return 1;}

calci.y-

%{ #include<stdio.h>
   int yylex(void);
   void yyerror(char *);
%}
%token INTEGER
%left '+' '-'
%left '*' '/'
%%
Program:
    	Program expr '\n'
    	{printf("%d\n",$2);}
    	|
    	;
expr:
    	INTEGER
    	|expr '+' expr {$$=$1+$3;}
    	|expr '-' expr {$$=$1-$3;}
    	|expr '*' expr {$$=$1*$3;}
    	|expr '/' expr {$$=$1/$3;}
    	;
%%
 void yyerror(char *s)
 {fprintf(stderr,"%s\n",s);}
 int main(void)
 {yyparse(); return 0;}



/*Output-

c222@22D301B12:~$ lex calci.l
c222@22D301B12:~$ yacc calci.y
c222@22D301B12:~$ yacc -d calci.y
c222@22D301B12:~$ gcc y.tab.c lex.yy.c
c222@22D301B12:~$ ./a.out
2/2+1*3
4
2*3-4/4+1
6
ab+c
unknown character
unknown character
syntax error
c222@22D301B12:~$ ./a.out
3^2
unknown character
syntax error
*/