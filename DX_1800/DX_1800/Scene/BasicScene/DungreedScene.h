#pragma once
class DungreedScene : public Scene
{
public:
	DungreedScene();
	virtual ~DungreedScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<DunPlayer> _player;
	shared_ptr<DunPlayer> _arrow;
	shared_ptr<DunBullet> _bullet;
};

