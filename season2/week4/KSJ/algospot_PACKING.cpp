#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAX_N = 100;
const int MAX_W = 1000;

string names[MAX_N + 1];
int volumes[MAX_N + 1], needs[MAX_N + 1];
int nItems;

int cache[MAX_N + 1][MAX_W + 1];

// pack(i, w) : i번째 물건을 선택할 수 있고 캐리어 용량이 w일때 가능한 최대 절박도
int pack(int i, int w)
{
    // BASE CASE : 더 이상 물건을 선택할 수 없는 경우
    if (i > nItems)
        return 0;

    int &ret = cache[i][w];
    if (ret != -1)
        return ret;

    // 선택한 경우
    if (w - volumes[i] >= 0)
        ret = max(ret, pack(i + 1, w - volumes[i]) + needs[i]);

    // 선택하지 않은 경우
    ret = max(ret, pack(i + 1, w));

    return ret;
}

// pack(i, w)가 선택한 물건을 items에 저장
void reconstruct(int i, int w, vector<string> &items)
{
    // BASE CASE : 더 이상 물건을 선택할 수 없는 경우
    if (i > nItems)
        return;

    // pack(i, w)가 i번째 물건을 선택하지 않은 경우와 같을 때 목록에 저장하지 않음
    if (pack(i, w) == pack(i + 1, w))
        reconstruct(i + 1, w, items);
    else
    {
        items.push_back(names[i]);
        reconstruct(i + 1, w - volumes[i], items);
    }
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n, w;
        cin >> n >> w;
        nItems = n;

        for (int i = 1; i <= n; ++i)
            cin >> names[i] >> volumes[i] >> needs[i];

        memset(cache, -1, sizeof(cache));
        int maxNeed = pack(1, w);

        vector<string> items;
        reconstruct(1, w, items);

        cout << maxNeed << ' ' << items.size() << endl;
        for (string item : items)
            cout << item << endl;
    }

    return 0;
}