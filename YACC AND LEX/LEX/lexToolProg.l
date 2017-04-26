%{
int key=0,op=0,id=0,relop=0,arop=0;
%}
LETTER [a-zA-Z]
DIGIT [0-9]
%%
(begin|if|else|while|do|then) {key++;printf(" \n keyword: %s \n",yytext);}
("+"|"*"|"-"|"/"|"=") {arop++;printf("\n arithmatic operators: %s \n",yytext);}
("<="|">="|"!="|"<"|">") {relop++;printf("\n relational operators: %s \n",yytext);}
{LETTER}({LETTER}|{DIGIT})* {id++;printf("ID:%s \n",yytext);}
%%
main()
{
yylex();
printf("no.of ids= %d\n keyword= %d \nNo.of arithmatic operation= %d \nno.of relop= %d\n",id,key,arop,relop);
}  

Output:

c404@c404-OptiPlex-390:~/Desktop$ lex lexToolProg.l
c404@c404-OptiPlex-390:~/Desktop$ gcc lex.yy.c -ll
c404@c404-OptiPlex-390:~/Desktop$ ./a.out <input.txt
 
 keyword: begin 
 keyword: if 
 arithmatic operators: + 
 arithmatic operators: - 
 relational operators: > 
 relational operators: > 
 arithmatic operators: = 

no.of ids= 2
keyword= 2 
No.of arithmatic operation= 3 
no.of relop= 2