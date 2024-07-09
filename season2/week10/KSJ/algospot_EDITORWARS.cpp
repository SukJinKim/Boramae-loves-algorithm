#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;

struct DisjointSet
{
    vector<int> parent, rank, size, enemy;

    DisjointSet(int n) : parent(n), rank(n, 0), size(n, 1), enemy(n, -1)
    {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u)
    {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }

    // u와 v를 병합하여 만든 트리의 루트 반환
    int merge(int u, int v)
    {
        if (u == -1 || v == -1)
            return max(u, v);

        u = find(u), v = find(v);

        if (u == v)
            return u;

        // 항상 rank[u] <= rank[v] 조건을 만족함
        // 따라서 v의 자식으로 u를 넣는다.
        if (rank[u] > rank[v])
            swap(u, v);

        parent[u] = v;
        if (rank[u] == rank[v])
            ++rank[v];
        size[v] += size[u];

        return v;
    }

    // 상호 우호관계여부 반환
    bool ack(int u, int v)
    {
        u = find(u), v = find(v);

        if (enemy[u] == v)
            return false;

        int a = merge(u, v);
        int b = merge(enemy[u], enemy[v]);

        enemy[a] = b;
        if (b != -1)
            enemy[b] = a;

        return true;
    }

    // 상호 적대관계여부 반환
    bool dis(int u, int v)
    {
        u = find(u), v = find(v);

        if (u == v)
            return false;

        int a = merge(enemy[u], v);
        int b = merge(u, enemy[v]);

        enemy[a] = b;
        enemy[b] = a;

        return true;
    }
};

// 모순여부 반환
bool judge(DisjointSet &ds, string &relationship, int u, int v)
{
    return (relationship == "ACK") ? ds.ack(u, v) : ds.dis(u, v);
}

int maxParty(DisjointSet &ds)
{
    int ret = 0;
    for (int node = 0; node < n; ++node)
        // node가 루트인 경우
        if (ds.parent[node] == node)
        {
            int enemy = ds.enemy[node];

            if (node < enemy)
                continue;

            int mySize = ds.size[node];
            int enemySize = (enemy != -1) ? ds.size[enemy] : 0;

            ret += max(mySize, enemySize);
        }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> m;

        DisjointSet ds(n);
        bool notContradicted;
        int firstIdx = -1;
        for (int i = 1; i <= m; ++i)
        {
            string relationship;
            int u, v;
            cin >> relationship >> u >> v;

            notContradicted = judge(ds, relationship, u, v);
            if (!notContradicted && firstIdx == -1)
            {
                firstIdx = i;
                cout << "CONTRADICTION AT " << firstIdx << endl;
            }
        }

        if (notContradicted && firstIdx == -1)
            cout << "MAX PARTY SIZE IS " << maxParty(ds) << endl;
    }
    return 0;
}