#include <bits/stdc++.h>
using namespace std; 

// struct para las aristas
struct Edge {
    int u;
    int v;
    int w;
};

// 1e18 es un valor suficientemente grande para representar infinito (creo)
const long long INF = 1e18;
const long long NEGINF = -1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, s;
    bool first_case = true; // para manejar la línea en blanco de salida

    // leer la entrada hasta recibir "0 0 0 0"
    while (cin >> n >> m >> q >> s && (n != 0 || m != 0 || q != 0 || s != 0)) {

        if (!first_case) {
            cout << "\n";
        }
        first_case = false;

        // leer todas las 'm' aristas
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        // dp (bellman-ford, como en la tarea de SO): 'dist[i]' es la distancia más corta desde 's' a 'i'
        vector<long long> dist(n, INF);
        dist[s] = 0; // la distancia al nodo de inicio 's' es 0 

        // fase 1: bellman-ford (n iteraciones)
        // esto encuentra los caminos más cortos simples (hasta n-1 aristas)
        // la iteración n-ésima (índice n-1) sirve como primera detección de ciclos
        for (int i = 0; i < n; ++i) {
            for (const auto& edge : edges) {
                // si no podemos llegar a 'u', o 'u' ya es -inf, continuamos
                if (dist[edge.u] == INF) continue;

                // propagamos -infinito
                if (dist[edge.u] == NEGINF) {
                    dist[edge.v] = NEGINF;
                    continue;
                }

                // relajación de la arista
                if (dist[edge.v] > dist[edge.u] + edge.w) {
                    dist[edge.v] = dist[edge.u] + edge.w;
                }
            }
        }

        // fase 2: propagación de ciclos negativos (n iteraciones)
        // si un nodo cambió en la iteración 'n' de la fase 1, está afectado por un ciclo negativo
        // corremos n iteraciones más para propagar este efecto (-inf) a todos los nodos alcanzables desde los ciclos
        for (int i = 0; i < n; ++i) {
            for (const auto& edge : edges) {
                if (dist[edge.u] == INF) continue;

                // si 'u' es -infinito, 'v' también lo es
                if (dist[edge.u] == NEGINF) {
                    dist[edge.v] = NEGINF;
                    continue;
                }

                // si 'v' todavía puede mejorar, es parte de un ciclo neg o alcanzable desde uno
                if (dist[edge.v] > dist[edge.u] + edge.w) {
                    dist[edge.v] = NEGINF;
                }
            }
        }

        // finalmente responder las 'q' consultas
        for (int i = 0; i < q; ++i) {
            int query_node;
            cin >> query_node;

            if (dist[query_node] == INF) {
                cout << "Impossible\n"; // 
            } else if (dist[query_node] == NEGINF) {
                cout << "-Infinity\n"; // 
            } else {
                cout << dist[query_node] << "\n"; // 
            }
        }

    }

    return 0;
}