#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Fortress
{
public:
    int x, y, r;

    Fortress(int x, int y, int r)
    {
        this->x = x;
        this->y = y;
        this->r = r;
    }
};

// Fortress 1이 Foreess 2를 포함하고 있는지 return
bool includes(const Fortress &f1, const Fortress &f2)
{
    // return (((f1.x - f1.r) < (f2.x - f2.r)) &&
    //         ((f2.x - f2.r) < (f2.x + f2.r)) &&
    //         ((f2.x + f2.r) < (f1.x + f1.r))) &&
    //        (((f1.y - f1.r) < (f2.y - f2.r)) &&
    //         ((f2.y - f2.r) < (f2.y + f2.r)) &&
    //         ((f2.y + f2.r) < (f1.y + f1.r)));
    double d = sqrt(pow(f1.x - f2.x, 2) + pow(f1.y - f2.y, 2));
    return (f1.r > f2.r) &&
           ((f1.r - f2.r) > d);
}

bool isChild(int parent,
             int child,
             int n,
             vector<Fortress> &fortresses)
{
    if (!includes(fortresses[parent], fortresses[child]))
        return false;
    for (int i = 0; i < n; ++i)
        if (i != parent && i != child &&
            includes(fortresses[parent], fortresses[i]) &&
            includes(fortresses[i], fortresses[child]))
            return false;
    return true;
}

void makeTree(int root,
              int n,
              vector<Fortress> &fortresses,
              unordered_map<int, vector<int>> &tree)
{
    for (int ch = 0; ch < n; ++ch)
        if (isChild(root, ch, n, fortresses))
        {
            tree[root].push_back(ch);
            makeTree(ch, n, fortresses, tree);
        }
}

// root를 루트로 하는 트리의 height를 heights에 저장
int getHeight(int root,
              vector<int> &heights,
              unordered_map<int, vector<int>> &tree)
{
    int &ret = heights[root];
    if (ret != -1)
        return ret;

    int height = 0;
    vector<int> children = tree[root];
    for (int child : children)
    {
        height = max(height, 1 + getHeight(child, heights, tree));
    }

    return ret = height;
}

// root를 루트로 하는 트리로부터 최장거리 계산
// root를 루트로 하는 트리의 높이 vs (#서브트리 > 1일떄)root의 서브트리 중 가장 긴 첫번째, 두번째 높이의 합 + 2
int getLongest(int root,
               vector<int> &heights,
               unordered_map<int, vector<int>> &tree)
{
    int longest = heights[root];

    vector<int> subHeights;
    vector<int> children = tree[root];
    for (int child : children)
        subHeights.push_back(heights[child]);

    if (subHeights.size() > 1)
    {
        sort(subHeights.begin(), subHeights.end());
        longest = max(longest, 2 + subHeights[subHeights.size() - 1] +
                                   subHeights[subHeights.size() - 2]);
    }

    return longest;
}

// 임의의 두 지점 이동간 성벽 넘는 최대 횟수 return
int solve(int n, unordered_map<int, vector<int>> &tree)
{
    int ans = 0;

    vector<int> heights(n, -1);
    for (int i = 0; i < n; ++i)
        getHeight(i, heights, tree);

    for (int i = 0; i < n; ++i)
        ans = max(ans, getLongest(i, heights, tree));

    return ans;
}

int main()
{
    int C;
    cin >> C;

    while (C--)
    {
        int n;
        cin >> n;

        vector<Fortress> fortresses;
        // <K, V> = <parent, children>
        unordered_map<int, vector<int>> tree;

        for (int i = 0; i < n; ++i)
        {
            int x, y, r;
            cin >> x >> y >> r;
            fortresses.push_back(Fortress(x, y, r));

            tree[i] = vector<int>();
        }

        makeTree(0, n, fortresses, tree);

        cout << solve(n, tree) << endl;
    }

    return 0;
}