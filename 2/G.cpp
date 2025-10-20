#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    // leer los tamaños de las latas de pintura
    vector<long long> can_sizes(n);
    for (int i = 0; i < n; i++) {
        cin >> can_sizes[i];
    }
    
    // ordenar los tamaños de las latas
    sort(can_sizes.begin(), can_sizes.end());
    
    // leer las cantidades necesarias de cada color
    vector<long long> needs(m);
    for (int i = 0; i < m; i++) {
        cin >> needs[i];
    }
    
    long long total_waste = 0;
    
    // para cada color, encontrar la lata más pequeña que cumple con la necesidad
    for (int i = 0; i < m; i++) {
        // usar búsqueda binaria para encontrar la primera lata que sea >= a la necesidad
        auto it = lower_bound(can_sizes.begin(), can_sizes.end(), needs[i]);
        
        // si encontramos una lata válida, calcular el desperdicio
        if (it != can_sizes.end()) {
            total_waste += (*it - needs[i]);
        }
    }
    
    cout << total_waste << endl;
    
    return 0;
}