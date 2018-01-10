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
extern YYSTYPE yylval;
