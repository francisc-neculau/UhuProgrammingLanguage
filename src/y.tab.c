/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 3 "parser.y"
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
#line 60 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
	double numberValue;
	int    booleanValue;
	char * stringValue;
	char * stringIdentifier;
	char * stringConstantIdentifier;
	char * stringType;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 93 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define PRINT_CALL 257
#define MEMORY_DUMP_CALL 258
#define CONSTANT_MODIFIER 259
#define CLASS_MARKER 260
#define WHILE_LOOP 261
#define FOR_LOOP 262
#define IF 263
#define NUMERIC_VALUE 264
#define STRING_VALUE 265
#define BOOLEAN_VALUE 266
#define TYPE 267
#define IDENTIFIER 268
#define CONSTANT_IDENTIFIER 269
#define SEMICOLON 270
#define ASSIGN 271
#define COMMA 272
#define PARENTHESIS_BEGIN 273
#define PARENTHESIS_END 274
#define BRACES_BEGIN 275
#define BRACES_END 276
#define BRACKETS_BEGIN 277
#define BRACKETS_END 278
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,   13,   13,   14,   14,   15,   15,   15,   15,   15,
   15,   15,   15,   15,   15,   16,   16,   16,   16,   25,
   25,   25,   25,   25,   30,   30,   29,   29,   29,   29,
   29,   29,   26,   26,   32,   32,   32,   32,   33,   33,
   34,   17,   17,   35,   35,   19,   21,   21,   21,   18,
   18,   18,    7,    7,    6,    6,   23,   23,   23,   24,
    1,    1,    1,    1,    1,    1,    1,    5,    5,    2,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    4,   20,   20,    8,    8,   27,   27,    9,    9,
   10,   10,   22,   22,   11,   11,   12,   12,   12,   12,
   12,   12,   12,   12,   36,   37,   38,   39,   39,   39,
   40,   40,   41,   41,   28,   28,   28,   31,   31,
};
static const YYINT yylen[] = {                            2,
    1,    1,    2,    1,    1,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    1,    1,    1,    1,    2,
    3,    4,    4,    5,    1,    2,    1,    1,    2,    2,
    3,    3,    4,    5,    1,    1,    2,    2,    2,    2,
    1,    2,    3,    2,    3,    5,    3,    3,    3,    4,
    4,    4,    1,    3,    1,    3,    4,    4,    4,    4,
    1,    3,    3,    3,    3,    3,    3,    1,    1,    3,
    1,    3,    3,    3,    3,    3,    3,    3,    3,    2,
    3,    3,    4,    5,    1,    3,    5,    6,    2,    4,
    3,    4,    5,    6,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    3,    5,    5,    9,    1,    1,    0,
    1,    0,    1,    0,    1,    1,    1,    1,    2,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,   55,    0,    0,
    0,    0,    0,    0,    0,    1,    0,    4,    5,    0,
    0,    0,    0,    0,    0,    0,    0,   16,   17,   18,
   19,  115,  117,  116,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   20,
   25,    0,    0,    0,    0,    0,   13,    0,    0,   11,
    3,    6,    7,    8,    9,   10,   12,   14,   15,   68,
   71,   69,    0,    0,    0,    0,    0,    0,   61,    0,
    0,    0,    0,    0,    0,    0,    0,  108,  109,    0,
    0,    0,   44,    0,   43,    0,  101,  100,    0,   91,
    0,   98,   99,    0,   97,    0,    0,    0,   54,    0,
    0,  119,   21,    0,   26,    0,    0,   56,    0,    0,
    0,    0,   47,    0,    0,    0,   80,   57,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   59,
    0,    0,   58,   60,    0,    0,   33,    0,    0,   41,
    0,   35,   36,    0,    0,    0,    0,    0,    0,    0,
   51,    0,   52,   45,    0,    0,   92,    0,    0,    0,
   23,   22,    0,    0,   31,   67,   81,   70,    0,    0,
    0,    0,   66,   72,   73,   74,   75,   77,   76,   79,
   78,   46,    0,   39,   40,   34,   37,   38,  105,    0,
    0,  106,    0,    0,   87,   84,    0,  104,   82,   96,
   93,    0,    0,   83,   24,    0,    0,    0,   86,   88,
   94,    0,    0,  113,    0,   90,    0,  107,
};
static const YYINT yydgoto[] = {                         12,
  124,   77,  125,  103,   79,   13,   14,  159,  160,   15,
  106,  107,   16,   17,   51,   19,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   53,   54,   55,
   56,  151,  152,  153,   45,   32,   33,   34,   90,  201,
  225,
};
static const YYINT yysindex[] = {                        39,
 -238, -228, -216, -204, -177, -157, -141,    0, -198,    8,
  -61,    0,  -41, -134, -110,    0,   39,    0,    0, -100,
  -97,  -92,  -78,  -71,  -65,  -59,  -57,    0,    0,    0,
    0,    0,    0,    0,  -33,  -48,  -39,  -38,  -27, -111,
  -27,   -3,  -24,   -4, -191,   44,   25,   37, -165,    0,
    0,   72,  -74,  -15,   72,  -91,    0,   12,  -56,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -30, -139,  -27,  -32,  -55,  -26,    0,  -18,
   46,   40, -153,  -27,  -22,   45,  276,    0,    0,   62,
  -17, -170,    0,  -45,    0,   58,    0,    0,    3,    0,
  -30,    0,    0,  295,    0,   76,   75,   78,    0,    9,
   77,    0,    0,   27,    0,  -91,   72,    0,   79, -139,
   47,  295,    0,    5,  -11,  -13,    0,    0, -139, -139,
 -139, -139, -139,   80,   80,   80,   80,   80,   80,    0,
  -27,  -27,    0,    0,   90, -125,    0,   85,   86,    0,
 -123,    0,    0,   83,  -27,   83, -114,   83,   87,   88,
    0,   47,    0,    0,   91,  -37,    0, -126,   51,  -83,
    0,    0,   84,  -91,    0,    0,    0,    0,   41,   41,
  269,  269,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   10,    0,    0,    0,    0,    0,    0,  -29,
   94,    0,   93,   99,    0,    0,   83,    0,    0,    0,
    0,   95,   96,    0,    0,  -64,   45,  100,    0,    0,
    0,  102,   83,    0,   97,    0,   83,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  101,
    0,    0,    0,    0,    0,    0,  373,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  104,
    0,    4,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -148,    0,   48,   66,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  101,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -150,    0,
    0,    0,    0,    6,    0,    0,  103,    0,    0,    4,
    0,    0,    0,    0,    0,   68,   70,    0,   -1,    0,
 -115,  -84,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  105,    0,  106,  108,    0,    0,
    0,  109,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   73,    0,    0,    0,    0,  -12,   -6,
  -25,  -19,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    4,    0,    0,    0,    0,    0,    0,  111,
    0,    0,  110,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  106,    0,    0,    0,  112,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   32,   11,   30,    0,    0,   26,   29,  172,  164,   14,
  158,    0,  366,    0,   19,    0,  -75,   18,    0,    0,
  -36,    0,    0,    0,   64,    0,  -69,   63,    7,  -16,
   13,    0,  234,  236,    0,    0,    0,    0,    0,    0,
    0,
};
#define YYTABLESIZE 387
static const YYINT yytable[] = {                         75,
  141,   58,   75,   89,  135,   75,  134,  148,  141,  131,
  130,  141,  129,  150,  132,  141,   64,   64,   18,   64,
  141,   64,   65,   65,   58,   65,  141,   65,  131,  130,
   63,  129,   63,  132,   35,   18,   62,   44,   62,  117,
   69,   69,   48,   69,   36,   69,  131,  130,  165,  129,
   37,  132,   47,   48,   48,   48,  102,   88,  111,  105,
   80,  133,   31,   38,   78,  112,   76,  116,   85,   42,
   91,  104,  123,  115,   52,  148,   95,   44,   43,   31,
  133,  150,  131,  118,  122,   96,  142,  132,  131,  130,
  121,  129,   69,  132,  142,   39,  157,  142,  133,  174,
  149,  142,  110,  158,  127,  126,  142,  163,  118,  118,
  118,   43,  142,  146,   44,   40,  118,  114,  118,  118,
  173,  103,  147,  103,   70,  162,  118,  118,   72,  175,
  166,   41,  126,  120,  133,  115,   59,   97,    8,   98,
  133,   99,  193,  146,  184,  185,  186,  187,  188,  189,
  101,   43,  196,  203,   49,   86,   87,  204,   49,   60,
  179,  180,  181,  182,  183,    1,    2,    3,  149,   62,
  190,  191,   63,    8,   44,   49,   10,   64,  102,  102,
  224,  105,  105,  213,  200,   48,    5,    6,    7,   48,
  214,   65,  115,  104,  104,    1,    2,    3,   66,    5,
    6,    7,  222,    8,   67,   49,   10,   70,    8,  223,
   68,  119,   69,   11,   50,   81,  120,  199,   70,  202,
  161,  205,  119,  136,  137,  138,  139,  120,   57,   82,
   70,    8,   71,   70,   72,   71,   83,   72,   71,   73,
  209,  128,   73,   74,   64,   84,   74,  140,   64,   74,
   65,  154,   64,   93,   65,  143,  156,   63,   65,   11,
  113,   63,  177,   62,  178,   63,   94,   62,   69,   92,
  220,   62,   69,   42,   53,   46,    8,  102,  176,  102,
   46,  170,  216,    1,    2,    3,  205,    5,    6,    7,
  228,    8,  108,   49,   10,    1,    2,    3,    4,    5,
    6,    7,  172,    8,  109,    9,   10,   97,    8,   98,
  145,   99,   87,   11,   97,    8,   98,  100,   99,  144,
  101,   48,   27,   27,  211,  210,  212,  101,    1,    2,
    3,  155,    5,    6,    7,  164,    8,   58,   49,   10,
   28,   28,   29,   29,   30,   30,  168,   32,   32,  167,
  169,   46,  171,  192,  194,  195,   74,   11,  208,  215,
  206,  207,  133,  217,  218,  213,  222,  204,  221,  203,
  227,   53,    2,  110,  112,  219,   95,   83,   50,   85,
  111,  226,   61,   89,  197,  114,  198,
};
static const YYINT yycheck[] = {                         33,
   38,   43,   33,   40,   60,   33,   62,   83,   38,   42,
   43,   38,   45,   83,   47,   38,   42,   43,    0,   45,
   38,   47,   42,   43,   43,   45,   38,   47,   42,   43,
   43,   45,   45,   47,  273,   17,   43,    9,   45,   56,
   42,   43,   46,   45,  273,   47,   42,   43,   46,   45,
  267,   47,   45,   46,   46,   46,   46,   40,   52,   46,
   35,   94,    0,  268,   35,   53,   35,   55,   39,  268,
   41,   46,   59,   55,   11,  151,  268,   49,  277,   17,
   94,  151,   42,   58,   59,  277,  124,   47,   42,   43,
   59,   45,   94,   47,  124,  273,  267,  124,   94,  116,
   83,  124,  268,  274,   75,   74,  124,   94,  257,  258,
  259,  277,  124,  267,   86,  273,  265,   54,  267,  268,
  114,  272,  276,  274,  264,   94,  275,  276,  268,  117,
  101,  273,  101,  273,   94,  117,  271,  264,  265,  266,
   94,  268,  268,  267,  134,  135,  136,  137,  138,  139,
  277,  277,  276,  268,  270,  267,  268,  272,  274,  270,
  129,  130,  131,  132,  133,  257,  258,  259,  151,  270,
  141,  142,  270,  265,  146,  267,  268,  270,  168,  169,
  217,  168,  169,  267,  155,  270,  261,  262,  263,  274,
  274,  270,  174,  168,  169,  257,  258,  259,  270,  261,
  262,  263,  267,  265,  270,  267,  268,  264,  265,  274,
  270,  268,  270,  275,  276,  264,  273,  154,  264,  156,
  266,  158,  268,  279,  280,  281,  282,  273,  270,  269,
  264,  265,  266,  264,  268,  266,  275,  268,  266,  273,
  278,  274,  273,  277,  270,  273,  277,  274,  274,  277,
  270,  274,  278,  278,  274,  274,  274,  270,  278,  275,
  276,  274,  274,  270,  278,  278,  271,  274,  270,  273,
  207,  278,  274,  270,  271,  273,  265,  272,  274,  274,
  273,  273,  273,  257,  258,  259,  223,  261,  262,  263,
  227,  265,  268,  267,  268,  257,  258,  259,  260,  261,
  262,  263,  276,  265,  268,  267,  268,  264,  265,  266,
  271,  268,  268,  275,  264,  265,  266,  274,  268,  274,
  277,   46,  275,  276,  274,  168,  169,  277,  257,  258,
  259,  270,  261,  262,  263,  278,  265,   43,  267,  268,
  275,  276,  275,  276,  275,  276,  272,  275,  276,  274,
  273,  273,  276,  264,  270,  270,  277,  275,  268,  276,
  274,  274,   94,  270,  272,  267,  267,  272,  274,  268,
  274,  271,    0,  270,  270,  204,  274,  270,  270,  274,
  270,  218,   17,  274,  151,  274,  151,
};
#define YYFINAL 12
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 282
#define YYUNDFTOKEN 326
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,"'&'",0,0,0,"'*'","'+'",0,"'-'","'.'","'/'",0,0,0,0,0,0,0,0,0,0,0,
0,"'<'",0,"'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,"PRINT_CALL","MEMORY_DUMP_CALL","CONSTANT_MODIFIER",
"CLASS_MARKER","WHILE_LOOP","FOR_LOOP","IF","NUMERIC_VALUE","STRING_VALUE",
"BOOLEAN_VALUE","TYPE","IDENTIFIER","CONSTANT_IDENTIFIER","SEMICOLON","ASSIGN",
"COMMA","PARENTHESIS_BEGIN","PARENTHESIS_END","BRACES_BEGIN","BRACES_END",
"BRACKETS_BEGIN","BRACKETS_END","\">=\"","\"<=\"","\"!=\"","\"==\"",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : genericStatements",
"genericStatements : genericStatement",
"genericStatements : genericStatement genericStatements",
"genericStatement : simpleStatement",
"genericStatement : complexStatement",
"simpleStatement : variableDeclaration SEMICOLON",
"simpleStatement : variableInitialization SEMICOLON",
"simpleStatement : constant SEMICOLON",
"simpleStatement : functionDeclaration SEMICOLON",
"simpleStatement : assignment SEMICOLON",
"simpleStatement : functionCall SEMICOLON",
"simpleStatement : classFunctionCall SEMICOLON",
"simpleStatement : strings SEMICOLON",
"simpleStatement : printFunction SEMICOLON",
"simpleStatement : memoryDumpFunction SEMICOLON",
"complexStatement : block",
"complexStatement : classDefinition",
"complexStatement : functionDefinition",
"complexStatement : controlFlowStatemt",
"block : BRACES_BEGIN BRACES_END",
"block : BRACES_BEGIN compundStatement BRACES_END",
"block : BRACES_BEGIN compundStatement block BRACES_END",
"block : BRACES_BEGIN block compundStatement BRACES_END",
"block : BRACES_BEGIN compundStatement block compundStatement BRACES_END",
"simpleStatements : simpleStatement",
"simpleStatements : simpleStatements simpleStatement",
"compundStatement : simpleStatements",
"compundStatement : controlFlowStatemts",
"compundStatement : simpleStatements controlFlowStatemts",
"compundStatement : controlFlowStatemts simpleStatements",
"compundStatement : controlFlowStatemts simpleStatements controlFlowStatemts",
"compundStatement : simpleStatements controlFlowStatemts simpleStatements",
"classDefinition : CLASS_MARKER IDENTIFIER BRACES_BEGIN BRACES_END",
"classDefinition : CLASS_MARKER IDENTIFIER BRACES_BEGIN classStatements BRACES_END",
"classStatements : fields",
"classStatements : methods",
"classStatements : classStatements fields",
"classStatements : classStatements methods",
"fields : variableDeclaration SEMICOLON",
"fields : variableInitialization SEMICOLON",
"methods : functionDefinition",
"variableDeclaration : TYPE IDENTIFIER",
"variableDeclaration : TYPE dimensions IDENTIFIER",
"dimensions : BRACKETS_BEGIN BRACKETS_END",
"dimensions : dimensions BRACKETS_BEGIN BRACKETS_END",
"constant : CONSTANT_MODIFIER TYPE CONSTANT_IDENTIFIER ASSIGN NUMERIC_VALUE",
"assignment : genericIdentifier ASSIGN functionCall",
"assignment : genericIdentifier ASSIGN strings",
"assignment : genericIdentifier ASSIGN arithmeticExpression",
"variableInitialization : TYPE genericIdentifier ASSIGN arithmeticExpression",
"variableInitialization : TYPE genericIdentifier ASSIGN BOOLEAN_VALUE",
"variableInitialization : TYPE genericIdentifier ASSIGN functionCall",
"genericIdentifier : IDENTIFIER",
"genericIdentifier : IDENTIFIER '.' IDENTIFIER",
"strings : STRING_VALUE",
"strings : strings '+' strings",
"printFunction : PRINT_CALL PARENTHESIS_BEGIN arithmeticExpression PARENTHESIS_END",
"printFunction : PRINT_CALL PARENTHESIS_BEGIN strings PARENTHESIS_END",
"printFunction : PRINT_CALL PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END",
"memoryDumpFunction : MEMORY_DUMP_CALL PARENTHESIS_BEGIN NUMERIC_VALUE PARENTHESIS_END",
"arithmeticExpression : arithmeticTerm",
"arithmeticExpression : arithmeticExpression '+' arithmeticExpression",
"arithmeticExpression : arithmeticExpression '-' arithmeticExpression",
"arithmeticExpression : arithmeticExpression '*' arithmeticExpression",
"arithmeticExpression : arithmeticExpression '/' arithmeticExpression",
"arithmeticExpression : arithmeticExpression '^' arithmeticExpression",
"arithmeticExpression : PARENTHESIS_BEGIN arithmeticExpression PARENTHESIS_END",
"arithmeticTerm : NUMERIC_VALUE",
"arithmeticTerm : IDENTIFIER",
"arExWrp : BRACKETS_BEGIN arithmeticExpression BRACKETS_END",
"booleanExpression : BOOLEAN_VALUE",
"booleanExpression : arExWrp '>' arExWrp",
"booleanExpression : arExWrp '<' arExWrp",
"booleanExpression : arExWrp \">=\" arExWrp",
"booleanExpression : arExWrp \"<=\" arExWrp",
"booleanExpression : arExWrp \"==\" arExWrp",
"booleanExpression : arExWrp \"!=\" arExWrp",
"booleanExpression : booleanExpression '|' booleanExpression",
"booleanExpression : booleanExpression '&' booleanExpression",
"booleanExpression : '!' booleanExpression",
"booleanExpression : PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END",
"blExWrp : BRACKETS_BEGIN booleanExpression BRACKETS_END",
"functionDeclaration : TYPE IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END",
"functionDeclaration : TYPE IDENTIFIER PARENTHESIS_BEGIN inputTypes PARENTHESIS_END",
"inputTypes : TYPE",
"inputTypes : TYPE COMMA inputTypes",
"functionDefinition : TYPE IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END block",
"functionDefinition : TYPE IDENTIFIER PARENTHESIS_BEGIN parameters PARENTHESIS_END block",
"parameters : TYPE IDENTIFIER",
"parameters : TYPE IDENTIFIER COMMA parameters",
"functionCall : IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END",
"functionCall : IDENTIFIER PARENTHESIS_BEGIN arguments PARENTHESIS_END",
"classFunctionCall : IDENTIFIER '-' IDENTIFIER PARENTHESIS_BEGIN PARENTHESIS_END",
"classFunctionCall : IDENTIFIER '-' IDENTIFIER PARENTHESIS_BEGIN arguments PARENTHESIS_END",
"arguments : argument",
"arguments : argument COMMA arguments",
"argument : functionCall",
"argument : arExWrp",
"argument : blExWrp",
"argument : BOOLEAN_VALUE",
"argument : NUMERIC_VALUE",
"argument : strings",
"argument : IDENTIFIER",
"argument : IDENTIFIER '.' IDENTIFIER",
"whileLoopStatement : WHILE_LOOP PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END block",
"ifStatement : IF PARENTHESIS_BEGIN booleanExpression PARENTHESIS_END block",
"forStatement : FOR_LOOP PARENTHESIS_BEGIN forExpression1 SEMICOLON forExpression2 SEMICOLON forExpression3 PARENTHESIS_END block",
"forExpression1 : variableInitialization",
"forExpression1 : assignment",
"forExpression1 :",
"forExpression2 : booleanExpression",
"forExpression2 :",
"forExpression3 : assignment",
"forExpression3 :",
"controlFlowStatemt : whileLoopStatement",
"controlFlowStatemt : forStatement",
"controlFlowStatemt : ifStatement",
"controlFlowStatemts : controlFlowStatemt",
"controlFlowStatemts : controlFlowStatemt controlFlowStatemts",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 303 "parser.y"
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
#line 903 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 42:
#line 175 "parser.y"
	{ actOnVariableDeclaration(yystack.l_mark[-1].stringType, yystack.l_mark[0].stringIdentifier); }
