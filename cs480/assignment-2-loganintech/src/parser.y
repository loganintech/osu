%{
#include <iostream>
#include <set>
#include <vector>
#include <string>

std::set<std::string> idents;
std::vector<std::string> lines;

void yyerror (const char *err);
extern int yylex();
extern int yylineno;
%}

%define api.pure full
%define api.push-pull push
%define parse.error verbose

%union {
    std::string* str;
    float fval;
    bool bval;
    int lex_category;
}

%token <str> IDENTIFIER
%token <fval> NUMBER
%token <bval> BOOL
%token <lex_category> EQ NEQ GT LT GTE LTE PLUS MINUS TIMES DIVIDEBY ASSIGN
%token <lex_category> AND OR NOT
%token <lex_category> IF ELIF ELSE WHILE
%token <lex_category> LPAREN RPAREN COLON COMMA
%token <lex_category> BREAK RETURN
%token <lex_category> NEWLINE ENDOFFILE INDENT DEDENT

%type <str> expression
%type <str> controlflow

// TIMES and DIVIDEBY have a HIGHER precedence here
%left AND OR EQ NEQ GT LT GTE LTE NOT
%left PLUS MINUS
%left TIMES DIVIDEBY

%start program

%%

program
    : program statement
    | statement
    ;

statement
    : IDENTIFIER ASSIGN expression NEWLINE {
      // std::cout << std::endl << std::endl << "Writing Ident: " << *$1 << " - " << $3 << std::endl << std::endl;
      lines.push_back(std::string(*$1 + " = " + *$3 + ";"));
      idents.insert(*$1); }
    | controlflow
    ;

controlflow
    : IF expression COLON NEWLINE INDENT { lines.push_back(std::string("if (" + *$2 + ") {")); }
    | ELIF expression COLON NEWLINE INDENT { lines.push_back(std::string("else if (" + *$2 + ") {")); }
    | ELSE COLON NEWLINE INDENT { lines.push_back(std::string("else {")); }
    | WHILE expression COLON NEWLINE INDENT { lines.push_back(std::string("while (" + *$2 + ") {")); }
    | BREAK NEWLINE { lines.push_back(std::string("break;")); }
    | DEDENT { lines.push_back(std::string("}")); }
    ;

expression
    : LPAREN expression RPAREN { $$ = new std::string("(" + *$2 + ")"); }
    | expression PLUS expression { $$ = new std::string(*$1 + "+" + *$3); }
    | expression MINUS expression { $$ = new std::string(*$1 + "-" + *$3); }
    | expression TIMES expression { $$ = new std::string(*$1 + "*" + *$3); }
    | expression DIVIDEBY expression { $$ = new std::string(*$1 + "/" + *$3); }
    | expression GT expression { $$ = new std::string(*$1 + ">" + *$3); }
    | expression LT expression { $$ = new std::string(*$1 + "<" + *$3); }
    | expression GTE expression { $$ = new std::string(*$1 + ">=" + *$3); }
    | expression LTE expression { $$ = new std::string(*$1 + "<=" + *$3); }
    | expression AND expression { $$ = new std::string(*$1 + "&&" + *$3); }
    | expression OR expression { $$ = new std::string(*$1 + "||" + *$3); }
    | expression EQ expression { $$ = new std::string(*$1 + "==" + *$3); }
    | expression NEQ expression { $$ = new std::string(*$1 + "!=" + *$3); }
    | NOT expression { $$ = new std::string("!" + *$2); }
    | NUMBER { $$ = new std::string(std::to_string($1)); }
    | BOOL { $$ = new std::string(std::to_string($1)); }
    | IDENTIFIER {
      // std::cout << std::endl << std::endl << "Reading Ident: " << *$1 << " - " << idents[*$1] << std::endl << std::endl;
      $$ =  $1; }
    ;

%%

void yyerror(const char* err) {
  std::cerr << "Parser Error: " << err << " on line " << yylineno << std::endl;
}

int main() {
  yydebug = 0;
  if (!yylex()) {

    std::cout << "#include <iostream>" << std::endl;
    std::cout << "int main() {" << std::endl;
    for (auto ident: idents) {
      std::cout << "double " << ident << ";" << std::endl;
    }

    std::cout << std::endl << "/* Begin program */" << std::endl << std::endl;

    for (auto i: lines) {
      std::cout << i << std::endl;
    }

    std::cout << std::endl << "/* End program */" << std::endl << std::endl;

    for (auto ident: idents) {
      std::cout << "std::cout << \"" << ident <<": \" << " << ident << " << std::endl;" << std::endl;
    }

    std::cout << "}" << std::endl;
    return 0;
  } else {
    return 1;
  }
}
