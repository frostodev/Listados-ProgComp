#include <bits/stdc++.h>
using namespace std;

// struct que representa un ítem de la mochila
struct Item {
	int value;
	int weight;
	int index;
};

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int c, n; // capacidad, cantidad items
	
	// bucle principal para leer los múltiples casos de prueba
	while (cin >> c >> n) {
		vector<Item> items(n); 
		
		// leer cada item y guardar su índice original
		for (int i = 0; i < n; ++i) {
			cin >> items[i].value >> items[i].weight;
			items[i].index = i;
		}
		
		// tabla DP
		// dp[i][w] = el máximo valor usando los primeros 'i' ítems con capacidad 'w'
		// dimensiones: (n+1) x (c+1)
		vector<vector<int>> dp(n + 1, vector<int>(c + 1, 0));

		// llenar la tabla
		for (int i = 1; i <= n; ++i) {
			// datos del ítem actual
			int v = items[i-1].value;
			int w = items[i-1].weight;
			
			for (int j = 0; j <= c; ++j) { // 'j' es la capacidad actual
				// opción 1: no tomar el ítem 'i'
				// el valor es el mismo que teníamos con (i-1) ítems
				dp[i][j] = dp[i-1][j];
				
				// opción 2: tomar el ítem 'i' (si cabe)
				if (j >= w) {
					// comparar "no tomarlo" vs "tomarlo"
					// "tomarlo" = su valor + el mejor valor para el peso restante
					dp[i][j] = max(dp[i][j], v + dp[i-1][j - w]);
				}
			}
		}
		
		// el valor máximo total está en dp[n][c], pero no lo necesitamos imprimir
		// entonces, ahora vemos qué ítems se eligieron para llegar a dp[n][c]
		
		vector<int> chosen_indices;
		int current_c = c;

		// recorrer la tabla hacia atrás, desde el último ítem
		for (int i = n; i > 0; --i) {
			// si el valor en dp[i][current_c] != dp[i-1][current_c], significa que si tomamos el ítem 'i'
			// (porque si no lo hubiéramos tomado, los valores serían iguales)
			if (dp[i][current_c] != dp[i-1][current_c]) {
				// añadir el índice original de este ítem
				chosen_indices.push_back(items[i-1].index);
			
				// restar su peso de nuestra capacidad actual
				current_c -= items[i-1].weight;
			}
			
			// s son iguales, significa que NO tomamos el ítem 'i', así que simplemente pasamos al ítem i-1 sin hacer nada
		}

		// imprimir la cantidad de ítems y los índices (no importa el orden)
		cout << chosen_indices.size() << endl;

		for (int i = 0; i < chosen_indices.size(); ++i) {
			cout << chosen_indices[i] << (i == chosen_indices.size() - 1 ? "" : " ");
		}
		cout << endl;
	}
	
	return 0;
}