#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int INF = 987654321;
const int MAX_LEN = int(1e4);

vector<int> digits;

int cache[MAX_LEN];

// digits[left, right)까지의 최소 난이도 반환
int getLevel(int left, int right)
{
    // 모든 숫자가 같을 때
    bool level1 = true;
    for (int i = left; i < right; ++i)
        if (digits[i] != digits[left])
        {
            level1 = false;
            break;
        }
    if (level1)
        return 1;

    // 숫자가 1씩 단조 증가/감소할 때
    bool level2 = true;
    for (int i = left; i + 1 < right; ++i)
        if (abs(digits[left] - digits[left + 1]) != 1 ||
            digits[left] - digits[left + 1] != digits[i] - digits[i + 1])
        {
            level2 = false;
            break;
        }
    if (level2)
        return 2;

    // 두 개의 숫자가 번갈아 가며 출현할 때
    bool level4 = true;
    int n1 = digits[left], n2 = digits[left + 1];
    for (int i = left; i < right; i += 2)
        if (n1 != digits[i])
        {
            level4 = false;
            break;
        }
    for (int i = left + 1; i < right; i += 2)
        if (n2 != digits[i])
        {
            level4 = false;
            break;
        }
    if (level4)
        return 4;

    // 숫자가 등차 수열을 이룰 때
    bool level5 = true;
    int diff = digits[left] - digits[left + 1];
    for (int i = left; i + 1 < right; ++i)
        if (digits[i] - digits[i + 1] != diff)
        {
            level5 = false;
            break;
        }
    if (level5)
        return 5;

    return 10;
}

// digits[pos...]의 최소 난이도 반환
int solve(int pos)
{
    // BASE CASE
    if (pos == digits.size())
        return 0;

    int &ret = cache[pos];

    if (ret != -1)
        return ret;

    ret = INF;
    for (int offset = 3; pos + offset <= digits.size() && offset <= 5; ++offset)
    {
        int level = getLevel(pos, pos + offset) + solve(pos + offset);
        ret = min(ret, level);
    }

    return ret;
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        string str_digits;
        cin >> str_digits;

        digits.clear();
        for (int i = 0; i < str_digits.size(); ++i)
            digits.push_back(str_digits[i] - '0');

        memset(cache, -1, sizeof(cache));
        cout << solve(0) << endl;
    }
    return 0;
}