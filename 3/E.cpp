#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int h, w;
};

bool can_tile(Rect other1, Rect other2, int target_h, int target_w) {
    // iterar sobre las 4 posibles combinaciones de rotación para los dos rectángulos
    for (int i = 0; i < 4; ++i) {
        Rect o1 = (i & 1) ? Rect{other1.w, other1.h} : other1;
        Rect o2 = (i & 2) ? Rect{other2.w, other2.h} : other2;

        // caso 1: apilados verticalmente
        if (o1.w == o2.w && o1.w == target_w && (o1.h + o2.h) == target_h) {
            return true;
        }
        // caso 2: apilados horizontalmente
        if (o1.h == o2.h && o1.h == target_h && (o1.w + o2.w) == target_w) {
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Rect> rects(3);
    for (int i = 0; i < 3; ++i) {
        cin >> rects[i].h >> rects[i].w;
    }

    bool possible = false;

    // generar todas las permutaciones de los rectángulos (3! = 6)
    vector<int> p = {0, 1, 2};
    sort(p.begin(), p.end());
    do {
        Rect r1 = rects[p[0]];
        Rect r2 = rects[p[1]];
        Rect r3 = rects[p[2]];

        // iterar sobre las 8 combinaciones de rotación
        for (int i = 0; i < 8; ++i) {
            Rect c1 = (i & 1) ? Rect{r1.w, r1.h} : r1;
            Rect c2 = (i & 2) ? Rect{r2.w, r2.h} : r2;
            Rect c3 = (i & 4) ? Rect{r3.w, r3.h} : r3;

            if (c1.w == c2.w && c2.w == c3.w && c1.w == (c1.h + c2.h + c3.h)) {
                possible = true;
                break;
            }
        }
        if (possible) break;

        // iterar sobre las 2 rotaciones del rectángulo principal
        for (int i = 0; i < 2; ++i) {
            Rect main_rect = (i == 1) ? Rect{r1.w, r1.h} : r1;
            
            int side = main_rect.h; // el lado del cuadrado es la altura del rectángulo principal
            if (main_rect.w >= side) continue; // el ancho no puede ser mayor que el lado

            int target_h = side;
            int target_w = side - main_rect.w;
            
            if (can_tile(r2, r3, target_h, target_w)) {
                possible = true;
                break;
            }
        }
        if (possible) break;

    } while (next_permutation(p.begin(), p.end()));

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}