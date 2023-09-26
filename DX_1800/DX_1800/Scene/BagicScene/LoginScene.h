#pragma once
class LoginScene : public Scene
{
public:
	LoginScene();
	~LoginScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	Vector2 leftBottom();
	Vector2 rightTop();

	void SetPosition(Vector2 pos) { _col1->GetTransform()->SetPosition(pos); }
	void SetPosition2(Vector2 pos) { _col2->GetTransform()->SetPosition(pos); }
	shared_ptr<RectCollider> GetCollider() { return _col1; }
	shared_ptr<RectCollider> GetCollider2() { return _col2; }


private:
	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _quadCol;
	shared_ptr<RectCollider> _col1;
	shared_ptr<RectCollider> _col2;
	shared_ptr<Transform> _quadTrans;
	shared_ptr<Transform> _trans1;
	shared_ptr<Transform> _trans2;
};



