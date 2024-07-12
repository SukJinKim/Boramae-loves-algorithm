#include <vector>
#include <set>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 100;
const int MAX_P = 10;
const int INF = 987654321;

int cache[MAX_N][MAX_P];

vector<int> seq;
int n, s;

// seq[left, right)의 최소 SSE(Sum Square Error) 반환
int SSE(int left, int right)
{
    double sum = 0, len = right - left;
    for (int i = left; i < right; ++i)
        sum += seq[i];

    int avg = (int)round(sum / len);
    int sse = 0;

    for (int i = left; i < right; ++i)
        sse += pow((avg - seq[i]), 2);

    return sse;
}

// seq[left...]를 p개의 부분 수열로 나눈 뒤 각 부분 수열의 SSE를 합한 최솟값 반환
int quantize(int left, int p)
{
    int &ret = cache[left][p];

    if (ret != -1)
        return ret;

    // BASE CASE : 더이상 나눌 필요가 없는 경우 SSE(left, n) 반환
    if (p == 1)
        return ret = SSE(left, n);

    ret = INF;
    for (int right = left + 1; right + (p - 1) <= n; ++right)
        ret = min(ret, SSE(left, right) + quantize(right, p - 1));

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> s;

        seq.assign(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> seq[i];

        sort(seq.begin(), seq.end());

        set<int> uniques(seq.begin(), seq.end());
        int nUnique = uniques.size();

        int p = min(nUnique, s);
        memset(cache, -1, sizeof(cache));
        cout << quantize(0, p) << endl;
    }

    return 0;
}