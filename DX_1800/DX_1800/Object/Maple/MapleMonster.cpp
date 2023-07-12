#include "framework.h"
#include "MapleMonster.h"


MapleMonster::MapleMonster()
{
	_circleCol = make_shared<CircleCollider>(15);
	_circleTrans = make_shared<Transform>();

	_rectCol = make_shared<RectCollider>(Vector2(70.0f, 70.0f));
	_rectTrans = make_shared<Transform>();

	CreateAction("snail stand");
	CreateAction("snail work");
	CreateAction("snail hit");
	CreateAction("snail die");
	
	_circleCol->GetTransform()->SetPosition(Vector2(0, 0));
	_rectCol->GetTransform()->SetPosition(Vector2(0, 0));

	_circleTrans->SetParent(_circleCol->GetTransform());
	_rectTrans->SetParent(_rectCol->GetTransform());
	_circleTrans->SetPosition(Vector2(0, 0));
	_rectTrans->SetPosition(Vector2(0, 0));

	_actions[State::STAND]->Play();
	_actions[State::WORK]->Play();

	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();


}

MapleMonster::~MapleMonster()
{
}

void MapleMonster::Update()
{
	Hit();
	HitEnd();
	Dead();

	_circleCol->Update();
	_rectCol->Update();
	_circleTrans->Update();
	_rectTrans->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void MapleMonster::Render()
{
	_circleTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_circleCol->Render();
	_rectCol->Render();
}

void MapleMonster::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void MapleMonster::Dead()
{
	if (_isDead == false)
		return;

	if (_hp <= 0)
	{
		SetAction(State::DEAD);
	}

}

void MapleMonster::Hit()
{
	if (_isDead == true)
		return;

	if (_isDamaged == true)
	SetAction(State::HIT);
}

void MapleMonster::HitEnd()
{
	if (_isDead == true)
		return;

	if (_isDamaged == false)
		SetAction(State::WORK);
}

void MapleMonster::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Maple/snail/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Maple/snail/" + name + ".xml";
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
	//action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	sprite->SetPS(ADD_PS(L"Shader/ActionPS.hlsl"));
	_sprites.push_back(sprite);
}
