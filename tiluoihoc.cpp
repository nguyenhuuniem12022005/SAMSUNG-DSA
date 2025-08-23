
// Bài tập lớn môn CTDL&GT gồm có N bài tập nhỏ hơn. Sau nhận được đáp án, các bạn sinh viên có thể tự tính điểm của mình cho từng bài tập. Giáo viên bộ môn khá ưu ái cho lớp, nên đã cho phép các bạn sinh viên loại đi 1 bài tập có điểm thấp nhất, sau đó tính điểm trung bình của N – 1 bài tập còn lại. Các sinh viên cũng cần phải nộp bài viết giấy để giáo viên kiểm tra.

// Tí là một sinh viên lười học. Biết rằng điểm trung bình của mình sẽ thấp, Tí đã nói dối giáo viên bộ môn rằng bài làm của K bài đầu tiên của mình đã bị mất, do đứa em trai nghịch ngợm bé bóng đã xé mất chúng trong tệp bài làm của mình. Thầy giáo mới về trường công tác, còn trẻ người non dạ nên đã tin lời nói của Tí, cho phép Tí tính điểm tập lớn giống như các bạn khác sau khi không xem xét K bài làm đã bị mất.

// Tí băn khoăn nếu đã nói dối như vậy thì cần tìm cách để đạt điểm càng cao càng tốt. Các bạn hãy giúp Tí tìm một chiến lược để có thể đạt được điểm bài tập lớn là cao nhất có thể?

// Input:  Dòng đầu tiên chứa hai số nguyên N.  Dòng tiếp theo chứa N số nguyên A[i] (0 ≤ A[i] ≤ 100000) là điểm của Tí cho từng bài tập.

// Output:  In ra các giá trị K sao cho sau khi xóa bỏ điểm của K bài tập đầu tiên, điểm trung bình của các bài tập còn lại là lớn nhất có thể. Nếu có nhiều đáp án, in ra theo thứ tự tăng dần, mỗi số cách nhau một dấu cách..

// Chú ý : 1 ≤ K ≤ N-2.

// Giới hạn:

// Subtask 1 (40%): 3 ≤ N ≤ 5000

// Subtask 2 (60%): 3 ≤ N ≤ 100000.

// Test ví dụ:

// Input
// 5
// 4 1 10 3 8

//output
// 2


// Giải thích test ví dụ:

// Với K = 1, dãy số còn lại là 1 10 3 8. Xóa đi phần tử 1, điểm trung bình là (10+3+8)/3 = 7

// Với K = 2, dãy số còn lại là 10 3 8. Xóa đi phần tử 3, điểm trung bình còn lại là (10+8)/2 = 9

// Với K = 3, dãy số còn lại là 3 8. Xóa đi phần tử 3, điểm trung bình còn lại là (8)/1 = 8.#include <iostream>
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
        cout << best_k[i] << (i == best_k.size() - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
