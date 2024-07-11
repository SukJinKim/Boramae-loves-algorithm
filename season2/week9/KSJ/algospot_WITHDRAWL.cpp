#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000;

int r[N], c[N];
int n, k;

// 누적 등수가 acc 이하가 되도록 할 수 있는가
bool canRank(double acc)
{
    vector<double> v;
    for (int i = 0; i < n; ++i)
        v.push_back(acc * c[i] - r[i]);

    sort(v.begin(), v.end());

    double sum = 0;
    for (int i = n - k; i < n; ++i)
        sum += v[i];

    return 0 <= sum;
}

// 최소 누적 등수 출력
double solve()
{
    // 최소 누적 등수의 가능 범위 : [lo, hi)
    double lo = 0, hi = 1 + 0.1;
    int nIter = 100;

    for (int it = 0; it < nIter; ++it)
    {
        double mid = (lo + hi) / 2;

        if (canRank(mid))
            hi = mid;
        else
            lo = mid;
    }

    return hi;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        cin >> n >> k;

        for (int i = 0; i < n; ++i)
            cin >> r[i] >> c[i];

        double ans = solve();
        cout.precision(9);
        cout << ans << endl;
    }

    return 0;
}