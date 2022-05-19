%{
#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>

#include "parser.hpp"

struct word {
  std::string lexeme;
  std::string category;
};

std::vector<struct word> words;
std::set<std::string> ids;
bool have_error = false;

void save_word(const std::string& lexeme, const std::string& category) {
  struct word word = {
    .lexeme = lexeme,
    .category = category
  };
  words.push_back(word);
}

%}

%option noyywrap
%option yylineno

%%

%{
  /* No code to put at the top of yylex(). */
%}

[ \t\n]*      /* Ignore whitespace. */

[a-z][0-9]?   {
                /* save_word(yytext, "IDENTIFIER");
                ids.insert(yytext); */
                /* char* yytext; */
                yylval.str = new std::string(yytext, yyleng);
                return IDENTIFIER;
              }

[0-9]+("."[0-9]+)? {
                /* save_word(yytext, "NUMBER");  */
                yylval.num = atof(yytext);
                return NUMBER;
              }

"="           {
                /* save_word(yytext, "EQUALS"); */
                yylval.category = EQUALS;
                return EQUALS;
              }
"+"           {
                /* save_word(yytext, "PLUS"); */
                yylval.category = PLUS;
                return PLUS;
              }
"-"           {
                /* save_word(yytext, "MINUS"); */
                yylval.category = MINUS;
                return MINUS;
              }
"*"           {
                /* save_word(yytext, "TIMES"); */
                yylval.category = TIMES;
                return TIMES;
              }
"/"           {
                /* save_word(yytext, "DIVIDEDBY"); */
                yylval.category = DIVIDEDBY;
                return DIVIDEDBY;
              }

";"           {
                /* save_word(yytext, "SEMICOLON"); */
                yylval.category = SEMICOLON;
                return SEMICOLON;
              }
"("           {
                /* save_word(yytext, "LPAREN"); */
                yylval.category = LPAREN;
                return LPAREN;
              }
")"           {
                /* save_word(yytext, "RPAREN"); */
                yylval.category = RPAREN;
                return RPAREN;
              }

.             {
                std::cerr << "Invalid symbol on line " << yylineno
                  << ": " << yytext << std::endl;
                have_error = true;
                yylval.category = yytext[0];
                return yytext[0];
              }

<<EOF>>       {
                if (have_error) {
                  return 1;
                }
                return 0;
              }


%%

/* int main() {
  if (!yylex()) {
    std::vector<struct word>::iterator wit;
    for (wit = words.begin(); wit != words.end(); ++wit) {
      std::cout << wit->lexeme << "\t" << wit->category << std::endl;
    }

    std::cout << std::endl << "Identifiers:" << std::endl;
    std::set<std::string>::iterator iit;
    for (iit = ids.begin(); iit != ids.end(); ++iit) {
      std::cout << *iit << std::endl;
    }
  }
} */
