// Puzzle: https://www.codingame.com/ide/puzzle/mime-type

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

const char* unknownMessage = "UNKNOWN";

int main()
{
    int N, Q;
    cin >> N; 
    cin.ignore();
    cin >> Q; 
    cin.ignore();

    unordered_map<string, string> m;
    for (int i = 0; i < N; i++) 
    {
        string extension;
        string mimeType;

        cin >> extension >> mimeType; 
        cin.ignore();

        for_each(extension.begin(), extension.end(), [](char& ch) { ch = tolower(ch); });
        m[extension] = mimeType; 
    }

    for (int i = 0; i < Q; i++) 
    {
        string fileName;
        getline(cin, fileName);

        int lastDot = fileName.find_last_of('.');
        if (lastDot == -1 && lastDot != fileName.length() - 1)
        {
            cout << unknownMessage << endl;
            continue;
        }

        string fileExtension = fileName.substr(lastDot + 1, fileName.length() - lastDot);
        for_each(fileExtension.begin(), fileExtension.end(), [](char& ch) { ch = tolower(ch); });

        if (m.find(fileExtension) != m.end())
            cout << m[fileExtension] << endl;
        else
            cout << unknownMessage << endl;
    }
}