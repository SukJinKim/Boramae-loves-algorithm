#include <iostream>
#include <string>

using namespace std;

const int MAX = int(1e9) + 1;
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

// length[i] = i세대 드래곤 커브의 길이
int length[51];

void precalc()
{
    length[0] = 1;
    for (int i = 1; i <= 50; ++i)
        length[i] = min(MAX, length[i - 1] * 2 + 2);
}

// dragonCurve를 generations세대까지 진화시킬때 skip번째 문자 반환
char expand(const string &dragonCurve, int generations, int skip)
{
    // BASE CASE
    if (generations == 0)
        return dragonCurve[skip];

    for (int i = 0; i < dragonCurve.size(); ++i)
        if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y')
        {
            if (skip >= length[generations])
                skip -= length[generations];
            else if (dragonCurve[i] == 'X')
                return expand(EXPAND_X, generations - 1, skip);
            else
                return expand(EXPAND_Y, generations - 1, skip);
        }
        // +나 F를 만난 경우
        else if (skip > 0)
            --skip;
        else
            return dragonCurve[i];
    return '#';
}

int main()
{
    int c;
    cin >> c;

    precalc();
    while (c--)
    {
        int n, p, l;
        cin >> n >> p >> l;

        for (int i = 0; i < l; ++i)
            cout << expand("FX", n, (p - 1) + i);
        cout << endl;
    }

    return 0;
}