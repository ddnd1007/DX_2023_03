#pragma once
class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static SceneManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();
	void PreRender();
	void PostRender();

	void NextScene();
	void PrevScene();
	void SetScene(int number);

private:
	static SceneManager* _instance;

	vector<shared_ptr<Scene>> _scenes;

	shared_ptr<class PlayerManager> _player;
	shared_ptr<class MapleMap> _map;
	shared_ptr<class MapleBossMap> _bossMap;

	UINT _curScene = 0;

	UINT _test = 0;
};

