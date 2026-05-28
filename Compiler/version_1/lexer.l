
%option noyywrap
%option nostdinit
%option yylineno
%option case-insensitive
%option full

%{
    #include <iostream>
    using namespace std;
    extern string yylval;
%}


LETTER [a-zA-Z]
DIGIT [0-9]
%% // --------------------------------------------------------------------------
"//"[^\n]*\n                            {yy_current_state=yy_start; yyleng = 0;}
"/*"([^\*]*(\*+)[^*/])*([^\*]*)(\*+)"/" {yy_current_state=yy_start; yyleng = 0;}

"("                                     {yylval = ""; return OPEN;}
")"                                     {yylval = ""; return CLOSE;}
[\n\t" "]*                              {yy_current_state=yy_start; yyleng = 0;}
";"                                     {yylval = ""; return SEMICOLON;}
","                                     {yylval = ""; return COMMA;}
"."                                     {yylval = ""; return DOT;}

"if"                                    {yylval = ""; return IF;}
"then"                                  {yylval = ""; return THEN;}
"else"                                  {yylval = ""; return ELSE;}
"begin"                                 {yylval = ""; return BEGN;}
"end"                                   {yylval = ""; return END;}
"while"                                 {yylval = ""; return WHILE;}
"do"                                    {yylval = ""; return DO;}
"in/out"                                {yylval = ""; return INOUT;}

"or"                                    {yylval = ""; return OR;}
"and"                                   {yylval = ""; return AND;}
"not"                                   {yylval = ""; return NOT;}

"proc"                                  {yylval = ""; return PROC;}
"var"                                   {yylval = ""; return VAR;}
"const"                                 {yylval = ""; return CONST;}

":="                                    {yylval = ""; return ASSIGN;}
"+"                                     {yylval = ""; return ADD;}
"-"                                     {yylval = ""; return SUB;}
"*"                                     {yylval = ""; return MUL;}
"/"                                     {yylval = ""; return DIV;}

"="                                     {yylval = ""; return EQ;}
"<>"                                    {yylval = ""; return NEQ;}
"<"                                     {yylval = ""; return LT;}
"<="                                    {yylval = ""; return LE;}
">"                                     {yylval = ""; return GT;}
">="                                    {yylval = ""; return GE;}

{LETTER}({LETTER}|{DIGIT})*             {yylval = string(yytext); return ID;}
{DIGIT}+                                {yylval = string(yytext); return NUM;}

.|\n                                    {cerr << "\n\nLEXICAL ERROR (Line "
                                              << yylineno
                                              << "): Unexpected character \""
                                              << yytext[0] << "\"\n";
                                              yy_current_state=yy_start; yyleng = 0;}
%% //---------------------------------------------------------------------------