break;
case 43:
#line 176 "parser.y"
	{ actOnVariableDeclaration(yystack.l_mark[-2].stringType, yystack.l_mark[0].stringIdentifier); }
break;
case 49:
#line 186 "parser.y"
	{ actOnNumericVariableAssignment(yystack.l_mark[-2].stringIdentifier, yystack.l_mark[0].numberValue); }
break;
case 50:
#line 189 "parser.y"
	{ actOnVariableInitialization(yystack.l_mark[-3].stringType, yystack.l_mark[-2].stringIdentifier, yystack.l_mark[0].numberValue); }
break;
case 53:
#line 193 "parser.y"
	{ yyval.stringIdentifier = yystack.l_mark[0].stringIdentifier; }
break;
case 54:
#line 194 "parser.y"
	{ yyval.stringIdentifier = strdup("-");/* INFO: this is the skip indicator*/ }
break;
case 55:
#line 196 "parser.y"
	{ yyval.stringValue = strdup(yystack.l_mark[0].stringValue); }
break;
case 56:
#line 197 "parser.y"
	{ char * s = strdup(yystack.l_mark[-2].stringValue); strcat(s,yystack.l_mark[0].stringValue); yyval.stringValue=s; }
break;
case 57:
#line 199 "parser.y"
	{printf("print : %f\n", yystack.l_mark[-1].numberValue);}
