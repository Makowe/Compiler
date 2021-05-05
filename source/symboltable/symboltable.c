#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "../additional/define.h"

entry* firstEntry = NULL;
entry* lastEntry = NULL;

int identifier_exists(char *identifier) {
    entry* current = firstEntry;
    while(current != NULL) {
        if(!strcmp(current->identifier,identifier)) {
            fprintf(stdout, "SYM: Identifier %s altready exists", identifier);
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int add_entry(int type, int arity, char* identifier, char* varType) {
    entry* newEntry = (entry*) malloc(sizeof(entry));
    
    //copy all values into the new struct
    newEntry->type = type;
    newEntry->arity = arity;
    newEntry->next = NULL;

    // copy predicate string of identifier in new allocated space
    char* identifier_string = (char*) malloc(strlen(identifier)+1);
    strcpy(identifier_string, identifier);
    newEntry->identifier = identifier_string;

    //if varname exists, copy string in new allocated space
    if(varType != NULL) {
        char* varType_string = (char*) malloc(strlen(varType)+1);
        strcpy(varType_string, varType);
        newEntry->varType = varType_string;
    }
    else {
        newEntry->varType = NULL;
    }
    if(firstEntry == NULL) {
        firstEntry = newEntry;
        lastEntry = newEntry;
    }
    else {
        if(!identifier_exists(identifier)) {
            lastEntry->next = newEntry;
            lastEntry = newEntry;
        }
        else {
            return 1;
        }
    }
    fprintf(stdout, "SYM: New Entry: %s: %d, type: %d, varType: %s\n", identifier, arity, type, varType);
    return 0;
}

struct entry* get_symbol_entry(char* identifier) {
    entry* current = firstEntry;
    while(current != NULL) {
        if(!strcmp(current->identifier, identifier)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_entries() {

    fprintf(stdout,"\n--- PRINT ALL SYMBOLS ---\n\n");
    entry* current = firstEntry;
    
    while(current != NULL) {
        switch (current->type)
        {
        case DECLARATION_PREDICATE:
            fprintf(stdout, "SYM: Predicate %s with Arity %d\n",current->identifier,current->arity);
            break;
        case DECLARATION_FUNCTION:
            fprintf(stdout, "SYM: Function %s with Arity %d\n",current->identifier,current->arity);
            break;
        case DECLARATION_VARIABLE:
            fprintf(stdout, "SYM: Variable %s with VarType %s\n",current->identifier,current->varType);
            break;
        default:
            fprintf(stderr, "SYM: Wrong Declaration Type\n");
        }
        current = current->next;
    }
}