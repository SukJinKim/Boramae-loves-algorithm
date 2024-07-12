#include <iostream>
#include <list>

using namespace std;

void josephus(int n, int k)
{
    list<int> soldiers;

    for (int id = 1; id <= n; ++id)
        soldiers.push_back(id);

    list<int>::iterator suicide = soldiers.begin();

    while (n > 2)
    {
        suicide = soldiers.erase(suicide);
        n--;
        if (suicide == soldiers.end())
            suicide = soldiers.begin();

        for (int i = 0; i < k - 1; ++i)
        {
            suicide++;
            if (suicide == soldiers.end())
                suicide = soldiers.begin();
        }
    }

    cout << soldiers.front() << ' ' << soldiers.back() << endl;
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