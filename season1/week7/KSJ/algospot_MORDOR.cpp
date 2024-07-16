#include <cstdio>
#include <vector>
#include <limits>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();
const int MIN_INT = numeric_limits<int>::min();

struct MinST
{
    int n;
    vector<int> rangeMin;
    MinST(const vector<int> &array)
    {
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n - 1, 1);
    }

    int init(const vector<int> &array, int left, int right, int node)
    {
        if (left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        if (right < nodeLeft || nodeRight < left)
            return MAX_INT;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int query(int left, int right)
    {
        return query(left, right, 1, 0, n - 1);
    }
};

struct MaxST
{
    int n;
    vector<int> rangeMax;
    MaxST(const vector<int> &array)
    {
        n = array.size();
        rangeMax.resize(n * 4);
        init(array, 0, n - 1, 1);
    }

    int init(const vector<int> &array, int left, int right, int node)
    {
        if (left == right)
            return rangeMax[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMax[node] = max(leftMin, rightMin);
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight)
    {
        if (right < nodeLeft || nodeRight < left)
            return MIN_INT;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMax[node];
        int mid = (nodeLeft + nodeRight) / 2;
        return max(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 + 1, mid + 1, nodeRight));
    }

    int query(int left, int right)
    {
        return query(left, right, 1, 0, n - 1);
    }
};

int main()
{
    int C;
    scanf("%d", &C);

    while (C--)
    {
        int N, Q;
        scanf("%d %d", &N, &Q);

        vector<int> heights;
        int h;
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &h);
            heights.push_back(h);
        }

        MinST minST = MinST(heights);
        MaxST maxST = MaxST(heights);

        for (int i = 0; i < Q; ++i)
        {
            int a, b;
            scanf("%d %d", &a, &b);

            int maxH, minH;
            maxH = maxST.query(a, b);
            minH = minST.query(a, b);

            printf("%d\n", maxH - minH);
        }
    }
    return 0;
}