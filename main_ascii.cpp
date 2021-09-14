// https://www.codingame.com/ide/puzzle/ascii-art

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ?";
const char undefinedCharacter = '?';

int main()
{
    int letterWidth, letterHeight;
    cin >> letterWidth;
    cin.ignore();
    cin >> letterHeight;
    cin.ignore();

    map<char, int> characterPosMap;
    for (int i = 0; i < characters.length(); i++)
        characterPosMap[characters[i]] = i * letterWidth;

    string text;
    getline(cin, text);

    stringstream ss;
    for (int i = 0; i < letterHeight; i++) {
        string ROW;
        getline(cin, ROW);

        ss << ROW;
    }

    string ASCIIData = ss.str();

    for (int i = 0; i < letterHeight; i++)
    {
        for (int j = 0; j < text.length(); j++)
        {
            char ch = text[j];
            if (characterPosMap.find(ch) == characterPosMap.end())
            {
                char upper = toupper(ch);
                ch = characterPosMap.find(upper) != characterPosMap.end() ? upper : undefinedCharacter;
            }
            string letterRow = ASCIIData.substr(characterPosMap[ch] + i * characters.length() * letterWidth, letterWidth);
            cout << letterRow;
        }

        cout << endl;
    }
}