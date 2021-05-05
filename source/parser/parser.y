%{ 
    #include <stdio.h>
    #include "../symboltable/symboltable.h"
    #include "../syntaxtree/syntaxtree.h"
    #include "../additional/define.h"

    int yylex(void);
    int yyerror(char *s) {
        fprintf(stderr, "ERROR: %s\n", s);
    }
%}

%token DECLARE PREDICATE FUNCTION VARIABLE TRUE FALSE 
COLON SEMICOLON COMMA NUMBER STRING
EXIST ALL EQUIVALENT IMPLICATION DISJUNCTION CONJUNCTION NEGATION 
R_BRACKETS_O R_BRACKETS_C S_BRACKETS_O S_BRACKETS_C


%left EQUIVALENT    
%left IMPLICATION
%left DISJUNCTION
%left CONJUNCTION
%left NEGATION
%left EXIST ALL S_BRACKETS_O S_BRACKETS_C

%type <string> STRING
%type <number> NUMBER
%type <pointer> formula
%type <pointer> term
%type <pointer> multiple_terms

%union {
    char string[100];
    int number;
    void* pointer;
}

%%
program:
    declarations formula SEMICOLON {
        print_entries();
        print_syntax_tree();
    }
;

declarations:
    | declaration declarations
;


declaration:
    DECLARE PREDICATE STRING COLON NUMBER {
        fprintf(stderr, "PAR: Declare Predicate %s with Arity %i\n", $3, $5);
        add_entry(DECLARATION_PREDICATE, $5, $3, NULL);
    }
    | DECLARE FUNCTION STRING COLON NUMBER {
        fprintf(stderr, "PAR: Declare Function %s with Arity %i\n", $3, $5);
        add_entry(DECLARATION_FUNCTION, $5, $3, NULL);
    }
    | DECLARE VARIABLE STRING COLON STRING {
        fprintf(stderr, "PAR: Declare Variable %s of Type %s\n", $3, $5);
        add_entry(DECLARATION_VARIABLE, 0, $3, $5);
    }
;

formula:
    STRING R_BRACKETS_O R_BRACKETS_C {
        entry* identifier = get_symbol_entry($1);
        if(identifier == NULL) {
            fprintf(stderr,"PAR: unknown identifier %s", $1);
            return 1;
        }
        if(identifier->type != DECLARATION_PREDICATE) {
            //symbol is either function or variable -> syntax error
            fprintf(stderr,"PAR: identifier %s is not a predicate", $1);
            return 1;
        }
        $$ = make_unary_node(NODE_PREDICATE, NULL);
        fprintf(stderr, "PAR: Atom: %s\n", $1);

    }
    | STRING R_BRACKETS_O multiple_terms R_BRACKETS_C {
        entry* identifier = get_symbol_entry($1);
        if(identifier == NULL) {
            fprintf(stderr,"PAR: unknown identifier %s", $1);
            return 1;
        }
        if(identifier->type != DECLARATION_PREDICATE) {
            //symbol is either function or variable -> syntax error
            fprintf(stderr,"PAR: identifier %s is not a predicate", $1);
            return 1;
        }
        fprintf(stderr, "PAR: Predicate: %s\n", $1);
        $$ = make_unary_node(NODE_NEGATION, $3);
    }
    | TRUE {
        $$ = make_leaf_node(NODE_TRUE);
        fprintf(stderr, "PAR: True\n");
    }
    | FALSE {
        $$ = make_leaf_node(NODE_FALSE);
        fprintf(stderr, "PAR: False\n");
    }
    | R_BRACKETS_O formula R_BRACKETS_C {
        $$ = $2;
        fprintf(stderr, "PAR: formula in Brackets\n");
    }
    | NEGATION formula {
        fprintf(stderr, "PAR: Negation\n");
        $$ = make_unary_node(NODE_NEGATION, $2);
    }
    | formula EQUIVALENT formula
    {
        fprintf(stderr, "PAR: Equivalent\n");
        $$ = make_binary_node(NODE_EQUIVALENT, $1, $3);
    }
    | formula IMPLICATION formula {
        fprintf(stderr, "PAR: Implication\n");
        $$ = make_binary_node(NODE_IMPLICATION, $1, $3);
    }
    | formula CONJUNCTION formula
    {
        fprintf(stderr, "PAR: Conjunction\n");
        $$ = make_binary_node(NODE_CONJUNCTION, $1, $3);
    }
    | formula DISJUNCTION formula {
        fprintf(stderr, "PAR: Disjunction\n");
        $$ = make_binary_node(NODE_DISJUNCTION, $1, $3);
    }
    | ALL S_BRACKETS_O STRING S_BRACKETS_C formula {
        fprintf(stderr, "PAR: All\n");
        $$ = make_binary_node(NODE_ALL, (void*)get_symbol_entry($3), $5);
    }
    | EXIST S_BRACKETS_O STRING S_BRACKETS_C formula {
        fprintf(stderr, "PAR: Exist\n");
        $$ = make_binary_node(NODE_EXIST, (void*)get_symbol_entry($3), $5);
    }
;


multiple_terms:
    term {
        $$ = $1;
    }
    | term COMMA multiple_terms {
        $$ = $1;
        //set second child of term to term list to link the arguments
        ((node*)$$)->child2 = $3;
    }
;

term: 
    STRING {
        entry* identifier = get_symbol_entry($1);
        if(identifier == NULL) {
            fprintf(stderr,"PAR: unknown identifier %s", $1);
            return 1;
        }
        if(identifier->type == DECLARATION_VARIABLE || (identifier->type == DECLARATION_FUNCTION && identifier->arity == 0)) {
            fprintf(stderr, "PAR: Term of type variable or constant: %s\n", $1);
            $$ = make_binary_node(NODE_ARGUMENT, (void*)get_symbol_entry($1), NULL);
        }
        else {
            //symbol is not a variable and not a constant
            fprintf(stderr,"PAR: identifier %s is not a variable and not a constant", $1);
            return 1;
        }
    }
    | NUMBER
    {
        $$ = make_number_node($1);
        fprintf(stderr, "PAR: Term: %d\n", $1);
    }
    | STRING R_BRACKETS_O multiple_terms R_BRACKETS_C {
        entry* identifier = get_symbol_entry($1);
        if(identifier == NULL) {
            fprintf(stderr,"PAR: unknown identifier %s", $1);
            return 1;
        }
        if(identifier->type != DECLARATION_FUNCTION) {
            //symbol is not a variable
            fprintf(stderr,"PAR: identifier %s is not a function", $1);
            return 1;
        }
        fprintf(stderr, "PAR: Term of type function: %s\n", $1);
        $$ = make_binary_node(NODE_FUNCTION, (void*)get_symbol_entry($1), $3);
    }
;

%%