#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long l, d;
    int n;
    cin >> l >> d >> n;

    // caso especial: si no hay pájaros, calculamos sobre todo el largo
    if (n == 0) {
        // el espacio útil es desde la marca de 6cm hasta l-6
        long long available_space = l - 12;
        if (available_space < 0) {
            cout << 0 << endl;
        } else {
            // la fórmula para saber cuántos puntos caben en un segmento es (largo / distancia) + 1
            long long count = available_space / d + 1;
            cout << count << endl;
        }
        return 0;
    }

    // si llegamos aquí, es porque n > 0
    vector<long long> birds(n);
    for (int i = 0; i < n; ++i) {
        cin >> birds[i];
    }

    // para analizar los huecos, primero hay que ordenar las posiciones
    sort(birds.begin(), birds.end());

    long long additional_birds = 0;

    // primer hueco: desde el poste (posición 6) hasta el primer pájaro
    // cada pájaro que ponemos "consume" d centímetros del hueco
    additional_birds += (birds[0] - 6) / d;

    // huecos intermedios: entre cada par de pájaros que ya estaban
    for (int i = 0; i < n - 1; ++i) {
        long long space_between = birds[i+1] - birds[i];
        // si el espacio es de al menos 2*d, cabe un pájaro nuevo
        // la fórmula es (espacio entre pájaros / d) - 1
        if (space_between >= 2 * d) {
            additional_birds += (space_between / d) - 1;
        }
    }

    // último hueco: desde el último pájaro hasta el final del cable (posición l-6)
    additional_birds += (l - 6 - birds[n-1]) / d;

    cout << additional_birds << endl;

    return 0;
}