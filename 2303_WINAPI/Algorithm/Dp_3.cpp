#include <iostream>
#include <vector>

using namespace std;

//참조 무결성 함수
// 입력값이 같을 때 무조건 같은 값이 나와야한다.

// Lis (최장 부분 증가 수열 찾기)
// Longest Increasing SubSequence

// 부분 수열 : 인접에 상관 없이, 순서에 맞는 부분 수열
// {1, 2, 8, 5, 3, 7, 10} v
// {1, 2 ,8} 부분 수열(O)
// {1, 5, 7} 부분 수열(O)
// {5, 1, 2, 8, 7} 부분 수열(X)

// 부분 증가 수열 : 부분 수열이면서 수열이 증가하는 형태를 띄는 수열
// {1, 2, 8} O
// {1, 8, 3, 7} X

// 최장 부분 증가 수열 : 부분 증가 수열 중에 제일 긴 것
// {1 2 5 7 10} 5
// {1 2 3 7 10} 5

vector<int> cache = vector<int>(100, -1);

int Lis(int n, vector<int>& v)
{
	// 기저 처리
	if (n >= v.size() - 1)
		return 1;

	//메모이제이션
	int& ref = cache[n];
	if (ref != -1)
		return ref;


	// 구하기
	ref = 1;
	for (int i = n + 1; i < v.size(); i++)
	{
		if (v[n] <= v[i])
		{
			return ref = max(ref, Lis(i, v) + 1);
		}	
	}

	return ref;
}

int main()
{
	vector<int> v0 = { 1,2,3 };

	cout << Lis(0, v0) << endl;;

	vector<int> v1 = { 1, 2, 8, 5, 3, 7, 10 };

	cout << Lis(0, v1) << endl;;

	vector<int> v2 = { 5,6,7,8,1,2,3 };


	

	return 0;
}