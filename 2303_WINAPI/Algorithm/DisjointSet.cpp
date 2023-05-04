#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>

using namespace std;
// 탐욕법을 사용할 떄 좋다.
struct User
{
	int guild_id;
	//여러정보...
};

void GuildSystem()
{
	vector<User> users;
	users.reserve(1000);

	for (int i = 0; i < 1000; i++)
	{
		User user;
		user.guild_id = i;

		users.push_back(user);
	}

	users[4].guild_id = users[1].guild_id;
}

class NaiveDisJointSet
{
public:
	NaiveDisJointSet(int n)
	{
		_parent.resize(n);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		_parent[vLeader] = uLeader;
	}
	

private:
	vector<int> _parent;
};

class DisJointSet
{
public:
	DisJointSet(int n)
	{
		_parent.resize(n);
		_rank.resize(n, 1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int uLeader = FindLeader(u);
		int vLeader = FindLeader(v);

		if (uLeader == vLeader)
			return;

		if (_rank[vLeader] > _rank[uLeader])
			std::swap(uLeader, vLeader);

		_parent[vLeader] = uLeader;

		if (_rank[uLeader] == _rank[vLeader])
			_rank[uLeader]++;
	}


private:
	vector<int> _parent;
	vector<int> _rank;
};

int main()
{
	DisJointSet d = DisJointSet(5);

	d.Merge(1, 3);
	d.Merge(1, 4);
	d.Merge(4, 2);

	cout << d.FindLeader(2) << endl;


	return 0;
}