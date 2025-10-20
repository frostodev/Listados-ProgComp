#include <bits/stdc++.h>
using namespace std;

int main() {
    int P;
    cin >> P;
    
    for (int i = 0; i < P; i++) {
        int K;
        cin >> K;
        
        vector<int> heights(20);
        for (int j = 0; j < 20; j++) {
            cin >> heights[j];
        }
        
        // simulamos el proceso de inserción
        vector<int> line;
        int total_steps = 0;
        
        for (int j = 0; j < 20; j++) {
            int current = heights[j];
            
            // buscar el primer estudiante más alto que el actual
            bool found = false;
            for (int k = 0; k < line.size(); k++) {
                if (line[k] > current) {
                    // insertar antes del más alto
                    line.insert(line.begin() + k, current);
                    // cada estudiante detrás de esta posición debe dar un paso atrás
                    total_steps += line.size() - k - 1;
                    found = true;
                    break;
                }
            }
            
            // si no se encuentra a nadie más alto, lo ponemos al final
            if (!found) {
                line.push_back(current);
            }
        }
        
        cout << K << " " << total_steps << endl;
    }
    
    return 0;
}