#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ENCHANT
// 0강에서부터 시작

// +1
// +2
// +3

// n강을 할 때 강화하는 모든 경우의 수

// 예 : 3강을 하고 싶다. -> 4가지
// 1 + 1 + 1 
// 1 + 2 
// 2 + 1
// 3

// 예 : 4강 -> 7가지
// 1 + 1 + 1 + 1
// 1 + 2 + 1
// 1 + 1 + 2
// 1 + 3
// 2 + 1 + 1
// 2 + 2
// 3 + 1

vector<vector<int>> dp;
int  Enchant(int n, int m)
{
    
    if (n == 0)
       return 1;

    if (n < 0 || m == 0)
        return 0;
    

    if (dp[n][m] != -1)
        return dp[n][m];

    return dp[n][m] = Enchant(n, m - 1) + Enchant(n - m, m);

}

void printPermutations(vector<int>& permutation)
{
    while (true)
    {
        if (std::next_permutation(permutation.begin(), permutation.end()))
        {
            for (int value : permutation)
            {
                cout << value << " ";
            }
            cout << endl;
        }
        else
            break;
    }
    return;
}
int main()
{
    int n = 6; // 강화 횟수
    int m = 3; // 최대 강화 옵션
   
    dp = vector<vector<int>>(n + 1, vector<int>(m + 1, -1));

    vector<int> options;
    for (int i = 0; i <= m; i++)
    {
        options.push_back(i);
    }
     
    printPermutations(options);
   
        
    return 0;
}