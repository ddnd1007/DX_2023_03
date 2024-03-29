#include "framework.h"
#include "Bossprojectiles.h"

Bossprojectiles::Bossprojectiles()
{
	_col = make_shared<CircleCollider>(20);
	_col->GetTransform()->SetPosition(Vector2(-30.0f, 0.0f));
	
	CreateAction("ball");

	_trans = make_shared<Transform>();
	_trans->SetParent(_col->GetTransform());
	//_trans->SetScale(Vector2(5.0f, 5.0f));
	//_trans->SetAngle(-PI * 2.0f);
	_trans->SetPosition(Vector2(-80.0f, -20.0f));

	_actions[BALL]->SetEndEvent(std::bind(&Bossprojectiles::EndEvent, this));
	_col->GetTransform()->SetPosition(Vector2(-WIN_WIDTH * 5, -WIN_HEIGHT * 5));
	_isActive = false;

	_sprites[0]->SetLeft();
	
	_col->Update();
	_trans->Update();
}

Bossprojectiles::~Bossprojectiles()
{
}

void Bossprojectiles::Update()
{
	_col->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);
	
	_col->Update();
	_trans->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void Bossprojectiles::Render()
{
	if (_isActive == false)
		return;

	_trans->SetWorldBuffer(0);
	_sprites[_curState]->Render();
	//_col->Render();
}

void Bossprojectiles::Shoot(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_col->GetTransform()->SetPosition(startPos);
	_dir = dir.NorMalVector2();
	float angle = _dir.Angle();
	_col->GetTransform()->SetAngle(angle);
}

void Bossprojectiles::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void Bossprojectiles::EndEvent()
{
	_curState = BALL;
	_actions[BALL]->Play();
}

void Bossprojectiles::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
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
	//action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	sprite->SetPS(ADD_PS(L"Shader/ActionPS.hlsl"));
	_sprites.push_back(sprite);
}


