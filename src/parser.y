/******************************************************1*/
%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stddef.h>

void yyerror (char * s);
int yylex();
extern int yylineno;
extern FILE* yyin;

struct FunctionsMetadataTable;
#define MAX_FMT_SIZE        100
#define MAX_FUNCTION_NAME_SIZE 100
#define MAX_SIGNATURE_SIZE     100
int fmtCounter = 0; /* INFO: keeps track of the current empty cell in the table */

struct VariablesMetadataTable;
#define MAX_VMT_SIZE        100
#define MAX_TYPE_SIZE       100
#define MAX_IDENTIFIER_SIZE 100
int vmtCounter = 0; /* INFO: keeps track of the current empty cell in the table */


void actOnFunctionDefinition(char *, char *, char *, int);
void actOnFunctionDeclaration(char *, char *, char *, int);
char * actOnFunctionCall(char *, char *, int);

int isFunctionDefined(char *, char *, int);
void setFunctionDefined(char *, char *, int);
int isFunctionDeclared(char *, char *, int);
int findFunctionIndex(char *, char *, int);
void addFunction(char *, char *, char *, int, int);
void dumpFmt();


char * actOnFetchVariableType(char *);
void   actOnVariableExistance(char *);
void   actOnVariableDeclaration(char *, char *);
void   actOnVariableInitialization(char *, char *, double);
double actOnNumericVariableEvaluation(char *);
void   actOnNumericVariableAssignment(char *, double);

int    declareVariable(char *, char *);
int    isVariableDeclared(char *);
int    getVariableIndex(char *);
double getNumericValue(char *);
int    setNumericValue(char *, double);
int    isTypeEqual(char * , char *);
void dumpVmt();

char * actOnIntWrapper(char *);
void actOnMemoryDump(int);

/******************************************************2*/
%}

%token PRINT_CALL MEMORY_DUMP_CALL
%union
{
	double numberValue;
	int    booleanValue;
	char * stringValue;
	char * stringIdentifier;
	char * stringConstantIdentifier;
	char * stringType;
}

%token CONSTANT_MODIFIER CLASS_MARKER
%token WHILE_LOOP FOR_LOOP IF

%token <numberValue>NUMERIC_VALUE 
%token <stringValue>STRING_VALUE
%token <booleanValue>BOOLEAN_VALUE

%token <stringType>TYPE 
%token <stringIdentifier>IDENTIFIER 
%token <stringConstantIdentifier>CONSTANT_IDENTIFIER 

%token SEMICOLON ASSIGN COMMA
%token PARENTHESIS_BEGIN PARENTHESIS_END BRACES_BEGIN BRACES_END BRACKETS_BEGIN BRACKETS_END

%token '-' '+' '*' '/' '^'
%left 	'+' '-'
%left 	'*' '/'
%left 	'^'

%token  '&' '|' '!'
%left	'&' '|'
%right 	'!'

%token '>' '<' '>=' '<=' '!=' '=='
%left '>' '<' '>=' '<=' '!=' '=='

%type <numberValue>arithmeticExpression
%type <numberValue>arExWrp
%type <booleanValue>booleanExpression
%type <booleanValue>blExWrp
%type <numberValue>arithmeticTerm
%type <stringValue>strings
%type <stringIdentifier>genericIdentifier
%type <stringValue>inputTypes
%type <stringValue>parameters
%type <stringValue>functionCall
%type <stringValue>arguments
%type <stringValue>argument

%start 	program
/******************************************************3*/
%%

program : genericStatements
		;
