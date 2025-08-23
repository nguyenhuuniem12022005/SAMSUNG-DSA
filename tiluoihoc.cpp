#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;
void solve(){
    int n;
    cin>>n;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin>> a[i];
    double max_tb=-1.0;
    vector<int> best_k;
    long long sum_suffix=a[n-1];
    long long suffix_min=a[n-1];
    for (int k=n-2;k>=1;k--){
        sum_suffix +=a[k];
        suffix_min = min(suffix_min,a[k]);
        double cur_tb = (double)(sum_suffix-suffix_min)/(n-k-1);
        if(cur_tb>max_tb){
            max_tb=cur_tb;
            best_k.clear();
            best_k.push_back(k);
        }else if(abs(cur_tb-max_tb)<1e-9){
            best_k.push_back(k);
        }
    }
    sort(best_k.begin(),best_k.end());
     for (size_t i = 0; i < best_k.size(); ++i) {
        std::cout << best_k[i] << (i == best_k.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    solve();

    return 0;
}
