#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

const int MAX_V = 1000;
const int INF = numeric_limits<int>::max();

// adj[i] : (i번 정점과 연결된 정점의 번호, 가중치) 저장
vector<pair<int, int>> adj[MAX_V + 1];

vector<int> dijkstra(int src, int V)
{
    vector<int> dist(V + 1, INF);
    dist[src] = 0;
    // (src까지의 거리, 정점의 번호) 저장
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, src));

    while (!pq.empty())
    {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if (dist[here] < cost)
            continue;

        for (int i = 0; i < adj[here].size(); ++i)
        {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;

            if (dist[there] > nextDist)
            {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }

    return dist;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int V, E, n, m;
        cin >> V >> E >> n >> m;

        vector<int> firePlace(n);
        vector<int> fireStation(m);

        for (int i = 0; i < E; ++i)
        {
            int here, there, time;
            cin >> here >> there >> time;

            adj[here].push_back(make_pair(there, time));
            adj[there].push_back(make_pair(here, time));
        }

        for (int i = 0; i < n; ++i)
            cin >> firePlace[i];
        for (int i = 0; i < m; ++i)
            cin >> fireStation[i];

        // 가상의 시작점(0번)에서 각 소방서까지 가중치 0인 간선 추가
        // 어떤 소방서인지 상관없이 가장 짧은 도착시간만 중요하기 때문에
        for (int i = 0; i < fireStation.size(); ++i)
        {
            int fs = fireStation[i];
            adj[0].push_back(make_pair(fs, 0));
            adj[fs].push_back(make_pair(0, 0));
        }

        vector<int> dist = dijkstra(0, V);

        int ans = 0;
        for (int i = 0; i < firePlace.size(); ++i)
            ans += dist[firePlace[i]];

        cout << ans << endl;

        // 초기화
        for (int i = 0; i <= V; ++i)
            adj[i].clear();
    }
    return 0;
}