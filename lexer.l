%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"


int words = 0;
int chars = 1;
int lines = 1;

%}

letter      	[a-zA-Z]
digit       	[0-9]
ID          	{letter}({letter}|{digit})*
delim       	[ \t\n]
NUMBER      	{digit}+(\.{digit}+)?(E[+\-]?(digit)+)?
ws          	{delim}+

%%

//Rule for comments
"/*"    		{
				int c;
					while((c = input()) != 0) {
						if(c == '*') {
							if((c = input()) == '/')
								break;
							else
								unput(c);
						}
					}
				}

//Rule for int		
"int"			{words++; chars += strlen(yytext);
				printf("%s : TYPE\n", yytext);
				yylval.string = strdup(yytext); 
				return TYPE;
				}

//Rule for void
"void"			{words++; chars += strlen(yytext);
				printf("%s : TYPE\n", yytext);
				yylval.string = strdup(yytext); 
				return TYPE;
				}

//Rule for float
"float"			{words++; chars += strlen(yytext);
				printf("%s : TYPE\n", yytext);
				yylval.string = strdup(yytext); 
				return TYPE;
				}

//Rule for if
"if"			{words++; chars += strlen(yytext);
				printf("%s : IF\n", yytext);
				yylval.string = strdup(yytext); 
				return IF;
				}

//Rule for else
"else"			{words++; chars += strlen(yytext);
				printf("%s : ELSE\n", yytext);
				yylval.string = strdup(yytext); 
				return ELSE;
				}

//Rule for while
"while"			{words++; chars += strlen(yytext);
				printf("%s : WHILE\n", yytext);
				yylval.string = strdup(yytext); 
				return WHILE;
				}
				
//Rule for write
"write"			{words++; chars += strlen(yytext);
				printf("%s : WRITE\n", yytext);
				yylval.string = strdup(yytext); 
				return WRITE;
				}

//Rule for identifiers
{ID}			{words++; chars += strlen(yytext);
			  	printf("%s : ID\n",yytext);
			  	yylval.string = strdup(yytext); 
			  	return ID;
				}

//Rule for numbers			
{NUMBER}		{words++; chars += strlen(yytext);
			  	printf("%s : NUMBER\n",yytext);
			 	yylval.number = atoi(strdup(yytext)); 
			  	return NUMBER;
				}

//Rule for semicolons			
";"				{chars++;
		  		printf("%s : SEMICOLON\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return SEMICOLON;
				}

//Rule for assignment equals
"="				{chars++;
		  		printf("%s : EQ\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return EQ;
				}

//Rule for multiplication
"*"				{chars++;
		  		printf("%s : MATHOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return MATHOP;
				}

//Rule for divison
"/"				{chars++;
		  		printf("%s : MATHOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return MATHOP;
				}

//Rule for addition
"+"				{chars++;
		  		printf("%s : MATHOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return MATHOP;
				}

//Rule for subtraction
"-"				{chars++;
		  		printf("%s : MATHOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return MATHOP;
				}

//Rule for not
"!"				{chars++;
		  		printf("%s : NOT\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return NOT;
				}

//Rule for equivalency check
"=="			{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for negative equivalency check
"!="			{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for less than
"<"				{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for greater than
">"				{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for less than or equal to
"<="			{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for greater than or equal to
">="			{chars++;
		  		printf("%s : COMPOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMPOP;
				}

//Rule for AND logical operator
"&&"			{chars++;
		  		printf("%s : LOGOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return LOGOP;
				}

//Rule for OR logical operator
"||"			{chars++;
		  		printf("%s : LOGOP\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return LOGOP;
				}

//Rule for left parentheses
"("				{chars++;
		  		printf("%s : LPAREN\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return LPAREN;
				}

//Rule for right parentheses
")"				{chars++;
		  		printf("%s : RPAREN\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return RPAREN;
				}

//Rule for left brace
"{"				{chars++;
		  		printf("%s : LBRACE\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return LBRACE;
				}

//Rule for right brace
"}"				{chars++;
		  		printf("%s : RBRACE\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return RBRACE;
				}

//Rule for left bracket
"["				{chars++;
		  		printf("%s : LBRACK\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return LBRACK;
				}

//Rule for right bracket
"]"				{chars++;
		  		printf("%s : RBRACK\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return RBRACK;
				}

//Rule for comma
","				{chars++;
		  		printf("%s : COMMA\n", yytext);
		  		yylval.string = strdup(yytext); 
		  		return COMMA;
				}

//Rule for new line
[\n]			{lines++; chars = 0;}

//Rule for tab
[ \t]			{chars++;}

//Rule for unrecognized symbols
.				{chars++;
         		printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
				}
		
%%