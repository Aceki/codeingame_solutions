// Puzzle: https://www.codingame.com/training/medium/what-the-brainfuck

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>

const char* syntaxError = "SYNTAX ERROR";
const char* outOfBounds = "POINTER OUT OF BOUNDS";
const char* incorrectValue = "INCORRECT VALUE";

using namespace std;

bool validateBrackets(const string& program)
{
    int brackets = 0;
    for (int i = 0; i < program.length(); i++)
    {
        if (program[i] == '[')
            brackets++;
        else if (program[i] == ']')
            brackets--;
    }
    
    return brackets == 0;
}

int main()
{
    int linesCount, cellsCount, inputsCount;
    cin >> linesCount >> cellsCount >> inputsCount; 
    cin.ignore();
    vector<int> inputs(inputsCount);
    vector<unsigned char> cells(cellsCount, 0);
    stringstream ss;
    string program;

    for (int i = 0; i < linesCount; i++) {
        string line;
        getline(cin, line);

        ss << line;
    }

    program = ss.str();

    for (int i = 0; i < inputsCount; i++) {
        int ch;
        cin >> ch; 
        cin.ignore();

        inputs.push_back(ch);
    }

    if (!validateBrackets(program))
    {
        cout << syntaxError << endl;
        terminate();
    }

    int currentCellIndex = 0;
    for (int i = 0; i < program.length(); i++)
    {
        switch (program[i])
        {
        case '>':
            if (currentCellIndex < cellsCount - 1)
                currentCellIndex++;
            else
            {
                cout << outOfBounds << endl;
                terminate();
            }
            break;
        case '<':
            if (currentCellIndex > 0)
                currentCellIndex--;
            else
            {
                cout << outOfBounds << endl;
                terminate();
            }
            break;
        case '+':
            if (cells[currentCellIndex] < 255)
                cells[currentCellIndex]++;
            else
            {
                cout << incorrectValue  << endl;
                terminate();
            }
            break;
        case '-':
            if (cells[currentCellIndex] > 0)
                cells[currentCellIndex]--;
            else
            {
                cout << incorrectValue << endl;
                terminate();
            }
            break;
        case '.':
            cout << cells[currentCellIndex];
            break;
        case ',':
            cells[currentCellIndex]  = inputs.back();
            inputs.pop_back();
            break;
        case '[':
            if (cells[currentCellIndex] == 0) 
            {
                int skip = 1;
                while (skip > 0) 
                {
                    i++;
                    if (program[i] == '[')
                        skip++;
                    if (program[i] == ']')
                        skip--;
                }
            }
            break;
        case ']':
            if (cells[currentCellIndex] != 0) 
            {
                int skip = 1;
                while (skip > 0) 
                {
                    i--;
                    if (program[i] == '[')
                        skip--;
                    if (program[i] == ']')
                        skip++;
                }
                i--;
            }
            break;
        default:
            break;
        }
    }

    cout << endl;
}