#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

const int MAX_N = 50;
const int MAX_LEN = 100;

int cache[MAX_N][MAX_LEN];

string pattern, fname;

int match(int pIdx, int fnIdx)
{
    // BASE CASE : pIdx와 fnIdx가 동시에 끝에 도달한 경우만 true
    if (pIdx == pattern.size())
        return fnIdx == fname.size();

    int &ret = cache[pIdx][fnIdx];

    if (ret != -1)
        return ret;

    char p = pattern[pIdx];
    if (p == '?')
        return ret = match(pIdx + 1, fnIdx + 1);
    else if (p == '*')
        for (int skip = 0; fnIdx + skip <= fname.size(); ++skip)
            if (match(pIdx + 1, fnIdx + skip))
                return ret = true;

    char f = fname[fnIdx];
    if (p != f)
        return ret = false;

    return ret = match(pIdx + 1, fnIdx + 1);
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        cin >> pattern;

        int n;
        cin >> n;
        vector<string> fnames(n);
        for (int i = 0; i < n; ++i)
            cin >> fnames[i];

        sort(fnames.begin(), fnames.end());

        for (int i = 0; i < n; ++i)
        {
            fname = fnames[i];
            memset(cache, -1, sizeof(cache));
            if (match(0, 0))
                cout << fname << endl;
        }
    }
    return 0;
}