genericStatements 		: genericStatement 
				  		| genericStatement genericStatements
				  		;
	genericStatement 	: simpleStatement
				 		| complexStatement
				 		;

		simpleStatement : variableDeclaration   	SEMICOLON
						| variableInitialization 	SEMICOLON
						| constant 		 			SEMICOLON
						| functionDeclaration 		SEMICOLON
						| assignment     			SEMICOLON
						| functionCall   			SEMICOLON
						| classFunctionCall			SEMICOLON
						| strings			 		SEMICOLON
						| printFunction	 			SEMICOLON
						| memoryDumpFunction		SEMICOLON
						;
		complexStatement: block
						| classDefinition
						| functionDefinition
						| controlFlowStatemt
						; 
			block		: BRACES_BEGIN BRACES_END
	  					| BRACES_BEGIN compundStatement BRACES_END
	  					| BRACES_BEGIN compundStatement block BRACES_END
	  					| BRACES_BEGIN block compundStatement BRACES_END
	  					| BRACES_BEGIN compundStatement block compundStatement BRACES_END
	  					;

	simpleStatements	: simpleStatement
				 		| simpleStatements simpleStatement 
				 		;
	compundStatement	: simpleStatements
						| controlFlowStatemts
						| simpleStatements    controlFlowStatemts
						| controlFlowStatemts simpleStatements
						| controlFlowStatemts simpleStatements controlFlowStatemts
						| simpleStatements controlFlowStatemts simpleStatements
						;
	classDefinition 	: CLASS_MARKER IDENTIFIER BRACES_BEGIN BRACES_END
						| CLASS_MARKER IDENTIFIER BRACES_BEGIN classStatements BRACES_END
						;
	classStatements 	: fields
						| methods
						| classStatements fields
						| classStatements methods
						;
		fields  		: variableDeclaration    SEMICOLON
						| variableInitialization SEMICOLON
						;
		methods     	: functionDefinition
						;

/* 
 *       #######################
 *       ### CORE COMPONENTS ###
 *       #######################
 */
 						/* variableDeclaration refers to the introduction of a new name in the program */
variableDeclaration 	: TYPE IDENTIFIER 			 { actOnVariableDeclaration($1, $2); }
						| TYPE dimensions IDENTIFIER { actOnVariableDeclaration($1, $3); }
						;
	dimensions			: BRACKETS_BEGIN BRACKETS_END
						| dimensions BRACKETS_BEGIN BRACKETS_END
						;
constant 				: CONSTANT_MODIFIER TYPE CONSTANT_IDENTIFIER ASSIGN NUMERIC_VALUE
						;
						/* assignment refers to the operation of giving a value or a new value to a variable */
assignment 				: genericIdentifier ASSIGN functionCall
						| genericIdentifier ASSIGN strings
		   				| genericIdentifier ASSIGN arithmeticExpression { actOnNumericVariableAssignment($1, $3); }
		   				;
		   				/* variableInitialization refers to the introduction of a new name in the program and giving it a value */
variableInitialization 	: TYPE genericIdentifier ASSIGN arithmeticExpression { actOnVariableInitialization($1, $2, $4); }
						| TYPE genericIdentifier ASSIGN BOOLEAN_VALUE
			   			| TYPE genericIdentifier ASSIGN functionCall
			   			;
	genericIdentifier 	: IDENTIFIER                { $$ = $1; }
						| IDENTIFIER '.' IDENTIFIER { $$ = strdup("-");/* INFO: this is the skip indicator*/ }
						;
strings					: STRING_VALUE		  { $$ = strdup($1); }
						| strings '+' strings { char * s = strdup($1); strcat(s,$3); $$=s; }
						;
printFunction	    	: PRINT_CALL PARENTHESIS_BEGIN arithmeticExpression PARENTHESIS_END {printf("print : %f\n", $3);}
						| PRINT_CALL PARENTHESIS_BEGIN strings    			PARENTHESIS_END {printf("print : %s\n", $3);}
						| PRINT_CALL PARENTHESIS_BEGIN booleanExpression    PARENTHESIS_END {printf("print : %s\n", ($3 == 1 ? "true" : "false"));}
						;
memoryDumpFunction		: MEMORY_DUMP_CALL PARENTHESIS_BEGIN NUMERIC_VALUE PARENTHESIS_END {actOnMemoryDump($3);}
						;
