#include <bits/stdc++.h>
using namespace std;

string S;

bool is_vowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

long long count_pleasant(int index, int vowels, int consonants, bool has_L) {
    // si ya tenemos 3 vocales o 3 consonantes seguidas, esta rama no es valida
    if (vowels >= 3 || consonants >= 3) {
        return 0;
    }

    // si llegamos  al final de la cadena, hemos formado una palabra completa
    if (index == S.length()) {
        return has_L ? 1 : 0;
    }

    long long total = 0;
    char current_char = S[index];

    if (current_char == '_') {
        // sustituir con vocal
        total += 5 * count_pleasant(index + 1, vowels + 1, 0, has_L);

        // sustituir con L
        total += 1 * count_pleasant(index + 1, 0, consonants + 1, true);

        // sustituir con cualquier otra consonante
        total += 20 * count_pleasant(index + 1, 0, consonants + 1, has_L);

    } else {
        // El caracter es una letra especifica. hay un solo camino a seguir

        if (is_vowel(current_char)) {
            total += count_pleasant(index + 1, vowels + 1, 0, has_L);
        } else {
            // consonante, verificar si es L
            bool new_condition_L = has_L || (current_char == 'L');
            total += count_pleasant(index + 1, 0, consonants + 1, new_condition_L);
        }
    }

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S;

    long long resultado = count_pleasant(0, 0, 0, false);
    cout << resultado << endl;

    return 0;
}