// SYMBOL_TABLE
#define DECLARATION_PREDICATE 0
#define DECLARATION_FUNCTION 1
#define DECLARATION_VARIABLE 2

// SYNTAX_TREE
//0 children
#define NODE_TRUE 0
#define NODE_FALSE 3

//1 child
#define NODE_NEGATION 10    //child = node

#define NODE_VARIABLE 1     //child = symbol table entry
#define NODE_CONSTANT 31

#define NODE_NUMBER 7       //child = number

//2 children
#define NODE_CONJUNCTION 20 //child 1 = node, child 2 = node
#define NODE_DISJUNCTION 50
#define NODE_IMPLICATION 80
#define NODE_EQUIVALENT 110

#define NODE_ALL 26         //child 1 = symbol table entry, child 2 = node
#define NODE_EXIST 56        
#define NODE_PREDICATE 86 
#define NODE_FUNCTION 116    

#define NODE_ARGUMENT 23    //child 1 = symbol table entry

/* 
The defined number for each node_type is assigned according to a system. 
The C Program uses modulo operations to calculate number of children and type of children nodes

Node_Type % 3 = Number of Children
    0: 0 children
    1: 1 child
    2: 2 children
Node_Type % 5 = Type of Child 1
    0: Child 1 is another Node
    1: Child 1 is symbol table entry
    2: Child 1 is Number
    3: Child 1 is Argument of Argument List
    4: Not used
Node_Type % 2 = Type of Child 2
    0: Child 2 is another Node
    1: Child 2 is another Item in Argument list
*/