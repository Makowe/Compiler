#include <stdio.h>
#include <stdlib.h>
#include "syntaxtree.h"
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