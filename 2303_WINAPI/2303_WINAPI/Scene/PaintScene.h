#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetCenter(Vector2 pos) { _center = pos; }

private:
	shared_ptr<CircleCollider> circlecollider;
};