break;
case 58:
#line 200 "parser.y"
	{printf("print : %s\n", yystack.l_mark[-1].stringValue);}
break;
case 59:
#line 201 "parser.y"
	{printf("print : %s\n", (yystack.l_mark[-1].booleanValue == 1 ? "true" : "false"));}
break;
case 60:
#line 203 "parser.y"
	{actOnMemoryDump(yystack.l_mark[-1].numberValue);}
break;
case 62:
#line 206 "parser.y"
	{yyval.numberValue=yystack.l_mark[-2].numberValue+yystack.l_mark[0].numberValue;}
break;
case 63:
#line 207 "parser.y"
	{yyval.numberValue=yystack.l_mark[-2].numberValue-yystack.l_mark[0].numberValue;}
break;
case 64:
#line 208 "parser.y"
	{yyval.numberValue=yystack.l_mark[-2].numberValue*yystack.l_mark[0].numberValue;}
break;
case 65:
#line 209 "parser.y"
	{yyval.numberValue=yystack.l_mark[-2].numberValue/yystack.l_mark[0].numberValue;}
break;
case 66:
#line 210 "parser.y"
	{yyval.numberValue=pow(yystack.l_mark[-2].numberValue, yystack.l_mark[0].numberValue);}
break;
case 67:
#line 211 "parser.y"
	{yyval.numberValue=yystack.l_mark[-1].numberValue;}
