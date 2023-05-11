#include <iostream>

using namespace std;

// 유클르디의 호재법, 알고리즘
// -> 최대공약수 구할 때 많이 쓰임

// p, q 두 수의 최대 공약수
// 이 떄 p > q

// 15 6
// 9 6
// 6 3
// 3 3
// gcd(p,q) == gcd {p - q, q}

int gcd(int p, int q)
{
	if (q == 0) return p;
	return gcd(q, p % q);
}

int main()
{

	cout << gcd(21, 6) << endl;
	return 0;
}