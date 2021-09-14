// Puzzle: https://www.codingame.com/ide/puzzle/custom-game-of-life

#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr char fieldAliveSymbol = 'O';
constexpr char fieldDeadSymbol = '.';
constexpr char conditionAliveSymbol = '1';
constexpr char conditionDeadSymbol = '0';

struct Point
{
    int x;
    int y;
};

vector<Point> getNeighboringPoints(Point point)
{
    return {
        { point.x - 1, point.y + 1 },
        { point.x, point.y + 1 },
        { point.x + 1, point.y + 1 },
        { point.x + 1, point.y },
        { point.x + 1, point.y - 1 },
        { point.x, point. y - 1 },
        { point.x - 1, point.y - 1 },
        { point.x - 1, point.y }
    };
}

void printField(const string& field, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            cout << field[index];
        }
        cout << endl;
    }
}

int main()
{
    int height;
    int width;
    int n;
    string alive;
    string dead;
    string field;
    string fieldNext;

    cin >> height >> width >> n; 
    cin.ignore();
    getline(cin, alive);
    getline(cin, dead);

    stringstream ss;
    for (int i = 0; i < height; i++) {
        string line;
        getline(cin, line);

        ss << line;
    }

    field = ss.str();
    fieldNext = field;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                int currentCellIndex = j * width + i;
                int aliveNeighbours = 0;
                vector<Point> neighboringPoints = getNeighboringPoints({ i, j });

                for (Point& p: neighboringPoints) // check neighbours
                {
                    if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height)
                    {
                        int neighboringCellIndex = p.y * width + p.x;
                        if (field[neighboringCellIndex] == fieldAliveSymbol)
                            aliveNeighbours++;
                    }
                }

                if (field[currentCellIndex] == fieldAliveSymbol) // if alive
                {
                    if (alive[aliveNeighbours] == conditionAliveSymbol)
                        fieldNext[currentCellIndex] = fieldAliveSymbol;
                    else
                        fieldNext[currentCellIndex] = fieldDeadSymbol;
                }
                else
                {
                    if (dead[aliveNeighbours] == conditionAliveSymbol)
                        fieldNext[currentCellIndex] = fieldAliveSymbol;
                    else
                        fieldNext[currentCellIndex] = fieldDeadSymbol;
                }
            }
        }

        field = fieldNext;
    }

    printField(field, width, height);
}