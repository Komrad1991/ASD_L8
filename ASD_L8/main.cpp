#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<char, string> morseCode = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};

string wordToMorse(const string& word)
{
    string morse;
    for (char c : word)
    {
        morse += morseCode[toupper(c)];
    }
    return morse;
}

int main()
{
    string morseSequence;
    getline(cin, morseSequence);
    int N;
    cin >> N;
    cin.ignore();

    vector<string> dictionary(N);
    for (int i = 0; i < N; ++i)
    {
        getline(cin, dictionary[i]);
    }

    unordered_map<string, int> morseWordCount;
    for (const string& word : dictionary)
    {
        string morseWord = wordToMorse(word);
        morseWordCount[morseWord]++;
    }

    int L = morseSequence.length();
    vector<unsigned long long> dp(L + 1, 0);
    dp[0] = 1;

    for (int i = 0; i <= L; ++i)
    {
        if (dp[i] == 0)
        {
            continue;
        }
        for (int len = 1; len <= 100 && i + len <= L; ++len)
        {
            string substring = morseSequence.substr(i, len);
            if (morseWordCount.find(substring) != morseWordCount.end())
            {
                dp[i + len] += dp[i] * morseWordCount[substring];
            }
        }
    }

    cout << dp[L] << endl;

    return 0;
}