#pragma once
class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	virtual ~ArkanoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
};

