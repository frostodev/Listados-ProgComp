#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<double> plot_radio(n);
    for (int i = 0; i < n; ++i) {
        cin >> plot_radio[i];
    }
    sort(plot_radio.begin(), plot_radio.end());

    // vector para almacenar los radios efectivos de todas las casas
    vector<double> house_effective_radio;
    house_effective_radio.reserve(m + k);

    double r;
    for (int i = 0; i < m; ++i) {
        cin >> r;
        house_effective_radio.push_back(r);
    }

    double s;
    for (int i = 0; i < k; ++i) {
        cin >> s;
        // el radio efectivo es la mitad de la diagonal: s * sqrt(2) / 2
        house_effective_radio.push_back(s * sqrt(2.0) / 2.0);
    }
    
    // ordenar todas las casas por su radio efectivo de forma ascendente
    sort(house_effective_radio.begin(), house_effective_radio.end());

    // algoritmo greedy con dos punteros para emparejar casas y terrenos
    int houses_placed = 0;
    int plot_idx = 0;
    int house_idx = 0;

    while (plot_idx < n && house_idx < m + k) {
        // comprobar si la casa actual cabe en el terreno actual
        // la condición es estricta: radio_efectivo < radio_terreno
        if (house_effective_radio[house_idx] < plot_radio[plot_idx]) {
            // si cabe, se coloca la casa y se pasa al siguiente terreno
            houses_placed++;
            house_idx++;
            plot_idx++;
        } else {
            // el terreno es muy pequeño
            plot_idx++;
        }
    }
    cout << houses_placed << endl;

    return 0;
}