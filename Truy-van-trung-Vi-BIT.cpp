#include <iostream>
#include <vector>
#include <string>
#include <ios>
const int MAX_VAL = 1000001;
std::vector<int> bit(MAX_VAL, 0);
long long total_count = 0;
void update(int index, int delta) {
    for (; index < MAX_VAL; index += index & -index) {
        bit[index] += delta;
    }
}

/**
 *  Tìm phần tử nhỏ nhất thứ k trong dãy.
 * Kỹ thuật "đi trên cây" (binary lifting).
 *  Giá trị của phần tử trung vị.
 */
int find_kth(int k) {
    int median_val = 0;
    // Bắt đầu từ lũy thừa lớn nhất của 2 nhỏ hơn MAX_VAL
    int p_of_2 = 1;
    while ((p_of_2 << 1) < MAX_VAL) {
        p_of_2 <<= 1;
    }

    // "Đi" từ bit cao xuống bit thấp
    for (; p_of_2 > 0; p_of_2 >>= 1) {
        // Nếu có thể "nhảy" một bước p_of_2 mà không vượt quá k
        if (median_val + p_of_2 < MAX_VAL && bit[median_val + p_of_2] < k) {
            // Thực hiện bước nhảy
            k -= bit[median_val + p_of_2];
            median_val += p_of_2;
        }
    }
    return median_val + 1;
}

int main() {
    // Tối ưu hóa nhập xuất
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int Q;
    std::cin >> Q;

    std::string command;
    int x;

    while (Q--) {
        std::cin >> command;
        if (command[0] == 'a') { // add
            std::cin >> x;
            update(x, 1);
            total_count++;
        } else if (command[0] == 'd') { // del
            std::cin >> x;
            update(x, -1);
            total_count--;
        } else { // print
            if (total_count == 0) {
                // Có thể đề bài không cho trường hợp này, nhưng xử lý cho chắc chắn
                // Hoặc in ra thông báo lỗi tùy yêu cầu
            } else {
                int k = (total_count + 1) / 2;
                std::cout << find_kth(k) << "\n";
            }
        }
    }

    return 0;
}