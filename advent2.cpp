#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int MAX_RED = 12;
int MAX_GREEN = 13;
int MAX_BLUE = 14;

vector<int> validGames;
int finalAnswer = 0;

vector<string> splitString(string str, string delimiter) {
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        // std::cout << token << std::endl;
        str.erase(0, pos + delimiter.length());
        result.push_back(token);
    }
    result.push_back(str);
    return result;
}

bool checkResults (vector<string> results) {
    bool redPossible = true;
    bool greenPossible = true;
    bool bluePossible = true;

    for (const string set : results) {

        vector<string> colorSets = splitString(set, ", ");

        for (const string colorSet : colorSets) {
            int space = colorSet.find(" ");
            string count = colorSet.substr(0, space);
            string color = colorSet.substr(space + 1);

            if (color == "red") {
                if (stoi(count) > MAX_RED) {
                    redPossible = false;
                }
            }

            if (color == "green") {
                if (stoi(count) > MAX_GREEN) {
                    greenPossible = false;
                }
            }

            if (color == "blue") {
                if (stoi(count) > MAX_BLUE) {
                    bluePossible = false;
                }
            }
        }
    }

    if (redPossible && greenPossible && bluePossible) {
        return true;
    }

    return false;
}

string getGameId (string game) {
    size_t semicolonPos = game.find(":");
    size_t startPos = game.find("Game ") + 5;

    string id = game.substr(startPos, semicolonPos - startPos);
    return id;
}

string parseGame (string results) {
    string game = getGameId(results);
    cout << "Parsing GAME: " + game;
    cout << endl;

    string cleaned = results.substr(results.find(": ") + 2);

    vector<string> parsedResults = splitString(cleaned, "; ");
    bool valid = checkResults(parsedResults);

    if (valid == 1) {
        cout << "Game " + game + " valid" << endl;
        validGames.push_back(stoi(game));
        finalAnswer += stoi(game);
    } else {
        cout << "Game " + game + " invalid" << endl;
    }

    return "";
}

int main()
{
    ifstream results;
    string game;

    results.open("input2.txt");

    while (getline(results, game))
    {
        string parsed = parseGame(game);
    }
    results.close();

    cout << "Final answer: " + to_string(finalAnswer) << endl;
}