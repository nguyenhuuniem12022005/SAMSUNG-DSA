# Cho dãy số A[] có N phần tử. Có Q truy vấn:

# Loại 1: 1 u K
# Tăng giá trị phần tử A[u] lên K đơn vị

# Lọai 2: 2 u v
# Yêu cầu in ra tổng A[u] + A[u+1] + … + A[v].

# Input

# Dòng đầu tiên là số nguyên N (1 <= N <= 100 000).
# Dòng tiếp theo gồm N số nguyên A[i] (1 <= A[i] <= 10^9).
# Tiếp theo là số lượng truy vấn Q (1 <= Q <= 100 000).
# Q dòng tiếp theo, mỗi dòng gồm một loại truy vấn.
# Giới hạn: 1 <= u <= v <= N, 1 <= K <= 10^9.
# Output

# Với mỗi truy vấn, in ra đáp án tìm được trên một dòng.
# Test ví dụ:

# Input
# 5
# 1 2 3 4 5
# 3
# 2 1 5
# 1 2 5
# 2 1 5
# Output
# 15
# 20

import sys
input = sys.stdin.readline

def solve():
    N = int(input()) 
    A = list(map(int, input().split()))
    bit = [0] * (N + 1)
    def update(idx, val):
        while idx <= N:
            bit[idx] += val
            idx += idx & (-idx)
    def query(idx):
        total_sum = 0
        while idx > 0:
            total_sum += bit[idx]
            idx -= idx & (-idx)
        return total_sum
    for i in range(N):
        update(i + 1, A[i]) 

    Q = int(input()) 
    for _ in range(Q):
        line = list(map(int, input().split()))
        query_type = line[0]

        if query_type == 1:
            u, K = line[1], line[2]
            update(u, K)
        else:
            u, v = line[1], line[2]
            result = query(v) - query(u - 1)
            sys.stdout.write(str(result) + "\n") 


solve()