break;
case 68:
#line 214 "parser.y"
	{yyval.numberValue = yystack.l_mark[0].numberValue;}
break;
case 69:
#line 215 "parser.y"
	{yyval.numberValue = actOnNumericVariableEvaluation(yystack.l_mark[0].stringIdentifier);}
break;
case 70:
#line 217 "parser.y"
	{yyval.numberValue=yystack.l_mark[-1].numberValue;}
break;
case 71:
#line 219 "parser.y"
	{yyval.booleanValue=yystack.l_mark[0].booleanValue;}
break;
case 72:
#line 220 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue > yystack.l_mark[0].numberValue;}
break;
case 73:
#line 221 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue < yystack.l_mark[0].numberValue;}
break;
case 74:
#line 222 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue >= yystack.l_mark[0].numberValue;}
break;
case 75:
#line 223 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue <= yystack.l_mark[0].numberValue;}
break;
case 76:
#line 224 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue == yystack.l_mark[0].numberValue;}
break;
case 77:
#line 225 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].numberValue != yystack.l_mark[0].numberValue;}
break;
case 78:
#line 226 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].booleanValue|yystack.l_mark[0].booleanValue;}
break;
case 79:
#line 227 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-2].booleanValue&yystack.l_mark[0].booleanValue;}
break;
case 80:
#line 228 "parser.y"
	{yyval.booleanValue=!yystack.l_mark[0].booleanValue;}
