#include <iostream>

using namespace std;

int n;
long long A[1000001];
long long B, C;
long long ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i =0; i <n; i++) {
        cin >> A[i];
    }
    cin >> B >> C;
    
    for (int i =0; i < n; i++) {
        long long last = A[i] - B;
        if ( last > 0 ) {
            ans += (last + C - 1)/C;
        }
        ans++;
    }
    
    cout << ans;

    return 0;
}