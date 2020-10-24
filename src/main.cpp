#include "foo.h"

int main()
{
    info* INF = init();
    enter_words(INF);
    char ans[100];
    int ans2;
    info_out();
    while (1) {
        cout << "> ";
        cin >> ans;
        std::string answer(ans);
        if (answer == "Q") {
            cout << "Thank you for your attention!\nGood luck!" << endl;
            return 0;
        } else if (answer == "L") {
            cout << "List of words:\n";
            trie_print(INF, INF->root, 0);
        } else if (trie_lookup(INF, INF->root, ans)) {
            cout << trie_lookup(INF, INF->root, ans)->value << endl;
        } else if (answer == "D") {
            cout << "Enter word for erase:\n> ";
            cin >> ans;
            trie_delete(INF, INF->root, ans);
        } else if (answer == "A") {
            cout << "Enter word:\n> ";
            cin >> ans;
            correct(ans);
            cout << "Enter key:\n> ";
            cin >> ans2;
            trie_insert(INF, ans, ans2);
        }
    }
}