typedef struct entry
{
    int type;
    int arity;
    char* identifier;
    char* varType;
    struct entry* next;
} entry;

int identifier_exists(char *identifier);
int add_entry(int type, int arity, char* identifier, char* varType);
struct entry* get_symbol_entry(char* identifier);
void print_entries();