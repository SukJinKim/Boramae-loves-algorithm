#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_N = 50;
const int MAX_D = 100;

// adj[i][j] : i번 마을과 j번 마을의 연결여부
int adj[MAX_N][MAX_N];
// moveProb[src][dest] : src번 마을에서 dest번 마을로 이동할 확률
double moveProb[MAX_N][MAX_N];
// cache[d][n] : d일 후 n번 마을에 있을 확률
double cache[MAX_D + 1][MAX_N];

int prison, nVillage;

double hide(int d, int dest)
{
    // BASE CASE : 0일은 prison에서 dest번 마을로 이동할 확률 반환
    if (d == 1)
        return moveProb[prison][dest];

    double &ret = cache[d][dest];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int src = 0; src < nVillage; ++src)
        if (adj[src][dest])
            ret += hide(d - 1, src) * moveProb[src][dest];

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n, d, p;
        cin >> n >> d >> p;
        prison = p, nVillage = n;

        // init adj
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> adj[i][j];

        // init moveProb
        for (int src = 0; src < n; ++src)
        {
            double denominator = 0;
            for (int v = 0; v < n; ++v)
                if (adj[src][v])
                    denominator += 1;

            for (int dest = 0; dest < n; ++dest)
            {
                double numerator = adj[src][dest];
                moveProb[src][dest] = numerator / denominator;
            }
        }

        // init cache
        for (int i = 0; i <= MAX_D; ++i)
            for (int j = 0; j < MAX_N; ++j)
                cache[i][j] = -1.0;

        int t;
        cin >> t;
        for (int i = 0; i < t; ++i)
        {
            int dest;
            cin >> dest;

            cout << setprecision(10) << hide(d, dest) << ' ';
        }
        cout << endl;
    }

    return 0;
}