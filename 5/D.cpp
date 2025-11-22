#include <bits/stdc++.h>
using namespace std;

// usamos valores constantes grandes para los límites
// m <= 40, suma total <= 1000
const int INF = 1e9; // un valor grande para "infinito"
const int MAX_M = 45; // 40 + 5 de margen
const int MAX_H = 1005; // 1000 + 5 de margen

int m; // número de distancias
int dist[MAX_M]; // array para guardar las distancias

// dp[i][h] = guarda el "peak" (altura máxima) más bajo para estar en altura 'h' después de 'i' pasos.
int dp[MAX_M][MAX_H];

// path[i][h] = guarda la decisión ('U' o 'D') que nos llevó al estado óptimo dp[i][h].
char path[MAX_M][MAX_H];

// función que resuelve un solo caso de prueba
void solve() {
    cin >> m;
    int suma_total = 0;
    for (int i = 0; i < m; i++) {
        cin >> dist[i];
        suma_total += dist[i]; // la altura max posible es la suma total
    }

    // inicializar nuestras tablas de dp y path
    for (int i = 0; i <= m; i++) {
        for (int h = 0; h <= suma_total; h++) {
            dp[i][h] = INF; // por defecto, inalcanzable
            path[i][h] = 0; // 0 o ' ' (nulo)
        }
    }

    // caso base: en el paso 0, estamos en altura 0 y el peak máximo alcanzado es 0
    dp[0][0] = 0;

    // iterar sobre cada distancia 
    for (int i = 0; i < m; i++) {
        // iterar sobre cada altura posible 'h' en la que podríamos estar
        for (int h = 0; h <= suma_total; h++) {
            // si este estado (i, h) es inalcanzable, no podemos seguir desde aquí
            if (dp[i][h] == INF) continue;

            int d_actual = dist[i]; // la distancia de este paso
            int peak_actual = dp[i][h]; // el peak más bajo para llegar aquí

            // opción 1: subir
            int h_up = h + d_actual;
            if (h_up <= suma_total) { // control de límites
                // el nuevo peak es el máximo entre el peak anterior y la nueva altura
                int peak_up = max(peak_actual, h_up);

                // si este camino (peak_up) es mejor que el que ya teníamos guardado para (i+1, h_up), se actualiza
                if (peak_up < dp[i + 1][h_up]) {
                    dp[i + 1][h_up] = peak_up;
                    path[i + 1][h_up] = 'U'; // guardamos que vinimos subiendo
                }
            }

            // opción 2: bajar
            int h_down = h - d_actual;
            if (h_down >= 0) {
                // si bajamos, el peak máximo no cambia
                int peak_down = peak_actual;

                // si este camino (peak_down) es mejor
                if (peak_down < dp[i + 1][h_down]) {
                    dp[i + 1][h_down] = peak_down;
                    path[i + 1][h_down] = 'D'; // guardamos que vinimos bajando
                }
            }
        }
    }
	
    // ahora revisar el resultado final
    // la condición es terminar en altura 0
    if (dp[m][0] == INF) {
        // si es inf, nunca encontramos un camino legal
        cout << "IMPOSSIBLE" << endl;
    } else {
        // sí hay solución, ahora hay que reconstruir el camino
        string ans = "";
        int h_actual = 0; // empezar desde el final (paso m, altura 0)

        // recorrer los pasos hacia atrás, desde m hasta 1
        for (int i = m; i > 0; i--) {
            // qué movimiento (u/d) nos trajo a (i, h_actual)?
            char move = path[i][h_actual];
            ans += move;

            // revertir el movimiento para saber dónde estábamos en el paso i-1
            if (move == 'U') {
                h_actual -= dist[i - 1]; // si subimos, veníamos de más abajo
            } else { // move == 'D'
                h_actual += dist[i - 1]; // si bajamos, veníamos de más arriba
            }
        }

        // la respuesta la construimos al revés (del final al inicio), así que la volteamos
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // número de escenarios
    cin >> n;
    while (n--) {
        solve();
    }
    return 0;
}