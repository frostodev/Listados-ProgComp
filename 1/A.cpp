#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> moves; // pila de movimientos
    for (int i = 0; i < k; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "undo") {
            int m;
            cin >> m;
            while (m-- && !moves.empty()) {
                moves.pop_back();
            }
        } else {
            // cmd es un número (positivo o negativo)
            int p = stoi(cmd);
            moves.push_back(p);
        }
    }

    long long pos = 0;
    for (size_t i = 0; i < moves.size(); i++) {
        pos += moves[i];
    }

    // ajustar dentro de [0, n-1]
    pos %= n;
    if (pos < 0) pos += n;

    cout << pos << "\n";
    return 0;
}