break;
case 81:
#line 229 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-1].booleanValue;}
break;
case 82:
#line 231 "parser.y"
	{yyval.booleanValue=yystack.l_mark[-1].booleanValue;}
break;
case 83:
#line 238 "parser.y"
	{actOnFunctionDeclaration(yystack.l_mark[-3].stringType, yystack.l_mark[-2].stringIdentifier, NULL, 1);}
break;
case 84:
#line 239 "parser.y"
	{actOnFunctionDeclaration(yystack.l_mark[-4].stringType, yystack.l_mark[-3].stringIdentifier, yystack.l_mark[-1].stringValue  , 0);}
break;
case 85:
#line 241 "parser.y"
	{ yyval.stringValue = strdup(actOnIntWrapper(yystack.l_mark[0].stringType)); }
break;
case 86:
#line 242 "parser.y"
	{ char * s = strdup(actOnIntWrapper(yystack.l_mark[-2].stringType)); strcat(s,yystack.l_mark[0].stringValue); yyval.stringValue=s; }
break;
case 87:
#line 244 "parser.y"
	{actOnFunctionDefinition(yystack.l_mark[-4].stringType, yystack.l_mark[-3].stringIdentifier, NULL, 1);}
break;
case 88:
#line 245 "parser.y"
	{actOnFunctionDefinition(yystack.l_mark[-5].stringType, yystack.l_mark[-4].stringIdentifier, yystack.l_mark[-2].stringValue  , 0);}
