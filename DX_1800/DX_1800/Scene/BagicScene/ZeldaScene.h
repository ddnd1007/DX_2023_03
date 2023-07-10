#pragma once
class ZeldaScene : public Scene
{
public:
	ZeldaScene();
	virtual ~ZeldaScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CameraShake();

private:
	shared_ptr<class Zelda> _zelda;
	shared_ptr<Button> _button;
};

