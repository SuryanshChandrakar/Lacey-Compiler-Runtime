%{
#define YYSTYPE string
#define YYERROR_VERBOSE

extern int yylineno;
void yyerror(const char*);
extern int yylex (void);

#include<iostream>
#include<vector>
#include<map>
using namespace std;

string itoa(int i) {
	if(i == 0)
		return "0";
	string result;
	while(i > 0) {
		result = string(1, '0'+i%10) + result;
		i /= 10;
	}
	return result;
}

enum id_type {variable, procedure, constant};
class id_info {                                // class for symbol-table entries
	public:
		id_type type;
		int local_variables; // only for procedures
		int const_val; // only for constants
		int offset; // address of var in its frame
		int declaration_level;
		id_info() {}
};
id_info var_info(int offs, int lvl) {
	id_info info;
	info.type = variable;
	info.offset = offs;
	info.declaration_level = lvl;
	return info;
}
id_info const_info(int constval) {
	id_info info;
	info.type = constant;
	info.const_val = constval;
	return info;
}
id_info proc_info(int loc, int lvl) {
	id_info info;
	info.type = procedure;
	info.local_variables = loc;
	info.declaration_level = lvl;
	return info;
}

int jumplabel_counter = 1; // used to give unique names to all jump-labels (a1 a2...)
map<int, map<string, id_info> > symbol_table; // now every procedure gets its
                    // own symbol-table and can access the ones of higher frames
int level=0;
map<int,int> local_vars; // count of vars in current procedure

%} // Yacc Deklarationen



%start prog
%token
INOUT VAR CONST PROC OPEN CLOSE SEMICOLON DOT COMMA BEGN END
IF THEN ELSE WHILE DO
ASSIGN NUM ID ADD SUB MUL DIV EQ NEQ GE GT LE LT
OR AND NOT

%left OR
%left AND
%right NOT
%left LE GE LT GT EQ NEQ
%left ADD SUB
%left MUL DIV MOD



%% // Produktionen
prog : INOUT {local_vars[0]=0;} var_ids SEMICOLON {level=1;} const_decls var_decls proc_decls statement DOT {
           cout << "\tCALL aGamma 1 " << local_vars[1] << "\n"
                << "\tJMP 0\n"
                << $8
                << "aGamma:\n"
                << $9
                << "\tRET\n";
        }
     ;


const_decls : { $$ = ""; }
            | CONST const_ids SEMICOLON { $$ = ""; }
            ;
const_ids : ID EQ NUM {
                map<string, id_info>::iterator it = symbol_table[level].find($1);
                if(it == symbol_table[level].end())
                   symbol_table[level][$1] = const_info(atoi($3.c_str()));
                else
                   cerr << "ERROR: (line " << yylineno << "): " << $1 << " is already declared";
                $$ = "";
             }
          | ID EQ NUM COMMA {
                map<string, id_info>::iterator it = symbol_table[level].find($1);
                if(it == symbol_table[level].end())
                   symbol_table[level][$1] = const_info(atoi($3.c_str()));
                else
                   cerr << "ERROR: (line " << yylineno << "): " << $1 << " is already declared";
             } const_ids { $$ = ""; }
          ;
var_decls : {$$="";}
          | VAR var_ids SEMICOLON
          ;
var_ids : ID {
              map<string, id_info>::iterator it = symbol_table[level].find($1);
              if(it == symbol_table[level].end())
                 symbol_table[level][$1] = var_info(++local_vars[level], level);
              else
                 cerr << "ERROR: (line " << yylineno << "): " << $1 << " is already declared";
              $$ = "";
           }
        | ID COMMA {
              map<string, id_info>::iterator it = symbol_table[level].find($1);
              if(it == symbol_table[level].end())
                 symbol_table[level][$1] = var_info(++local_vars[level], level);
              else
                 cerr << "ERROR: (line " << yylineno << "): " << $1 << " is already declared";
           } var_ids {$$="";}
        ;
proc_decls : { $$=""; }
           | proc proc_decls {$$ = $1+$2;}
           ;
proc : PROC ID SEMICOLON {local_vars[++level]=0; symbol_table[level].clear();} const_decls var_decls  {
           map<string, id_info>::iterator it = symbol_table[level].find($2);
           if(it == symbol_table[level].end())
              symbol_table[level][$2] = proc_info(local_vars[level], level-1);
           else
              cerr << "ERROR: (line " << yylineno << "): " << $2 << " is already declared";
        } proc_decls statement SEMICOLON {
           $$ = $8 + $2 + ":\n" + $9 + "\tRET\n";
           level--;
        }

     ;



statements : statement {$$ = $1;} // not terminating the last statement is a pretty bad idea, i can tell you...
           | statement SEMICOLON statements {$$ = $1 + $3;}
           ;
