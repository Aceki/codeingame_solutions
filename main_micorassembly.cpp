// Puzzle: https://www.codingame.com/ide/puzzle/micro-assembly

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

enum ArgumentType
{
    Register,
    Immediate
};

enum Mnemonic 
{
    MOV,
    ADD,
    SUB,
    JNE
};

unordered_map<string, int> reg = {
    { "a", 0 },
    { "b", 0 },
    { "c", 0 },
    { "d", 0 }   
};

unordered_map<string, Mnemonic> mnemonics = {
    { "MOV", MOV },
    { "ADD", ADD },
    { "SUB", SUB },
    { "JNE", JNE }
};

ArgumentType checkArgumentType(const string& str)
{
    if (reg.find(str) != reg.end())
        return Register;
    return Immediate;
}

int main()
{
    int n;
    cin >> reg["a"] >> reg["b"] >> reg["c"] >> reg["d"]; 
    cin.ignore();
    cin >> n; 
    cin.ignore();

    vector<string> instructions;

    for (int i = 0; i < n; i++) {
        string instruction;
        getline(cin, instruction);

        instructions.push_back(instruction);
    }

    stringstream ss;
    for (int i = 0; i < n; i++)
    {
        ss << instructions[i];

        string mnemonic;
        string arg1, arg2, arg3;
        int temp;

        ss >> mnemonic;

        switch (mnemonics[mnemonic])
        {
            case MOV:
                ss >> arg1 >> arg2;
                reg[arg1] = checkArgumentType(arg2) == Register ? reg[arg2] : atoi(arg2.c_str());
                break;
            case ADD:
                ss >> arg1 >> arg2 >> arg3;
                temp = checkArgumentType(arg2) == Register ? reg[arg2] : atoi(arg2.c_str());
                temp += checkArgumentType(arg3) == Register ? reg[arg3] : atoi(arg3.c_str());
                reg[arg1] = temp;
                break;
            case SUB:
                ss >> arg1 >> arg2 >> arg3;
                temp = checkArgumentType(arg2) == Register ? reg[arg2] : atoi(arg2.c_str());
                temp -= checkArgumentType(arg3) == Register ? reg[arg3] : atoi(arg3.c_str());
                reg[arg1] = temp;
                break;
                break;
            case JNE:
                ss >> arg1 >> arg2 >> arg3;
                temp = reg[arg2];
                temp -= checkArgumentType(arg3) == Register ? reg[arg3] : atoi(arg3.c_str());
                if (temp != 0)
                    i = atoi(arg1.c_str()) - 1;
                break;
            default:
                break;
        }
        ss.clear();
    }

    cout << reg["a"] << ' ' << reg["b"] << ' ' << reg["c"] << ' ' << reg["d"];
    cout << endl;
}

