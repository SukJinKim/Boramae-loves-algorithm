#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <iostream>

using namespace std;

unordered_map<string, int> userId;
unordered_map<int, string> userName;

const int N = 1000;

bool accused[N][N];
bool banned[N];

vector<int> solution(vector<string> id_list, vector<string> report, int k)
{
    int n = id_list.size();
    vector<int> answer(n, 0);

    for (int i = 0; i < n; ++i)
        userId[id_list[i]] = i;

    for (const string &rpt : report)
    {
        stringstream ss(rpt);
        string from, to;
        ss >> from >> to;

        accused[userId[from]][userId[to]] = true;
    }

    for (int i = 0; i < n; ++i)
    {
        int nAccused = 0;
        for (int j = 0; j < n; ++j)
            if (accused[j][i])
                nAccused++;

        if (nAccused >= k)
            banned[i] = true;
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (accused[i][j] && banned[j])
                answer[i]++;

    return answer;
}