break;
case 89:
#line 247 "parser.y"
	{ yyval.stringValue = strdup(actOnIntWrapper(yystack.l_mark[-1].stringType)); }
break;
case 90:
#line 248 "parser.y"
	{ char * s = strdup(actOnIntWrapper(yystack.l_mark[-3].stringType)); strcat(s,yystack.l_mark[0].stringValue); yyval.stringValue=s; }
break;
case 91:
#line 251 "parser.y"
	{yyval.stringValue = strdup(actOnFunctionCall(yystack.l_mark[-2].stringIdentifier, NULL, 1));}
break;
case 92:
#line 252 "parser.y"
	{yyval.stringValue = strdup(actOnFunctionCall(yystack.l_mark[-3].stringIdentifier,   yystack.l_mark[-1].stringValue, 0));}
break;
case 95:
#line 257 "parser.y"
	{ yyval.stringValue = strdup(yystack.l_mark[0].stringValue); }
break;
case 96:
#line 258 "parser.y"
	{ char * s = strdup(yystack.l_mark[-2].stringValue); strcat(s,yystack.l_mark[0].stringValue); yyval.stringValue=s; }
break;
case 97:
#line 260 "parser.y"
	{yyval.stringValue = yystack.l_mark[0].stringValue;}
break;
case 98:
#line 261 "parser.y"
	{yyval.stringValue = strdup("double");}
break;
case 99:
#line 262 "parser.y"
	{yyval.stringValue = strdup("boolean");}
break;
case 100:
#line 263 "parser.y"
	{yyval.stringValue = strdup("boolean");}
break;
case 101:
#line 264 "parser.y"
	{yyval.stringValue = strdup("double");}
break;
case 102:
#line 265 "parser.y"
	{yyval.stringValue = strdup("string");}
break;
case 103:
#line 266 "parser.y"
	{yyval.stringValue = actOnFetchVariableType(yystack.l_mark[0].stringIdentifier);}
break;
case 104:
#line 267 "parser.y"
	{ yyval.stringValue = strdup("-");}
break;
#line 1317 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
