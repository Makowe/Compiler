#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "../syntaxtree/syntaxtree.h"

void optimize_tree();
node* double_negation(node* current_node);
node* optimize_sub_tree(node* current_node);

#endif