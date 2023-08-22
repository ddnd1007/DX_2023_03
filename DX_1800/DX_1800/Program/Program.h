#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	shared_ptr<SceneManager> _curScene;
	shared_ptr<SceneManager> _oldScene;
};

