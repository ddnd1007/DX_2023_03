#pragma once
class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<ArkanoidBricks> _arkanoidBricks;
	shared_ptr<Frame> _arkanoidFrame;
	shared_ptr<Bar> _arkanoidBar;
};

