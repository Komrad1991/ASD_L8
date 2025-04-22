#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int l;
    cin >> l; cin.ignore();
    int n;
    cin >> n; cin.ignore();
    vector<pair<int, int>> cuts;
    for (int i = 0; i < n; i++)
    {
        int length;
        int value;
        cin >> length >> value; cin.ignore();
        cuts.push_back(make_pair(length, value));
    }
    vector<long long> dp(l + 1, 0);

    for (int i = 1; i <= l; ++i)
    {
        for (const auto& cut : cuts)
        {
            int l = cut.first;
            int v = cut.second;
            if (i >= l)
            {
                if (dp[i - l] + v > dp[i])
                {
                    dp[i] = dp[i - l] + v;
                }
            }
        }
    }

    cout << dp[l] << endl;
}