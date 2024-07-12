#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

const char linked[SWITCHES][CLOCKS + 1] = {
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",

    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",

    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",

    "...xxx...x...x..",
};

bool areAligned(vector<int> &clocks)
{
    return all_of(clocks.cbegin(), clocks.cend(),
                  [](int i)
                  { return i == 12; });
}

void push(vector<int> &clocks, int switchId)
{
    for (int clock = 0; clock < CLOCKS; ++clock)
    {
        if (linked[switchId][clock] == 'x')
        {
            clocks[clock] += 3;
            if (clocks[clock] == 15)
                clocks[clock] = 3;
        }
    }
}

int countNumPush(vector<int> &clocks, int switchId)
{
    if (switchId == SWITCHES)
        return areAligned(clocks) ? 0 : INF;

    int ret = INF;
    for (int cnt = 0; cnt < 4; ++cnt)
    {
        ret = min(ret, cnt + countNumPush(clocks, switchId + 1));
        push(clocks, switchId);
    }

    return ret;
}

int main()
{
    int c;
    scanf("%d", &c);

    while (c--)
    {
        int ans, clockState;
        vector<int> clocks;

        for (int i = 0; i < CLOCKS; ++i)
        {
            scanf("%d", &clockState);
            clocks.push_back(clockState);
        }

        ans = countNumPush(clocks, 0);
        if (ans == INF)
            ans = -1;
        printf("%d\n", ans);
    }

    return 0;
}