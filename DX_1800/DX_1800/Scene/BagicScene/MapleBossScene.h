#pragma once
class MapleBossScene : public Scene
{
public:
	MapleBossScene();
	~MapleBossScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class PlayerManager> _player;
	shared_ptr<class MapleBossMap> _bossMap;
	shared_ptr<class MaplePortar> _portar;
	//shared_ptr<class Meso> _meso;
};

