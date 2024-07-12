#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int n, m;
// canEat[i] = i번 친구가 먹을 수 있는 음식의 집합
// eaters[i] = i번 음식을 먹을 수 있는 친구들의 집합
vector<int> canEat[50], eaters[50];
unordered_map<string, int> friendIds;

int best;

// edible[i] = 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
// chosen : 지금까지 선택한 음식의 수
void search(vector<int> &edible, int chosen)
{
    if (chosen >= best)
        return;

    // 아직 먹을 음식이 없는 친구 찾기
    int first = 0;
    while (first < n && edible[first] > 0)
        ++first;
    if (first == n)
    {
        best = chosen;
        return;
    }

    for (int i = 0; i < canEat[first].size(); ++i)
    {
        int food = canEat[first][i];
        for (int j = 0; j < eaters[food].size(); ++j)
            edible[eaters[food][j]]++;
        search(edible, chosen + 1);
        for (int j = 0; j < eaters[food].size(); ++j)
            edible[eaters[food][j]]--;
    }
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> n >> m;

        // 초기화 (이전 데이터 삭제)
        friendIds.clear();
        for (int i = 0; i < 50; ++i)
        {
            canEat[i].clear();
            eaters[i].clear();
        }
        // 초기화 (새로운 데이터 입력)
        for (int i = 0; i < n; ++i)
        {
            string fName;
            cin >> fName;

            friendIds[fName] = i;
        }

        for (int i = 0; i < m; ++i)
        {
            int nEaters;
            cin >> nEaters;

            vector<int> canEaters;
            for (int j = 0; j < nEaters; ++j)
            {
                string fName;
                cin >> fName;

                int id = friendIds[fName];
                eaters[i].push_back(id);
                canEat[id].push_back(i);
            }
        }

        vector<int> edible(n, 0);
        best = INF;
        search(edible, 0);

        cout << best << endl;
    }

    return 0;
}