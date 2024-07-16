const char WALL = '+';

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

bool inRange(int m, int n, int x, int y)
{
    return ((0 <= x) && (x < m)) &&
           ((0 <= y) && (y < n));
}

bool inRange(vector<vector<char>> &maze, vector<int> &here)
{
    return inRange(maze.size(), maze[0].size(), here[0], here[1]);
}

bool isExit(int m, int n, int x, int y)
{
    return (0 == x) || (x == m - 1) ||
           (0 == y) || (y == n - 1);
}

bool isExit(vector<vector<char>> &maze, vector<int> &start, vector<int> &here)
{
    return isExit(maze.size(), maze[0].size(), here[0], here[1]) && (start != here);
}

class Solution
{
public:
    int bfs(vector<vector<char>> &maze, vector<int> &start)
    {
        map<vector<int>, int> distance;
        queue<vector<int>> q;

        distance[start] = 0;
        q.push(start);

        while (!q.empty())
        {
            vector<int> here = q.front();
            q.pop();

            if (isExit(maze, start, here))
                return distance[here];

            for (int i = 0; i < 4; ++i)
            {
                vector<int> there(2);
                there[0] = here[0] + dx[i];
                there[1] = here[1] + dy[i];

                if (inRange(maze, there) &&
                    maze[there[0]][there[1]] != WALL &&
                    distance.count(there) == 0)
                {
                    distance[there] = distance[here] + 1;
                    q.push(there);
                }
            }
        }

        return -1;
    }

    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        return bfs(maze, entrance);
    }
};