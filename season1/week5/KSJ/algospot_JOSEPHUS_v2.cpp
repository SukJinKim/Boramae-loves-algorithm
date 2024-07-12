#include <iostream>
#include <queue>

using namespace std;

void josephus(int n, int k)
{
    queue<int> soldiers;

    for (int id = 1; id <= n; ++id)
        soldiers.push(id);

    while (soldiers.size() > 2)
    {
        soldiers.pop();

        for (int i = 0; i < k - 1; ++i)
        {
            soldiers.push(soldiers.front());
            soldiers.pop();
        }
    }

    cout << min(soldiers.front(), soldiers.back()) << ' '
         << max(soldiers.front(), soldiers.back()) << endl;
}

int main()
{
    int c, n, k;
    cin >> c;

    while (c--)
    {
        cin >> n >> k;
        josephus(n, k);
    }
}