typedef struct node {
    int node_type;
    void* child1;
    void* child2;
    
} node;

void* make_leaf_node(int node_type);
void* make_unary_node(int node_type, void* child1);
void* make_binary_node(int node_type, void* child1, void* child2);
void* make_number_node(int number);