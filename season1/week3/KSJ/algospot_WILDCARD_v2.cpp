#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

string pattern, fname;

int cache[101][101];

// pattern[patternIdx, INF) == fname[fnameIdx, INF) 일치여부 판별
bool match(int patternIdx, int fnameIdx)
{
    int &ret = cache[patternIdx][fnameIdx];
    if (ret != -1)
        return ret;

    // base case 1
    if (patternIdx == pattern.size() && fnameIdx == fname.size())
        return ret = true;

    char ch_pattern = pattern[patternIdx];
    char ch_fname = fname[fnameIdx];

    if (ch_pattern == '*')
    {
        for (int nSkip = 0; nSkip + fnameIdx <= fname.size(); nSkip++)
            if (match(patternIdx + 1, fnameIdx + nSkip))
                return ret = true;
    }
    // base case 2
    else if (ch_pattern != '?' && ch_pattern != ch_fname)
        return ret = false;
    else
        return ret = match(patternIdx + 1, fnameIdx + 1);

    return ret = false;
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
            memset(cache, -1, sizeof(cache));
            fname = fnames[i];
            if (match(0, 0))
                cout << fname << endl;
        }
    }
}