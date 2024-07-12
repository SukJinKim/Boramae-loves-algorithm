#include <iostream>
#include <string>
#include <stack>

using namespace std;

string match(string formula)
{
    stack<char> opens;

    for (char paren : formula)
    {
        if (paren == '(' || paren == '[' || paren == '{')
            opens.push(paren);
        else
        {
            if (!opens.empty() &&
                ((opens.top() == '(' && paren == ')') ||
                 (opens.top() == '[' && paren == ']') ||
                 (opens.top() == '{' && paren == '}')))
                opens.pop();
            else
                return "NO";
        }
    }

    return (opens.empty()) ? "YES" : "NO";
}

int main()
{
    int c;
    cin >> c;

    while (c--)
    {
        string formula;
        cin >> formula;

        cout << match(formula) << endl;
    }
}