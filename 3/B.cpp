#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    char grid[4][4];
    
    // leer la entrada
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> grid[i][j];
        }
    }
    
    // posiciones objetivo de cada letra
    char target[4][4] = {
        {'A','B','C','D'},
        {'E','F','G','H'},
        {'I','J','K','L'},
        {'M','N','O','.'}
    };
    
    int scatter = 0;
    
    // recorrer cada celda del grid actual
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            char ch = grid[r][c];
            if (ch == '.') continue; // ignorar el espacio vacío
            
            // buscar la posición objetivo de ch
            for (int tr = 0; tr < 4; tr++) {
                for (int tc = 0; tc < 4; tc++) {
                    if (target[tr][tc] == ch) {
                        scatter += abs(r - tr) + abs(c - tc);
                        break;
                    }
                }
            }
        }
    }
    
    cout << scatter << endl;
    
    return 0;
}