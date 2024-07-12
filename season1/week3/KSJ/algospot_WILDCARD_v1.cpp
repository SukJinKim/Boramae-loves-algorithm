#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string pattern, fname;

// pattern[patternIdx, INF) == fname[fnameIdx, INF) 일치여부 판별
bool match(int patternIdx, int fnameIdx)
{
    // base case 1
    if (patternIdx == pattern.size() && fnameIdx == fname.size())
        return true;

    bool ret = false;
    char ch_pattern = pattern[patternIdx];
    char ch_fname = fname[fnameIdx];

    if (ch_pattern == '*')
    {
        for (int nSkip = 0; nSkip + fnameIdx <= fname.size(); nSkip++)
            ret = ret || match(patternIdx + 1, fnameIdx + nSkip);
    }
    // base case 2
    else if (ch_pattern != '?' && ch_pattern != ch_fname)
        return false;
    else
        ret = ret || match(patternIdx + 1, fnameIdx + 1);

    return ret;
}

// ASCII 순서로 정렬하기 위한 compare function
bool cmpASCII(const string &str1, const string &str2)
{
    return str1 < str2;
}

int main()
{
    int C, N;
    cin >> C;

    while (C--)
    {
        cin >> pattern;

        cin >> N;
        vector<string> fnames;
        for (int i = 0; i < N; ++i)
        {
            cin >> fname;
            fnames.push_back(fname);
        }

        sort(fnames.begin(), fnames.end(), cmpASCII);

        for (int i = 0; i < N; ++i)
        {
            fname = fnames[i];
            if (match(0, 0))
                cout << fname << endl;
        }
    }
}