arithmeticExpression	: arithmeticTerm
				  		| arithmeticExpression '+' arithmeticExpression   {$$=$1+$3;}
				  		| arithmeticExpression '-' arithmeticExpression   {$$=$1-$3;}
				  		| arithmeticExpression '*' arithmeticExpression   {$$=$1*$3;}
				  		| arithmeticExpression '/' arithmeticExpression   {$$=$1/$3;}
				  		| arithmeticExpression '^' arithmeticExpression   {$$=pow($1, $3);}
				  		| PARENTHESIS_BEGIN arithmeticExpression PARENTHESIS_END {$$=$2;}
				  		;
				  		/* FIXME: error 'yacc: 2 reduce/reduce conflicts.'*/
	arithmeticTerm 		: NUMERIC_VALUE {$$ = $1;}
						| IDENTIFIER 	{$$ = actOnNumericVariableEvaluation($1);}
						;
arExWrp					: BRACKETS_BEGIN arithmeticExpression BRACKETS_END {$$=$2;}
						;
booleanExpression   	: BOOLEAN_VALUE {$$=$1;}
						| arExWrp '>'  arExWrp {$$=$1 > $3;}
						| arExWrp '<'  arExWrp {$$=$1 < $3;}
						| arExWrp '>=' arExWrp {$$=$1 >= $3;}
						| arExWrp '<=' arExWrp {$$=$1 <= $3;}
						| arExWrp '==' arExWrp {$$=$1 == $3;}
						| arExWrp '!=' arExWrp {$$=$1 != $3;}
						| booleanExpression '|' booleanExpression   {$$=$1|$3;}
				  		| booleanExpression '&' booleanExpression   {$$=$1&$3;}
				  		| 					'!' booleanExpression   {$$=!$2;}
				  		| PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END {$$=$2;}
				  		;
blExWrp					: BRACKETS_BEGIN booleanExpression BRACKETS_END {$$=$2;}
						;
/* 
 *       #################
 *       ### FUNCTIONS ###
 *       #################
 */
functionDeclaration 	: TYPE IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END 		   {actOnFunctionDeclaration($1, $2, NULL, 1);}
		  				| TYPE IDENTIFIER PARENTHESIS_BEGIN inputTypes PARENTHESIS_END {actOnFunctionDeclaration($1, $2, $4  , 0);}
		  				;
	inputTypes			: TYPE 					{ $$ = strdup(actOnIntWrapper($1)); }
			   			| TYPE COMMA inputTypes { char * s = strdup(actOnIntWrapper($1)); strcat(s,$3); $$=s; }
			   			;
functionDefinition 		: TYPE IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END block            {actOnFunctionDefinition($1, $2, NULL, 1);}
				   		| TYPE IDENTIFIER PARENTHESIS_BEGIN parameters PARENTHESIS_END block {actOnFunctionDefinition($1, $2, $4  , 0);}
				   		;
	parameters			: TYPE IDENTIFIER 				   { $$ = strdup(actOnIntWrapper($1)); }
		   				| TYPE IDENTIFIER COMMA parameters { char * s = strdup(actOnIntWrapper($1)); strcat(s,$4); $$=s; }
		   				;
		   				/* functionCall refers to requesting the execution of a function */
functionCall 			: IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END           {$$ = strdup(actOnFunctionCall($1, NULL, 1));}
	 		 			| IDENTIFIER PARENTHESIS_BEGIN arguments PARENTHESIS_END {$$ = strdup(actOnFunctionCall($1,   $3, 0));}
	 		 			;
