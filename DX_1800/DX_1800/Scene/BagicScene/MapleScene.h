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
	shared_ptr<class MapleBoss> _mapleBoss;
};

