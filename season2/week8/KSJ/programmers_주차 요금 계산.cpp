#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

int timeToMinute(const string &time)
{
    stringstream ss(time);
    int hour, minute;
    char column;
    ss >> hour >> column >> minute;

    return 60 * hour + minute;
}

vector<int> solution(vector<int> fees, vector<string> records)
{
    map<string, int> entryTime;
    map<string, int> parkedTime;
    vector<int> answer;

    int defaultTime = fees[0], defaultFee = fees[1], unitTime = fees[2], unitFee = fees[3];
    int endOfDay = timeToMinute("23:59");

    for (const string &record : records)
    {
        stringstream ss(record);
        string time, carNumber, action;
        ss >> time >> carNumber >> action;

        if (action == "IN")
            entryTime[carNumber] = timeToMinute(time);
        else // "OUT"
        {
            int duration = timeToMinute(time) - entryTime[carNumber];
            parkedTime[carNumber] += duration;
            entryTime.erase(carNumber);
        }
    }

    for (auto entry : entryTime)
    {
        parkedTime[entry.first] += endOfDay - entry.second;
    }

    for (auto parked : parkedTime)
    {
        int time = parked.second;
        int fee = defaultFee;
        if (defaultTime < time)
        {
            fee += (int)ceil((time - defaultTime) / (double)unitTime) * unitFee;
        }
        answer.push_back(fee);
    }

    return answer;
}