classFunctionCall 		: IDENTIFIER '-' IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END
	 		 			| IDENTIFIER '-' IDENTIFIER PARENTHESIS_BEGIN arguments PARENTHESIS_END
	 		 			;
	arguments			: argument 				   { $$ = strdup($1); }
		  				| argument COMMA arguments { char * s = strdup($1); strcat(s,$3); $$=s; }
		  				;
		argument 		: functionCall 		   {$$ = $1;}
						| arExWrp              {$$ = strdup("double");}
						| blExWrp			   {$$ = strdup("boolean");}
						| BOOLEAN_VALUE  	   {$$ = strdup("boolean");}
						| NUMERIC_VALUE  	   {$$ = strdup("double");}
						| strings		   	   {$$ = strdup("string");}
		 				| IDENTIFIER	   	   {$$ = actOnFetchVariableType($1);}
		 				| IDENTIFIER '.' IDENTIFIER { $$ = strdup("-");} /* INFO: maybe this is not going to work properly */
		 				;	
/* 
 *       ####################
 *       ### FLOW CONTROL ###
 *       ####################
 */
whileLoopStatement 		: WHILE_LOOP PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END block
				   		;
ifStatement 			: IF PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END block
				   		;
forStatement 			: FOR_LOOP PARENTHESIS_BEGIN 
										forExpression1 SEMICOLON 
										forExpression2 SEMICOLON
										forExpression3
								   PARENTHESIS_END block
				   		;
	forExpression1		: variableInitialization
						| assignment
						|
						;
	forExpression2		: booleanExpression
						|
						;
	forExpression3		: assignment
						|
						;
controlFlowStatemt 		: whileLoopStatement
						| forStatement
				   		| ifStatement
				   		;
controlFlowStatemts 	: controlFlowStatemt
						| controlFlowStatemt controlFlowStatemts
						;

%%
/**
 *	This struct will hold information about all
 * functions( declared and defined ) in the program.
 */
struct FunctionsMetadataTable
{
	/* return type of the function */
    char 	returnType[MAX_TYPE_SIZE];     // FIXME: Throw error for type bigger than *size*
	/* name of the function */
	char	name[MAX_FUNCTION_NAME_SIZE];
	/* concatenation of the input types */
    char 	signature[MAX_SIGNATURE_SIZE]; // FIXME: Throw error for type bigger than *size*
	/* boolean indicator of wether the function has any input type */
    int 	voidSignature;
    /* boolean indicator of wether the function is defined or just declared */
    int 	defined;
} fmt[MAX_FMT_SIZE] = {};


/**
 *	FUNCTIONS
 *	---------
 *	These functions control the flow of the 
 * program
 */

// adds a function declaration with it's code block
void actOnFunctionDefinition(char * returnType, char * name, char * signature, int voidSignature)
{
	// FIXME : logic error here
	if(isFunctionDefined(name, signature, voidSignature))
	{
		yyerror("redefinition of defined function");
		return;
	}
	if(isFunctionDeclared(name, signature, voidSignature))
	{
		setFunctionDefined(name, signature, voidSignature);
		return;
	}
	addFunction(returnType, name, signature, voidSignature, 1);
}

void actOnFunctionDeclaration(char * returnType, char * name, char * signature, int voidSignature)
{
	if(isFunctionDeclared(name, signature, voidSignature))
	{
		yyerror("redeclaration of declared function");
		return;
	}
	addFunction(returnType, name, signature, voidSignature, 0);
}

char * actOnFunctionCall(char * name, char * signature, int voidSignature)
{
	if(!isFunctionDefined(name, signature, voidSignature))
	{
		yyerror("cannot call an undefined function");
		return "";
	}
	int functionIndex = findFunctionIndex(name, signature, voidSignature);
	return fmt[functionIndex].returnType;
	//dumpFmt();
}

/**
 *	FUNCTIONS
 *	---------
 *	These functions provide core functionality for
 * the flow control functions of the program
 */

int isFunctionDefined(char * name, char * signature, int voidSignature)
{
	int functionIndex = findFunctionIndex(name, signature, voidSignature);
	if(functionIndex == -1)
		return 0;
	if(fmt[functionIndex].defined == 1)
		return 1;
	return 0;
}

void setFunctionDefined(char * name, char * signature, int voidSignature)
{
	int functionIndex = findFunctionIndex(name, signature, voidSignature); 
	if(functionIndex != -1)
		fmt[functionIndex].defined = 1;
}

