#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<string> board;

// 3^9
const int MAX_ID = 19683;
// 1(이김) / 0(비김) / -1(짐) 저장
int cache[MAX_ID];

// turn으로 이루어진 한 줄이 완성되었는지 반환
bool isFinished(const vector<string> &board, char turn)
{
    // row test
    for (int w = 0; w < 3; ++w)
        if (board[w] == string(3, turn))
            return true;

    // col test
    for (int h = 0; h < 3; ++h)
    {
        string col = "";
        for (int w = 0; w < 3; ++w)
            col += board[w][h];
        if (col == string(3, turn))
            return true;
    }

    // diagonal test
    string diag1 = "";
    string diag2 = "";
    for (int i = 0; i < 3; ++i)
    {
        diag1 += board[i][i];
        diag2 += board[i][2 - i];
    }
    if (diag1 == string(3, turn) ||
        diag2 == string(3, turn))
        return true;

    return false;
}

// 3x3 크기의 게임판에서 각 칸은 3가지 상태(./x/o) 중 하나를 가진다.
// 따라서 게임판 상태를 9자리 3진수로 표현할 수 있다.
int boardId(const vector<string> &board)
{
    int id = 0;
    for (int w = 0; w < 3; ++w)
        for (int h = 0; h < 3; ++h)
        {
            id = id * 3; // 자리 수 올리기
            if (board[w][h] == 'o')
                id += 1;
            else if (board[w][h] == 'x')
                id += 2;
        }
    return id;
}

// 게임판의 현재 상태 board와 이번 차례(turn)가 주어질 때
// 이번 차례 이후 플레이어가 이길지(1), 비길지(0), 질지(-1) 반환
int canWin(vector<string> &board, char turn)
{
    // 지난 차례에 상대 플레이어가 이긴 경우
    if (isFinished(board, 'o' + 'x' - turn))
        return -1;

    int &ret = cache[boardId(board)];
    if (ret != -2)
        return ret;

    // 상대 플레이어가 가질 수 있는 최악의 결과
    int minValue = 2;
    for (int w = 0; w < 3; ++w)
        for (int h = 0; h < 3; ++h)
            if (board[w][h] == '.')
            {
                board[w][h] = turn;
                minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
                board[w][h] = '.';
            }

    // 상대 플레이어가 더이상 플레이할 수 없거나 비기는 경우
    if (minValue == 2 || minValue == 0)
        return ret = 0;
    // (현재 플레이어가 가질 수 있는 최고의 결과) = -(상대 플레이어가 가질 수 있는 최악의 결과)
    return ret = -minValue;
}

char chooseTurn(const vector<string> &board)
{
    char turn = 'x';

    int nO = 0, nX = 0;
    for (int w = 0; w < 3; ++w)
        for (int h = 0; h < 3; ++h)
        {
            if (board[w][h] == 'o')
                nO++;
            else if (board[w][h] == 'x')
                nX++;
        }

    // x가 o보다 하나 더 놓인 경우
    if (nX == nO + 1)
        turn = 'o';

    return turn;
}

int main()
{
    int c;
    cin >> c;

    for (int i = 0; i < MAX_ID; ++i)
        cache[i] = -2;

    while (c--)
    {
        board.clear();
        for (int w = 0; w < 3; ++w)
        {
            string row;
            cin >> row;
            board.push_back(row);
        }

        char turn = chooseTurn(board);
        int result = canWin(board, turn);
        if (result == 0)
            cout << "TIE" << endl;
        else if (result == 1)
            cout << turn << endl;
        else
            cout << (char)('o' + 'x' - turn) << endl;
    }

    return 0;
}