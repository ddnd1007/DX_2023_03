#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<CircleCollider> _circleCollider;
	shared_ptr<RectCollider> _rectColliderMouse;
	shared_ptr<RectCollider> _rectCollider2;

	Vector2 _pos = { 1.0f, 1.0f };
	Vector2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;
};

