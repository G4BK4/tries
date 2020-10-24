#ifndef FOO_PREF
#define FOO_PREF

#include "node.h"
#include <vector>
#define d 27

using std::vector;

typedef struct trie {
    char key;
    int value;
    int child_n;
    tree* rb_child;
} trie;

typedef struct info {
    char alphabet[d];
    struct trie* root;
    int node_n;
} info;

void enter_words(info* INF);
int correct(char* out);
void info_out();

info* init();
trie* trie_create();
trie* trie_insert(info* INF, char* key, int value);
trie* trie_lookup(info* INF, trie* root, char* key);
trie* trie_delete(info* INF, trie* root, char* key);
void trie_print(info* INF, trie* root, unsigned int level);

#endif