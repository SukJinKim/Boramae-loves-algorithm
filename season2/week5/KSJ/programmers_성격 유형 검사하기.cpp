#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cmath>

using namespace std;

unordered_map<char, int> characterScore;

int choiceToScore(int choice)
{
    int ret;
    switch (choice)
    {
    case 1:
        ret = -3;
        break;
    case 2:
        ret = -2;
        break;
    case 3:
        ret = -1;
        break;
    case 4:
        ret = 0;
        break;
    case 5:
        ret = 1;
        break;
    case 6:
        ret = 2;
        break;
    case 7:
        ret = 3;
        break;
    }

    return ret;
}

string solution(vector<string> survey, vector<int> choices)
{
    string answer = "RCJA";
    int n = survey.size();

    for (int i = 0; i < n; ++i)
    {
        char disagree = survey[i][0], agree = survey[i][1];
        int score = choiceToScore(choices[i]);
        if (score < 0)
            characterScore[disagree] += abs(score);
        else if (score > 0)
            characterScore[agree] += score;
    }

    char category1 = (characterScore['R'] >= characterScore['T']) ? 'R' : 'T';
    char category2 = (characterScore['C'] >= characterScore['F']) ? 'C' : 'F';
    char category3 = (characterScore['J'] >= characterScore['M']) ? 'J' : 'M';
    char category4 = (characterScore['A'] >= characterScore['N']) ? 'A' : 'N';

    answer[0] = category1;
    answer[1] = category2;
    answer[2] = category3;
    answer[3] = category4;

    return answer;
}