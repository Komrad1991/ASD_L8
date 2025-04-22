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
    int n;
    cin >> n; cin.ignore();
    int c;
    cin >> c; cin.ignore();
    vector<int> all_b;
    for (int i = 0; i < n; i++)
    {
        int b;
        cin >> b; cin.ignore();
        all_b.push_back(b);
    }
    int total_b = 0;
    for (auto x : all_b)
    {
        total_b += x;
    }
    if (total_b < c)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    int avr = total_b / all_b.size() - 1;

    std::sort(all_b.begin(), all_b.end());
    int needed = c;
    vector<int> payers(n, 0);

    for (int i = 0; i < n; i++)
    {
        int should = needed / (n - i);
        payers[i] = min(all_b[i], should);
        needed -= payers[i];
    }
    int i = n - 1;
    while (needed > 0 && i >= 0)
    {
        // Calculate how much more can be added without exceeding the budget
        int add = min(all_b[i] - payers[i], needed);
        payers[i] += add;
        needed -= add;
        --i;
    }
    sort(payers.begin(), payers.end());
    for (int amount : payers)
    {
        cout << amount << endl;
    }
}