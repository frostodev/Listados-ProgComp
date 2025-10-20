#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string p;
        int n;
        string arr;
        cin >> p >> n >> arr;

        deque<int> dq;
        string num;
        for (int i = 0; i < (int)arr.size(); i++) {
            if (isdigit(arr[i])) {
                num += arr[i];
            } else {
                if (!num.empty()) {
                    dq.push_back(stoi(num));
                    num.clear();
                }
            }
        }

        bool rev = false, error = false;
        for (char c : p) {
            if (c == 'R') {
                rev = !rev;
            } else if (c == 'D') {
                if (dq.empty()) {
                    error = true;
                    break;
                }
                if (!rev) dq.pop_front();
                else dq.pop_back();
            }
        }

        if (error) {
            cout << "error\n";
            continue;
        }

        cout << "[";
        if (!dq.empty()) {
            if (!rev) {
                for (size_t i = 0; i < dq.size(); i++) {
                    if (i) cout << ",";
                    cout << dq[i];
                }
            } else {
                for (size_t i = dq.size(); i-- > 0;) {
                    if (i != dq.size() - 1) cout << ",";
                    cout << dq[i];
                }
            }
        }
        cout << "]\n";
    }
    return 0;
}
