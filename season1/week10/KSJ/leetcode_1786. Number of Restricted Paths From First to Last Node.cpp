class Solution
{
public:
    static const int MAX_V = 20000;
    // (연결된 정점, 가중치) 저장
    vector<pair<int, int>> adj[MAX_V + 1];
    // (distanceToLastNode 값) 저장
    vector<long long> dist;

    Solution()
    {
        const long long INF = numeric_limits<long long>::max();
        dist.assign(MAX_V + 1, INF);
    }

    void initGraph(vector<vector<int>> &edges)
    {
        for (int i = 0; i < edges.size(); ++i)
        {
            int u, v, w;
            vector<int> edge = edges[i];
            u = edge[0], v = edge[1], w = edge[2];

            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }
    }

    void distanceToLastNode(int src)
    {
        dist[src] = 0;
        // (n까지의 거리, 정점의 번호) 저장
        priority_queue<pair<long long, int>> pq;
        pq.push(make_pair(-dist[src], src));

        while (!pq.empty())
        {
            long long cost = -pq.top().first;
            int here = pq.top().second;
            pq.pop();

            if (dist[here] < cost)
                continue;

            for (int i = 0; i < adj[here].size(); ++i)
            {
                int there = adj[here][i].first;
                long long nextDist = cost + adj[here][i].second;

                if (dist[there] > nextDist)
                {
                    dist[there] = nextDist;
                    pq.push(make_pair(-nextDist, there));
                }
            }
        }

        return;
    }

    int _countRestrictedPaths(int n)
    {
        // cache[i] = i번 정점부터 n번 정점까지 연결가능한 retricted path 개수
        vector<int> cache(n + 1, 0);
        cache[n] = 1;

        // (도착점까지 최소 거리, 정점 번호) 저장
        vector<pair<long long, int>> nodes;
        for (int i = 1; i <= n; ++i)
            nodes.push_back(make_pair(dist[i], i));

        sort(nodes.begin(), nodes.end());

        // restricted path 개수가 적은(도착점까지 최소거리가 작은) 정점부터 계산
        for (int i = 0; i < nodes.size(); ++i)
        {
            int here = nodes[i].second;
            for (int j = 0; j < adj[here].size(); ++j)
            {
                int there = adj[here][j].first;
                if (dist[here] > dist[there])
                    cache[here] = (cache[here] + cache[there]) % int(1e9 + 7);
            }
        }

        return cache[1];
    }

    int countRestrictedPaths(int n, vector<vector<int>> &edges)
    {
        int ans = 0;

        initGraph(edges);
        distanceToLastNode(n);
        ans = _countRestrictedPaths(n);

        return ans;
    }
};