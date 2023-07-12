#pragma once
class MapleScene : public Scene
{
public:
	MapleScene();
	~MapleScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class MaplePlayer> _player;
	shared_ptr<class MapleMap> _map;
	shared_ptr<class MapleMonster> _monster;
	//shared_ptr<class Meso> _meso;
};

