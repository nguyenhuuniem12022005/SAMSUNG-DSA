#include <bits/stdc++.h>
#define endl "\n"
#define int long long
using namespace std;
signed main()
{
    int test;
    cin >> test;
    while (test--)
    {
        int n,m;
        cin>>n>>m;
        int a[n+1][m+1];
        int dp[n+1][m+1];

        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=m;j++)
            {
                cin>>a[i][j];
                dp[i][j] =a[i][j];
            }
        }

        int res=0;
        for (int i=2;i<=n;i++)
        {
            for (int j=2;j<=m;j++)
            {
                if(a[i][j] ==1)
                {
                    dp[i][j]=min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]})+1;
                    res=max(res,dp[i][j]);
                }
            }
        }
        cout<<res<<endl;
    }
    return 0;
}