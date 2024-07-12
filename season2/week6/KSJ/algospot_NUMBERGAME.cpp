#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 50;
const int UNK = 987654321;

int cache[MAX_N][MAX_N];

// 게임판이 board[lo, hi]와 같을 때, 현재 플레이어가 얻을 수 있는 최대 점수
int getBestScore(const vector<int> &board, int lo, int hi)
{
    // BASE CASE : 더이상 플레이할 수 없는 경우
    if (lo > hi)
        return 0;

    int &ret = cache[lo][hi];
    if (ret != UNK)
        return ret;

    // 게임판의 왼쪽 끝에 있는 숫자 하나를 가져가는 경우
    int bestScore = board[lo] - getBestScore(board, lo + 1, hi);
    // 게임판의 오른쪽 끝에 있는 숫자 하나를 가져가는 경우
    bestScore = max(bestScore, board[hi] - getBestScore(board, lo, hi - 1));
    if (hi - lo + 1 >= 2)
    {
        // 게임판의 왼쪽 끝에서 2개를 지우는 경우
        bestScore = max(bestScore, -getBestScore(board, lo + 2, hi));
        // 게임판의 오른쪽 끝에서 2개를 지우는 경우
        bestScore = max(bestScore, -getBestScore(board, lo, hi - 2));
    }

    return ret = bestScore;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        int n;
        cin >> n;

        vector<int> board(n);
        for (int i = 0; i < n; ++i)
            cin >> board[i];

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cache[i][j] = UNK;

        cout << getBestScore(board, 0, n - 1) << endl;
    }
    return 0;
}