#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int dw[4] = {-1, 0, 1, 0};
const int dh[4] = {0, 1, 0, -1};

char cache[1 << 25];

// board에 놓을 수 있는 블록들의 위치
vector<int> moves;

bool inRange(int w, int h)
{
    return (0 <= w && w < 5) && (0 <= h && h < 5);
}

// 5x5 크기의 게임판의 각 칸은 2가지 상태(./#)를 가짐
// 따라서 게임판은 25자리 2진수로 대응 가능함
int calcBoardId(const vector<string> &board)
{
    int id = 0;
    for (int w = 0; w < 5; ++w)
        for (int h = 0; h < 5; ++h)
        {
            id = id << 1;
            if (board[w][h] == '#')
                id++;
        }
    return id;
}

// board에 놓을 수 있는 블록들의 위치를 미리 계산
void precalc()
{
    vector<string> board(5, ".....");

    for (int w = 0; w < 5; ++w)
        for (int h = 0; h < 5; ++h)
        {
            // 3칸짜리 L자 모양 블록의 위치
            for (int i = 0; i < 4; ++i)
            {
                int nextW1 = w + dw[i];
                int nextH1 = h + dh[i];
                int nextW2 = w + dw[(i + 1) % 4];
                int nextH2 = h + dh[(i + 1) % 4];

                if (inRange(nextW1, nextH1) && inRange(nextW2, nextH2))
                {
                    board[w][h] = board[nextW1][nextH1] = board[nextW2][nextH2] = '#';
                    moves.push_back(calcBoardId(board));
                    board[w][h] = board[nextW1][nextH1] = board[nextW2][nextH2] = '.';
                }
            }

            // 2칸짜리 블록의 위치
            for (int i = 0; i < 4; ++i)
            {
                int nextW = w + dw[i];
                int nextH = h + dh[i];

                if (inRange(nextW, nextH))
                {
                    board[w][h] = board[nextW][nextH] = '#';
                    moves.push_back(calcBoardId(board));
                    board[w][h] = board[nextW][nextH] = '.';
                }
            }
        }
}

// 게임판이 boardId와 같을 때, 현재 플레이어가 승리할 수 있는 방법이 있는가
char play(int boardId)
{
    char &ret = cache[boardId];
    if (ret != -1)
        return ret;

    ret = 0; // 더이상 플레이할 수 없는 경우 0 반환

    for (int i = 0; i < moves.size(); ++i)
        // 블록을 놓을 수 있는 경우
        if ((moves[i] & boardId) == 0)
        {
            // 상대방이 더이상 플레이 할 수 없는 경우
            if (!play(boardId | moves[i]))
            {
                ret = 1;
                break;
            }
        }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    precalc();
    memset(cache, -1, sizeof(cache));

    while (c--)
    {
        vector<string> board(5);
        for (int i = 0; i < 5; ++i)
            cin >> board[i];

        int boardId = calcBoardId(board);
        if (play(boardId))
            cout << "WINNING" << endl;
        else
            cout << "LOSING" << endl;
    }

    return 0;
}