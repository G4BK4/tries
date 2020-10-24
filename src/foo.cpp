#include "foo.h"

void space(unsigned int a, unsigned int b)
{
    for (unsigned int i = 0; i < a - b; i++) {
        cout << " ";
    }
}
void info_out()
{
    std::string first("Enter word for search");
    std::string second("Enter 'Q' if you wanna go away");
    std::string third("Enter 'A' if you wanna add word");
    std::string fourth("Enter 'D' if you wanna delete word");
    std::string fiveth("Enter 'L' if you wanna see all words in trie");

    cout << "+";
    for (unsigned int i = 0; i < fiveth.length() + 2; i++) {
        cout << "-";
    }
    cout << "+" << endl;
    cout << "| " + first, space(fiveth.length(), first.length());
    cout << " |\n| " + second, space(fiveth.length(), second.length());
    cout << " |\n| " + third, space(fiveth.length(), third.length());
    cout << " |\n| " + fourth, space(fiveth.length(), fourth.length());
    cout << " |\n| " + fiveth + " |" << endl;
    cout << "+";
    for (unsigned int i = 0; i < fiveth.length() + 2; i++) {
        cout << "-";
    }
    cout << "+" << endl;
}
info* init()
{
    info* temp = new info;
    if (temp) {
        temp->node_n = 1;
        for (int i = 0; i < d - 1; i++) {
            temp->alphabet[i] = 'a' + i;
        }
        temp->alphabet[d - 1] = '\0';
        temp->root = trie_create();
        if (temp->root == NULL) {
            return NULL;
        } else {
            return temp;
        }
    } else {
        return NULL;
    }
}
trie* trie_create()
{
    trie* node = new trie;
    if (node == NULL) {
        return NULL;
    } else {
        node->child_n = 0;
        node->value = -1;
        node->key = '\0';
        node->rb_child = tree_init();
        return node;
    }
}
int correct(char* out)
{
    for (int i = 0; out[i] != '\0'; i++) {
        if (isupper(out[i]) != 0) {
            out[i] += 32;
        }
        if (isdigit(out[i]) != 0) {
            return 0;
        }
        if (isspace(out[i]) != 0) {
            for (int j = i; j < 100; j++) {
                out[i] = '\0';
            }
            return 1;
        }
    }
    return 1;
}
void enter_words(info* INF)
{
    char out[100];
    int key, count = 0;
    while (1) {
        if (count == 10) {
            break;
        }
        cout << "Enter word:\n> ";
        cin >> out;
        if (out[0] == 'q' && out[1] == '\0') {
            break;
        } else {
            correct(out);
            cout << "Enter key:\n> ";
            cin >> key;
            trie_insert(INF, out, key);
            count++;
        }
    }
}
trie* get_child(info* INF, trie* trnode, char a)
{
    int find = a - 'a' + 1;
    if (a == '\0') {
        find = 27;
    }
    node* ptr = RBT_lookup(trnode->rb_child, find);
    if (ptr != NULL) {
        return (trie*)ptr->value;
    } else {
        return NULL;
    }
}
trie* set_child(info* INF, trie* trnode, char a)
{
    trie* temp = trie_create();
    if (temp) {
        temp->key = a;
        temp->value = -1;
        int find = a - 'a' + 1;
        if (a == '\0') {
            find = 27;
        }
        trnode->child_n++;
        if (trnode->rb_child->root == NULL) {
            trnode->rb_child->root = RBT_create(trnode->rb_child, find, temp);
        } else {
            RBT_add(trnode->rb_child, find, temp);
        }
        return temp;
    }
    return NULL;
}
trie* trie_insert(info* INF, char* key, int value)
{
    if (INF) {
        if (INF->root) {
            trie* trnode = INF->root;
            trie* child = NULL;
            std::string skey(key);
            for (unsigned int i = 0; i < skey.length(); i++) {
                child = get_child(INF, trnode, skey[i]);
                if (child == NULL) {
                    child = set_child(INF, trnode, skey[i]);
                }
                trnode = child;
                if (i + 1 == skey.length()) {
                    child = get_child(INF, trnode, '\0');
                    if (child == NULL) {
                        child = set_child(INF, trnode, '\0');
                    }
                    trnode = child;
                }
            }
            trnode->value = value;
            return trnode;
        }
    }
    return NULL;
}
trie* trie_lookup(info* INF, trie* root, char* key)
{
    if (INF) {
        if (root) {
            trie* child = NULL;
            std::string skey(key);
            for (unsigned int i = 0; i < skey.length() + 1; i++) {
                child = get_child(INF, root, key[i]);
                if (child == NULL) {
                    return NULL;
                }
                root = child;
            }
            if (root->value == -1) {
                return NULL;
            }
            return root;
        }
    }
    return NULL;
}
trie* get_parent(info* INF, trie* root, char* key)
{
    trie* child = NULL;
    trie* save = NULL;
    trie* ptr = INF->root;
    std::string skey(key);
    for (unsigned int i = 0; i < skey.length() + 1; i++) {
        save = child;
        child = get_child(INF, ptr, key[i]);
        if (child == root) {
            return save;
        }
        ptr = child;
    }
    return NULL;
}
trie* trie_delete(info* INF, trie* root, char* key)
{
    if (INF) {
        if (root) {
            trie* ptr = trie_lookup(INF, root, key);
            if (ptr != NULL) {
                trie* parent = get_parent(INF, ptr, key);
                while (1) {
                    if (ptr->child_n == 0) {
                        if (ptr->key == '\0') {
                            RBT_delete(parent->rb_child, 27);
                        } else {
                            RBT_delete(parent->rb_child, ptr->key - 'a');
                        }
                        delete ptr;
                        ptr = parent;
                        parent = get_parent(INF, ptr, key);
                    } else {
                        RBT_delete(parent->rb_child, ptr->key);
                        break;
                    }
                }
                return parent;
            }
        }
    }
    return NULL;
}
void max_height(info* INF, trie* ptr, unsigned int level, std::string str)
{
    trie* child;
    for (int i = 0; i < d; i++) {
        child = get_child(INF, ptr, INF->alphabet[i]);
        if (child) {
            if (child->value != -1 && level <= (str.length() + 1)) {
                cout << (str + child->key) << "  " << child->value << endl;
            }
            max_height(INF, child, level, (str + child->key));
        }
    }
}
void trie_print(info* INF, trie* root, unsigned int level)
{
    max_height(INF, root, level, "");
}