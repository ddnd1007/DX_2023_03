#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene() {}

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:

};

