#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = 1000000;
int lookup[MAX][21];  

void buildSparseTable(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        lookup[i][0] = arr[i];
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {
            lookup[i][j] = min(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int L, int R) {
    int j = (int)log2(R - L + 1);
    return min(lookup[L][j], lookup[R - (1 << j) + 1][j]);
}

int main() {
    int n, m;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    buildSparseTable(arr, n);

    cin >> m;
    long long ans = 0;

    while (m--) {
        int u, v;
        cin >> u >> v;
        ans += query(u, v);  
    }

    cout << ans << endl;

    return 0;
}
