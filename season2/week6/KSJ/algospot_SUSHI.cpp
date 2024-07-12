#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 20;
const int MAX_PRICE = 200;

int prices[MAX_N];
int prefs[MAX_N];
int cache[MAX_PRICE + 1];

int n, m;

// 주어진 예산 안에서 가장 큰 선호도의 합
int solve()
{
    int ret = 0;
    cache[0] = 0;
    for (int budget = 1; budget <= m; ++budget)
    {
        int &pref = cache[budget % (MAX_PRICE + 1)];

        for (int sushi = 0; sushi < n; ++sushi)
            if (budget >= prices[sushi])
                pref = max(pref,
                           prefs[sushi] + cache[(budget - prices[sushi]) % (MAX_PRICE + 1)]);

        ret = max(ret, pref);
    }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> m;
        m = m / 100;

        for (int i = 0; i < n; ++i)
        {
            int price;
            cin >> price;
            prices[i] = price / 100;

            cin >> prefs[i];
        }

        memset(cache, 0, sizeof(cache));
        cout << solve() << endl;
    }
    return 0;
}