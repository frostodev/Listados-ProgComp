#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int S; // número de estados
    cin >> S;

    int D_total = 0;         // total de delegados en el país
    int D_const_win = 0;     // delegados que ya ganamos "gratis"
    
    // un vector para guardar los estados "disputables"
    vector<pair<long long, int>> contestable;

    for (int i = 0; i < S; ++i) {
        int D;  // delegados de este estado
        long long C, F, U; // votantes: Constituents, Federals, Undecided
        cin >> D >> C >> F >> U;

        D_total += D;
        // para ganar, necesitamos: C + u > F + (U - u)
        long long rhs = F + U - C + 1; // el lado derecho de la desigualdad
        long long cost;

        if (rhs <= 0) {
            // si rhs es <= 0, ya ganamos (C > F+U o C=F+U+1, etc)
            cost = 0;
        } else {
            // calcular el "techo" de (rhs / 2.0)
            cost = (rhs + 1) / 2;
        }

        if (cost == 0) {
            // lo ganamos gratis
            D_const_win += D;
        } else if (cost <= U) {
            // es "disputable", podemos ganarlo si pagamos el costo
            contestable.push_back({cost, D});
        } else {
            // los federales lo ganan, no hacemos nada
        }
    }

    // calcular cuántos delegados necesitamos para la victoria
    int D_win = (D_total / 2) + 1;

    // delegados que aún necesitamos ganar (descontando los gratis)
    int D_needed = D_win - D_const_win;

    if (D_needed <= 0) {
        cout << 0 << "\n";
        return 0;
    }

    // dp[j] = costo mínimo para obtener exactamente j delegados de la bolsa de estados "disputables".
    // D_total es <= 2016, así que un vector de 2020 es seguro
    vector<long long> dp(D_total + 1, INF);
    
    // caso base: cuesta 0 obtener 0 delegados
    dp[0] = 0;

    // iterar por cada estado "disputable"
    for (const auto& state : contestable) {
        long long cost = state.first;
        int delegates = state.second;

        // iterar hacia atrás para no usar el mismo estado múltiples veces en esta pasada (knapsack 0/1)
        for (int j = D_total; j >= delegates; --j) {
            
            // si podemos alcanzar el estado (j - delegates)
            if (dp[j - delegates] != INF) {
                // ver si es más barato long longegar a 'j' pasando por (j - delegates) y sumando este estado
                dp[j] = min(dp[j], dp[j - delegates] + cost);
            }
        }
    }
	
    // necesitamos al menos D_needed delegados
    // así que buscamos el costo mínimo en dp[j] para j >= D_needed
    long long min_cost = INF;
    for (int j = D_needed; j <= D_total; ++j) {
        min_cost = min(min_cost, dp[j]);
    }

    // si min_cost sigue siendo infinito, no hay combinación de estados que nos de la victoria
    if (min_cost == INF) {
        cout << "impossible\n";
    } else {
        cout << min_cost << "\n";
    }

    return 0;
}