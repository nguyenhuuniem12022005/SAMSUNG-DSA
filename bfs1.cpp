// Có một chiếc bảng hình chữ nhật với 6 miếng ghép, trên mỗi miếng ghép được điền một số nguyên trong khoảng từ 1 đến 6. Tại mỗi bước, chọn một hình vuông (bên trái hoặc bên phải), rồi quay theo chiều kim đồng hồ.

// Hình giữa --> sang phải: xoay bên phải

// Hình giữa --> sang trái: xoay bên trái

// 4 1 3   1 2 3   1 5 2
// 5 2 6   4 5 6   4 6 3

// Yêu cầu: Cho một trạng thái của bảng, hãy tính số phép biến đổi ít nhất để đưa bảng đến trạng thái đích.

// Input:

// Dòng đầu tiên chứa 6 số là trạng thái bảng ban đầu (thứ tự từ trái qua phải, dòng 1 tới dòng 2).

// Dòng thứ hai chứa 6 số là trạng thái bảng đích (thứ tự từ trái qua phải, dòng 1 tới dòng 2).

// Output: 

// In ra một số nguyên là đáp số của bài toán.

// Test ví dụ:

// Input

// Output

// 1 2 3 4 5 6

// 4 1 2 6 5 3

 
// OUTPUT
// 2


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

vector<int> rotate_left(const vector<int>& state) {
    vector<int> next_state = state;
    next_state[0] = state[3];
    next_state[1] = state[0];
    next_state[3] = state[4];
    next_state[4] = state[1];
    return next_state;
}

vector<int> rotate_right(const vector<int>& state) {
    vector<int> next_state = state;
    next_state[1] = state[4];
    next_state[2] = state[1];
    next_state[4] = state[5];
    next_state[5] = state[2];
    return next_state;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> start_state(6);
    vector<int> target_state(6);

    for (int i = 0; i < 6; ++i) {
        cin >> start_state[i];
    }
    for (int i = 0; i < 6; ++i) {
        cin >> target_state[i];
    }

    if (start_state == target_state) {
        cout << 0 << endl;
        return 0;
    }

    queue<pair<vector<int>, int>> q;
    set<vector<int>> visited;

    q.push({start_state, 0});
    visited.insert(start_state);

    while (!q.empty()) {
        pair<vector<int>, int> current = q.front();
        q.pop();

        vector<int> current_state = current.first;
        int current_dist = current.second;

        vector<int> next_state_left = rotate_left(current_state);
        if (next_state_left == target_state) {
            cout << current_dist + 1 << endl;
            return 0;
        }
        if (visited.find(next_state_left) == visited.end()) {
            visited.insert(next_state_left);
            q.push({next_state_left, current_dist + 1});
        }

        vector<int> next_state_right = rotate_right(current_state);
        if (next_state_right == target_state) {
            cout << current_dist + 1 << endl;
            return 0;
        }
        if (visited.find(next_state_right) == visited.end()) {
            visited.insert(next_state_right);
            q.push({next_state_right, current_dist + 1});
        }
    }

    return 0;
}
