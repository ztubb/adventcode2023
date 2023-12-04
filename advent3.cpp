#include <fstream>
#include <string>
#include <iostream>

using namespace std;

vector<string> symbols = { "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "/", "=" };
vector<string> partNumbers;
int sumPartNumbers = 0;

vector<string> findNumbers (string line) {
    vector<string> foundNumbers;
    string tmpNumber;
    bool building = false;

    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            building = true;
            tmpNumber += line[i];
        } else {
            if (building) {
                foundNumbers.push_back(tmpNumber);
            }
            tmpNumber = "";
            building = false;
        }
    }

    if (building == true) {
        foundNumbers.push_back(tmpNumber);
    }

    return foundNumbers;
}

vector<string> checkSymbolsInline (vector<string> numbers, string line) {
    vector<string> localNumbers = numbers;

    for (string number : numbers) {
        int start = line.find(number);
        int end = start + number.length() - 1;

        // check preceding char for symbol
        if (start > 0 && find(symbols.begin(), symbols.end(), line.substr(start - 1, 1)) != symbols.end()) {
            cout << number + " is a part" << endl;

            // store off part info
            partNumbers.push_back(number);
            sumPartNumbers += stoi(number);

            auto it = find(localNumbers.begin(), localNumbers.end(), number);
            if (it != localNumbers.end()) {
                localNumbers.erase(it);
            }
        }

        // check subsequent char for symbol
        else if (end < line.length() - 1 && find(symbols.begin(), symbols.end(), line.substr(end + 1, 1)) != symbols.end()) {
            cout << number + " is a part" << endl;
            
            // store off part info
            partNumbers.push_back(number);
            sumPartNumbers += stoi(number);
            
            auto it = find(localNumbers.begin(), localNumbers.end(), number);
            if (it != localNumbers.end()) {
                localNumbers.erase(it);
            }
        }

         // remove occurrence in string to prevent re-check if there are multiple instance
        for (int k = start; k < start + number.length(); k++) {
            line[k] = '.';
        }

    }

    return localNumbers;
}

vector<string> checkSymbolsAdjLine (vector<string> numbers, string line, string adjLine) {
    vector<string> localNumbers = numbers;

    if (adjLine == "") {
        return localNumbers;
    }

    for (int i = 0; i < numbers.size(); i++) {
        string number = numbers[i];
        int start = line.find(number);
        int end = start + number.length() + 1;

        for (int j = start - 1; j < end; j++) {
            while (j < 0) {
                j++;
            }

            if (find(symbols.begin(), symbols.end(), adjLine.substr(j, 1)) != symbols.end()) {
                cout << number + " is a part" << endl;

                // store off part info
                partNumbers.push_back(number);
                sumPartNumbers += stoi(number);

                // remove occurrence in string to prevent re-check if there are multiple instance
                for (int k = start; k < end - 1; k++) {
                    line[k] = '.';
                }
                break;
            }
        }
        // remove occurrence in string to prevent re-check if there are multiple instance
        for (int k = start; k < start + number.length(); k++) {
            line[k] = '.';
        }

    }
    return localNumbers;
}

int parseLine(string prevLine, string line, string nextLine) {
    vector<string> prevLineNumbers = findNumbers(prevLine);
    vector<string> nextLineNumbers = findNumbers(nextLine);

    vector<string> lineNumbers = findNumbers(line);

    if (lineNumbers.size() > 0) {
        lineNumbers = checkSymbolsInline(lineNumbers, line);
    }

    // check any remaining numbers against symbols in other rows
    if (lineNumbers.size() > 0) {
        lineNumbers = checkSymbolsAdjLine(lineNumbers, line, nextLine);
    }

    if (lineNumbers.size() > 0) {
        lineNumbers = checkSymbolsAdjLine(lineNumbers, line, prevLine);
    }

    return 0;
}

int main()
{
    ifstream file;
    file.open("input3.txt");

    string prevLine;
    string currLine;
    string nextLine;
    string tmpLine;
    int lineCount = 0;

    getline(file, currLine);
    lineCount++;

    getline(file, nextLine);
    lineCount++;

    parseLine("", currLine, nextLine);

    while (getline(file, tmpLine)) {
        lineCount++;
        prevLine = currLine;
        currLine = nextLine;
        nextLine = tmpLine;

        parseLine(prevLine, currLine, nextLine);
    }

    // check last line against next to last line
    parseLine(currLine, nextLine, "");

    file.close();

    cout << "Total lines: " + to_string(lineCount) << endl;
    cout << "Sum of part numbers: " + to_string(sumPartNumbers);
}