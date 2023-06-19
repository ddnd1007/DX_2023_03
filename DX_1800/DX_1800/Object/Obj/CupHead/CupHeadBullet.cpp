#include "framework.h"
#include "CupHeadBullet.h"

CupHeadBullet::CupHeadBullet()
{
	_col = make_shared<CircleCollider>(15);

	_spriteTrans = make_shared<Transform>();
	_spriteTrans->SetParent(_col->GetTransform());
	_spriteTrans->SetAngle(-PI * 0.5f);
	_spriteTrans->SetPosition(Vector2(-50.0f, 0.0f));

	CreateAction("Intro");
	CreateAction("Loop");
	
	_actions[State::INTRO]->Play();
	_actions[State::LOOP]->Play();

	_actions[State::INTRO]->SetEndEvent(std::bind(&CupHeadBullet::EndEvent, this));
}

CupHeadBullet::~CupHeadBullet()
{
}

void CupHeadBullet::Update()
{
	if (_isActive == false)
		return;

	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	
	_col->Update();
	_actions[_state]->Update();
	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Update();
	_spriteTrans->Update();

}

void CupHeadBullet::Render()
{
	if (_isActive == false)
		return;

	_spriteTrans->SetWorldBuffer(0);
	
	_sprites[_state]->Render();

	_col->Render();
}

void CupHeadBullet::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/CupHead/" + wName + L".png";
	
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/CupHead/" + name + ".xml";
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
	_sprites.push_back(sprite);
}

void CupHeadBullet::Fire(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_state = State::INTRO;
	_actions[_state]->Play();
	_actions[State::LOOP]->Reset();

	_col->GetTransform()->SetPosition(startPos);
	if (dir.x > 0.0f)
	{
		_dir = RIGHT_VECTOR;
		SetRight();
	}
	else
	{
		_dir = -RIGHT_VECTOR;
		SetLeft();
	}
}

void CupHeadBullet::EndEvent()
{
	_state = State::LOOP;
	_actions[State::LOOP]->Play();
}



