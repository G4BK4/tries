#include "foo.h"

tree* tree_init()
{
    tree* temp = new tree;
    if (temp) {
        temp->NILL = new node;
        temp->NILL->parent = temp->NILL->left = temp->NILL->right = NULL;
        temp->NILL->color = "BLACK";
        temp->NILL->key = 0;
        temp->NILL->value = NULL;
        temp->count = 0;
        temp->root = NULL;
        return temp;
    } else {
        return NULL;
    }
}

node* RBT_min(tree* T, node* ptr)
{
    while (ptr != NULL && ptr->left != T->NILL) {
        ptr = ptr->left;
    }
    return ptr;
}

node* RBT_max(tree* T, node* ptr)
{
    while (ptr != NULL && ptr->right != T->NILL) {
        ptr = ptr->right;
    }
    return ptr;
}

node* RBT_create(tree* T, int key, void* value)
{
    node* temp = new node;
    if (temp) {
        temp->parent = temp->left = temp->right = T->NILL;
        temp->color = "BLACK";
        temp->value = value;
        temp->key = key;
        T->count += 1;
        return temp;
    } else {
        return NULL;
    }
}
void rotate_left(tree* T, node* temp)
{
    node* ptr = temp->right;
    temp->right = ptr->left;
    if (ptr->left != NULL) {
        ptr->left->parent = temp;
    }
    ptr->parent = temp->parent;
    if (temp == temp->parent->left) {
        temp->parent->left = ptr;
    } else {
        temp->parent->right = ptr;
    }
    ptr->left = temp;
    temp->parent = ptr;
    return;
}
void rotate_right(tree* T, node* temp)
{
    node* ptr = temp->left;
    temp->left = ptr->right;
    if (ptr->right != NULL) {
        ptr->right->parent = temp;
    }
    ptr->parent = temp->parent;
    if (temp == temp->parent->right) {
        temp->parent->right = ptr;
    } else {
        temp->parent->left = ptr;
    }
    ptr->right = temp;
    temp->parent = ptr;
    return;
}
void fixup(tree* T, node* temp)
{
    node* uncle;
    while (temp->parent->color == "RED") {
        if (temp->parent == temp->parent->parent->left) {
            uncle = temp->parent->parent->right;
            if (uncle->color == "RED") {
                temp->parent->color = "BLACK";
                uncle->color = "BLACK";
                temp->parent->parent->color = "RED";
                temp = temp->parent->parent;
            } else {
                if (temp == temp->parent->right) {
                    temp = temp->parent;
                    rotate_left(T, temp);
                }
                temp->parent->color = "BLACK";
                temp->parent->parent->color = "RED";
                rotate_right(T, temp->parent->parent);
            }
        } else {
            uncle = temp->parent->parent->left;
            if (uncle->color == "RED") {
                temp->parent->color = "BLACK";
                uncle->color = "BLACK";
                temp->parent->parent->color = "RED";
                temp = temp->parent->parent;
            } else {
                if (temp == temp->parent->left) {
                    temp = temp->parent;
                    rotate_right(T, temp);
                }
                temp->parent->color = "BLACK";
                temp->parent->parent->color = "RED";
                rotate_left(T, temp->parent->parent);
            }
        }
    }
    T->root = RBT_find_root(T);
    T->root->color = "BLACK";
    return;
}

void print_level(tree* T, node* root, int level)
{
    if (root == T->NILL) {
        return;
    }
    if (level == 0) {
        if (root->parent != T->NILL) {
            cout << root->color << " " << root->key << " (" << root->parent->key << ") ";
        } else {
            cout << root->color << " " << root->key << " (0) ";
        }
    } else {
        print_level(T, root->left, level - 1);
        print_level(T, root->right, level - 1);
    }
}

