#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX_N = 100;
const int INF = 987654321;

int scoreRussia[MAX_N], scoreKorea[MAX_N];
bool selected[MAX_N];

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n;
        cin >> n;

        memset(selected, false, sizeof(selected));
        for (int i = 0; i < n; ++i)
            cin >> scoreRussia[i];
        for (int i = 0; i < n; ++i)
            cin >> scoreKorea[i];

        sort(scoreKorea, scoreKorea + n);

        int wins = 0, lowest = 0;
        for (int i = 0; i < n; ++i)
        {
            int diff = INF, player = -1;

            for (int j = 0; j < n; ++j)
                if (!selected[j] &&
                    scoreRussia[i] <= scoreKorea[j] &&
                    abs(scoreRussia[i] - scoreKorea[j]) < diff)
                {
                    diff = abs(scoreRussia[i] - scoreKorea[j]);
                    player = j;
                }

            if (player == -1)
            {
                selected[lowest] = true;
                lowest++;
            }
            else
            {
                selected[player] = true;
                wins++;
            }
        }

        cout << wins << endl;
    }

    return 0;
}