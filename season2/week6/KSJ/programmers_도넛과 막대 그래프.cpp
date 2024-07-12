#include <string>
#include <vector>
#include <utility>

using namespace std;

const int MAX_V = int(1e6) + 1;
// inOut[i] : i번 정점의 (들어오는 간선의 개수, 나가는 간선의 수) 저장
vector<pair<int, int>> inOut;

vector<int> solution(vector<vector<int>> edges)
{
    vector<int> answer(4, 0);

    for (int i = 0; i < MAX_V; ++i)
        inOut.push_back(make_pair(0, 0));

    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i][0], v = edges[i][1];
        // u로부터 나가는 간선의 수 + 1
        inOut[u].second++;
        // v로 들어오는 간선의 수 + 1
        inOut[v].first++;
    }

    for (int u = 1; u <= inOut.size(); ++u)
    {
        // 나가는 간선은 2개 이상이고 들어오는 간선이 없으면 '추가 정점'
        if (inOut[u].second >= 2 && inOut[u].first == 0)
            answer[0] = u;
        // 나가는 간선이 없고 들어오는 간선이 1개 이상이면 '막대'
        else if (inOut[u].second == 0 && inOut[u].first >= 1)
            answer[2]++;
        // 나가는 간선이 2개 이상이고 들어오는 간선이 2개 이상이면 '8자'
        else if (inOut[u].second >= 2 && inOut[u].first >= 2)
            answer[3]++;
    }
    // 도넛 = 전체 - (막대 + 8자)
    answer[1] = inOut[answer[0]].second - (answer[2] + answer[3]);

    return answer;
}