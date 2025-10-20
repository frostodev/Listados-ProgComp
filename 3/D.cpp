#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string x_str;
    cin >> x_str;

    // recorremos de derecha a izquierda, buscando el primer digito que es menor que el digito a su derecha
    int pivot_idx = -1;
    for (int i = x_str.length() - 2; i >= 0; --i) {
        if (x_str[i] < x_str[i + 1]) {
            pivot_idx = i;
            break;
        }
    }

	// si no se encontro pivote, los digitos estan en orden descendente
    if (pivot_idx == -1) {
        cout << 0 << endl;
        return 0;
    }

    // buscamos de derecha a izquierda el primer digito mayor que el pivote
    int successor_idx = -1;
    for (int i = x_str.length() - 1; i > pivot_idx; --i) {
        if (x_str[i] > x_str[pivot_idx]) {
            successor_idx = i;
            break;
        }
    }

    // intercambiar
    swap(x_str[pivot_idx], x_str[successor_idx]);

    // invertir la parte del string a la derecha del pivote para obtener la permutacion mas pequeña
    reverse(x_str.begin() + pivot_idx + 1, x_str.end());

    cout << x_str << endl;

    return 0;
}