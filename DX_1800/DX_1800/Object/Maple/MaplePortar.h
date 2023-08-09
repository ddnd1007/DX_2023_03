#pragma once
class MaplePortar
{
public:
	MaplePortar();
	MaplePortar(const std::string& destinationScene)
		: destinationScene(destinationScene) {};
	~MaplePortar();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void Interact(shared_ptr<PlayerManager> player);
	const std::string& GetDestinationScene() const { return destinationScene; }
	shared_ptr<RectCollider> GetCollider() { return _col; }

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _trans;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;
	std::string destinationScene;



};

