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

// 1
// 1

// 2
// 1 + 1
// 2

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

int targetNum = 6;

int Enchant(int n)
{
    if (n > targetNum)
        return 0;

    if (n == targetNum)
        return 1;

    //메모이제이션
    if (cache[n] != -1)
        return cache[n];

    // 구하기
    return cache[n] =  Enchant(n + 1) + Enchant(n + 2) + Enchant(n + 3);
}


int main()
{
    cout << Enchant(0) << endl;

    return 0;
}