%option noyywrap

%{
    #include "../parser/parser.tab.h"
%}

EQUIVALENT      <->
IMPLICATION     ->
DISJUNCTION     \|
CONJUNCTION     &
NEGATION        ~
DECLARE         DECLARE
PREDICATE       PREDICATE
FUNCTION        FUNCTION
VARIABLE        VARIABLE
TRUE            TRUE
FALSE           FALSE
ALL             ALL
EXIST           EXIST
R_BRACKETS_O    \(
R_BRACKETS_C    \)
S_BRACKETS_O    \[
S_BRACKETS_C    \]
COLON           :
SEMICOLON       ;
COMMA           ,
COMMENT         \/\*.*\*\/
STRING          [a-zA-Z][a-zA-Z\_0-9]*
NUMBER          [0-9][0-9]*
IGNORE          [ \t\n\r]+

%%
{IGNORE} {

}

{COMMENT} { 
    fprintf(stderr, "LEX: COMMENT: %s\n", yytext); 
}
{R_BRACKETS_O} { 
    fprintf(stderr, "LEX: ROUND BRACKET OPEN\n"); 
    return R_BRACKETS_O;
}
{R_BRACKETS_C} { 
    fprintf(stderr, "LEX: ROUND BRACKET CLOSE\n"); 
    return R_BRACKETS_C;
}
{S_BRACKETS_O} { 
    fprintf(stderr, "LEX: SQUARE BRACKET OPEN\n"); 
    return S_BRACKETS_O;
}
{S_BRACKETS_C} { 
    fprintf(stderr, "LEX: SQUARE BRACKET CLOSE\n"); 
    return S_BRACKETS_C;
}
{EQUIVALENT} { 
    fprintf(stderr, "LEX: EQUIVALENT\n"); 
    return EQUIVALENT;
}
{IMPLICATION} { 
    fprintf(stderr, "LEX: IMPLICATION\n"); 
    return IMPLICATION;
}
{DISJUNCTION} { 
    fprintf(stderr, "LEX: DISJUNCTION\n"); 
    return DISJUNCTION;
}
{CONJUNCTION} { 
    fprintf(stderr, "LEX: CONJUNCTION\n"); 
    return CONJUNCTION;
}
{NEGATION} { 
    fprintf(stderr, "LEX: NEGATION\n"); 
    return NEGATION;
}
{COLON} { 
    fprintf(stderr, "LEX: COLON\n"); 
    return COLON;
}
{SEMICOLON} { 
    fprintf(stderr, "LEX: SEMICOLON\n"); 
    return SEMICOLON;
}
{COMMA} { 
    fprintf(stderr, "LEX: COMMA\n"); 
    return COMMA;
}
{DECLARE} { 
    fprintf(stderr, "LEX: DECLARE\n");
    return DECLARE;
}
{PREDICATE} { 
    fprintf(stderr, "LEX: PREDICATE\n"); 
    return PREDICATE;
}
{FUNCTION} { 
    fprintf(stderr, "LEX: FUNCTION\n"); 
    return FUNCTION;
}
{VARIABLE} { 
    fprintf(stderr, "LEX: VARIABLE\n"); 
    return VARIABLE;
}
{TRUE} { 
    fprintf(stderr, "LEX: TRUE\n"); 
    return TRUE;
}
{FALSE} {
    fprintf(stderr, "LEX: FALSE\n");
    return FALSE;
}
{ALL} { 
    fprintf(stderr, "LEX: ALL\n"); 
    return ALL;
}
{EXIST} {
    fprintf(stderr, "LEX: EXIST\n");
    return EXIST;
}
{STRING} { 
    fprintf(stderr, "LEX: STRING: %s\n", yytext); 
    strcpy(yylval.string, yytext);
    return STRING;
}
{NUMBER} { 
    fprintf(stderr, "LEX: NUMBER: %s\n", yytext); 
    int num_int = atoi(yytext);
    yylval.number = num_int;
    return NUMBER;
}


%%
int main( int argc, char** argv) {
    ++argv, --argc;
    if(argc > 0) { 
        yyin = fopen( argv[0], "r");
        if(!yyin) {
            fprintf(stderr, "Error while opening File");
            return 1;
        }
    }
    else {
        yyin = stdin;
    }
    fprintf(stdout, "\n--- START PARSING ---\n\n");
    yyparse();
    fclose(yyin);
    return 0;
}
