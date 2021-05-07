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

node* double_negation(node* current_node) {

    if(current_node == NULL) { return current_node; }
    if(current_node->node_type == NODE_NEGATION) {
        //check for child and grand child
        node* child = (node*)current_node->child1;
        if(child->node_type == NODE_NEGATION) {
            node* grand_child = (node*)child->child1;
            free(current_node);
            free(child);
            fprintf(stderr, "OPT: removed double negation");
            return grand_child;
        }
    }
    return current_node;
}

