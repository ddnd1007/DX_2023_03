#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr <RectCollider> _rectCollider;
};

