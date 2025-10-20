#include <bits/stdc++.h>
using namespace std;

unsigned char reverse_operation(unsigned char y) {
    unsigned char x = 0;
    
    // reconstruir bit por bit
    for (int i = 0; i < 8; i++) {
        // calcular el bit actual de x
        unsigned char bit;
        if (i == 0) {
            bit = y & 1;  // el primer bit es igual al de y
        } else {
            // bit_i = y_i XOR bit_{i-1}
            bit = ((y >> i) & 1) ^ ((x >> (i - 1)) & 1);
        }
        x |= (bit << i);
    }
    
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> result;
    for (int i = 0; i < n; i++) {
        int b;
        cin >> b;
        result.push_back(reverse_operation(b));
    }
    
    for (int i = 0; i < n; i++) {
        cout << result[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}