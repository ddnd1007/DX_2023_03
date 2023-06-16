#pragma once
class CupHeadScene : public Scene
{
public:
	CupHeadScene();
	~CupHeadScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class CupHead> _player;
};

