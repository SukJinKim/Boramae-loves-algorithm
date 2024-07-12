#include <cstdio>
#include <algorithm>

#define MAX_N 20000

using namespace std;

int fence[MAX_N];

// [lo, hi) 에 속하는지 판별
bool inRange(int idx, int lo, int hi)
{
    return (lo <= idx) && (idx < hi);
}

int findMaxRectArea(int N)
{
    int ret = 0;
    for (int i = 0; i < N; ++i)
    {
        int minHeight = fence[i];
        int left = i - 1, right = i + 1;
        while (inRange(left, 0, N) && fence[left] >= minHeight)
            --left;
        while (inRange(right, 0, N) && fence[right] >= minHeight)
            ++right;
        int width = right - left - 1; // 범위 : (left, right)

        ret = max(minHeight * width, ret);
    }
    return ret;
}

int main()
{
    int C;
    scanf("%d", &C);
    while (C--)
    {
        int N;
        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
            scanf("%d", &fence[i]);

        int ans = findMaxRectArea(N);
        printf("%d\n", ans);
    }
}