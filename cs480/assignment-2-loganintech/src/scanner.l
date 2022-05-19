%option noyywrap

%{
    #include <math.h>
    #include <iostream>
    #include <cstdlib>
    #include <vector>
    #include <set>
    #include "parser.hpp"

    int indent_level = 0;
    int indent_step = 1 << 30;

    struct word {
        std::string lexeme;
        std::string lex_category;
    };

    std::vector<struct word> words;
    std::set<std::string> ids;
    bool have_error = false;

    YYSTYPE yylval;
    yypstate* pstate = yypstate_new();

    void save_word(const std::string& lexeme, const std::string& lex_category) {
    struct word word = {
        .lexeme = lexeme,
        .lex_category = lex_category
    };
    words.push_back(word);
    }

#define PUSH_TOKEN(lex_category) do {                             \
    int status = yypush_parse(pstate, lex_category, &yylval);     \
    if (status != YYPUSH_MORE) {                              \
      yypstate_delete(pstate);                                \
      return status;                                          \
    }                                                         \
  } while (0)

%}

%option noyywrap
%option yylineno


%%


True    {
            yylval.lex_category = BOOL;
            yylval.bval = true;
            PUSH_TOKEN(BOOL);
        }

False   {
            yylval.lex_category = BOOL;
            yylval.bval = false;
            PUSH_TOKEN(BOOL);
        }

and     {
            yylval.lex_category = AND;
            PUSH_TOKEN(AND);
        }

break   {
            yylval.lex_category = BREAK;
            PUSH_TOKEN(BREAK);
        }

elif    {
            yylval.lex_category = ELIF;
            PUSH_TOKEN(ELIF);
        }

else    {
            yylval.lex_category = ELSE;
            PUSH_TOKEN(ELSE);
        }

if      {
            yylval.lex_category = IF;
            PUSH_TOKEN(IF);
        }

not     {
            yylval.lex_category = NOT;
            PUSH_TOKEN(NOT);
        }

or      {
            yylval.lex_category = OR;
            PUSH_TOKEN(OR);
        }

return {
            yylval.lex_category = RETURN;
            PUSH_TOKEN(RETURN);
        }

while   {
            yylval.lex_category = WHILE;
            PUSH_TOKEN(WHILE);
        }

"!="    {
            yylval.lex_category = NEQ;
            PUSH_TOKEN(NEQ);
        }

"=="    {
            yylval.lex_category = EQ;
            PUSH_TOKEN(EQ);
        }

">="    {
            yylval.lex_category = GTE;
            PUSH_TOKEN(GTE);
        }

"<="    {
            yylval.lex_category = LTE;
            PUSH_TOKEN(LTE);
        }

"+"     {
            yylval.lex_category = PLUS;
            PUSH_TOKEN(PLUS);
        }

"-"     {
            yylval.lex_category = MINUS;
            PUSH_TOKEN(MINUS);
        }

"*"     {
            yylval.lex_category = TIMES;
            PUSH_TOKEN(TIMES);
        }

"/"     {
            yylval.lex_category = DIVIDEBY;
            PUSH_TOKEN(DIVIDEBY);
        }

"="     {
            yylval.lex_category = ASSIGN;
            PUSH_TOKEN(ASSIGN);
        }

">"     {
            yylval.lex_category = GT;
            PUSH_TOKEN(GT);
        }

"<"     {
            yylval.lex_category = LT;
            PUSH_TOKEN(LT);
        }

"("     {
            yylval.lex_category = LPAREN;
            PUSH_TOKEN(LPAREN);
        }

")"     {
            yylval.lex_category = RPAREN;
            PUSH_TOKEN(RPAREN);
        }

","     {
            yylval.lex_category = COMMA;
            PUSH_TOKEN(COMMA);
        }

":"     {
            yylval.lex_category = COLON;
            PUSH_TOKEN(COLON);
        }

[.+\n](?:\n)* {
    yylval.lex_category = NEWLINE;
    PUSH_TOKEN(NEWLINE);
}

^[\t ]+ {
    // This rule will match the first indentation
    if(indent_step > yyleng) {
        indent_step = yyleng;
    }
    if(yyleng > indent_level) {
        indent_level = yyleng;
        yylval.lex_category = INDENT;
        PUSH_TOKEN(INDENT);
    }
    if(yyleng < indent_level) {
        indent_level = yyleng;
        yylval.lex_category = DEDENT;
        PUSH_TOKEN(DEDENT);
    }
}

#.*\n ;
[.+[[:space:]]+.+] ;
[[:space:]] ;


(?:\-?[0-9]+\.)?[0-9]+ {
    // std::cout << std::endl << "Parsing Float: " << yytext << std::endl;
    yylval.fval = atof(yytext);
    PUSH_TOKEN(NUMBER);
}


^[a-zA-Z\_]+[a-zA-z0-9\_]* {
    for(; 0 < indent_level; indent_level-=indent_step) {
        yylval.lex_category = DEDENT;
        PUSH_TOKEN(DEDENT);
    }
    ids.insert(yytext);
    yylval.str = new std::string(yytext, yyleng);
    PUSH_TOKEN(IDENTIFIER);
}

[a-zA-Z\_]+[a-zA-z0-9\_]* {
    ids.insert(yytext);
    yylval.str = new std::string(yytext, yyleng);
    PUSH_TOKEN(IDENTIFIER);
}

. {
    std::cerr << "Invalid symbol on line " << yylineno << ": " << yytext << std::endl;
    have_error = true;
    yylval.lex_category = yytext[0];
    PUSH_TOKEN(yytext[0]);
}

<<EOF>> {
    for(; 0 < indent_level; indent_level-=indent_step) {
        yylval.lex_category = DEDENT;
        PUSH_TOKEN(DEDENT);
    }
    int status = yypush_parse(pstate, 0, NULL);
    yypstate_delete(pstate);
    return status;
}


%%
