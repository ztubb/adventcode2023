#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits.h>
#include <map>

using namespace std;

std::vector<std::string> spelledDigits = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
map<string, string> spelledDigitMap = {{"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

tuple<int, string> getFirstSpelledDigit(const std::string &word)
{
    int location = INT_MAX;
    string finalDigit;

    for (string digit : spelledDigits)
    {
        int index = word.find(digit);

        if (index > -1)
        {
            if (index < location)
            {
                location = index;
                finalDigit = digit;
            }

            if (index == 0)
            {
                break;
            }
        }
    }
    return make_tuple(location, finalDigit);
}

tuple<int, string> getLastSpelledDigit(const std::string &word)
{
    int location = -1;
    string finalDigit;

    for (string digit : spelledDigits)
    {

        vector<int> positions;
        int index = word.find(digit);

        while (index != string::npos)
        {
            positions.push_back(index);
            index = word.find(digit, index + 1);
        }

        if (positions.size() > 0)
        {
            auto lastOccurrence = max_element(positions.begin(), positions.end());
            if (*lastOccurrence > location)
            {
                location = *lastOccurrence;
                finalDigit = digit;
            }
        }
    }
    return make_tuple(location, finalDigit);
}

tuple<int, string> getFirstDigit(const std::string &word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (isdigit(word[i]))
        {
            return make_tuple(i, string() + word[i]);
        }
    }
    return make_tuple(0, "0");
}

tuple<int, string> getLastDigit(const std::string &word)
{
    for (int i = 0; i < word.length(); i++)
    {
        int index = word.length() - 1 - i;
        char letter = word[index];
        if (isdigit(letter))
        {
            return make_tuple(index, string() + word[index]);
        }
    }
    return make_tuple(0, "0");
}

string getFirstNumber(const std::string &word)
{

    if (isdigit(word[0]))
    {
        return string() + word[0];
    }

    int firstWordIndex;
    string firstWord;
    tie(firstWordIndex, firstWord) = getFirstDigit(word);

    int firstSpelledWordIndex;
    string firstSpelledWord;

    tie(firstSpelledWordIndex, firstSpelledWord) = getFirstSpelledDigit(word);

    if (firstWordIndex < firstSpelledWordIndex)
    {
        return firstWord;
    }
    else
    {
        return spelledDigitMap.at(firstSpelledWord);
    }
    return "0";
}

string getLastNumber(const std::string &word)
{
    if (isdigit(word[word.length() - 1]))
    {
        return string() + word[word.length() - 1];
    }

    int lastWordIndex;
    string lastWord;
    tie(lastWordIndex, lastWord) = getLastDigit(word);

    int lastSpelledWordIndex;
    string lastSpelledWord;

    tie(lastSpelledWordIndex, lastSpelledWord) = getLastSpelledDigit(word);

    if (lastWordIndex > lastSpelledWordIndex)
    {
        return lastWord;
    }
    else
    {
        return spelledDigitMap.at(lastSpelledWord);
    }
    return "";
}

int main()
{
    int total = 0;
    ifstream myfile;
    string word;

    myfile.open("input1.txt");

    while (getline(myfile, word))
    {
        cout << word + "...";
        cout << endl;

        string first = getFirstNumber(word);
        string last = getLastNumber(word);

        cout << first + "-" + last + " = " + first + last;
        cout << endl;

        total += stoi(first + last);
        cout << "total: " + to_string(total);
        cout << endl;
        cout << endl;
    }

    cout << "ANSWER: " + to_string(total);
    cout << endl;
    myfile.close();
}