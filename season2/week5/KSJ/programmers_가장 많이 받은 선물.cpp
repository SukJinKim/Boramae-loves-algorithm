#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

const int MAX_FRIENDS = 50;

unordered_map<string, int> friendToId;
// rec[i][j] : i가 j에게 준 선물의 수
int rec[MAX_FRIENDS][MAX_FRIENDS];
int giftFactor[MAX_FRIENDS];
int numRecvGifts[MAX_FRIENDS];

int solution(vector<string> friends, vector<string> gifts)
{
    int answer = 0;

    for (int i = 0; i < friends.size(); ++i)
        friendToId[friends[i]] = i;

    // 주고받은 선물 기록 저장
    for (int i = 0; i < gifts.size(); ++i)
    {
        string from, to;
        stringstream parse(gifts[i]);
        parse >> from >> to;

        int fromId = friendToId[from], toId = friendToId[to];
        rec[fromId][toId]++;
    }

    // 선물 지수 계산
    for (int i = 0; i < friends.size(); ++i)
    {
        int numSend = 0, numRecv = 0;

        for (int j = 0; j < friends.size(); ++j)
        {
            numSend += rec[i][j];
            numRecv += rec[j][i];
        }

        giftFactor[i] = numSend - numRecv;
    }

    for (int i = 0; i < friends.size(); ++i)
    {
        for (int j = i + 1; j < friends.size(); ++j)
        {
            // 선물을 주고받은 적이 있고 주고받은 선물의 개수가 다른 경우
            if ((rec[i][j] || rec[j][i]) && rec[i][j] != rec[j][i])
            {
                if (rec[i][j] > rec[j][i])
                    numRecvGifts[i]++;
                else
                    numRecvGifts[j]++;
            }
            else // 선물을 주고받은 적이 없거나 주고받은 선물의 개수가 같은 경우
            {
                if (giftFactor[i] > giftFactor[j])
                    numRecvGifts[i]++;
                else if (giftFactor[i] < giftFactor[j])
                    numRecvGifts[j]++;
            }
        }
    }

    answer = *max_element(numRecvGifts, numRecvGifts + friends.size());

    return answer;
}