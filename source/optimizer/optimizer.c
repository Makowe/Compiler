#include "optimizer.h"
#include "../syntaxtree/syntaxtree.h"
#include "../additional/define.h"
#include <stdlib.h>
#include <stdio.h>


void optimize_tree() {
    node* root_node = get_root_node();
    node* new_root_node = optimize_sub_tree(root_node);
    set_root_node(new_root_node);
}

node* optimize_sub_tree(node* current_node) {
    if(current_node == NULL) { return current_node; }

    //OPTIMIZATION THE CURRENT NODE

    current_node = double_negation(current_node);
    current_node = bool_negation(current_node);


    // OPTIMIZE CHILDREN NODES RECURSIVE 
    int num_children = current_node->node_type % 3;
    
    //node has child and child1 is another node
    if(num_children >= 1 && current_node->node_type % 5 == 0) {
        current_node->child1 = optimize_sub_tree((node*)current_node->child1);
    }

    if(num_children >= 2) {
        current_node->child2 = optimize_sub_tree((node*)current_node->child2);
    }
    return current_node;
}

node* double_negation(node* parent_node) {

    if(parent_node == NULL) { return parent_node; }
    if(parent_node->node_type == NODE_NEGATION) {

        node* child = (node*)parent_node->child1;
        if(child->node_type == NODE_NEGATION) {
            node* grand_child = (node*)child->child1;
            free(parent_node);
            free(child);
            fprintf(stderr, "OPT: removed double negation\n");
            return grand_child;
        }
    }
    // no double negation -> return self
    return parent_node;
}

node* bool_negation(node* parent_node) {
    if(parent_node == NULL) { return parent_node; }
    if(parent_node->node_type == NODE_NEGATION) {

        node* child = (node*)parent_node->child1;
        if(child->node_type == NODE_TRUE) {
            free(parent_node);
            free(child);
            node* new_node = make_leaf_node(NODE_FALSE);
            fprintf(stderr, "OPT: ~TRUE -> FALSE \n");
            return new_node;
        }
        if(child->node_type == NODE_FALSE) {
            free(parent_node);
            free(child);
            node* new_node = make_leaf_node(NODE_TRUE);
            fprintf(stderr, "OPT: ~FALSE -> TRUE \n");
            return new_node;
        }
    }
    // no double negation -> return self
    return parent_node;
}