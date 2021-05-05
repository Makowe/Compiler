#include <stdio.h>
#include <stdlib.h>
#include "syntaxtree.h"
#include "../symboltable/symboltable.h"
#include "../additional/define.h"


void* make_leaf_node(int node_type) {
    node* new_node = (node*) malloc(sizeof(node));
    fprintf(stderr,"SXT: making leaf node of type %d\n", node_type);
    new_node->node_type = node_type;
    new_node->child1 = NULL;
    new_node->child2 = NULL;
    return (void*)new_node;
}

void* make_unary_node(int node_type, void* child1) {
    node* new_node = (node*) malloc(sizeof(node));
    fprintf(stderr,"SXT: making unary node of type %d\n", node_type);
    new_node->node_type = node_type;
    new_node->child1 = child1;
    new_node->child2 = NULL;
    return (void*)new_node;
}

void* make_binary_node(int node_type, void* child1, void* child2) {
    node* new_node = (node*) malloc(sizeof(node));
    fprintf(stderr,"SXT: making binary node of type %d\n", node_type);
    new_node->node_type = node_type;
    new_node->child1 = child1;
    new_node->child2 = child2;
    return (void*)new_node;
}

void* make_number_node(int number) {
    int* number_pointer = (int*) malloc(sizeof(int));
    *number_pointer = number;
    return make_unary_node(NODE_NUMBER, number_pointer);
}

void print_syntax_tree(void* root_node) {
    fprintf(stdout, "\n--- PRINT SYNTAX TREE ---\n\n");
    node* node_pointer = ((node*)root_node);
    print_node_and_children(node_pointer, 0, 1);
}

void print_single_node(node* node, int level, int print_dots) {
    if(node == NULL) { return; }
    
    for(int i = 0; i < level && print_dots == 1; i++) {
        fprintf(stdout, ". ");
    }
    switch(node->node_type) {
        //Only print Name of Node
        case NODE_TRUE: 
            fprintf(stdout, "TRUE\n"); 
            return;
        case NODE_FALSE: 
            fprintf(stdout, "FALSE\n"); 
            return;
        case NODE_NEGATION: 
            fprintf(stdout, "NOT\n"); 
            return;
        case NODE_CONJUNCTION: 
            fprintf(stdout, "AND\n"); 
            return;
        case NODE_DISJUNCTION: 
            fprintf(stdout, "OR\n"); 
            return;
        case NODE_IMPLICATION: 
            fprintf(stdout, "IMPLICATION\n"); 
            return;
        case NODE_EQUIVALENT: 
            fprintf(stdout, "EQUIVALENT\n"); 
            return;
        case NODE_VARIABLE: 
            fprintf(stdout, "VARIABLE: ");
            return;
        case NODE_CONSTANT: 
            fprintf(stdout, "CONSTANT: ");
            return;
        case NODE_NUMBER:          
            fprintf(stdout, "NUMBER: ");
            return;
        case NODE_ALL:
            fprintf(stdout, "ALL: "); 
            return;
        case NODE_EXIST:
            fprintf(stdout, "EXIST: "); 
            return;
        case NODE_PREDICATE:
            fprintf(stdout, "PREDICATE: ");
            return;
        case NODE_FUNCTION:
            fprintf(stdout, "FUNCTION: ");
            return;
        case NODE_ARGUMENT:
            // dont print anything. algorithm will autonatically print children
            return;
    }
}

void print_node_and_children(node* node_pointer, int level, int print_dots) {
    if(node_pointer == NULL) { return; }
    print_single_node(node_pointer, level, print_dots);

    //use modulo operations to calculate number and type of children
    // see ../additional/define.h for more information
    int num_children = node_pointer->node_type % 3;
    int child_type1 = node_pointer->node_type % 5;
    int child_type2 = node_pointer->node_type % 2;  

    if(num_children >= 1 ) {
        //print first child
        switch (child_type1) {
            case 0: {
                //print child1 recursive
                node* child1 = (node*)node_pointer->child1;
                print_node_and_children(child1, level+1, 1);
                break;
            }
            case 1: {
                //print symbol table entry
                entry* symbol = (entry*)node_pointer->child1;
                fprintf(stdout, "%s\n", symbol->identifier);
                break;
            }
            case 2: {
                //print value of number node
                int* number = (int*)node_pointer->child1;
                fprintf(stdout, "%d\n", *number);
                break;
            }
            case 3: {
                //print type and value of argument. Set level to 0 to prevent printing dots
                node* child1 = (node*)node_pointer->child1;
                print_node_and_children(child1, level, 0);
                break;
            }
        }
    }
    if(num_children >= 2) {
        switch (child_type2) {
            case 0: {
                //print child2 recursive
                node* child2 = (node*)node_pointer->child2;
                print_node_and_children(child2, level+1, 1);
                break;
            }
            case 1: {
                //print rest of argument list
                node* child2 = (node*)node_pointer->child2;
                print_node_and_children(child2, level, 1);
                break;
            }
        }
    }
}