#include <bits/stdc++.h>
using namespace std;

// comparador para ordenar según el ratio w/s
struct Comp {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        // compara la fracción w/s de dos pares
        return (float)a.first / a.second < (float)b.first / b.second;
    }
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    float ratio;
    int n;

    // leemos mientras haya pares ratio y n
    while (cin >> ratio >> n) {
        // priority queue con nuestro comparador
        priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;

        float minimal = pow(10, 7); // empezamos con un número grande para el mínimo ratio
        int w;

        // metemos todos los pesos con divisor 1 y actualizamos el mínimo ratio
        for (int i = 0; i < n; i++) {
            cin >> w;
            pq.push({w, 1});
            minimal = min(minimal, w / 1.0f); // guardamos el menor ratio
        }

        int res = 0; // contador de pasos que hacemos

        // mientras haya elementos en la cola
        while (!pq.empty()) {
            auto top = pq.top(); // sacamos el top con menor ratio

            // si la condición ya se cumple, paramos
            if (minimal / ((float)top.first / (float)top.second) >= ratio) {
                break;
            }

            pq.pop(); // quitamos el top
            pq.push({top.first, top.second + 1}); // metemos el mismo peso pero con divisor +1

            // actualizamos el mínimo ratio con este nuevo valor
            minimal = min(minimal, (float)top.first / (float)(top.second + 1));
            res++; // aumentamos el contador
        }

        cout << res << "\n"; // mostramos el resultado final
    }

    return 0;
}
