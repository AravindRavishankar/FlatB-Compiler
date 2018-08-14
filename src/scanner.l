%{
#include"ast_temp.h"
#include "parser.tab.h"
#include<bits/stdc++.h>
#define YY_DECL extern "C" int yylex()
using namespace std;
int LINENUM=0;
%}

%%
int		return INT;
for		{ //printf("for"); 
			return FOR; }
declblock return DECLBLOCK;
codeblock { //printf("codeblock");  
			return CODEBLOCK;}
\;		{ //printf(";"); 
			return ';'; }
println 	return PRINTLN;
print 	{ //printf("print"); 
				return PRINT; }
if		return IF;
else 	return ELSE;
goto 	{ //printf("goto"); 
				return GOTO; }
got { 
		return GOT; }
read 	{ //printf("read"); 
			return READ; }
while 	return WHILE;

":"		return ':';
"+" 	return PLUS;
"-"		return MINUS;
"*"		return MUL;
"/"		return DIV;
"<="	return LE;
">="	return GE;
">" 	return  GT;
"<" 	return LT;
"=="	return EQEQ;
"!="	return NEQ;
"="		{ // printf("="); 
			return '='; }
"{"		{ return  '{'; }
"}"		{ //printf("}");  
				return '}'; }
"["		{ //printf("["); 
				return '[';}
"]"		{ //printf("]"); 
			return ']'; }
","		return ',';
\".*\"	{  //printf("string"); 
    	yytext[yyleng-1] = '\0';
		yylval.str = strdup(yytext+1);
			return STRING; }

[0-9][0-9]*  	{  //printf("number"); 
 				yylval.num = atoi(yytext);
					return NUMBER; } 
[_a-zA-Z][_a-zA-Z0-9]*  {	 //printf("identifier");  
						yylval.str = strdup(yytext);
							return IDENTIFIER; }

[\t ]		 {  ; }
[\n]	 { ++LINENUM;  ;}
.		{ return ETOK;}
%%


