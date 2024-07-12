#include <cstdio>

#define MAX_H 20
#define MAX_W 20
#define BLACK '#'
#define WHITE '.'

int dH[4][2] = {{0, 1}, {1, 1}, {1, 1}, {0, 1}};
int dW[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {1, 1}};

bool inRange(int targetH, int targetW, int H, int W)
{
    return (0 < targetH) && (targetH <= H) &&
           (0 < targetW) && (targetW <= W);
}

int countNumCover(int H, int W, char board[MAX_H + 1][MAX_W + 1])
{
    // 가정 : 특정한 점을 기준으로 위, 왼쪽에 위치한 모든 점들은 black
    int ret = 0, firstH = 0, firstW = 0;

    for (int pH = 1; pH <= H; ++pH)
    {
        for (int pW = 1; pW <= W; ++pW)
        {
            if (board[pH][pW] == WHITE)
            {
                firstH = pH;
                firstW = pW;
                break;
            }
        }
        if (firstW != 0)
            break;
    }

    // BASE CASE : 모든 점이 black인 경우 1 return
    if ((firstH == 0) && (firstW == 0))
        return 1;

    for (int type = 0; type < 4; ++type)
    {
        int p1H, p1W, p2H, p2W;

        p1H = firstH + dH[type][0];
        p1W = firstW + dW[type][0];
        p2H = firstH + dH[type][1];
        p2W = firstW + dW[type][1];

        if (inRange(firstH, firstW, H, W) && inRange(p1H, p1W, H, W) && inRange(p2H, p2W, H, W) &&
            board[firstH][firstW] == WHITE && board[p1H][p1W] == WHITE && board[p2H][p2W] == WHITE)
        {
            board[p1H][p1W] = BLACK;
            board[firstH][firstW] = BLACK;
            board[p2H][p2W] = BLACK;

            ret += countNumCover(H, W, board);

            board[p1H][p1W] = WHITE;
            board[firstH][firstW] = WHITE;
            board[p2H][p2W] = WHITE;
        }
    }

    return ret;
}

int main()
{
    int c;
    scanf("%d", &c);

    while (c--)
    {
        int h, w, ans;
        char board[MAX_H + 1][MAX_W + 1];

        scanf("%d %d", &h, &w);

        for (int i = 1; i <= h; ++i)
            scanf("%s", &board[i][1]);

        int nWhite = 0;
        for (int i = 1; i <= h; ++i)
            for (int j = 1; j <= w; ++j)
                if (board[i][j] == WHITE)
                    nWhite++;

        ans = (nWhite % 3 == 0) ? countNumCover(h, w, board) : 0;

        printf("%d\n", ans);
    }
}