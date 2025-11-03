#include <bits/stdc++.h>
using namespace std;

void solve() {
    int l, n;
    cin >> l >> n;

    int earliest_time = 0;
    int latest_time = 0;

    for (int i = 0; i < n; ++i) {
        int ant_pos;
        cin >> ant_pos;

        // calcular el tiempo mínimo y máximo para la hormiga actual
        int time_to_left = ant_pos;
        int time_to_right = l - ant_pos;

        int current_min_time = min(time_to_left, time_to_right);
        int current_max_time = max(time_to_left, time_to_right);

        // actualizar el tiempo mínimo global
        if (current_min_time > earliest_time) {
            earliest_time = current_min_time;
        }

        // actualiza el tiempo máximo global
        if (current_max_time > latest_time) {
            latest_time = current_max_time;
        }
    }

    cout << earliest_time << " " << latest_time << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_cases;
    cin >> num_cases;
    while (num_cases--) {
        solve();
    }

    return 0;
}