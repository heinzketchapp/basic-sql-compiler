%{
    #include "y.tab.h"
    #include <cstring>
%}
%option noyywrap
%%
"create"  { return CREATE; }
"table"   { return TABLE; }
"select"  { return SELECT; }
"insert"  { return INSERT; }
"into"    { return INTO; }
"from"   { return FROM; }
"values"  { return VALUES; }
"drop"    { return DROP; }
"varchar"   { return CHAR; }
"number"  { return NUMBER; }
"count"   {return COUNT; }
"where"   {return WHERE;}
";"     { return SCOLON; }
"("     { return OBR; }
")"     { return CBR; }
"*"     { return ALL; }
","     { return COMMA;}
"'"     { return QUOTE; }
"="      {return EQUALS; }
\n      { return EOL;}
[0-9]+  { yylval.sval = (char *)malloc(strlen(yytext)+1);
          strcpy(yylval.sval, yytext);
          return INTEGER; }
[A-Za-z]+       { yylval.sval = (char *) malloc(strlen(yytext)+1);
                  strcpy(yylval.sval, yytext); 
                  return STRING; }
.   ;
%%