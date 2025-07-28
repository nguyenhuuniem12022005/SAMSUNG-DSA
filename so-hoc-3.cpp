// Tìm số nguyên M lớn nhất sao cho N! chia hết cho K^M.

// Input:

// Dòng đầu tiên là số lượng bộ test T (T <= 100).

// Mỗi test gồm 2 số nguyên dương N và K (N <= 10^18, K <= 10^12).

// Output: 

// In ra số nguyên M tìm được.

// Example:            

// Input



// 2

// 5 2

// 10 10

// Output
// 3

// 2

#include<bits/stdc++.h>
using namespace std;
long long gett(long long n,long long p)
{
    long long count =0;
    while (n>0){
        n /=p;
        count += n;

    }
    return count;
}
map< long long ,int> thuasonto(long long k)
{
    map<long long ,int> fac;
    while (k %2 ==0)
    {
        fac[2]++;
        k/=2;

    }
    for (long long  i=3; i*i <=k;i+=2)
    {
        while (k%i ==0)
        {
            fac[i]++;
            k/=i;
        }
    }
    if (k>1)
    {
        fac[k]++;
    }
    return fac;
}

int main(){
    int t;
    cin >>t;
    while (t--)
    {
        long long n,k;
        cin>>n>>k;
        if (k == 1)
        {
            cout << "0\n";
            continue;
        }
        map<long long,int> kfac= thuasonto(k);
        long long minM=LLONG_MAX;
        for (auto const& pair: kfac)
        {
            long long p= pair.first;
            int m= pair.second;
            long long count = gett(n, p);
            long long m1 = count / m;
            minM = min(minM, m1);
        }
        cout << minM << "\n";
    }
    return 0;
}