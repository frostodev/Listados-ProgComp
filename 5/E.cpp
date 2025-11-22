#include <bits/stdc++.h>
using namespace std;

// n <= 200, así que 205 es un tamaño seguro
const int MAXN = 205;

// para almacenar los números de entrada
long long a[MAXN];

// dp[i] almacenará la lista lexicográficamente más temprana que termina en a[i]
vector<long long> dp[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        // leer los n números en el arreglo 'a'
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            // limpiar el estado de dp del caso de prueba anterior
            // es importante para evitar usar datos viejos
            dp[i].clear(); 
        }


        for (int i = 0; i < n; i++) {
            // inicializar la lista que termina en 'i' con solo el elemento 'i'
            dp[i].push_back(a[i]);

            // ahora, mirar todos los elementos 'j' que vienen antes de 'i'
            for (int j = 0; j < i; j++) {
                
                // si a[j] < a[i], podemos extender la subsecuencia que termina en j
                if (a[j] < a[i]) {
                    
                    // calcular el tamaño de la nueva subsecuencia candidata
                    int candidate_size = dp[j].size() + 1;

                    // si la nueva subsecuencia es más larga que la actual para 'i'
                    if (candidate_size > dp[i].size()) {
                        // entonces se reemplaza nomás. copiamos la de 'j' y añadimos a[i]
                        dp[i] = dp[j];
                        dp[i].push_back(a[i]);
                    } 
                    // si es del mismo tamaño, debemos revisar el orden lexicográfico
                    else if (candidate_size == dp[i].size()) {
                        // crear la secuencia candidata completa para comparar
                        vector<long long> candidate = dp[j];
                        candidate.push_back(a[i]);
                        
                        // la comparación de vectores en c++ es lexicográfica por defecto
                        // si la nueva candidata es "menor" (lexicográficamente)
                        if (candidate < dp[i]) {
                            // se reemplaza
                            dp[i] = candidate;
                        }
                    }
                }
            }
        }
        

        // ahora buscamos la mejor entre todas las dp[i]
        // (la más larga, y entre las más largas, la lexicográficamente primera)
        
        // inicializar la mejor con la primera
        vector<long long> best = dp[0];
        
        for (int i = 1; i < n; i++) {
            // si encontramos una más larga
            if (dp[i].size() > best.size()) {
                best = dp[i];
            } 
            // si encontramos una del mismo tamaño
            else if (dp[i].size() == best.size()) {
                // se revisa el orden lexicográfico
                if (dp[i] < best) {
                    best = dp[i];
                }
            }
        }

        // tamaño
        cout << best.size();
        
        // cada elemento de la subsecuencia
        for (int k = 0; k < best.size(); k++) {
            cout << " " << best[k];
        }
        cout << "\n";
    }

    return 0;
}