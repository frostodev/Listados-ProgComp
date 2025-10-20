#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, h;
    cin >> n >> h;
    
    // arrays para contar obstaculos en cada altura
    // bottom: obstaculos que vienen del suelo (stalagmites)
    // top: obstaculos que vienen del techo (stalactites)
    vector<int> bottom(h + 1, 0);
    vector<int> top(h + 1, 0);
    
    // leer los datos
    for (int i = 0; i < n; i++) {
        int size;
        cin >> size;
        
        if (i % 2 == 0) {
            // es stalagmite (suelo)
            bottom[size]++;
        } else {
            // es stalactite (techo)
            top[h - size + 1]++;
        }
    }
    
    // calcular prefix sums para bottom (de abajo hacia arriba)
    for (int i = h - 1; i >= 1; i--) {
        bottom[i] += bottom[i + 1];
    }
    
    // calcular prefix sums para top (de arriba hacia abajo)
    for (int i = 2; i <= h; i++) {
        top[i] += top[i - 1];
    }
    
    int min_obstacles = n + 1;
    int count_levels = 0;
    
    // para cada altura posible, calcular obstaculos a destruir
    for (int i = 1; i <= h; i++) {
        int obstacles = bottom[i] + top[i];
        
        if (obstacles < min_obstacles) {
            min_obstacles = obstacles;
            count_levels = 1;
        } else if (obstacles == min_obstacles) {
            count_levels++;
        }
    }
    
    cout << min_obstacles << " " << count_levels << endl;
    
    return 0;
}