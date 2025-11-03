#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // vectores para guardar los tiempos
    vector<int> task_times(n);
    vector<int> quiet_intervals(m);

    // leer los tiempos de las tareas
    for (int i = 0; i < n; ++i) {
        cin >> task_times[i];
    }

    // leer los tiempos de los intervalos
    for (int i = 0; i < m; ++i) {
        cin >> quiet_intervals[i];
    }

    // ordenar ambos arreglos de menor a mayor
    sort(task_times.begin(), task_times.end());
    sort(quiet_intervals.begin(), quiet_intervals.end());

    int completed_tasks = 0; // contador para las tareas que se completan
    int task_index = 0;      // para recorrer las tareas
    int interval_index = 0;  // para recorrer los intervalos

    // mientras queden tareas e intervalos por revisar...
    while (task_index < n && interval_index < m) {
        // si la tarea actual cabe en el intervalo actual
        if (task_times[task_index] <= quiet_intervals[interval_index]) {
            // se completó nomas
            completed_tasks++;
            task_index++;       // pasamos a la siguiente tarea
            interval_index++;   // y al siguiente intervalo
        } else {
            // si la tarea es muy larga para este intervalo
            // se deja la tarea y probamos con un intervalo más grande
            interval_index++;
        }
    }

    cout << completed_tasks << endl;

    return 0;
}