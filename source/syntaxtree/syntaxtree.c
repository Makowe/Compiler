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
    print_node_and_children(node_pointer, 0);
}

void print_single_node(node* node, int level) {
    if(node == NULL) { return; }
    
    for(int i = 0; i < level; i++) {
        fprintf(stdout, ".");
    }
    switch(node->node_type) {
        //Only print Name of Node
        case NODE_TRUE: fprintf(stdout, "TRUE\n"); return;
        case NODE_FALSE: fprintf(stdout, "FALSE\n"); return;
        case NODE_NEGATION: fprintf(stdout, "NOT\n"); return;
        case NODE_CONJUNCTION: fprintf(stdout, "AND\n"); return;
        case NODE_DISJUNCTION: fprintf(stdout, "OR\n"); return;
        case NODE_IMPLICATION: fprintf(stdout, "IMPLICATION\n"); return;
        case NODE_EQUIVALENT: fprintf(stdout, "EQUIVALENT\n"); return;

        // more complex nodes
        case NODE_VARIABLE: {
            char* variable_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "VARIABLE: %s\n", variable_name);
            return;
        }

        case NODE_NUMBER: {            
            int* number = (int*)node->child1;
            fprintf(stdout, "NUMBER: %d\n", *number);
            return;
        }
        case NODE_ALL: {
            char* variable_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "ALL: %s\n", variable_name); 
            return;
        }
        case NODE_EXIST: {
            char* variable_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "EXIST: %s\n", variable_name); 
            return;
        }

        case NODE_PREDICATE: {
            char* predicate_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "PREDICATE: %s\n", predicate_name);
            return;
        }
        case NODE_FUNCTION: {
            char* function_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "FUNCTION: %s\n", function_name);
            return;
        }
        case NODE_ARGUMENT: {
            char* argument_name = ((entry*)node->child1)->identifier;
            fprintf(stdout, "ARGUMENT: %s\n", argument_name);
            return;
        }
    }
}

void print_node_and_children(node* node_pointer, int level) {
    if(node_pointer == NULL) { return; }
    print_single_node(node_pointer, level);

    //use modulo operations to calculate number and type of children
    // see ../additional/define.h for more information
    int num_children = node_pointer->node_type % 3;
    int children_types = node_pointer->node_type % 5;
    int auto_increment_level = node_pointer->node_type != NODE_ARGUMENT;

    if(num_children >= 1 ) {
        //print first child
        switch (children_types) {
            case 0:;
                node* child1 = (node*)node_pointer->child1;
                print_node_and_children(child1, level+1);
                break;
            default:
                //do nothing else, because first child is not a node
                break;
        }
    }
    if(num_children >= 2) {
        switch (children_types) {
            case 0: //fallthrough
            case 1: {
                //print right hand side tree
                node* child2 = (node*)node_pointer->child2;
                print_node_and_children(child2, level+1);
                break;
            }
            case 4: {
                //print right hand side tree but don't increase level
                node* child2 = (node*)node_pointer->child2;
                print_node_and_children(child2, level);
                break;
            }
        }
    }
}