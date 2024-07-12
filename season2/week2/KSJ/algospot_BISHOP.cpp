#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int MAX_N = 8;
const int MAX_V = MAX_N * MAX_N; // 64
const char BLANK = '.';

vector<string> board;

// 대각선의 방향 : LD, RD
const int dx[2] = {-1, 1};
const int dy[2] = {1, 1};

// id[dir][y][x] : dir방향 대각선을 따라 인접한 빈 칸 묶음들 중 (y, x)가 속한 묶음의 번호
int id[2][MAX_N][MAX_N];

// 이분 그래프의 정보
int n, m;
int adj[MAX_V][MAX_V];
vector<int> aMatch, bMatch;
vector<bool> visited;

// A의 정점인 a에서 B의 매칭되지 않는 정점의 가는 경로를 찾는다.
bool dfs(int a)
{
    if (visited[a])
        return false;

    visited[a] = true;
    for (int b = 0; b < m; ++b)
        if (adj[a][b])
            // b가 매칭되지 않았으면 증가 경로 찾기
            // 만약 매칭되어 있다면 bMatch[b]에서부터 시작해 증가 경로 찾기
            if (bMatch[b] == -1 || dfs(bMatch[b]))
            {
                aMatch[a] = b;
                bMatch[b] = a;
                return true;
            }
    return false;
}

// 최대 매칭의 크기를 반환
int bipartiteMatch()
{
    // 초기에는 어떤 정점도 연결되지 않음
    aMatch = vector<int>(n, -1);
    bMatch = vector<int>(m, -1);
    int size = 0;
    for (int start = 0; start < n; ++start)
    {
        visited = vector<bool>(n, false);
        if (dfs(start))
            size++;
    }
    return size;
}

bool inRange(int y, int x, int N)
{
    return ((0 <= y) && (y < N)) &&
           ((0 <= x) && (x < N));
}

// 체스판의 각 칸에 속한 묶음의 번호를 부여하고 이를 토대로 이분 그래프를 만든다.
// 그 후에 최대 이분 매칭의 크기를 반환한다.
int placeBishops()
{
    memset(id, -1, sizeof(id));
    // 이분 그래프를 구성하는 두 정점 집합의 크기
    int count[2] = {0, 0};
    for (int dir = 0; dir < 2; ++dir)
        for (int y = 0; y < board.size(); ++y)
            for (int x = 0; x < board.size(); ++x)
                // 빈 칸이고 id가 부여되지 않은 칸이라면 id 부여
                if (board[y][x] == BLANK && id[dir][y][x] == -1)
                {
                    int cy = y, cx = x;
                    while (inRange(cy, cx, board.size()) &&
                           board[cy][cx] == BLANK)
                    {
                        id[dir][cy][cx] = count[dir];
                        cy += dy[dir];
                        cx += dx[dir];
                    }
                    count[dir]++;
                }

    n = count[0];
    m = count[1];
    memset(adj, 0, sizeof(adj));
    for (int y = 0; y < board.size(); ++y)
        for (int x = 0; x < board.size(); ++x)
            // 두 묶음에 공통 원소(빈 칸)가 있을 때 두 정점을 간선으로 연결
            if (board[y][x] == BLANK)
                adj[id[0][y][x]][id[1][y][x]] = 1;

    return bipartiteMatch();
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int N;
        cin >> N;

        board.clear();
        for (int i = 0; i < N; ++i)
        {
            string h;
            cin >> h;

            board.push_back(h);
        }

        cout << placeBishops() << endl;
    }

    return 0;
}