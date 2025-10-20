#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	
    // leer la primera linea de atributos
    string line;
    getline(cin, line);
    
    // dividir los atributos en un vector
    vector<string> attributes;
    string temp = "";
    for (char c : line) {
        if (c == ' ') {
            if (!temp.empty()) {
                attributes.push_back(temp);
                temp = "";
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        attributes.push_back(temp);
    }
    
    // crear un mapa para encontrar el indice de cada atributo
    map<string, int> attr_index;
    for (int i = 0; i < attributes.size(); i++) {
        attr_index[attributes[i]] = i;
    }
    
    // leer el numero de canciones
    int m;
    cin >> m;
    cin.ignore(); // ignorar el newline
    
    // leer las canciones
    vector<vector<string>> songs(m);
    for (int i = 0; i < m; i++) {
        getline(cin, line);
        vector<string> song_attrs;
        temp = "";
        for (char c : line) {
            if (c == ' ') {
                if (!temp.empty()) {
                    song_attrs.push_back(temp);
                    temp = "";
                }
            } else {
                temp += c;
            }
        }
        if (!temp.empty()) {
            song_attrs.push_back(temp);
        }
        songs[i] = song_attrs;
    }
    
    // leer el numero de comandos de ordenamiento
    int n;
    cin >> n;
    cin.ignore(); // ignorar el newline
    
    // procesar cada comando de ordenamiento
    for (int cmd = 0; cmd < n; cmd++) {
        string sort_attr;
        getline(cin, sort_attr);
        
        // obtener el indice del atributo por el que ordenaremos
        int sort_index = attr_index[sort_attr];
        
        // ordenar establemente usando el atributo especificado
        stable_sort(songs.begin(), songs.end(), 
            [sort_index](const vector<string>& a, const vector<string>& b) {
                return a[sort_index] < b[sort_index];
            });
        
        // imprimir la linea de atributos
        for (int i = 0; i < attributes.size(); i++) {
            if (i > 0) cout << " ";
            cout << attributes[i];
        }
        cout << endl;
        
        // imprimir las canciones ordenadas
        for (const auto& song : songs) {
            for (int i = 0; i < song.size(); i++) {
                if (i > 0) cout << " ";
                cout << song[i];
            }
            cout << endl;
        }
        
        // imprimir linea en blanco entre resultados (excepto el ultimo)
        if (cmd < n - 1) {
            cout << endl;
        }
    }
    
    return 0;
}