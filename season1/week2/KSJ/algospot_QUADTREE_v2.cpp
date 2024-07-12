#include <iostream>
#include <string>

using namespace std;

string upsideDown(string &qtree, int &idx)
{
    if (idx >= qtree.length())
        return string();
    char node = qtree[idx];
    idx++;
    if (node == 'w' || node == 'b')
        return string(1, node);

    string lt = upsideDown(qtree, idx);
    string rt = upsideDown(qtree, idx);
    string lb = upsideDown(qtree, idx);
    string rb = upsideDown(qtree, idx);

    return 'x' + lb + rb + lt + rt;
}

int main()
{
    int C;
    cin >> C;
    while (C--)
    {
        string qtree;
        cin >> qtree;

        int idx = 0;
        cout << upsideDown(qtree, idx) << endl;
    }
}