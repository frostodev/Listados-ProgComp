#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, B;
    cin >> N >> B;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    int pos = -1;
    for (int i = 0; i < N; i++) {
        if (A[i] == B) pos = i;
    }

    // transformar en -1 / 0 / +1
    for (int i = 0; i < N; i++) {
        if (A[i] < B) A[i] = -1;
        else if (A[i] > B) A[i] = 1;
        else A[i] = 0;
    }

    // balance prefix a la izquierda de pos
    unordered_map<int,int> left_count;
    int balance = 0;
    left_count[0] = 1; // subsecuencia que empieza justo en B
    for (int i = pos - 1; i >= 0; i--) {
        balance += A[i];
        left_count[balance]++;
    }

    // ahora hacia la derecha, combinando
    long long result = 0;
    balance = 0;
    for (int i = pos; i < N; i++) {
        balance += A[i];
        // queremos que leftBalance + rightBalance = 0
        int need = -balance;
        if (left_count.count(need)) {
            result += left_count[need];
        }
    }

    cout << result << "\n";
    return 0;
}
