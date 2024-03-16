#include <iostream>
#include <climits>
#include <vector>
using namespace std;

int main() { 
    int N;
    int K;
    cin >> N;
    cin >> K;
    vector<int> list_of_prices;
    int profit[K+1];
    int prev[K+1];

    for (int i=0; i<K+1; i++) { 
        profit[i] = 0;
        prev[i] = INT_MIN;
    }

    for (int i=0; i<N; i++) {
        int price;
        cin >> price;
        list_of_prices.push_back(price);
    }

    for (int i=0; i<N; i++) {
        for (int j=1; j<=K; j++) {
            prev[j] = max(prev[j], profit[j-1]-list_of_prices[i]);
            profit[j] = max(profit[j], list_of_prices[i]+prev[j]);
        }
    }

    cout << profit[K] << endl;

    return 0;
}
