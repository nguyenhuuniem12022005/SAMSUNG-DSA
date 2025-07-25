// // SOLVE: https://oj.vnoi.info/problem/nuclear/editorial
// Hai nhà máy điện nguyên tử sẽ được xây dựng tại Byteland trong tương lai gần. Nhà máy điện thứ nhất có bán kính nguy hiểm là R1 và nhà máy điện thứ hai có bán kính nguy hiểm là R2. Tất cả các hộ gia đình cách nhà máy thứ nhất <= R1 km hoặc cách nhà máy thứ hai <=R2 km đều đang trong tình trạng nguy hiểm. Các gia đình nằm trong khu vực nguy hiểm này sẽ bắt buộc phải di chuyển chỗ ở.

// Hai nhà máy sẽ được xây dựng cũng như các hộ gia đình đều nằm trên mặt phẳng với hệ tọa độ Descartes vuông góc Oxy , trong đó khoảng cách giữa hai điểm (x1, y1) và (x2, y2) được tính theo công thức: sqrt((x1 – x2 )^2 + (y1 – y2 )^2).

// Nhiều phương án xây dựng được đưa ra với kích thước 2 nhà máy là khác nhau, gọi thông số bán kính nguy hiểm của hai nhà máy lần lượt là (R1, R2). Nhiệm vụ của bạn là xác định số lượng gia đình bắt buộc phải chuyển chỗ ở ứng với mỗi phương án.

// Input

// Dòng đầu tiên chứa số nguyên dương N là số hộ gia đình (1 <= N <= 200 000)
// N dòng tiếp, mỗi dòng chứa hai số nguyên là tọa độ (x[i], y[i]) của một hộ gia đình
// Dòng N+2 chứa 5 số nguyên ax, ay, bx, by và Q, lần lượt là tọa độ của nhà máy thứ nhất (ax, ay), tọa độ của nhà máy thứ hai (bx, by) và số lượng phương án Q (Q <= 200 000).
// Q dòng tiếp theo, dòng thứ j chứa hai số nguyên R1, R2 lần lượt là bán kính nguy hiểm của nhà máy thứ nhất và bán kính nguy hiểm của nhà máy thứ hai trong phương án thứ j.
// Tất cả tọa độ là số nguyên không âm và không lớn hơn 10^5.
// Output

// In ra Q dòng, dòng thứ j ghi một số nguyên duy nhất là số hộ gia đình buộc phải di chuyển chỗ ở nếu đề án thứ j được thực hiện.
// Test ví dụ:

// Input



// 11

// 95 75

// 27 6

// 93 5

// 124 13

// 34 49

// 65 61

// 81 49

// 77 33

// 110 50

// 91 22

// 110 25

// 57 42 97 36 2

// 31 25

// 25 25

 // Output

// 7

// 7

 #include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

#define sqr(x) 1LL*(x)*(x)
#define REP(i,n) for(int i = 0, _n = (n); i < _n; ++i)
#define TR(v,it) for(__typeof((v).begin()) it = (v).begin(), _e = (v).end(); it != _e; ++it)
typedef long long LL;
const static int MAX = (int)(2e5) + 1;

class FenwickTree {
    int t[MAX+1];

    public:
    FenwickTree() {
        fill(t,t+MAX,0);
    }

    void add(int idx, int v){
        for(; idx<=MAX; idx+=(idx+1)&-(idx+1)) t[idx]+=v;
    }

    int sum(int idx){
        int r=0;
        for(;idx>=0; idx-=(idx+1)&-(idx+1)) r+=t[idx];
        return r;
    }
};

class CPoint {
    public:
    int x, y, id; //x: k/c toi nha may 1, y: k/c toi nha may 2
    CPoint(int _x, int _y, int _id): x(_x), y(_y), id(_id) {}
    inline bool operator < (const CPoint & o) const {
        return y < o.y || y == o.y && x < o.x || y == o.y && x == o.x && id < o.id;
    }
};

int distance( int x, int y, int a, int b ) {
    LL d = sqr(x-a) + sqr(y-b);
    int res = (int) floor(sqrt(d));
    return sqr(res) < d ? res+1 : res;
}

int countX[MAX+1], countY[MAX+1], n, q, ax, bx, ay, by, answer[MAX];
vector<CPoint> a;
FenwickTree bit;

void enter() { //Enter and Pre-process
    scanf("%d",&n); 
    REP(i,n) { int x, y; scanf("%d%d",&x,&y); a.push_back(CPoint(x,y,0)); }
    scanf("%d%d%d%d%d",&ax,&ay,&bx,&by,&q);
    TR(a,it) {
        int tmpx = distance(it->x, it->y, ax, ay),
            tmpy = distance(it->x, it->y, bx, by);
        if((it->x = tmpx) <= MAX) ++countX[tmpx];
        if((it->y = tmpy) <= MAX) ++countY[tmpy];
    }
    REP(i,q) { int x,y; scanf("%d%d",&x,&y); a.push_back(CPoint(x,y,i+1)); }
    REP(i,MAX) {
        countX[i+1] += countX[i];
        countY[i+1] += countY[i];
    }
}

void solve() {
    sort(a.begin(), a.end());
    TR(a,it)
        if(it->id) answer[it->id - 1] = countX[it->x] + countY[it->y] - bit.sum(it->x);
        else bit.add(it->x, 1);
}

void print() {
    REP(i,q) printf("%d\n", answer[i]);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    enter();
    solve();
    print();
    return 0;
}
