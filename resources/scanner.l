%{
#include<stdio.h>

%}

integerNumber 0|[1-9][0-9]*
doubleNumber  {integerNumber}\.{integerNumber}
commentLine   \/\/.*
identifier    [a-zA-Z][a-zA-Z0-9]*
string		  ["][^"]*["]

%%

{commentLine}			; /* skip: comments */
{doubleNumber}          {printf("doubleValue ");/*yylval.doubleValue  = atof(yytext); return DOUBLE_VALUE;*/}
{integerNumber}         {printf("intValue ");/*yylval.integerValue = atoi(yytext); return INTEGER_VALUE;*/}
"int"|"double"|"string"	{printf("type ");/*return TYPE;*/}
"while"                 {printf("while");}
echo   					{printf("echo ");/*return ECHO_F;*/}
\{						{printf("begin ");}
\}						{printf("end ");}
{string}                {printf("string ");/*return STRING;*/} 
{identifier} 			{printf("identifier ");/*return IDENTIFIER;*/}
","						{printf("comma");}
";"                     {printf("semicolon ");/*return SEMICOLON;*/}
"="						{printf("assign ");/*return ASSIGN;*/}
[ \t] 					; /* skip: tabs and white spaces */
\n 						{yylineno++;} /* line index */
. 						{return yytext[0];} /*error text*/

%%

int main(int argc, char** argv)
{
	//if( argc > 0)
	//	yyin = fopen(argv[1],"r");
	//yylex();
	//printf("Number of : \nidentifiers %d\n" , i);

	FILE *g;
	if(!(g = fopen("output.txt","w")))
		fprintf(stderr,"eroare creare fisier!");
	else
		yyout=g;

	yylex();

}
