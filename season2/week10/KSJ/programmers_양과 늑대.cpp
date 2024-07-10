#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int MAX_N = 17;

int best = 0;

vector<int> adj[MAX_N];

void solve(vector<int> &info, int cur, int sheep, int wolf, int reachable)
{
    sheep += info[cur] ^ 1;
    wolf += info[cur];

    if (sheep <= wolf)
        return;

    if (best < sheep)
        best = sheep;

    for (auto &next : adj[cur])
        reachable |= (1 << next);

    int _reachable = reachable;
    while (_reachable)
    {
        int next = __builtin_ctz(_reachable);
        solve(info, next, sheep, wolf, reachable & ~(1 << next));
        _reachable &= (_reachable - 1);
    }
}

int solution(vector<int> info, vector<vector<int>> edges)
{

    for (auto &edge : edges)
    {
        int parent = edge[0], child = edge[1];
        adj[parent].push_back(child);
    }

    solve(info, 0, 0, 0, 0);

    return best;
}