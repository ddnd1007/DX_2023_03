#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

// ENCHANT
// 0���������� ����

// +1
// +2
// +3

// n���� �� �� ��ȭ�ϴ� ��� ����� ��

// 1
// 1

// 2
// 1 + 1
// 2

// �� : 3���� �ϰ� �ʹ�. -> 4����
// 1 + 1 + 1 
// 1 + 2 
// 2 + 1
// 3

// �� : 4�� -> 7����
// 1 + 1 + 1 + 1
// 1 + 2 + 1
// 1 + 1 + 2
// 1 + 3
// 2 + 1 + 1
// 2 + 2
// 3 + 1

vector<int> cache = vector<int>(100, -1);
<<<<<<< HEAD

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
=======

int targetNum = 6;

int Enchant(int n)
{
    if (n > targetNum)
        return 0;

    if (n == targetNum)
        return 1;

    //�޸������̼�
    if (cache[n] != -1)
        return cache[n];
>>>>>>> 7e5a2787bdda63c8bc3923b2793a1a69f7bfd60e

    // ���ϱ�
    return cache[n] =  Enchant(n + 1) + Enchant(n + 2) + Enchant(n + 3);
}

<<<<<<< HEAD
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
=======

int main()
{
    cout << Enchant(0) << endl;
>>>>>>> 7e5a2787bdda63c8bc3923b2793a1a69f7bfd60e

    return 0;
}