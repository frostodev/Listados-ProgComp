#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; // numero de articulos
    cin >> n;

    // vector para almacenar los precios de los articulos
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    // ordenar los precios en orden de mayor a menor
    sort(prices.begin(), prices.end(), greater<int>());

    long long total_discount = 0;

    // iterar sobre los articulos y sumar el precio del tercero de cada grupo
    // el bucle comienza en el indice 2 (el tercer articulo) y avanza de 3 en 3
    for (int i = 2; i < n; i += 3) {
        total_discount += prices[i];
    }

    cout << total_discount << endl;

    return 0;
}