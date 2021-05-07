#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "../syntaxtree/syntaxtree.h"

void optimize_tree();
node* optimize_sub_tree(node* current_node);
node* double_negation(node* parent_node);
node* bool_negation(node* parent_node);

#endif