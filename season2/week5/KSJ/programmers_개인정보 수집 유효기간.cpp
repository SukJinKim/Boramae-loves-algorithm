#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> validPeriods;

int dateToDays(int year, int month, int day)
{
    month += year * 12;
    day += month * 28;
    return day;
}

int dateToDays(string date)
{
    stringstream ss(date);
    int year, month, day;
    char dot;
    ss >> year >> dot >> month >> dot >> day;

    return dateToDays(year, month, day);
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies)
{
    vector<int> answer;

    int dToday = dateToDays(today);

    for (const string term : terms)
    {
        stringstream ss(term);
        string termId, period;
        ss >> termId >> period;

        validPeriods[termId] = stoi(period);
    }

    int privacyId = 1;
    for (const string privacy : privacies)
    {
        stringstream ss(privacy);
        int year, month, day;
        char dot;
        string termId;
        ss >> year >> dot >> month >> dot >> day >> termId;

        int expiredYear = year;
        int expiredMonth = month + validPeriods[termId];
        int expiredDay = day;
        int dExpired = dateToDays(expiredYear, expiredMonth, expiredDay);

        if (dExpired <= dToday)
            answer.push_back(privacyId);

        privacyId++;
    }

    return answer;
}