statement : ID ASSIGN expression {
                for(int i = level; i >= 0; --i) {
                   map<string, id_info>::iterator it = symbol_table[i].find($1);
                   if(it != symbol_table[i].end()) {
                      if(it->second.type == variable)
                         $$ = $3 + "\tSTO " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.offset) + "\n";
                      else
                         cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not a variable\n";
                   goto assign_found;}
                }
                cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not declared\n";
                assign_found:;
             }

          | ID OPEN CLOSE {
                for(int i = level; i >= 0; --i) {
                   map<string, id_info>::iterator it = symbol_table[i].find($1);
                   if(it != symbol_table[i].end()) {
                      if(it->second.type == procedure)
                         $$ = "\tCALL " + $1 + " " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.local_variables) + "\n";
                      else
                         cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not a procedure\n";
                   goto proc_found;}
                }
                cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not declared\n";
                proc_found:;
             }

          | WHILE expression DO statement {
                string jump1 = "a"+itoa(jumplabel_counter);
                string jump2 = "a"+itoa(jumplabel_counter+1);
                jumplabel_counter += 2;
                $$ = jump1 + ":\n"
                   + $2                      // code to test the condition
                   + "\tJFALSE " + jump2 + "\n"  // if false, jump behind looped code
                   + $4                      // looped code
                   + "\tJMP " + jump1 + "\n" // jump back to testing the condition
                   + jump2 + ":\n";
             }

          | BEGN statements END { $$ = $2; }

          | IF expression THEN statement {
                string jump1 = "a"+itoa(jumplabel_counter);
                jumplabel_counter++;
                $$ = $2                     // code to test the condition
                   + "\tJFALSE " + jump1 + "\n" // if false, jump behind then-codeblock
                   + $4                     // then-codeblock
                   + jump1 + ":\n";
             }

          | IF expression THEN statement ELSE statement {
                string jump1 = "a"+itoa(jumplabel_counter);
                string jump2 = "a"+itoa(jumplabel_counter+1);
                jumplabel_counter += 2;

                $$ = $2                      // code to test the condition
                   + "\tJFALSE " + jump1 + "\n"  // if false, jump to else-codeblock
                   + $4                      // then-codeblock
                   + "\tJMP " + jump2 + "\n" // jump behind else-codeblock
                   + jump1 + ":\n"
                   + $6                      // else-codeblock
                   + jump2 + ":\n";
             }
          ;



expression : NUM { $$ = "\tLIT "+$1+"\n"; }

           | ID {
                 for(int i = level; i >= 0; --i) {
                    map<string, id_info>::iterator it = symbol_table[i].find($1);
                    if(it != symbol_table[i].end()) {
                       if(it->second.type == variable)
                          $$ = "\tLOAD " + itoa(level-it->second.declaration_level) + " " + itoa(it->second.offset) + "\n";
                       else if(it->second.type == constant)
                          $$ = "\tLIT " + itoa(it->second.const_val) + "\n";
                       else
                          cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not a variable\n";
                    goto id_found;}
                 }
                 cerr << "ERROR (line " << yylineno << "): "  << $1 << " is not declared\n";
                 id_found:;
              }

           | OPEN expression CLOSE { $$ = $2; }

           | expression operator expression {
                 $$ = $1  // evaluate first expression (and push result on stack)
                    + $3  // evaluate second expression (and push result on stack)
                    + $2; // calculare result, depending on the operator
              }

           | NOT expression { $$ = $2 + "\tNOT\n"; }
           ;

operator : ADD  {$$ = "\tADD\n";}
         | SUB  {$$ = "\tSUB\n";}
         | MUL  {$$ = "\tMULT\n";}
         | DIV  {$$ = "\tDIV\n";}
         | EQ   {$$ = "\tEQ\n";}
         | NEQ  {$$ = "\tNEQ\n";}
         | GE   {$$ = "\tGE\n";}
         | GT   {$$ = "\tGT\n";}
         | LE   {$$ = "\tLE\n";}
         | LT   {$$ = "\tLT\n";}
         | AND  {$$ = "\tAND\n";}
         | OR   {$$ = "\tOR\n";}
         ;



%%

#include "lexer.cpp" // lexer einbinden

void yyerror(const char* s)
{
	cerr << "SYNTACTIC ERROR (Line " << yylineno << "): " << s << endl;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cerr << argv[0] << " needs a bps sourcecode as parameter\n";
		return 1;
	}
	yyin = fopen(argv[1], "r");
	yyparse();
	if(yynerrs != 0)
	{
		cerr << " " << yynerrs << " syntactic errors occured\n";
		return 1;
	}
	return 0;
}
