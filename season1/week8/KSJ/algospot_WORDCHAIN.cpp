#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 인접 행렬, adj[i][j] = (i, j) 사이 간선의 수
vector<vector<int>> adj;
vector<bool> visited;

void initGraph(vector<string> &words)
{
    int n = words.size();

    adj.assign(n, vector<int>());
    for (int i = 0; i < n; ++i)
        adj[i].assign(n, 0);

    // u -> v = words[u]에서 words[v]로 끝말잇기 가능
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            char i_first = words[i][0];
            char j_last = words[j][words[j].size() - 1];
            // j -> i
            if (i_first == j_last)
                adj[j][i]++;

            char i_last = words[i][words[i].size() - 1];
            char j_first = words[j][0];
            // i -> j
            if (i_last == j_first)
                adj[i][j]++;
        }
}

// here에서 시작하는 오일러 서킷 찾기
void getEulerCircuit(int here, vector<int> &circuit)
{
    visited[here] = true;
    for (int there = 0; there < adj[here].size(); ++there)
    {
        while (adj[here][there] > 0 && !visited[there])
        {
            adj[here][there]--;
            getEulerCircuit(there, circuit);
            adj[here][there]++;
        }
    }
    circuit.push_back(here);
}

// here에서 시작해서 there로 끝나는 오일러 트레일 찾기
void getEulerTrail(int here, int there, vector<int> &circuit)
{
    adj[there][here]++;
    getEulerCircuit(here, circuit);
    adj[there][here]--;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int n;
        cin >> n;

        vector<string> words(n);
        for (int i = 0; i < n; ++i)
            cin >> words[i];

        initGraph(words);

        vector<int> circuit;
        bool impossible = true;

        // 모든 정점 u에 대한 오일러 서킷 찾기
        // for (int u = 0; u < n; ++u)
        // {
        //     visited.assign(n, false);
        //     circuit.clear();

        //     getEulerCircuit(u, circuit);
        //     reverse(circuit.begin(), circuit.end());

        //     if (circuit.size() == n)
        //     {
        //         impossible = false;
        //         break;
        //     }
        // }

        // u에서 시작해서 v로 끝나는 오일러 트레일 찾기
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                visited.assign(n, false);
                circuit.clear();

                getEulerTrail(u, v, circuit);
                reverse(circuit.begin(), circuit.end());

                if (circuit.size() == n)
                {
                    impossible = false;
                    break;
                }
            }
            if (!impossible)
                break;
        }

        if (impossible)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            for (int c : circuit)
                cout << words[c] << ' ';
            cout << endl;
        }
    }
    return 0;
}