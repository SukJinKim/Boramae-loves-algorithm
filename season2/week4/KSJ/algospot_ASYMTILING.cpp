#include <iostream>
#include <cstring>

using namespace std;

const long long MOD = int(1e9) + 7;
const int MAX_N = 100;

int tilingCache[MAX_N + 1];

int tiling(int n)
{
    if (n <= 1)
        return 1;

    int &ret = tilingCache[n];
    if (ret != -1)
        return ret;

    return ret = (tiling(n - 1) % MOD + tiling(n - 2) % MOD) % MOD;
}

int asymmetric(int n)
{
    if (n % 2 == 1)
        return (tiling(n) - tiling(n / 2) + MOD) % MOD;

    int ret = tiling(n);
    ret = (ret - tiling(n / 2) + MOD) % MOD;
    ret = (ret - tiling(n / 2 - 1) + MOD) % MOD;
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

        memset(tilingCache, -1, sizeof(tilingCache));
        cout << asymmetric(n) << endl;
    }

    return 0;
}