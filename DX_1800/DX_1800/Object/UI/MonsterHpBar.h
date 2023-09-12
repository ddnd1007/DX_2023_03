#pragma once
class MonsterHpBar
{
public:
	MonsterHpBar();
	~MonsterHpBar();

	void Update();
	void PostRender();
	void PreRender();

	void SetPosition(Vector2 pos) { _quadTransform->SetPosition(pos); }
	void SetEvent(CallBack fn) { _event = fn; }
	void SetRatio(float ratio) { _buffer->_data.ratio = ratio; _buffer->Update_Resource(); }
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

private:
	shared_ptr<Transform> _quadTransform;
	shared_ptr<Quad> _quad;

	shared_ptr<BarBuffer> _buffer;

	weak_ptr<Transform> _parent;
	CallBack _event;
};

