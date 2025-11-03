#include <bits/stdc++.h>
using namespace std;

// para guardar los datos de cada investigador
struct Researcher {
    long long arrival, stay;

    // para poder ordenar el vector de investigadores por su tiempo de llegada
    bool operator<(const Researcher& other) const {
        return arrival < other.arrival;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long m;
    cin >> n >> m;

    vector<Researcher> researchers(n);
    for (int i = 0; i < n; ++i) {
        cin >> researchers[i].arrival >> researchers[i].stay;
    }

    // procesar eventos en orden cronológico
    sort(researchers.begin(), researchers.end());

    int saved_unlocks = 0;
    // cola de prioridad para saber qué máquina se bloqueará antes (min-heap)
    // guardamos el tiempo exacto en que una máquina libre se bloqueará
    priority_queue<long long, vector<long long>, greater<long long>> lock_times_pq;

    // recorrer todos los investigadores ya ordenados
    for (const auto& r : researchers) {
        // primero, sacamos del pq todas las máquinas que ya se bloquearon
        // o sea, cuyo tiempo de bloqueo es menor al tiempo de llegada del investigador actual
        while (!lock_times_pq.empty() && lock_times_pq.top() < r.arrival) {
            lock_times_pq.pop();
        }

        // ahora vemos si hay alguna máquina disponible
        // la que está en el top es la que se va a bloquear antes, nuestra mejor candidata
        if (!lock_times_pq.empty() && lock_times_pq.top() - m <= r.arrival) {
			// encontramos una
            saved_unlocks++;
            lock_times_pq.pop();
            lock_times_pq.push(r.arrival + r.stay + m);
        } else {
            // no hay máquinas disponibles, penelope tiene que trabajar :(
            // se desbloquea una nueva y la agregamos al pq para el futuro
            lock_times_pq.push(r.arrival + r.stay + m);
        }
    }

    cout << saved_unlocks << endl;

    return 0;
}