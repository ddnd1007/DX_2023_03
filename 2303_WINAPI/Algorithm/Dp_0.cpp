#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

// DP (Dynamic Programming)
// - �̸��� ���־
// 1. ����Ž��
// 2. �ð��� ���� �ɸ��� ����
// -> ���� �κ� ����
// ����ȭ(�޸������̼�, ĳ��)

// ĳ��, �޸������̼�
vector<int> cache = vector<int>(100, -1);

int Fibonacci(int n, int& count)
{
	// ��������
	if (n == 0 || n == 1)
		return 1;
	// ��������
	/*if (n == 2)
		return 2;*/

	//�޸������̼�
	//�������б����� ã���� ��, cache���ٰ� �����س��� ��
	if (cache[n] != -1)
		return cache[n];

	if (n == 2)
		count++;

	// ���ϱ�
	cache[n] = Fibonacci(n - 1, count) + Fibonacci(n - 2, count);
	//return Fibonacci(n - 1, count) + Fibonacci(n - 2, count);
}


int main()
{
	_int64 start = GetTickCount64();

	int count = 0;

	cout << Fibonacci(70, count) << endl;
	cout << count << endl;

	_int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	return 0;
}