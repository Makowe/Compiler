#include <stdlib.h>
#include <stdio.h>

#include "printer.h"
#include "../additional/define.h"


void print_file(FILE* file) {


    node* root_node = get_root_node();
    entry* first_entry = get_first_entry();

    print_entries_in_file(file, first_entry);

    print_nodes_in_file(file, root_node, 0);
    fprintf(file, ";");
}

void print_nodes_in_file(FILE* file, node* current_node, int precedence) {

    if(current_node == NULL) { return; }

    switch(current_node->node_type) {
        case NODE_TRUE:
            fprintf(file, " TRUE ");
            break;
        case NODE_FALSE:
            fprintf(file, " FALSE ");
            break;
        case NODE_VARIABLE:
        case NODE_CONSTANT:
            fprintf(stderr, "%s", ((entry*)current_node->child1)->identifier);
            fprintf(file, "%s", ((entry*)current_node->child1)->identifier);
            break;
        case NODE_NUMBER:
            fprintf(file, " %d ", *(int*)current_node->child1);
            break;
        case NODE_NEGATION:
            fprintf(stderr,"negation ");
            if(PRECEDENCE_NEGATION < precedence) fprintf(file, "(");
            fprintf(file, "~");
            print_nodes_in_file(file, (node*)current_node->child1, PRECEDENCE_NEGATION);
            if(PRECEDENCE_NEGATION < precedence) fprintf(file,")");
            break;
        case NODE_CONJUNCTION:
            if(PRECEDENCE_CONJUNCTION < precedence) fprintf(file,"(");
            print_nodes_in_file(file, (node*)current_node->child1, PRECEDENCE_CONJUNCTION);
            fprintf(file, " & ");
            print_nodes_in_file(file, (node*)current_node->child2, PRECEDENCE_CONJUNCTION);
            if(PRECEDENCE_CONJUNCTION < precedence) fprintf(file,")");
            break;
        case NODE_DISJUNCTION:
            if(PRECEDENCE_DISJUNCTION < precedence) fprintf(file,"(");
            print_nodes_in_file(file, (node*)current_node->child1, PRECEDENCE_DISJUNCTION);
            fprintf(file, " | ");
            print_nodes_in_file(file, (node*)current_node->child2, PRECEDENCE_DISJUNCTION);
            if(PRECEDENCE_DISJUNCTION < precedence) fprintf(file,")");
            break;
        case NODE_IMPLICATION:
            if(PRECEDENCE_IMPLICATION < precedence) fprintf(file,"(");
            print_nodes_in_file(file, (node*)current_node->child1, PRECEDENCE_IMPLICATION);
            fprintf(file, " -> ");
            print_nodes_in_file(file, (node*)current_node->child2, PRECEDENCE_IMPLICATION);
            if(PRECEDENCE_IMPLICATION < precedence) fprintf(file,")");
            break;
        case NODE_EQUIVALENT:
            if(PRECEDENCE_IMPLICATION < precedence) fprintf(file,"(");
            print_nodes_in_file(file, (node*)current_node->child1, PRECENDECE_EQUIVALENT);
            fprintf(file, " <-> ");
            print_nodes_in_file(file, (node*)current_node->child2, PRECENDECE_EQUIVALENT);
            if(PRECEDENCE_IMPLICATION < precedence) fprintf(file,")");
            break;
        case NODE_ALL:
            if(PRECEDENCE_QUANTOR < precedence) fprintf(file,"(");
            fprintf(file, "ALL[");
            fprintf(file, "%s", ((entry*)current_node->child1)->identifier);
            fprintf(file, "]");
            print_nodes_in_file(file, (node*)current_node->child2, PRECEDENCE_QUANTOR);
            if(PRECEDENCE_QUANTOR < precedence) fprintf(file,")");
            break;
        case NODE_EXIST:
            if(PRECEDENCE_QUANTOR < precedence) fprintf(file,"(");
            fprintf(file, "EXIST[");
            fprintf(file, "%s", ((entry*)current_node->child1)->identifier);
            fprintf(file, "]");
            print_nodes_in_file(file, (node*)current_node->child2, PRECEDENCE_QUANTOR);
            if(PRECEDENCE_QUANTOR < precedence) fprintf(file,")");
            break;
        case NODE_ARGUMENT:
            print_nodes_in_file(file, (node*)current_node->child1, 0);
            if((node*)current_node->child2 != NULL) fprintf(file, ",");
            if((node*)current_node->child2 != NULL) fprintf(stderr, ",");
            print_nodes_in_file(file, (node*)current_node->child2, 0);
            break;
        case NODE_FUNCTION:
            fprintf(file, "%s(", ((entry*)current_node->child1)->identifier);
            print_nodes_in_file(file, (node*)current_node->child2, 0);
            fprintf(file, ")");
            break;
        case NODE_PREDICATE:
            fprintf(file, "%s(", ((entry*)current_node->child1)->identifier);
            print_nodes_in_file(file, (node*)current_node->child2, 0);
            fprintf(file, ")");
            break;
    }
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
