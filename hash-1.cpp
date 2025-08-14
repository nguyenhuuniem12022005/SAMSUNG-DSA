// Cho xâu A và B chỉ gồm các chữ cái thường. Hãy tìm các vị trí xuất hiện của xâu B trong xâu A?

// Input:

// Input gồm 2 dòng. Dòng thứ nhất chứa xâu A, dòng thứ 2 chứa xâu B. Độ dài 2 xâu không vượt quá 10^6.

// Output: 

// In ra lần lượt các vị trí xuất hiện của xâu B. Chỉ số đánh dấu bắt đầu từ 1.

// Test ví dụ:

// Input:
// aaaaa
// aa

// out
// 1 2 3 4

// input
// abcde
// bc
 
// out
// 2

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

#define FOR(i,a,b) for(int i=a; i<=b; i++)
#define base 1000000003LL
#define ll long long
#define maxn 1000111
using namespace std;

ll POW[maxn], hashT[maxn];

ll getHashT(int i, int j) {
    return (hashT[j] - hashT[i-1] * POW[j-i+1] + base * base) % base;
}

int main() {
    string T, P;
    cin >> T >> P;
    int m = T.size(), n = P.size();
    
    T = " " + T; 
    P = " " + P;
    
    POW[0] = 1;
    FOR(i, 1, m) {
        POW[i] = (POW[i-1] * 26) % base;
    }
    hashT[0]=0;
    FOR(i, 1, m) {
        hashT[i] = (hashT[i-1] * 26 + T[i] - 'a') % base;
    }
    
    ll hashP = 0;
    FOR(i, 1, n) {
        hashP = (hashP * 26 + P[i] - 'a') % base;
    }
    
    FOR(i, 1, m-n+1) {
        if (hashP == getHashT(i, i+n-1)) {
            printf("%d ", i);
        }
    }
    return 0;
}