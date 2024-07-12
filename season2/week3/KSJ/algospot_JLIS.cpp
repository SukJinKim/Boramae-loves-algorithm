#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;

int n, m;
int A[MAX_N], B[MAX_M];
int cache[MAX_N + 1][MAX_M + 1];

const long long NEGINF = numeric_limits<long long>::min();

/**
 * A[aIdx...]와 B[bIdx...]로부터 만들 수 있는 합친 증가 부분 수열의 최대 길이 반환
 * jlis(aIdx, bIdx)로부터 만들어질 가장 긴 합친 증가 부분 수열은 반드시 A[aIdx]와 B[bIdx]를 포함(A[aIdx] != B[bIdx])
 * */
int jlis(int aIdx, int bIdx)
{
    int &ret = cache[aIdx + 1][bIdx + 1];
    if (ret != -1)
        return ret;

    long long a = (aIdx == -1) ? NEGINF : A[aIdx];
    long long b = (bIdx == -1) ? NEGINF : B[bIdx];
    long long maxValue = max(a, b);

    ret = 2;
    for (int nextA = aIdx + 1; nextA < n; ++nextA)
        if (maxValue < A[nextA])
            ret = max(ret, 1 + jlis(nextA, bIdx));

    for (int nextB = bIdx + 1; nextB < m; ++nextB)
        if (maxValue < B[nextB])
            ret = max(ret, 1 + jlis(aIdx, nextB));

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> m;
        for (int i = 0; i < n; ++i)
            cin >> A[i];
        for (int i = 0; i < m; ++i)
            cin >> B[i];

        memset(cache, -1, sizeof(cache));
        cout << jlis(-1, -1) - 2 << endl; // jlis에 포함된 2개의 NEGINF는 제외
    }

    return 0;
}