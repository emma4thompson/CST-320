%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include "tokens.h"
#include "cSymbolTable.h"
#include "lex.h"
#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */

%%

    // token definitions go here. "if" is an example.
"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);
"array"                     DO_RETURN(ARRAY);
"char"                      DO_RETURN(CHAR);
"."                         DO_RETURN('.');
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');
","                         DO_RETURN(',');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');
"%"                         DO_RETURN('%');
"="                         DO_RETURN('=');
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR); 
"//".*$                     {/* deletes comments*/}
[ \t\n\r]+                  {/* deletes whitespace*/}
[0-9]+"."[0-9]+             DO_RETURN(FLOAT_VAL);
[0-9]+                      DO_RETURN(INT_VAL);
.                           DO_RETURN(JUNK_TOKEN);

"{"                         {
                                cst.IncreaseScope();
                                return yytext[0];
                            }
"}"                         {
                                cst.DecreaseScope();
                                return yytext[0];
                            }
[_a-zA-Z][_a-zA-Z0-9]*      {
                                yylval.symbol = cst.Insert(yytext);
                                return (IDENTIFIER);
                            }

%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

