#pragma once
class DunGreedScene : public Scene
{
public:
	DunGreedScene();
	virtual ~DunGreedScene();

	virtual void Collider_Update() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<DunPlayer> _player;
	shared_ptr<DunBoss> _boss;
	bool _isActive = false;
};
