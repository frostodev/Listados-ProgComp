#include <bits/stdc++.h>
using namespace std;

// struct para almacenar una persona con su name y clase
struct Person {
    string name;
    string class_str;
    vector<int> values; // valores numéricos de la clase (2=upper, 1=middle, 0=lower)
};

// función para convertir string de clase a valores numéricos
vector<int> convert_class(const string& class) {
    vector<int> result;
    stringstream ss(class);
    string word;
    
    // dividir por guiones
    while (getline(ss, word, '-')) {
        if (word == "upper") {
            result.push_back(2);
        } else if (word == "middle") {
            result.push_back(1);
        } else if (word == "lower") {
            result.push_back(0);
        }
    }
    
    // revertir para comparar desde el nivel más específico
    reverse(result.begin(), result.end());
    return result;
}

// función para comparar dos personas
bool compare_person(const Person& a, const Person& b) {
    const vector<int>& va = a.values;
    const vector<int>& vb = b.values;
    
    // comparar los valores de clase
    size_t max_len = max(va.size(), vb.size());
    
    for (size_t i = 0; i < max_len; i++) {
        int val_a = (i < va.size()) ? va[i] : 1; // default a middle
        int val_b = (i < vb.size()) ? vb[i] : 1; // default a middle
        
        if (val_a != val_b) {
            return val_a > val_b; // mayor valor = clase más alta
        }
    }
    
    // si las clases son equivalentes, ordenar alfabéticamente
    return a.name < b.name;
}

int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(0);
	
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        cin.ignore(); // ignorar el salto de línea
        
        vector<Person> persons;
        
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            
            // encontrar el dos puntos
            size_t pos_colon = line.find(':');
            string name = line.substr(0, pos_colon);
            
            // extraer la parte de la clase (eliminar " class" al final)
            string complete_class = line.substr(pos_colon + 2);
            size_t pos_class = complete_class.find(" class");
            string clase = complete_class.substr(0, pos_class);
            
            // convertir la clase a valores numéricos
            vector<int> values = convert_class(clase);
            
            persons.push_back({name, clase, values});
        }
        
        // ordenar las personas
        sort(persons.begin(), persons.end(), compare_person);
        
        // imprimir resultados
        for (const auto& p : persons) {
            cout << p.name << endl;
        }
        
        // imprimir línea de separación
        cout << "==============================" << endl;
    }
    
    return 0;
}