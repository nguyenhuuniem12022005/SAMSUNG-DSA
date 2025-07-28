// Trong toán học, nếu số nguyên a chia hết cho số nguyên d thì số d được gọi là ước của số nguyên a, a được gọi là bội của d. Trong bài toán này, với một số nguyên n, chúng ta sẽ quan tâm đến các ước của n2 thỏa mãn điều kiện: nhỏ hơn n và không phải là ước của n.

// Yêu cầu: Cho số nguyên dương m, xét số n = m × (m+1) × (m+2), hãy đếm số ước của n2 thỏa mãn điều kiện: nhỏ hơn n và không phải là ước của n.

// Input:

// Dòng đầu chứa số nguyên T là số bộ dữ liệu;

// T dòng sau, mỗi dòng chứa một số nguyên dương m.

// Output:

// Gồm T dòng, mỗi dòng là số ước của n2 thỏa mãn: nhỏ hơn n và không phải là ước của n.

 

// Test ví dụ:

// Input

// Output

// 3

// 1

// 2

// 3
// output
// 1

// 3

// 11

 

// Subtask 1: m ≤ 103; T ≤ 10;

// Subtask 2: m ≤ 106; T ≤ 10;

// Subtask 3: m ≤ 106; T ≤ 103;

// Subtask 4: m ≤ 106; T ≤ 105;

 

// Giải thích test 3: n = 60. Có 11 số là ước của 3600 nhưng không là ước của 60:

// 8, 9, 16, 18, 24, 25, 36, 40, 45, 48, 50

#include <bits/stdc++.h>
#define endl "\n"
#define int long long

using namespace std;

void solve(int m, map<int, int> &mp) {
    int res = 1;

    for(int i = 2; i * i <= m; i++) {
        if(m % i == 0) {
            while(m % i == 0) {
                mp[i]++;
                m /= i;
            }

        }
    }

    if(m != 1)
        mp[m]++;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int testCase;
    cin >> testCase;
    while(testCase--) {
        int m; cin >> m;
        map<int, int> mp;
        for(int i = m; i <= m + 2; i++) {
            solve(i, mp);
        } 
        int a = 1, b = 1;
        for(auto it : mp) {
            a *= (it.second + 1);
            b *= (it.second * 2 + 1);
        }
        // cout << endl;
        // cout << a << " " << b << endl;
        cout << b/2-a+1 << endl;
    }
    return 0;
}