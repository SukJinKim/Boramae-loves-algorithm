#include <cstdio>
#include <algorithm>

#define MAX_N 20000

using namespace std;

int h[MAX_N];

int solve(int left, int right) // [left...right]
{
    if (left == right)
        return h[left];

    int mid = left + (right - left) / 2;
    int ret = max(solve(left, mid), solve(mid + 1, right));
    int lo = mid, hi = mid + 1;
    int height = min(h[lo], h[hi]);
    ret = max(ret, height * 2);

    while (left < lo || hi < right)
    {
        if (hi < right && (lo == left || h[lo - 1] < h[hi + 1]))
        {
            ++hi;
            height = min(height, h[hi]);
        }
        else
        {
            --lo;
            height = min(height, h[lo]);
        }

        ret = max(ret, height * (hi - lo + 1));
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
            scanf("%d", &h[i]);

        int ans = solve(0, N - 1);
        printf("%d\n", ans);
    }
}