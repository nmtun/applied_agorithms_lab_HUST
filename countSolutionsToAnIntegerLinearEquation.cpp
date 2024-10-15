#include <bits/stdc++.h>

using namespace std;

int a[100000];

int countSolutions(int a[], int n, int m, int sum = 0, int index = 0) {
    if (index == n) {
        return (sum == m) ? 1 : 0;
    }

    int count = 0;

    for (int x = 1; sum + a[index] * x <= m; ++x) {
        count += countSolutions(a, n, m, sum + a[index] * x, index + 1);
    }

    return count;
}

int main() {
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    cout << countSolutions(a, n, m);

    return 0;
}
