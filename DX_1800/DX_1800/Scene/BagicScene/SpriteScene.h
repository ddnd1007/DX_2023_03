#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	virtual ~SpriteScene();

	virtual void Update() override;
	virtual void Render() override;

	

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Sprite> _sprite;

};

