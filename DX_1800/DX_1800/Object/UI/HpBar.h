#pragma once
class HpBar
{
public:
	HpBar();
	~HpBar();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _quadTransform->SetPosition(pos); }
	void SetEvent(CallBack fn) { _event = fn; }
	void SetRatio(float ratio) { _barBuffer->_data.ratio = ratio; _barBuffer->Update_Resource(); }

private:
	shared_ptr<Transform> _quadTransform;
	shared_ptr<Quad> _quad;

	shared_ptr<BarBuffer> _barBuffer;

	CallBack _event;

};

