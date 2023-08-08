#pragma once
class MaplePotar
{
public:
	MaplePotar();
	~MaplePotar();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _trans;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

};

