#include <bits/stdc++.h>
using namespace std;

// struct simple para guardar los caminos (aristas)
struct Edge {
    int u, v, weight;
};

// función para comparar aristas por su peso
bool compare_edges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// struct para el DSU (Disjoint Set Union)
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n; // lee el numero de pueblos

    vector<Edge> edges;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int distance;
            cin >> distance;
            if (i < j) {
                edges.push_back({i, j, distance});
            }
        }
    }

    // ordenar todos los posibles caminos por su distancia (peso)
    sort(edges.begin(), edges.end(), compare_edges);

    DSU dsu(n);
    vector<pair<int, int>> map_roads;

    for (const auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            
            // guardar el camino
            // nos aseguramos que el numero menor vaya primero para ordenar facil
            if (edge.u < edge.v) {
                map_roads.push_back({edge.u, edge.v});
            } else {
                map_roads.push_back({edge.v, edge.u});
            }
            
            if (map_roads.size() == n - 1) {
                break;
            }
        }
    }

    // ordenar el resultado
    sort(map_roads.begin(), map_roads.end());

    // imprimir el resultado ya ordenado
    for (const auto& road : map_roads) {
        cout << road.first << " " << road.second << "\n";
    }

    return 0;
}