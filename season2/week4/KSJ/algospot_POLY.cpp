#include <iostream>
#include <cstring>

using namespace std;

const int MOD = int(1e7);
const int MAX_N = 100;

int cache[MAX_N + 1][MAX_N + 1];

// poly[nCurr][nRemain] = 전체 nRemain개의 남은 정사각형 중 현재 층에 nCurr개의 정사각형을 위치시킬 때 만들 수 있는 폴리오미노의 수
int poly(int nCurr, int nRemain)
{
    // BASE CASE : 현재 층에 남은 모든 정사각형을 위치시킬 때 만들 수 있는 폴리오미노의 수는 오직 한 개
    if (nCurr == nRemain)
        return 1;

    int &ret = cache[nCurr][nRemain];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int nNext = 1; nNext <= nRemain - nCurr; ++nNext)
    {
        // 현재 층과 다음 층에 위치한 정사각형들이 서로 맞닿을 수 있는 경우의 수
        int nTouch = nCurr + nNext - 1;
        // 현재 층과 다음 층에 각각 nCurrent, nNext개의 정사각형들을 위치시킬때 만들 수 있는 모든 폴리오미노의 수
        int nextPoly = ((nTouch % MOD) * (poly(nNext, nRemain - nCurr) % MOD)) % MOD;
        ret = (ret % MOD + nextPoly % MOD) % MOD;
    }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {

        int n;
        cin >> n;
        memset(cache, -1, sizeof(cache));

        int ans = 0;
        for (int i = 1; i <= n; ++i)
            ans = (ans % MOD + poly(i, n) % MOD) % MOD;

        cout << ans << endl;
    }
    return 0;
}