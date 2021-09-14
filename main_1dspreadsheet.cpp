// Puzzle: https://www.codingame.com/training/easy/1d-spreadsheet

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdlib>

using namespace std;

class Node
{
public:
    Node(function<int()> func) : m_func(func) { }

    int calculate() const
    {
        if (!m_calculated)
        {
            m_result = m_func();
            m_calculated = true;
        }

        return m_result;
    }
private:
    const function<int()> m_func;
    mutable bool m_calculated = false;
    mutable int m_result;
};

bool isReference(string arg)
{
    return arg[0] == '$';
}

int main()
{
    int N;
    cin >> N; 
    cin.ignore();

    vector<int> cells(N, 0);
    vector<Node> nodes;
    unordered_map<string, function<int(int, int)>> operations;

    operations["VALUE"] = [] (int arg1, int arg2) { return arg1; };
    operations["ADD"] = [] (int arg1, int arg2) { return arg1 + arg2; };
    operations["SUB"] = [] (int arg1, int arg2) { return arg1 - arg2; };
    operations["MULT"] = [] (int arg1, int arg2) { return arg1 * arg2; };

    for (int i = 0; i < N; i++) {
        string operation;
        string arg1, arg2;

        cin >> operation >> arg1 >> arg2; 
        cin.ignore();

        function<int()> func = [&nodes, &operations, operation, arg1, arg2] () {
            int arg1Value, arg2Value;

            if (!isReference(arg1))
                arg1Value = atoi(arg1.c_str()); 
            else
                arg1Value = nodes[atoi(arg1.substr(1, arg1.length() - 1).c_str())].calculate();
            
            if (!isReference(arg2))
                arg2Value = atoi(arg2.c_str());
            else
                arg2Value = nodes[atoi(arg2.substr(1, arg2.length() - 1).c_str())].calculate();

            return operations[operation](arg1Value, arg2Value);
        };
        nodes.push_back(Node(func));
    }

    for (int i = 0; i < N; i++) {
        cout << nodes[i].calculate() << endl;
    }
}