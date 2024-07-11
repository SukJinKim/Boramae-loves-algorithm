#include <string>
#include <vector>
#include <iostream>

using namespace std;

const int N = 1000;

int cumSum[N + 1][N + 1];

int countNotDestroyed(vector<vector<int>> &board)
{
    int notDestroyed = 0;

    for (int r = 0; r < board.size(); ++r)
        for (int c = 0; c < board[r].size(); ++c)
            if (board[r][c] > 0)
                notDestroyed++;

    return notDestroyed;
}

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    for (auto aSkill : skill)
    {
        int type = aSkill[0];
        int r1 = aSkill[1], c1 = aSkill[2];
        int r2 = aSkill[3], c2 = aSkill[4];
        int deg = (type == 1) ? -aSkill[5] : aSkill[5];

        cumSum[r1][c1] += deg;
        cumSum[r1][c2 + 1] += -deg;
        cumSum[r2 + 1][c2 + 1] += deg;
        cumSum[r2 + 1][c1] += -deg;
    }

    // Up to Down
    for (int c = 0; c < board[0].size() + 1; ++c)
        for (int r = 1; r < board.size() + 1; ++r)
            cumSum[r][c] += cumSum[r - 1][c];
    // Left to Right
    for (int r = 0; r < board.size() + 1; ++r)
        for (int c = 1; c < board[0].size() + 1; ++c)
            cumSum[r][c] += cumSum[r][c - 1];
    // board + cumSum
    for (int r = 0; r < board.size(); ++r)
        for (int c = 0; c < board[0].size(); ++c)
            board[r][c] += cumSum[r][c];

    int answer = countNotDestroyed(board);

    return answer;
}