int MAX(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int max_height(tree* T, node* ptr)
{
    if (ptr == T->NILL) {
        return 0;
    } else {
        return 1 + MAX(max_height(T, ptr->left), max_height(T, ptr->right));
    }
}

void RBT_print_dfs(tree* T, int level)
{
    int height = max_height(T, T->root);
    for (int i = level - 1; i < height; i++) {
        print_level(T, T->root, i);
        cout << endl;
    }
}
node* RBT_add(tree* T, int key, void* value)
{
    node* ptr = T->root;
    node* father = NULL;
    while (ptr != T->NILL) {
        father = ptr;
        if (key < ptr->key) {
            ptr = ptr->left;
        } else if (key > ptr->key) {
            ptr = ptr->right;
        } else {
            return NULL;
        }
    }
    node* temp = RBT_create(T, key, value);
    if (temp) {
        temp->parent = father;
        if (father->key > temp->key) {
            father->left = temp;
        } else if (father->key < temp->key) {
            father->right = temp;
        } else {
            return NULL;
        }
        temp->color = "RED";
        fixup(T, temp);
        return temp;
    } else {
        return NULL;
    }
}

node* RBT_find_root(tree* T)
{
    if (T->root->parent == T->NILL) {
        return T->root;
    } else {
        while (T->root->parent != T->NILL) {
            T->root = T->root->parent;
        }
        if (T->root->parent == T->NILL) {
            return T->root;
        } else {
            return T->NILL;
        }
    }
}

node* RBT_lookup(tree* T, int key)
{
    node* ptr = T->root;
    if (T->root) {
        while (ptr != T->NILL) {
            if (ptr->key < key) {
                ptr = ptr->right;
            } else if (ptr->key > key) {
                ptr = ptr->left;
            } else {
                return ptr;
            }
        }
        // cout << "ERROR: Item not found" << endl;
        return NULL;
    } else {
        // cout << "Root is NULL" << endl;
        return NULL;
    }
}

void node_free(tree* T, node* ptr)
{
    if (ptr != NULL) {
        if (ptr != T->NILL) {
            node_free(T, ptr->left);
            node_free(T, ptr->right);
            delete ptr;
        }
    }
}

void RBT_free(tree* T)
{
    if (T != NULL) {
        node_free(T, T->root);
        delete T->NILL;
        delete T;
    }
}

void fixup_del(tree* T, node* x)
{
    int stat = 0;
    while (x != T->root && x->color == "BLACK") {
        if (x == x->parent->left) {
            node* w = x->parent->right;
            if (w->color == "RED") {
                w->color = "BLACK";
                x->parent->color = "RED";
                rotate_left(T, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == "BLACK" && w->right->color == "BLACK") {
                w->color = "RED";
                x = x->parent;
                stat = 1;
            } else if (w->right->color == "BLACK") {
                w->left->color = "BLACK";
                w->color = "RED";
                rotate_right(T, w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = "BLACK";
            w->right->color = "BLACK";
            if (stat) {
                rotate_left(T, x);
                stat = 0;
            } else {
                rotate_left(T, x->parent);
            }
            x = T->root;
        } else {
            node* w = x->parent->left;
            if (w->color == "RED") {
                w->color = "BLACK";
                x->parent->color = "RED";
                rotate_right(T, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == "BLACK" && w->left->color == "BLACK") {
                w->color = "RED";
                x = x->parent;
                stat = 1;
            } else if (w->left->color == "BLACK") {
                w->right->color = "BLACK";
                w->color = "RED";
                rotate_left(T, w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = "BLACK";
            w->left->color = "BLACK";
            if (stat) {
                rotate_right(T, x);
                stat = 0;
            } else {
                rotate_right(T, x->parent);
            }
            x = T->root;
        }
    }
    x->color = "BLACK";
}

void RBT_transplant(tree* T, node* bg, node* ptr)
{
    if (bg->parent == T->NILL) {
        T->root = ptr;
    } else if (bg == bg->parent->left) {
        bg->parent->left = ptr;
    } else {
        bg->parent->right = ptr;
    }
    ptr->parent = bg->parent;
}

node* RBT_delete(tree* T, int key)
{
    node* bad_guy = RBT_lookup(T, key);
    if (bad_guy == NULL) {
        return NULL;
    } else {
        node *save = bad_guy, *child = NULL;
        string orig_color = bad_guy->color;
        if (bad_guy->left == T->NILL) {
            child = bad_guy->right;
            RBT_transplant(T, bad_guy, bad_guy->right);
        } else if (bad_guy->right == T->NILL) {
            child = bad_guy->left;
            RBT_transplant(T, bad_guy, bad_guy->left);
        } else {
            save = RBT_min(T, bad_guy->right);
            orig_color = save->color;
            child = save->right;
            if (save->parent == bad_guy) {
                if (child) {
                    child->parent = save;
                }
            } else {
                RBT_transplant(T, save, save->right);
                save->right = bad_guy->right;
                save->right->parent = save;
            }
            RBT_transplant(T, bad_guy, save);
            save->left = bad_guy->left;
            save->left->parent = save;
            save->color = bad_guy->color;
            delete bad_guy;
        }
        if (orig_color == "BLACK") {
            fixup_del(T, child);
        }
        return child;
    }
}
