#include "framework.h"
#include "BossSkill2.h"
//#include "PlayerManager.h"

BossSkill2::BossSkill2()
{
	_cirCol = make_shared<CircleCollider>(20);
	_cirTrans = make_shared<Transform>();

	_rectCol = make_shared<RectCollider>(Vector2(100,500));
	_rectTrans = make_shared<Transform>();

	_cirCol->GetTransform()->SetPosition(Vector2(0.0f, -530.0f));
	_cirTrans->SetParent(_cirCol->GetTransform());
	
    _rectCol->GetTransform()->SetParent(_cirCol->GetTransform());
	_rectCol->GetTransform()->SetPosition(Vector2(_cirCol->GetTransform()->GetPos() + Vector2(0,+550)));
	_rectTrans->SetParent(_rectCol->GetTransform());
	
	CreateAction("effect1");

	_actions[State::SKILL]->Play();

	_sprites[0]->SetLeft();
}

BossSkill2::~BossSkill2()
{
}

void BossSkill2::Update()
{
	_cirCol->Update();
	_cirTrans->Update();

	_rectCol->Update();
	_rectTrans->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void BossSkill2::Render()
{
	_cirTrans->SetWorldBuffer(0);
	_rectTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_cirCol->Render();
}

void BossSkill2::Skill2(shared_ptr<class PlayerManager> victim)
{
	if (victim->IsDead() == true)
		return;

	if (_skillActive == false)
	{
		SetAction(State::SKILL);
		_skillActive = true;

		if (_rectCol->IsCollision(victim->GetCollider()))
		{
			victim->TakeDamage(100);
		}
	}
}

void BossSkill2::EndSkill()
{
	if (_skillActive == true)
		_skillActive = false;
}

void BossSkill2::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

int BossSkill2::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);
	static bool seedInitialized = false;
	if (!seedInitialized) {
		srand(static_cast<unsigned int>(std::time(0)));
		seedInitialized = true;
	}
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

void BossSkill2::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
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
