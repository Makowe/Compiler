typedef struct node {
    int node_type;
    void* child1;
    void* child2;
    
} node;

void* make_leaf_node(int node_type);
void* make_unary_node(int node_type, void* child1);
void* make_binary_node(int node_type, void* child1, void* child2);
void* make_number_node(int number);
void print_syntax_tree();
void print_single_node(node* node, int level);
void print_node_and_children(node* node_pointer, int level);