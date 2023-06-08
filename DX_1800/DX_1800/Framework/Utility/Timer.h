#pragma once
class Timer
{
private:
	Timer();
	~Timer();

public:
	static void Create()
	{
		if (_instance == nullptr)
		_instance = new Timer();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static Timer* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();

	int GetFPS() { return _frameRate; }
	double GetDeltaTime() { return _deltaTime; }
	double GetRunTime() { return _runTime; }

private:
	static Timer* _instance;

	double _timeScale = 0.0;
	double _deltaTime = 0.0; // 한 번 업데이트에 걸리는 시간

	unsigned __int64 _curTime = 0;
	unsigned __int64 _lastTime = 0;
	unsigned __int64 _periodFrequency = 0;

	unsigned int _frameRate = 0;
	unsigned int _frameCount = 0;

	double _oneSecCount = 0.0;
	double _runTime = 0.0;
	double _lockFPS = 0.0;


};

