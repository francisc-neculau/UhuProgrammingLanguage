%{
#include <stdio.h>
#include "y.tab.h"
%}

integerNumber 	0|[1-9][0-9]*
doubleNumber  	{integerNumber}\.{integerNumber}
commentLine   	\/\/.*
identifier    	[a-zA-Z][a-zA-Z0-9]*
constantIdentifier [A-Z][A-Z0-9_]*
stringValue		["][^"]*["]
booleanValue    true|false
%%
{commentLine}			; /* SKIP: comments */
{stringValue}           {yylval.stringValue =       strdup(yytext); return STRING_VALUE;}
{doubleNumber}          {yylval.numberValue =         atof(yytext); return NUMERIC_VALUE;}
{integerNumber}         {yylval.numberValue = (double)atoi(yytext); return NUMERIC_VALUE;}
{booleanValue}			{
							if(yytext[0] == 't')
							{yylval.booleanValue = 1;}
							else
							{yylval.booleanValue = 0;} 
							return BOOLEAN_VALUE;
						}
"int"					{yylval.stringType = strdup(yytext); return TYPE;}
"double"				{yylval.stringType = strdup(yytext); return TYPE;}
"string"				{yylval.stringType = strdup(yytext); return TYPE;}
"boolean"				{yylval.stringType = strdup(yytext); return TYPE;}
"void"					{yylval.stringType = strdup(yytext); return TYPE;}

"while"					{return WHILE_LOOP;}
"for"					{return FOR_LOOP;}
"if"					{return IF;}
"constant"					{return CONSTANT_MODIFIER;}
"print"   				{return PRINT_CALL;}
"dump"					{return MEMORY_DUMP_CALL;}
"@class"				{return CLASS_MARKER;}
\{						{return BRACES_BEGIN;}
\}						{return BRACES_END;}
\[						{return BRACKETS_BEGIN;}
\]						{return BRACKETS_END;}
\(						{return PARENTHESIS_BEGIN;}
\)						{return PARENTHESIS_END;}
{identifier} 			{yylval.stringIdentifier = strdup(yytext); return IDENTIFIER; REJECT;}
{constantIdentifier}		{yylval.stringConstantIdentifier = strdup(yytext); return CONSTANT_IDENTIFIER;}
","						{return COMMA;}
";"                     {return SEMICOLON;}
"="						{return ASSIGN;}
[ \t] 					;                       /* SKIP: tabs and white spaces */
\n 						{yylineno++;} 			/* INFO: line index            */
. 						{return yytext[0];} 	/* INFO: error text            */

%%

/*
 STEPTS TO COMPILE& RUN :
 ------------------------
	1. lex scanner.l
	2. gcc lex.yy.c -ll -o scanner

	1. lex scanner.l
	2. yacc -d parser.y
	3. gcc lex.yy.c y.tab.c -ll -lm -o uhu
	4. ./uhu program.uhu

/*int main(int argc, char** argv)
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

}*/
