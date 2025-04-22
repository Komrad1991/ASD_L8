#include <iostream>
#include <vector>

struct Point
{
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double costTr(const Point& a, const Point& b, const Point& c)
{
    double ab = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    double bc = sqrt((b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y));
    double ca = sqrt((c.x - a.x) * (c.x - a.x) + (c.y - a.y) * (c.y - a.y));
    return ab + bc + ca;
}

double task13(const std::vector<Point>& polygon)
{
    int n = polygon.size();
    if (n < 3) return 0;

    std::vector<std::vector<double>> dp(n, std::vector<double>(n, 0));

    for (int gap = 2; gap < n; gap++)
    {
        for (int i = 0; i + gap < n; i++)
        {
            int j = i + gap;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++)
            {
                double cost = dp[i][k] + dp[k][j] +
                    costTr(polygon[i], polygon[k], polygon[j]);
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[0][n - 1];
}

long long task6(int n)
{
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (n == 3) return 2;

    std::vector<long long> dp(n+1, 0);
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 2;

    for (int i = 4; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + 1; 
        for (int k = 3; k <= i; ++k)
        {
            if (i - k - 1 >= 0)
            {
                dp[i] += dp[i - k - 1];
            }
        }
    }

    return dp[n];
}


std::vector<std::vector<int>> prefixes(const std::vector<std::vector<int>>& matrix)
{
    int M = matrix.size();
    if (M == 0) return {};
    int N = matrix[0].size();

    std::vector<std::vector<int>> prefix(M + 1, std::vector<int>(N + 1, 0));

    for (int i = 1; i <= M; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            prefix[i][j] = matrix[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    return prefix;
}

int subSum(const std::vector<std::vector<int>>& prefix, int i, int j, int m, int n)
{
    int total = prefix[i + m][j + n];
    int left = prefix[i][j + n];
    int top = prefix[i + m][j];
    int corner = prefix[i][j];

    return total - left - top + corner;
}

void task18(const std::vector<std::vector<int>>& matrix, int m, int n)
{
    int M = matrix.size();
    if (M == 0) return;
    int N = matrix[0].size();

    if (m <= 0 || n <= 0 || m > M || n > N)  return;

    auto prefix = prefixes(matrix);

    int minSum = INT_MAX;
    int minRow = -1, minCol = -1;

    for (int i = 0; i <= M - m; ++i)
    {
        for (int j = 0; j <= N - n; ++j)
        {
            int currentSum = subSum(prefix, i, j, m, n);

            if (currentSum < minSum)
            {
                minSum = currentSum;
                minRow = i;
                minCol = j;
            }
        }
    }

    std::cout <<"From: " << minRow << "*" << minCol << " to: " << minRow + m << "*" << minCol + n << " sum:" << minSum << std::endl;
}

int main()
{
    std::cout << "Task6: " << task6(50) << std::endl;
    std::vector<Point> polygon = {
        {0, 1},          
        {-0.951, 0.309},  
        {-0.588, -0.809}, 
        {0.588, -0.809}, 
        {0.951, 0.309}    
    };
    std::cout << "Task13: " << task13(polygon) << std::endl;

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int m = 2, n = 3;
    task18(matrix, m, n);
}