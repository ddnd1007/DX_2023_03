#include <iostream>
#include <vector>

using namespace std;

//���� ���Ἲ �Լ�
// �Է°��� ���� �� ������ ���� ���� ���;��Ѵ�.

// Lis (���� �κ� ���� ���� ã��)
// Longest Increasing SubSequence

// �κ� ���� : ������ ��� ����, ������ �´� �κ� ����
// {1, 2, 8, 5, 3, 7, 10} v
// {1, 2 ,8} �κ� ����(O)
// {1, 5, 7} �κ� ����(O)
// {5, 1, 2, 8, 7} �κ� ����(X)

// �κ� ���� ���� : �κ� �����̸鼭 ������ �����ϴ� ���¸� ��� ����
// {1, 2, 8} O
// {1, 8, 3, 7} X

// ���� �κ� ���� ���� : �κ� ���� ���� �߿� ���� �� ��
// {1 2 5 7 10} 5
// {1 2 3 7 10} 5

vector<int> cache = vector<int>(100, -1);

int Lis(int n, vector<int>& v)
{
	// ���� ó��
	if (n >= v.size() - 1)
		return 1;

	//�޸������̼�
	int& ref = cache[n];
	if (ref != -1)
		return ref;


	// ���ϱ�
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