#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> words;
    string w;
    while (cin >> w) {
        words.push_back(w);
    }

    unordered_set<string> compounds;
    compounds.reserve(words.size() * words.size()); // reduce rehashes

    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = 0; j < words.size(); j++) {
            if (i == j) continue;
            compounds.insert(words[i] + words[j]);
        }
    }

    vector<string> result(compounds.begin(), compounds.end());
    sort(result.begin(), result.end());

    for (auto &s : result) {
        cout << s << "\n";
    }
    return 0;
}
