#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Y;
    cin >> N >> Y;

    set<int> found; // set para evitar duplicados
    for (int i = 0; i < Y; i++) {
        int k;
        cin >> k;
        found.insert(k);
    }

    // imprimir los obstáculos que faltan
    for (int i = 0; i < N; i++) {
        if (found.find(i) == found.end()) {
            cout << i << "\n";
        }
    }

    cout << "Mario got " << found.size() << " of the dangerous obstacles.\n";

    return 0;
}
