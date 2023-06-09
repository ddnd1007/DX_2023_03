#pragma once
class DunGreedScene : public Scene
{
public:
	DunGreedScene();
	virtual ~DunGreedScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<class DunPlayer> _player;
};

