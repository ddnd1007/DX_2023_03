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

vector<int> cache = vector<int>(100, -1);

int  Enchant(int n)
{
    
    if (n == 1)
       return 1;

    if (n == 2)
        return 2;
    
    if (n == 3)
        return 4;

    if (cache[n] != -1)
        return cache[n];

    return cache[n] = Enchant(n - 1) + Enchant(n -2) + Enchant(n - 3);

}

void printPermutations(vector<int> permutation)
{
    while (true)
    {
        if (next_permutation(permutation.begin(), permutation.end()))
        {
           int sum = 0;
           for (auto value : permutation)
           {
               sum += value;
           }
           if (sum == Enchant(permutation.size()))
           {
               for (auto value : permutation)
               {
                   cout << value << " ";
               }
                   cout << endl;
           }
        }
           else
               break;
    }
}
int main()
{
    int n = 8;
    
    cout << Enchant(n) << endl;
   
    vector<int> options;
    for (int i = 1; i <= n; i++)
    {
        options.push_back(i);
    }
    sort(options.begin(), options.end());

    printPermutations(options);

    return 0;
}