int isFunctionDeclared(char * name, char * signature, int voidSignature)
{
	if(findFunctionIndex(name, signature, voidSignature) == -1)
		return 0;
	return 1;
}

int findFunctionIndex(char * name, char * signature, int voidSignature)
{
	if(!voidSignature)
	{
		for(int index = 0; index < fmtCounter; index++)
		{
			if( (strncmp(name     , fmt[index].name     , MAX_FUNCTION_NAME_SIZE) == 0) &&
				(strncmp(signature, fmt[index].signature, MAX_SIGNATURE_SIZE    ) == 0) )
			{
				return index;
			}
		}
	}
	else
	{
		for(int index = 0; index < fmtCounter; index++)
		{
			if( (strncmp(name     , fmt[index].name     , MAX_FUNCTION_NAME_SIZE) == 0) &&
				 voidSignature == fmt[index].voidSignature )
			{
				return index;
			}
		}
	}
	return -1;
}

void addFunction(char * returnType, char * name, char * signature, int voidSignature, int defined)
{
	strncpy(fmt[fmtCounter].returnType, returnType, MAX_TYPE_SIZE);
	strncpy(fmt[fmtCounter].name      , name      , MAX_FUNCTION_NAME_SIZE);
	if(!voidSignature)
		strncpy(fmt[fmtCounter].signature , signature , MAX_SIGNATURE_SIZE);
	fmt[fmtCounter].voidSignature = voidSignature;
	fmt[fmtCounter].defined 	  = defined;
	fmtCounter++;
}


void dumpFmt()
{
	printf("\n \tdumping fmt.. size : %d\n", fmtCounter);
	for (int index = 0; index < fmtCounter; ++index)
	{
		printf("~\t#%d | %s %s(%s) vs%d d%d\n",
			index 					 ,
			fmt[index].returnType    , 
			fmt[index].name          , 
			fmt[index].signature     ,
			fmt[index].voidSignature ,
			fmt[index].defined
		);
	}
	printf("\n");
}


/**
 *	VARIABLES
 *	---------
 *	This struct will hold information about all
 * numeric variables that have been declared in 
 * the program.
 */
struct VariablesMetadataTable
{
    char 	identifier[MAX_IDENTIFIER_SIZE]; // FIXME: Throw error for type bigger than *size*
    char 	type[MAX_TYPE_SIZE];             // FIXME: Throw error for type bigger than *size*    
    char *  stringValue;
    int     hasStringValue;
    double 	numericValue;    // Only for Numeric Types
    int 	hasValue;        // Only for Numeric Types
} vmt[MAX_VMT_SIZE] = {};



/**
 *	VARIABLES
 *	---------
 *	These functions control the flow of the 
 * program
 */

void actOnVariableDeclaration(char * type, char * identifier)
{
	//printf("%s\n", identifier);
	if(vmtCounter == MAX_VMT_SIZE)
	{
		yyerror("the variables table has reached maximum");
		return;
	}
	if(isVariableDeclared(identifier))
	{
		yyerror("redeclaration of variable");
		return;
	}
	declareVariable(type, identifier);
	//dumpVmt();
}

void actOnVariableInitialization(char * type, char * identifier, double numericValue)
{
	//printf("%s %s = %f \n", type, identifier, numericValue);
	if(identifier[0] == '-')
		return;
	if(vmtCounter == MAX_VMT_SIZE)
	{
		yyerror("the variables table has reached maximum");
		return;
	}
	if(isVariableDeclared(identifier))
	{
		yyerror("redeclaration of variable");
		return;
	}
	declareVariable(type, identifier);
	setNumericValue(identifier, numericValue);
	//dumpVmt();
}

