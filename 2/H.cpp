#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	
    int n;
    bool first_case = true;
    
    while (cin >> n && n != 0) {
        // separador entre casos de prueba
        if (!first_case) {
            cout << endl;
        }
        first_case = false;
        
        vector<int> list1(n), list2(n);
        
        // leer primera lista
        for (int i = 0; i < n; i++) {
            cin >> list1[i];
        }
        
        // leer segunda lista
        for (int i = 0; i < n; i++) {
            cin >> list2[i];
        }
        
        // crear copias ordenadas de ambas listas
        vector<int> sorted1 = list1;
        vector<int> sorted2 = list2;
        sort(sorted1.begin(), sorted1.end());
        sort(sorted2.begin(), sorted2.end());
        
        // mapear cada valor de la primera lista ordenada
        // a su correspondiente en la segunda lista ordenada
        map<int, int> correspondence;
        for (int i = 0; i < n; i++) {
            correspondence[sorted1[i]] = sorted2[i];
        }
        
        // para cada elemento en la primera lista original,
        // encontrar su correspondiente en la segunda lista
        for (int i = 0; i < n; i++) {
            cout << correspondence[list1[i]] << endl;
        }
    }
    
    return 0;
}