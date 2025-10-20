#include <bits/stdc++.h>
using namespace std;

// Sparse Table para RMQ (min)
struct SparseTable {
    int n, K;
    vector<vector<int>> st;
    vector<int> log2v;

    SparseTable(const vector<int>& arr) {
        n = arr.size();
        K = __lg(n) + 1;
        st.assign(K, vector<int>(n));
        st[0] = arr;
        for (int k = 1; k < K; k++) {
            for (int i = 0; i + (1 << k) <= n; i++) {
                st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
            }
        }
        log2v.assign(n+1,0);
        for (int i = 2; i <= n; i++) log2v[i] = log2v[i/2] + 1;
    }

    int query(int l, int r) { // [l,r]
        if (l > r) return INT_MAX;
        int k = log2v[r-l+1];
        return min(st[k][l], st[k][r-(1<<k)+1]);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> H(N);
    for (int i=0;i<N;i++) cin >> H[i];

    if (N < 2) {
        cout << 0 << "\n";
        return 0;
    }

    // preprocesar RMQ
    SparseTable rmq(H);

    // el siguiente mayor o igual (NGE) a la izquierda/derecha
    vector<int> left(N,-1), right(N,-1);
    stack<int> st;

    // el siguiente mayor a la izquierda
    for (int i=0;i<N;i++) {
        while (!st.empty() && H[st.top()] < H[i]) st.pop();
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }

    while(!st.empty()) st.pop();

    // el siguiente mayor a la derecha
    for (int i=N-1;i>=0;i--) {
        while (!st.empty() && H[st.top()] < H[i]) st.pop();
        if (!st.empty()) right[i] = st.top();
        st.push(i);
    }

    long long ans = 0;
    for (int i=0;i<N;i++) {
        if (left[i] != -1) {
            int l = left[i], r = i;
            int min_between = rmq.query(l+1, r-1);
            long long jump = min(H[l], H[r]) - min_between;
            ans = max(ans, jump);
        }
        if (right[i] != -1) {
            int l = i, r = right[i];
            int min_between = rmq.query(l+1, r-1);
            long long jump = min(H[l], H[r]) - min_between;
            ans = max(ans, jump);
        }
    }

    cout << ans << "\n";
}