double actOnNumericVariableEvaluation(char * identifier)
{
	// printf("%s %d\n", identifier, getVariableIndex(identifier));
	if(!isVariableDeclared(identifier))
		yyerror("variable is not declared");
	else
	{
		int index = getVariableIndex(identifier);
		if(!vmt[index].hasValue)
		{
			yyerror("variable is not initialized");
			return -0.0000000000001;
		}
		return vmt[index].numericValue;
	}
	return -0.0000000000001;
}

void actOnNumericVariableAssignment(char * identifier, double numericValue)
{
	if(!isVariableDeclared(identifier))
	{
		yyerror("variable not declared");
		return;
	}
	setNumericValue(identifier, numericValue);
}

void actOnVariableExistance(char * identifier)
{
	if(!isVariableDeclared(identifier))
	{
		yyerror("variable not declared");
		return;
	}
}

char * actOnFetchVariableType(char * identifier)
{
	if(!isVariableDeclared(identifier))
	{
		yyerror("use of undeclared variable");
		return "";
	}
	int variableIndex = getVariableIndex(identifier);
	return vmt[variableIndex].type;
}

/**
 *	VARIABLES
 *	---------
 *	These functions provide core functionality for
 * the flow control functions of the program
 */
int declareVariable(char * type, char * identifier)
{
	strncpy(vmt[vmtCounter].identifier, identifier, MAX_IDENTIFIER_SIZE);
	strncpy(vmt[vmtCounter].type      , type      , MAX_TYPE_SIZE);
	vmtCounter++;
	return 1;
}

int isVariableDeclared(char * identifier)
{
	if(getVariableIndex(identifier) != -1)
		return 1;
	return 0;
}

int getVariableIndex(char * identifier)
{
	int index;
	for(index = 0; index < vmtCounter; index++){
		//printf("'%s' '%s' '%d'\n", identifier, vmt[index].identifier, strncmp(identifier, vmt[index].identifier, MAX_IDENTIFIER_SIZE));
		if(strncmp(identifier, vmt[index].identifier, MAX_IDENTIFIER_SIZE) == 0)
			return index;
	}
	return -1;
}

double getNumericValue(char * identifier)
{
	int index = getVariableIndex(identifier);
	return vmt[index].numericValue;
}

int setNumericValue(char * identifier, double numericValue)
{
	int index = getVariableIndex(identifier);
	vmt[index].hasValue = 1;
	return vmt[index].numericValue = numericValue;
}

int isTypeEqual(char * sourceIdentifier, char * destinationIdentifier)
{
	int      sourceIndex = getVariableIndex(sourceIdentifier);
	int destinationIndex = getVariableIndex(destinationIdentifier);
	if(strncmp(vmt[sourceIndex].type, vmt[destinationIndex].type, MAX_TYPE_SIZE) == 0)
		return 1;
	return 0;
}

char * actOnIntWrapper(char * type)
{
	if(strncmp(type, "int", MAX_TYPE_SIZE) == 0)
		return "double";
	return type;
}

void dumpVmt()
{
	printf("\n \tdumping vmt.. size : %d\n", vmtCounter);
	for (int index = 0; index < vmtCounter; ++index)
	{
		if(vmt[index].hasValue)
			printf("~\t#%d | %s . %s . %f\n", index, vmt[index].type, vmt[index].identifier, vmt[index].numericValue);
		else
			printf("~\t#%d | %s . %s\n", index, vmt[index].type, vmt[index].identifier);
	}
	printf("\n");
}

void actOnMemoryDump(int dumpType)
{
	if(dumpType == 0)
	{
		dumpFmt();
		dumpVmt();
	}
	else if(dumpType == 1)
		dumpFmt();
	else
		dumpVmt();
}

void yyerror(char * s)
{
	printf("Error : '%s' at line : %d\n", s, yylineno);
}

int main(int argc, char* argv[]){
	if(argc < 2)
	{
		printf("functionCall format : '%s {fileName}\n", argv[0]);
		return -1;
	}
	yyin = fopen(argv[1], "r");
	if(yyin == NULL){
		printf("File I/O error for file : '%s'\n", argv[1]);
		return -1;
	}
	yyparse();
}
