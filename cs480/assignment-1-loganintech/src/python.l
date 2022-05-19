%option noyywrap

%{
    #include <math.h>

    int indent_level = 0;
    int indent_step = 1 << 30;
%}

%%


True    {
            yyval.category = BOOLEAN;
            return BOOLEAN;
        }

False   {
            yyval.category = BOOLEAN;
            return BOOLEAN;
        }

and     {
            yyval.category = AND;
            return AND;
        }

break   {
            yyval.category = BREAK;
            return BREAK;
        }

def     {
            yyval.category = DEF;
            return DEF;
        }

elif    {
            yyval.category = ELIF;
            return ELIF;
        }

else    {
            yyval.category = ELSE;
            return ELSE;
        }

for     {
            yyval.category = FOR;
            return FOR;
        }

if      {
            yyval.category = IF;
            return IF;
        }

not     {
            yyval.category = NOT;
            return NOT;
        }

or      {
            yyval.category = OR;
            return OR;
        }

return  {
            yyval.category = RETURN;
            return RETURN;
        }

while   {
            yyval.category = WHILE;
            return WHILE;
        }

"!="    {
            yyval.category = NEQ;
            return NEQ;
        }

"=="    {
            yyval.category = EQ;
            return EQ;
        }

">="    {
            yyval.category = LTE;
            return LTE;
        }

"<="    {
            yyval.category = GTE;
            return GTE;
        }

"+"     {
            yyval.category = PLUS;
            return PLUS;
        }

"-"     {
            yyval.category = MINUS;
            return MINUS;
        }

"*"     {
            yyval.category = TIMES;
            return TIMES;
        }

"/"     {
            yyval.category = DIVIDEDBY;
            return DIVIDEDBY;
        }

"="     {
            yyval.category = ASSIGN;
            return ASSIGN;
        }

">"     {
            yyval.category = GT;
            return GT;
        }

"<"     {
            yyval.category = LT;
            return LT;
        }

"("     {
            yyval.category = LPAREN;
            return LPAREN;
        }

")"     {
            yyval.category = RPAREN;
            return RPAREN;
        }

","     {
            yyval.category = COMMA;
            return COMMA;
        }

":"     {
            yyval.category = COLON;
            return COLON;
        }

[.+\n](?:\n)* {
    std::cout << "NEWLINE" << std::endl;
}

^[\t ]+ {
    // This rule will match the first indentation
    if(indent_step > yyleng) {
        indent_step = yyleng;
    }
    if(yyleng > indent_level) {
        indent_level = yyleng;
        std::cout << "INDENT" << std::endl;
    }
    if(yyleng < indent_level) {
        indent_level = yyleng;
        std::cout << "DEDENT" << std::endl;
    }
}

#.*\n ;
[.+[[:space:]]+.+] ;
[[:space:]] ;

\-?[0-9]+ {
    yyval.ival = atoi(yytext);
    return INTEGER;
}

(?:\-?[0-9]+)?\.[0-9]+ {
    yylval.ival = atof(yytext);
    return FLOAT;
}


^[a-zA-Z\_]+[a-zA-z0-9\_]* {
    for(; 0 < indent_level; indent_level-=indent_step) {
        std::cout << "DEDENT" << std::endl;
    }
    yylval.str = new std::string(yytext, yyleng);
}

[a-zA-Z\_]+[a-zA-z0-9\_]* {
    yylval.str = new std::string(yytext, yyleng);
    return IDENTIFIER;
}

. {
    std::cerr << "Invalid symbol on line " << yylineno << ": " << yytext << std::endl;
    have_error = true;
    yylval.category = yytext[0];
    return yytext[0];
}

<<EOF>> {
    for (int i = indent_level; i > 0; i-=indent_step) {
        std::cout << "DEDENT" << std::endl;
    }
    if (have_error) {
        return 1;
    }
    return 0;
}

%%
