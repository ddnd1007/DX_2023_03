#include "framework.h"
#include "MapleBoss.h"

MapleBoss::MapleBoss()
{
	_col = make_shared<CircleCollider>(30.0f);
	_transform = make_shared<Transform>();

	CreateAction("stand", 0.3f, Action::LOOP, nullptr);

	_col->GetTransform()->SetPosition(Vector2(0, 0));

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f, 20.0f));

	_actions[State::STAND]->Play();

	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();
}

MapleBoss::~MapleBoss()
{
}

void MapleBoss::Update()
{
	_col->Update();
	_transform->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();

}

void MapleBoss::Render()
{
	_transform->SetWorldBuffer(0);

	_sprites[_curState]->Render();

	_col->Render();
}

void MapleBoss::TakeDamage(int damage)
{
}

void MapleBoss::SetAction(State state)
{

}

void MapleBoss::PostRender()
{
}

void MapleBoss::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Maple/Boss/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Maple/Boss/" + name + ".xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;
	float averageW = 0;
	float averageH = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	sprite->SetPS(ADD_PS(L"Shader/ActionPS.hlsl"));
	_sprites.push_back(sprite);
}
