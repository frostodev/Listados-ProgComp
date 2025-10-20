#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    cin >> N;
    int freq_A[101] = {0};
    int freq_B[101] = {0};
    
    for (int round = 0; round < N; round++) {
        int A, B;
        cin >> A >> B;
        freq_A[A]++;
        freq_B[B]++;
        
        int count_A[101], count_B[101];
        for (int i = 1; i <= 100; i++) {
            count_A[i] = freq_A[i];
            count_B[i] = freq_B[i];
        }
        
        int i = 1, j = 100;
        int ans = 0;
        while (i <= 100 && j >= 1) {
            while (i <= 100 && count_A[i] == 0) i++;
            while (j >= 1 && count_B[j] == 0) j--;
            if (i > 100 || j < 1) break;
            
            int current_sum = i + j;
            ans = max(ans, current_sum);
            int min_count = min(count_A[i], count_B[j]);
            count_A[i] -= min_count;
            count_B[j] -= min_count;
        }
        
        cout << ans << '\n';
    }
    
    return 0;
}