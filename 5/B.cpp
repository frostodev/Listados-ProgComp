#include <bits/stdc++.h>
using namespace std;

/*
  dp[i][j] = cuántas formas hay de sumar 'i'
             usando solo los primeros 'j' items del menú
             (desde el item 0 hasta el item j).

  guardamos los valores así:
  0 = imposible
  1 = hay exactamente una forma
  2 = hay dos o más formas (le llamamos "ambiguo")
*/
int dp[30001][101]; // [suma_maxima + 1][items_maximos + 1]

vector<int> costs;
int n; // número de items

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    costs.resize(n); 
    for (int i = 0; i < n; ++i) {
        cin >> costs[i];
    }

    int max_s = 30000; // la suma máxima que nos pueden pedir

    // iteramos por cada item del menú (de 0 a n-1)
    for (int j = 0; j < n; ++j) {
        // iteramos por cada suma posible (de 0 a 30000)
        for (int i = 0; i <= max_s; ++i) {
            
            // caso base: sumar 0
            // siempre hay 1 forma de hacerlo: no pidiendo nada
            if (i == 0) {
                dp[i][j] = 1;
                continue; // saltamos al siguiente 'i'
            }

            // cuántas formas hay de sumar 'i' sin usar el item 'j'?
            int ways_without = (j == 0) ? 0 : dp[i][j - 1];

            // cuántas formas hay de sumar 'i' usando el item 'j' (al menos una vez)?
            int ways_with = (i < costs[j]) ? 0 : dp[i - costs[j]][j];

            // el total de formas es la suma de las dos
            dp[i][j] = min(2, ways_without + ways_with);
        }
    }

    // ahora, la tabla dp[s][n-1] tiene la respuesta (0, 1, o 2) para cualquier suma 's'

    int m; // cuántas órdenes vamos a procesar
    cin >> m;

    for (int k = 0; k < m; ++k) {
        int s; // la suma total de la orden
        cin >> s;

        // revisar la tabla que ya calculamos
        int result_type = dp[s][n - 1];

        if (result_type == 0) {
            cout << "Impossible\n";
        } else if (result_type > 1) { // o sea, 2
            cout << "Ambiguous\n";
        } else {
            vector<int> order;
            int current_s = s;
            int j = n - 1;

            while (current_s > 0) {
                // se podía lograr esta suma 'current_s' sin usar el item 'j'?
                if (j > 0 && dp[current_s][j - 1] == 1) {
                    j--;
                } else {
                    order.push_back(j + 1);
                    current_s -= costs[j];
                }
            }

            // la reconstrucción nos da los items en orden inverso (ej. 2, 2, 1)
            // pero el problema los pide en orden ascendente
            sort(order.begin(), order.end());

            for (int i = 0; i < order.size(); ++i) {
                cout << order[i] << (i == order.size() - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}