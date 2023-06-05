#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Collider> _mouseRect;
	shared_ptr<Collider> _circleCollider;

	vector<shared_ptr<Collider>> _colliders;
};
