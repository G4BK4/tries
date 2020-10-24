#ifndef FOO
#define FOO

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef struct node {
    node *parent, *left, *right;
    string color;
    void* value;
    int key;
} node;

typedef struct Tree {
    node* root;
    node* NILL;
    int count;
} tree;

node* RBT_create(tree* T, int key, void* value);
node* RBT_find_root(tree* T);
tree* tree_init();

node* RBT_add(tree* T, int key, void* value);
node* RBT_lookup(tree* T, int key);
node* RBT_delete(tree* T, int key);
node* RBT_min(tree* T, node* ptr);
node* RBT_max(tree* T, node* ptr);
void RBT_free(tree* T);
void RBT_print_dfs(tree* T, int level);

#endif