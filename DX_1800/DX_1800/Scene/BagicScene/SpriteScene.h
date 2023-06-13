#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	virtual ~SpriteScene();

	virtual void Update() override;
	virtual void Render() override;
	//virtual void PostRender() override;

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Zelda> _zelda;

	Vector2 _curFrame;
};

