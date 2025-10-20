#include <bits/stdc++.h>
using namespace std;

string wff;
int idx;

int values[5];

// funcion recursiva para evaluar la WFF
int eval() {
    // lee el carácter actual y avanza el índice
    char token = wff[idx++];

    switch (token) {
        // variables: p, q, r, s, t
        case 'p': return values[0];
        case 'q': return values[1];
        case 'r': return values[2];
        case 's': return values[3];
        case 't': return values[4];

        // operador NOT (unario)
        case 'N': {
            int operand = eval();
            return !operand; // negación lógica
        }

        // operadores binarios: K, A, C, E
        case 'K': { // AND
            int w = eval();
            int x = eval();
            return w && x;
        }
        case 'A': { // OR
            int w = eval();
            int x = eval();
            return w || x;
        }
        case 'C': { // implica (w -> x es equivalente a !w || x)
            int w = eval();
            int x = eval();
            return !w || x;
        }
        case 'E': { // equivalente (w <-> x)
            int w = eval();
            int x = eval();
            return w == x;
        }
    }
    // no debería llegar aquí con una WFF válida
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // leer WFFs hasta que la entrada sea "0"
    while (cin >> wff && wff != "0") {
        bool is_tautology = true;

        // iterar sobre las 32 combinaciones posibles de valores para 5 variables (2^5)
        for (int i = 0; i < 32; ++i) {
            // asignar valores a p, q, r, s, t usando los bits de 'i'
            values[0] = (i >> 4) & 1; // p
            values[1] = (i >> 3) & 1; // q
            values[2] = (i >> 2) & 1; // r
            values[3] = (i >> 1) & 1; // s
            values[4] = (i >> 0) & 1; // t

            // reiniciar el índice para evaluar la fórmula desde el principio
            idx = 0;
            if (eval() == 0) {
                // si la WFF es falsa para cualquier combinacion, no es una tautología
                is_tautology = false;
                break; // no es necesario seguir probando otras combinaciones
            }
        }

        if (is_tautology) {
            cout << "tautology\n";
        } else {
            cout << "not\n";
        }
    }

    return 0;
}