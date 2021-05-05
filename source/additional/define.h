// SYMBOL_TABLE
#define DECLARATION_PREDICATE 0
#define DECLARATION_FUNCTION 1
#define DECLARATION_VARIABLE 2

// SYNTAX_TREE
//0 children
#define NODE_TRUE 0
#define NODE_FALSE 3

//1 child
#define NODE_NEGATION 10 //child = node
#define NODE_VARIABLE 1 //child = symbol table entry
#define NODE_NUMBER 7   //child = number

//2 children
#define NODE_CONJUNCTION 5  //child 1 = node, child 2 = node
#define NODE_DISJUNCTION 20
#define NODE_IMPLICATION 35
#define NODE_EQUIVALENT 50
#define NODE_ALL 11          //child 1 = symbol table entry, child 2 = node
#define NODE_EXIST 26        
#define NODE_PREDICATE 41 
#define NODE_FUNCTION 56    
#define NODE_ARGUMENT 13

/* 
The number for each node type is assigned according to a system. 
The C Program uses modulo operations to calculate number of children and type of children nodes
Node Type % 3 = Number of children
    Node_Type % 3 == 0 -> 0 children
    Node_Type % 3 == 1 -> 1 children
    Node_Type % 3 == 2 -> 2 children
Node Type % 5 = Types of the children
    Node_Type % 5 == 0 -> all children are nodes
    Node_Type % 5 == 1 -> first child is symbol table entry, second child is node
    Node_Type % 5 == 2 -> first child is number second child does not exists
    Node_Type % 5 == 3 -> first child is simbol table entry, second child is rest of argument list 
*/
