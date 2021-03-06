#ifndef SYNTAXTREE
#define SYNTAXTREE

typedef struct node {
    int node_type;
    void* child1;
    void* child2;
    
} node;

void* make_leaf_node(int node_type);
void* make_unary_node(int node_type, void* child1);
void* make_binary_node(int node_type, void* child1, void* child2);
void* make_number_node(int number);
void set_root_node(void* node_pointer);
node* get_root_node(void);

void print_syntax_tree();
void print_single_node(node* node, int level, int print_dots);
void print_node_and_children(node* node_pointer, int level, int print_dots);

#endif //SYNTAXTREE