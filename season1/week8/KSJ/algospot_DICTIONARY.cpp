#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int alphaToNumber(char alpha)
{
    return alpha - 'a';
}

char numberToAlpha(int number)
{
    return number + 'a';
}

void init(vector<vector<int>> &graph)
{
    for (char ch = 'a'; ch <= 'z'; ++ch)
        graph[alphaToNumber(ch)].push_back(alphaToNumber(ch));
}

void reorder(vector<vector<int>> &graph,
             vector<string> &words)
{
    for (int i = 1; i < words.size(); ++i)
    {
        string word1 = words[i - 1];
        string word2 = words[i];

        for (int j = 0; j < word1.size() && j < word2.size(); ++j)
        {
            char ch1 = word1[j];
            char ch2 = word2[j];

            if (ch1 != ch2)
            {
                graph[alphaToNumber(ch1)][0] = alphaToNumber(ch2);
                break;
            }
        }
    }
}

void dfs(char alpha,
         vector<char> &tSort,
         vector<bool> &visited,
         vector<vector<int>> &graph)
{
    int num = alphaToNumber(alpha);
    visited[num] = true;
    for (int child : graph[num])
        if (!visited[child])
            dfs(numberToAlpha(child), tSort, visited, graph);
    tSort.push_back(alpha);
}

vector<char> topologicalSort(vector<bool> &visited,
                             vector<vector<int>> &graph)
{
    vector<char> tSort;
    for (char ch = 'a'; ch <= 'z'; ++ch)
        if (!visited[alphaToNumber(ch)])
            dfs(ch, tSort, visited, graph);
    reverse(tSort.begin(), tSort.end());
    return tSort;
}

bool checkCycle(vector<char> &tSort,
                vector<vector<int>> &graph)
{
    // tSort에서 child가 parent보다 순서가 앞서면 cycle
    for (char ch = 'a'; ch <= 'z'; ++ch)
    {
        int parent = alphaToNumber(ch);
        for (int child : graph[parent])
        {
            vector<char>::iterator posParent = find(tSort.begin(),
                                                    tSort.end(),
                                                    numberToAlpha(parent));
            vector<char>::iterator posChild = find(tSort.begin(),
                                                   tSort.end(),
                                                   numberToAlpha(child));

            if (posParent > posChild)
                return true;
        }
    }

    return false;
}

string solve(vector<bool> &visited,
             vector<vector<int>> &graph,
             vector<string> &words)
{
    string ans = "";

    reorder(graph, words);
    vector<char> tSort = topologicalSort(visited, graph);

    if (checkCycle(tSort, graph))
        ans = "INVALID HYPOTHESIS";
    else
    {
        for (char ch : tSort)
            ans += ch;
    }

    return ans;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int N;
        cin >> N;

        string word;
        vector<string> words;
        for (int i = 0; i < N; ++i)
        {
            cin >> word;
            words.push_back(word);
        }

        if (N == 1)
        {
            cout << "abcdefghijklmnopqrstuvwxyz" << endl;
        }
        else
        {
            vector<bool> visited(26, false);
            vector<vector<int>> graph(26, vector<int>());
            init(graph);
            cout << solve(visited, graph, words) << endl;
        }
    }

    return 0;
}