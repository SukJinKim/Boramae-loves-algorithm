#include <string>
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;



int solution(vector<int> queue1, vector<int> queue2) {
    long long L = accumulate(queue1.begin(), queue1.end(), 0);
    long long R = accumulate(queue2.begin(), queue2.end(), 0);
    long long sum = L + R;
    long long target = sum / 2;
    
    if(sum % 2 != 0)
        return -1;
    
    int n = queue1.size();
    vector<int> total(queue1);
    for(int q2 : queue2)
        total.push_back(q2);
    
    int ptr1 = 0, ptr2 = n;
    int answer = 0;
    // L = sum of total[ptr1, ptr2)
    while((ptr1 <= total.size()) && (ptr2 <= total.size()))
    {
        if(L > target)
        {
            L -= total[ptr1];
            ptr1++;
        }
        else if(L < target)
        {
            L += total[ptr2];
            ptr2++;
        }
        else
            return answer;
        
        answer++;
    }
    
    return -1;
}