#include <iostream>
#include <string>

using namespace std;

int main()
{
    string n;
    cin >> n;

    int idx = 0, num = 1;

    while (idx < n.length())
    {
        string num_str = to_string(num);

        for (auto digit : num_str)
        {
            if (idx >= n.length())
                break;
            if (digit == n[idx])
                idx++;
        }

        num++;
    }

    cout << (num - 1) << endl;
    return 0;
}