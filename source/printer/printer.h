#ifndef PRINTER_H
#define PRINTER_H

#include "../syntaxtree/syntaxtree.h"
#include "../symboltable/symboltable.h"
#include "../additional/define.h"

void print_file(FILE* file);
void print_nodes_in_file(FILE* file, node* current_node);
void print_entries_in_file(FILE *file, entry* current_entry);

#endif