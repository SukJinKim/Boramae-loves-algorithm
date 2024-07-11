#include <cstdio>

using namespace std;

const int N = 5000;

int L[N], M[N], G[N];
int n;
long long k;

// 시작점부터 pos까지 지나친 표지판 중 마지막으로 지나친 표지판의 순서 반환
long long getNth(int pos)
{
    long long nth = 0;

    for (int i = 0; i < n; ++i)
    {
        int first = L[i] - M[i], last = L[i], step = G[i];

        if (first <= pos && pos <= last)
            nth += (pos - first) / step + 1;
        else if (last < pos)
            nth += (last - first) / step + 1;
    }

    return nth;
}

// k번째 표지판의 위치 반환
int solve()
{
    // k번째 표지판의 위치 가능범위 : [lo, hi)
    int lo = 0, hi = 8030 * 1000 + 1;

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        long long nth = getNth(mid);

        if (nth >= k)
            hi = mid;
        else
            lo = mid + 1;
    }

    return hi;
}

int main()
{
    int c;
    scanf("%d", &c);

    while (c--)
    {
        scanf("%d %lld", &n, &k);

        for (int i = 0; i < n; ++i)
            scanf("%d %d %d", &L[i], &M[i], &G[i]);

        int ans = solve();
        printf("%d\n", ans);
    }

    return 0;
}