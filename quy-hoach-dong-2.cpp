// Alice có một mảnh giấy hình chữ nhật có cạnh dọc và ngang tương ứng là a và b  đơn vị. Mảnh giấy được chia thành a x b  ô vuông đơn vị, chiều dọc chia thành a hàng, các hàng được được đánh số từ 1  đến a  từ trên xuống dưới, chiều ngang được chia thành b  cột từ 1  đến b  từ trái sang phải. Ô nằm giao giữa hàng i và cột j  được gọi là ô (i.j) Có c  ô vuông của mảnh giấy đã được tô màu. Với cặp số (d,e) , Alice muốn chọn một hình vuông trên mảnh giấy ban đầu và cắt mảnh giấy hình vuông này từ mảnh giấy ban đầu thỏa mãn điều kiện sau:

// Mảnh giấy chứa nguyên các ô vuông của mảnh giấy ban đầu;
// Mảnh giấy có cạnh chia hết cho d ;
// Mảnh giấy có không quá e ô đã tô màu.
// Yêu cầu: Cho thông tin về mảnh giấy ban đầu và cặp số  (d,e) hãy tìm phương án cắt hình vuông thỏa mãn các điều kiện trên mà có cạnh lớn nhất.

// Input:

// Dòng đầu chứa năm số nguyên a,b,c,d,e ;
// Dòng thứ k  trong c  dòng tiếp theo chứa hai số nguyên   mô tả ô đã tô màu.
// Output: Ghi ra một số nguyên là độ dài cạnh hình vuông lớn nhất tìm được.

// Ràng buộc:

// Có 30% số test ứng với 30% số điểm của bài có zEYaDAKAAAAAElFTkSuQmCC
// Có 30% số test khác ứng với 30% số điểm của bài có AH0EAfuM5ht+AAAAAElFTkSuQmCC
// Có 20% số test khác ứng với 20% số điểm của bài có EfUDMbTL6cA6hXthR9V07HBjv6nHHvht8R9AoEUX0WaxJFMAAAAAElFTkSuQmCC  và 6uLSwY6x+W6AAAAAElFTkSuQmCC
// Có 20% số test còn lại ứng với 20% số điểm của bài có 6n2DzRV1pahoyJ0AAAAAElFTkSuQmCC  và QXH3K+VliaQ2QAAAABJRU5ErkJggg== .

#include <bits/stdc++.h>
#define endl "\n"
#define int long long

using namespace std;

int a, b, c, d, e;
int sum[6005][6005]; 

bool is_valid(int m) {
    for(int i = 1; i <= a - m + 1; i++) {
        for(int j = 1; j <= b - m + 1; j++) {
            if (sum[i + m - 1][j + m - 1] - sum[i + m - 1][j - 1] - sum[i - 1][j + m - 1] + sum[i - 1][j - 1] <= e) 
                return true;
        }
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> a >> b >> c >> d >> e;
    for(int i = 1; i <= c; i++) {
        int x, y; cin >> x >> y;
        sum[x][y] = 1;
    }

    for(int i = 1; i <= a; i++) {
        for(int j = 1; j <= b; j++) {
            sum[i][j] = sum[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }
    }

    int l = 0, r = min(a, b) / d;
    int res = 0;

    while(l <= r) {
        int m = (l + r) / 2;

        if (is_valid(m * d)) {
            res = m * d;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << res << endl;
    return 0;
}