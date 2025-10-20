#include <bits/stdc++.h>
using namespace std;

bool compare(const string &a, const string &b) {
    string a_prefix = a.substr(0, 2);
    string b_prefix = b.substr(0, 2);
    return a_prefix < b_prefix;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    int cont = 0;
    while (cin >> n && n != 0) {
        if (cont > 0) {
            cout << endl;
        }
        cont++;
        
        vector<string> names(n);
        for (int i = 0; i < n; i++) {
            cin >> names[i];
        }
        
        stable_sort(names.begin(), names.end(), compare);
        
        for (const string &nombre : names) {
            cout << nombre << endl;
        }
    }
    
    return 0;
}