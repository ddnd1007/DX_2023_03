#include <iostream>
#include <vector>

using namespace std;

int n = 50;
vector<bool> IsPrime = vector<bool>(51, true);
//true �Ҽ�

bool IsPrime_(int number)
{
	if (number == 0 || number == 1)
		return false;
	if (number == 2 || number == 3 || number == 5)
		return true;
}

void Eratothenes()
{
	IsPrime[0] = false;
	IsPrime[1] = false;
	int sqrtN = sqrt(n);

	for (int i = 2; i < sqrtN; i++)
	{
		if (IsPrime[i])
		{
			// i*i�� �̸��� ���� �̹� üũ�� �Ǿ����� ��.
			for (int j = i * i; j <= n; j += j)
			{
				IsPrime[j] = false;
			}
		}
	}
}

int main()
{
	Eratothenes();

	return 0;
}