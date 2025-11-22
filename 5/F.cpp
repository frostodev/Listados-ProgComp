#include <bits/stdc++.h>
using namespace std;

// estructura para las aristas del grafo
struct Edge {
    int u, v, w;
};

// definimos infinito para saber si llegamos o no
const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int W, H;
	
    while (cin >> W >> H && (W != 0 || H != 0)) {
        // mapa para marcar cosas: 0=pasto, 1=piedra, 2=agujero
        // usamos un mapa plano (w*h) para facilitar los indices
        int G;
        cin >> G;
        
        // set para búsqueda rápida de piedras
        set<pair<int, int>> stones;
        for (int i = 0; i < G; ++i) {
            int x, y;
            cin >> x >> y;
            stones.insert({x, y});
        }

        int E;
        cin >> E;
        // mapa para los agujeros: {x,y} -> {x2, y2, tiempo}
        map<pair<int, int>, tuple<int, int, int>> holes;
        for (int i = 0; i < E; ++i) {
            int x1, y1, x2, y2, t;
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            holes[{x1, y1}] = make_tuple(x2, y2, t);
        }

        // construimos el grafo (lista de aristas)
        vector<Edge> edges;
        int node_count = W * H;
        
        // direcciones para moverse en el pasto (n, s, e, o)
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int x = 0; x < W; ++x) {
            for (int y = 0; y < H; ++y) {
                int u = x + y * W; // id del nodo actual

                // si es la salida, no agregamos aristas salientes.
                // el enunciado dice que apenas llega, se va.
                if (x == W - 1 && y == H - 1) continue;

                // si es piedra, no se puede pisar ni salir de ella
                if (stones.count({x, y})) continue;

                // si es un agujero, te obliga a saltar (arista forzada)
                if (holes.count({x, y})) {
                    auto [x2, y2, t] = holes[{x, y}];
                    int v = x2 + y2 * W;
                    edges.push_back({u, v, t});
                } else {
                    // si es pasto normal, probamos los 4 vecinos
                    for (int i = 0; i < 4; ++i) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];

                        // chequeamos limites y que no sea piedra
                        if (nx >= 0 && nx < W && ny >= 0 && ny < H) {
                            if (!stones.count({nx, ny})) {
                                int v = nx + ny * W;
                                edges.push_back({u, v, 1}); // moverse cuesta 1 seg
                            }
                        }
                    }
                }
            }
        }

        // bellman-ford para distancias minimas
        vector<int> dist(node_count, INF);
        dist[0] = 0; // empezamos en (0,0)

        // relajamos v-1 veces
        for (int i = 0; i < node_count - 1; ++i) {
            bool changed = false; 
            for (auto& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                    changed = true;
                }
            }
            // optimizacion: si nada cambio, cortamos antes
            if (!changed) break; 
        }

        // chequeo de ciclo negativo (viaje en el tiempo infinito)
        bool negative_cycle = false;
        for (auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                negative_cycle = true;
                break;
            }
        }

        if (negative_cycle) {
            cout << "Never" << endl;
        } else if (dist[node_count - 1] == INF) {
            cout << "Impossible" << endl;
        } else {
            cout << dist[node_count - 1] << endl;
        }
    }

    return 0;
}