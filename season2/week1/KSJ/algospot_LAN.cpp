#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

const int MAX_V = 500;
const double INF = 987654321;

vector<pair<int, double>> adj[MAX_V];

// 최소 스패닝 트리의 가중치 합 반환
double prim(int V)
{
    vector<bool> added(V, false);
    vector<double> minWeight(V, INF);

    double ret = 0.0;
    minWeight[0] = 0.0;
    for (int iter = 0; iter < V; ++iter)
    {
        // 가장 가중치가 작은 정점 선택
        int u = -1;
        for (int v = 0; v < V; ++v)
            if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
                u = v;

        ret += minWeight[u];
        added[u] = true;

        // 인접한 간선들 검사
        for (int i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            double weight = adj[u][i].second;

            if (!added[v] && minWeight[v] > weight)
                minWeight[v] = weight;
        }
    }
    return ret;
}

int main()
{
    int C;
    scanf("%d", &C);

    while (C--)
    {
        int N, M;
        scanf("%d %d", &N, &M);

        int x[MAX_V], y[MAX_V];
        for (int i = 0; i < N; ++i)
            scanf("%d", &x[i]);
        for (int i = 0; i < N; ++i)
            scanf("%d", &y[i]);

        // 모든 정점에 대하여 가중치(유클리드 거리) 계산
        for (int u = 0; u < N; ++u)
            for (int v = u + 1; v < N; ++v)
            {
                int ux = x[u], uy = y[u];
                int vx = x[v], vy = y[v];
                double dist = sqrt(pow(ux - vx, 2) + pow(uy - vy, 2));

                adj[u].push_back(make_pair(v, dist));
                adj[v].push_back(make_pair(u, dist));
            }

        // 이미 만들어진 간선에 대하여 가중치 0 부여
        for (int i = 0; i < M; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);

            adj[u].push_back(make_pair(v, 0.0));
            adj[v].push_back(make_pair(u, 0.0));
        }

        double ans = 0.0;
        ans = prim(N);
        printf("%lf\n", ans);

        for (int i = 0; i < N; ++i)
            adj[i].clear();
    }

    return 0;
}