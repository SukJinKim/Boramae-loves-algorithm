#include <cstdio>
#include <cstring>

#define MAX_N 10

bool isFriend[MAX_N][MAX_N];
bool included[MAX_N];

int countAllFriendsCases(int n, int start)
{
    bool finished = true;
    for (int i = 0; i < n; ++i)
        if (!included[i])
        {
            finished = false;
            break;
        }

    if (finished)
    {
        return 1;
    }

    int ans = 0;
    for (int i = start; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (!included[i] && !included[j] && isFriend[i][j])
            {

                included[i] = included[j] = true;
                ans += countAllFriendsCases(n, i + 1);
                included[i] = included[j] = false;
            }

    return ans;
}

int main()
{
    int c;
    scanf("%d", &c);

    for (int i = 0; i < c; ++i)
    {
        int ans = 0, n, m;
        scanf("%d %d", &n, &m);

        memset(isFriend, false, sizeof(isFriend));
        memset(included, false, sizeof(included));

        for (int j = 0; j < m; ++j)
        {
            int frd1, frd2;
            scanf("%d %d", &frd1, &frd2);
            isFriend[frd1][frd2] = isFriend[frd2][frd1] = true;
        }

        ans = countAllFriendsCases(n, 0);

        printf("%d\n", ans);
    }
}