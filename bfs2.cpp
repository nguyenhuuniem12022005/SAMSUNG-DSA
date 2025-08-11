#include <bits/stdc++.h>
#define endl "\n"
#define int long long
#define pii pair<int, int>

const int mod = 1e9 + 7;

using namespace std;

string left_rotate(string a) {
    string ans = a;
    ans[0] = a[3];
    ans[1] = a[0];
    ans[5] = a[1];
    ans[3] = a[7];
    ans[8] = a[5];
    ans[7] = a[8];
    return ans;
}

string right_rotate(string a) {
    string ans = a;
    ans[1] = a[4];
    ans[2] = a[1];
    ans[6] = a[2];
    ans[4] = a[8];
    ans[9] = a[6];
    ans[8] = a[9];
    return ans;
}

string rev_left_rotate(string a) {
    string ans = a;
    ans[0] = a[1];
    ans[1] = a[5];
    ans[5] = a[8];
    ans[3] = a[0];
    ans[8] = a[7];
    ans[7] = a[3];
    return ans;
}

string rev_right_rotate(string a) {
    string ans = a;
    ans[1] = a[2];
    ans[2] = a[6];
    ans[6] = a[9];
    ans[4] = a[1];
    ans[9] = a[8];
    ans[8] = a[4];
    return ans;
}

int BFS(string a, string b) {
    if (a == b) 
        return 0;

    unordered_map<string, int> mp1, mp2;
    queue<string> q1, q2;
    q1.push(a); q2.push(b);
    mp1[a] = 0; mp2[b] = 0; 
    while(!q1.empty()) {
        string cur = q1.front(); q1.pop();
        if(cur == b)
            return mp1[cur];
        if(mp1[cur] > 15)
            break;
        string l = left_rotate(cur), r = right_rotate(cur);
        
        if(mp1[l] == 0) {
            mp1[l] = mp1[cur] + 1;
            q1.push(l);
        }
        
        if(mp1[r] == 0) {
            mp1[r] = mp1[cur] + 1;
            q1.push(r);
        }
    }

    while(!q2.empty()) {
        string cur = q2.front(); q2.pop();
        
        if(mp1.count(cur))
            return mp1[cur] + mp2[cur];
        string l = rev_left_rotate(cur), r = rev_right_rotate(cur);
        
        if(mp2[l] == 0) {
            mp2[l] = mp2[cur] + 1;
            q2.push(l);
        }
        
        if(mp2[r] == 0) {
            mp2[r] = mp2[cur] + 1;
            q2.push(r);
        }
    }

    return -1;
}
 
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string a = "", b = "1238004765";
    for(int i = 0; i < 10; i++) {
        char x; cin >> x;
        a += x;
    }
    cout << BFS(a, b) << endl;
    return 0;
}