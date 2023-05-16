#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

// DP (Dynamic Programming)
// - 이름이 멋있어서
// 1. 완전탐색
// 2. 시간이 많이 걸리는 문제
// -> 최적 부분 구조
// 최적화(메모이제이션, 캐싱)

// 캐싱, 메모이제이션
vector<int> cache = vector<int>(100, -1);

int Fibonacci(int n, int& count)
{
	// 기저사항
	if (n == 0 || n == 1)
		return 1;
	// 기저사항
	/*if (n == 2)
		return 2;*/

	//메모이제이션
	//최적구분구조를 찾았을 때, cache에다가 저장해놓는 것
	if (cache[n] != -1)
		return cache[n];

	if (n == 2)
		count++;

	// 구하기
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