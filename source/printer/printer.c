#include <stdlib.h>
#include <stdio.h>

#include "printer.h"


void print_file(FILE* file) {

    node* root_node = get_root_node();
    entry* first_entry = get_first_entry();

    print_entries_in_file(file, first_entry);
    print_nodes_in_file(file, root_node);
}

void print_nodes_in_file(FILE* file, node* current_node) {
    
}

void print_entries_in_file(FILE *file, entry* current_entry) {
    if(current_entry == NULL) {
        fprintf(file, "\n");
        return;
    }

    switch (current_entry->type)
    {
        case DECLARATION_PREDICATE:
            fprintf(file, "DECLARE PREDICATE %s : %d\n", current_entry->identifier, current_entry->arity);
            break;
        case DECLARATION_FUNCTION:
            fprintf(file, "DECLARE FUNCTION %s : %d\n", current_entry->identifier, current_entry->arity);
            break;
        case DECLARATION_VARIABLE:
            fprintf(file, "DECLARE VARIABLE %s : %s\n", current_entry->identifier, current_entry->varType);
            break;
    }

    print_entries_in_file(file, current_entry->next);

}