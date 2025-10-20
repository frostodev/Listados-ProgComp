#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    cin.ignore(); // quitar salto

    while (T--) {
        string s;
        getline(cin, s);

        list<char> text;
        list<char>::iterator cursor = text.begin();

        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '<') {
                if (cursor != text.begin()) {
                    cursor--;
                    cursor = text.erase(cursor);
                }
            } else if (c == '[') {
                cursor = text.begin();
            } else if (c == ']') {
                cursor = text.end();
            } else {
                text.insert(cursor, c);
            }
        }

        // imprimir resultado
        for (list<char>::iterator it = text.begin(); it != text.end(); ++it)
            cout << *it;
        cout << "\n";
    }

    return 0;
}
