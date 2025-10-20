#include <bits/stdc++.h>
using namespace std;

struct Order {
    int price, qty;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        // min-heap para sells (ask)
        multiset<pair<int,int>> asks; 
        // max-heap para buys (bid)
        multiset<pair<int,int>, greater<>> bids;

        int stock_price = -1;

        for (int i = 0; i < n; i++) {
            string type;
            int qty, price;
            string tmp;
            cin >> type >> qty >> tmp >> tmp >> price;

            if (type == "buy") {
                bids.insert({price, qty});
            } else {
                asks.insert({price, qty});
            }

            // matching
            while (!asks.empty() && !bids.empty() && bids.begin()->first >= asks.begin()->first) {
                auto [askPrice, askQty] = *asks.begin();
                auto [bidPrice, bidQty] = *bids.begin();
                int trade = min(askQty, bidQty);

                stock_price = askPrice; // transa al precio del vendedor

                asks.erase(asks.begin());
                bids.erase(bids.begin());

                if (askQty > trade) asks.insert({askPrice, askQty - trade});
                if (bidQty > trade) bids.insert({bidPrice, bidQty - trade});
            }

            // imprimir estado
            if (!asks.empty()) cout << asks.begin()->first << " ";
            else cout << "- ";

            if (!bids.empty()) cout << bids.begin()->first << " ";
            else cout << "- ";

            if (stock_price != -1) cout << stock_price << "\n";
            else cout << "-\n";
        }
    }
    return 0;
}
