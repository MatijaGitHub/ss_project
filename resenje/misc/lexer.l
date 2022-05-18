%{
  #include "parser.h"
  #include "stdlib.h"
%}

%option outfile="lexer.c" header-file="lexer.h"
%option noyywrap



LPAR  "["
RPAR  "]"
PLUS  "+"
MINUS "-"
MUL "*"
DIV "/"
SEMI  ";"
COMMA ","
COLON ":"
DOT "."
STRING ".*"
NEWL "\\n"
PERCENT "%"
DOLLAR "$"

LITERAL   [1-9][0-9]*
SYMBOL [A-Za-z_][A-Za-z0-9_]* 
COM   "#"[^\n\r]*
WS    [ \r\n\t]*






%%

{WS}        {}
{COM}       {}
{LITERAL}		{
	          sscanf(yytext, "%x", &yylval.number);
			  return TOKEN_LIT;
            }
{SYMBOL}     {
	          strcpy(yylval.symbol,yytext);
            return TOKEN_SYMBOL;
            }

{LPAR}      { return TOKEN_LPAR; }
{COLON}     { return TOKEN_COLON;}
{RPAR}      { return TOKEN_RPAR; }
{PLUS}      { return TOKEN_PLUS; }
{MINUS}     {return TOKEN_MINUS; }
{SEMI}      { return TOKEN_SEMI; }
{COMMA}     { return TOKEN_COMMA;}
{DOT}       {return TOKEN_DOT;}
{MUL}       {return TOKEN_MUL;}
{DIV}       {return TOKEN_DIV;}
{NEWL}      {return TOKEN_NEWL;}
{DOLLAR}    {return TOKEN_DOLLAR;}
{PERCENT}    {return TOKEN_PERCENT;}
{STRING}    {
            strcpy(yylval.string,yytext);
            return TOKEN_STRING;
            }
%%


int
yyerror(const char* msg)
{
    fprintf(stderr, "lexer error: %s\n", msg);
    return 0;
}