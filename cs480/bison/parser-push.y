%{
#include <iostream>
#include <map>

std::map<std::string, float> symbols;

void yyerror(const char* err);
extern int yylex();
%}

%define api.pure full
%define api.push-pull push
%define parse.error verbose

/* %define api.value.type { std::string* } */
%union {
  std::string* str;
  float num;
  int category;
}

%token <str> IDENTIFIER
%token <num> NUMBER
%token <category> EQUALS PLUS MINUS TIMES DIVIDEDBY
%token <category> SEMICOLON LPAREN RPAREN

%type <num> expression

%left PLUS MINUS
%left TIMES DIVIDEDBY
/* %right */
/* %nonassoc */

%start program

%%

program
  : program statement
  | statement
  ;

statement
  : IDENTIFIER EQUALS expression SEMICOLON { symbols[*$1] = $3; delete $1; }
  ;

expression
  : LPAREN expression RPAREN { $$ = $2; }
  | expression PLUS expression { $$ = $1 + $3; /* new std::string(*$1 + "+" + *$3) */ }
  | expression MINUS expression { $$ = $1 - $3; }
  | expression TIMES expression { $$ = $1 * $3; }
  | expression DIVIDEDBY expression { $$ = $1 / $3; }
  | NUMBER { $$ = $1; }
  | IDENTIFIER { $$ = symbols[*$1]; delete $1; }
  ;

/*
 * Python if statement:
 * if a == 2:
 *   b = 4
 *
 * Corresponding C/C++ if statement:
 * if (a == 2) {
 *   b = 4;
 * }
 *
 * Bison action for putting together C++ translation:
 * $$ = new std::string("if (" + *$2 + ")\n {" + *$5 + "}");
 */

%%

void yyerror(const char* err) {
  std::cerr << "Error: " << err << std::endl;
}

int main() {
  if (!yylex()) {
    /* Print the symbol values. */
    std::map<std::string, float>::iterator it;
    for (it = symbols.begin(); it != symbols.end(); it++) {
      std::cout << it->first << " = " << it->second << std::endl;
    }
    return 0;
  } else {
    return 1;
  }
}
