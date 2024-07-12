#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

long long createRawSignal(long long prevRawSignal)
{
    return (prevRawSignal * 214013 + 2531011) % (long long)pow(2, 32);
}

int analyze(int k, int n)
{
    int ret = 0;
    long long sum = 0;
    queue<long long> q;

    // A[0] = 1983
    long long prevRawSignal = 1983;
    for (int i = 1; i <= n; ++i)
    {
        long long rawSignal = createRawSignal(prevRawSignal);
        long long signal = (prevRawSignal % 10000) + 1;

        q.push(signal);
        sum += signal;

        prevRawSignal = rawSignal;

        while (sum >= k)
        {
            if (sum == k)
                ret++;

            sum -= q.front();
            q.pop();
        }
    }

    return ret;
}

int main()
{
    int c, n, k;
    cin >> c;

    while (c--)
    {
        cin >> k >> n;
        cout << analyze(k, n) << endl;
    }
}