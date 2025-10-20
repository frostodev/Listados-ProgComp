#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<string> colors(N);
        for (auto &c : colors) cin >> c;

        int M;
        cin >> M;

        // mapear los colores a índices
        unordered_map<string, int> id;
        for (int i = 0; i < N; i++) id[colors[i]] = i;

        vector<vector<bool>> bad(N, vector<bool>(N, false));
        for (int i = 0; i < M; i++) {
            string a, b;
            cin >> a >> b;
            int u = id[a], v = id[b];
            bad[u][v] = bad[v][u] = true;
        }

        // DP para contar todas las pinturas válidas
        vector<vector<long long>> dp(1 << N, vector<long long>(N, 0));

        for (int i = 0; i < N; i++)
            dp[1 << i][i] = 1;

        for (int mask = 1; mask < (1 << N); mask++) {
            for (int last = 0; last < N; last++) {
                if (!(mask & (1 << last))) continue;
                long long val = dp[mask][last];
                if (!val) continue;

                for (int nxt = 0; nxt < N; nxt++) {
                    if (mask & (1 << nxt)) continue;
                    if (!bad[last][nxt])
                        dp[mask | (1 << nxt)][nxt] += val;
                }
            }
        }

        long long total = 0;
        for (int i = 0; i < N; i++)
            total += dp[(1 << N) - 1][i];

        cout << total << "\n";

        // encontrar la pintura favorita
        vector<string> result;
        int full_mask = (1 << N) - 1;
        int prev = -1;
        int mask = 0;

        for (int step = 0; step < N; step++) {
            for (int i = 0; i < N; i++) {
                int idx = id[colors[i]]; // los colores ya están en orden de preferencia
                if (mask & (1 << idx)) continue; // ya usado
                if (prev != -1 && bad[prev][idx]) continue;

                // verificar si se puede completar desde aquí
                bool possible = false;

                // buscar si hay al menos una forma de completar la pintura desde este punto
                int new_mask = mask | (1 << idx);

                if (new_mask == full_mask) possible = true;
                else {
                    for (int nxt = 0; nxt < N; nxt++) {
                        if (new_mask & (1 << nxt)) continue;
                        if (!bad[idx][nxt] && dp[full_mask ^ new_mask][nxt] > 0) {
                            possible = true;
                            break;
                        }
                    }
                }

                if (possible) {
                    result.push_back(colors[i]);
                    prev = idx;
                    mask |= (1 << idx);
                    break;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (i) cout << ' ';
            cout << result[i];
        }
        cout << "\n";
    }

    return 0;
}
