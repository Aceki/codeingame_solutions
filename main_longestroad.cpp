// Puzzle: https://www.codingame.com/ide/puzzle/longest-road

#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <climits>
#include <memory>
#include <algorithm>

using namespace std;

struct Point
{
    int x;
    int y;
};

bool operator==(const Point& obj1, const Point& obj2)
{
    return obj1.x == obj2.x && obj1.y == obj2.y;
}

struct NodeData
{
    Point point;
    int length;
};

class Node
{
public:
    Node(NodeData data, shared_ptr<Node> previous = nullptr) : m_data(data), m_previous(previous) { }

    Node(const Node&) = delete;

    const shared_ptr<Node> previous() const { return m_previous; }

    NodeData& data() { return m_data; }

    Node& operator=(const Node&) = delete;
private:
    shared_ptr<Node> m_previous;
    NodeData m_data;
};

namespace std
{
    template<>
    struct hash<Point>
    {
        size_t operator()(const Point& obj) const
        {
            return hash<int>()(obj.x) + hash<int>()(obj.y);
        }
    };
}

vector<Point> getNeighboringPoints(Point point);
bool inBounds(Point point, int width, int height);

int main()
{
    int boardLength;
    cin >> boardLength; 
    cin.ignore();
    vector<string> field(boardLength);

    for (int i = 0; i < boardLength; i++) {
        string line;
        getline(cin, line);

        field[i] = line;
    }

    vector<shared_ptr<Node>> roads;
    for (int j = 0; j < boardLength; j++)
    {
        for (int i = 0; i < boardLength; i++)
        {
            if (field[j][i] == '#')
                continue;
            
            stack<shared_ptr<Node>> nodes;
            unordered_set<Point> visitedPoints;

            Point startPoint = { i, j };
            char startPlayer = tolower(field[j][i]);
            shared_ptr<Node> startNode(new Node({startPoint, 0}));

            nodes.push(startNode);

            visitedPoints.insert(startNode->data().point);

            while (nodes.size() > 0)
            {
                shared_ptr<Node> previousNode = nodes.top(); 
                nodes.pop();
                Point previousPoint = previousNode->data().point;
                if (islower(field[previousPoint.y][previousPoint.x]))
                    previousNode->data().length++;

                vector<Point> neighboringPoints = getNeighboringPoints({ previousPoint.x, previousPoint.y });
                bool hasNeighbours = false;
                for (Point& currentPoint: neighboringPoints)
                {
                    if (inBounds(currentPoint, boardLength, boardLength) 
                    &&  visitedPoints.find(currentPoint) == visitedPoints.end()
                    &&  tolower(field[currentPoint.y][currentPoint.x]) == tolower(field[previousPoint.y][previousPoint.x]))
                    {
                        hasNeighbours = true;
                        shared_ptr<Node> nextNode(new Node({currentPoint, previousNode->data().length}, previousNode));
                        nodes.push(nextNode);
                        visitedPoints.insert(currentPoint);
                    }
                }

                if (previousNode->data().length > 5 && !hasNeighbours)
                    roads.push_back(previousNode);  
            }
        }
    }

    if (roads.size() > 0)
    {
        auto maxIter = max_element(roads.begin(), roads.end(), [](shared_ptr<Node> f, shared_ptr<Node> s) {
            return f->data().length < s->data().length;
        });

        shared_ptr<Node> maxNode = *maxIter;

        char bestPlayer = toupper(field[maxNode->data().point.y][maxNode->data().point.x]);
        int bestLength = maxNode->data().length;

        cout << bestPlayer  << ' ' << bestLength;
    }
    else
        cout << 0;
}

vector<Point> getNeighboringPoints(Point point)
{
    return {
        { point.x, point.y + 1 },
        { point.x + 1, point.y },
        { point.x, point. y - 1 },
        { point.x - 1, point.y }
    };
}

bool inBounds(Point point, int width, int height)
{
    return point.x >= 0 && point.x < width && point.y >= 0 && point.y < height;
}