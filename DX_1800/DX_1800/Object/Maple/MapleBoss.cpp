#include "framework.h"
#include "MapleBoss.h"

MapleBoss::MapleBoss()
{
	_circleCol = make_shared<CircleCollider>(80);
	_circleTrans = make_shared<Transform>();

	CreateAction("stand");
	CreateAction("work");
	CreateAction("hit");
	//CreateAction("dead");

	_circleCol->GetTransform()->SetPosition(Vector2(10, 0));

	_circleTrans->SetParent(_circleCol->GetTransform());
	_circleTrans->SetPosition(Vector2(0, 0));

	_actions[State::STAND]->Play();
	
	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();
}

MapleBoss::~MapleBoss()
{
}

void MapleBoss::Update()
{
	_circleCol->Update();
	_circleTrans->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void MapleBoss::Render()
{
	_circleTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_circleCol->Render();
}

void MapleBoss::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void MapleBoss::TakeDamage(int damage)
{
	if (_isDamaged == true)
		return;

	_hp -= damage;
}

void MapleBoss::Hit(shared_ptr<class PlayerManager> player)
{
	if (IsActive() == false)
		return;

	if (_isDamaged == true && _curState != State::HIT)


		if (player->GetCollider()->IsCollision(_circleCol))
		{
			if (player->GetPosition().x > _circleCol->GetTransform()->GetWorldPos().x)
			{
				SetLeft();

			}
			else
			{
				SetRight();
			}
		}
}

void MapleBoss::Attack(shared_ptr<class PlayerManager> victim)
{
	if (IsActive() == false)
		return;
	if (_circleCol->IsCollision(victim->GetCollider()) == false || victim->IsDead() == true)
		return;

	victim->TakeDamage(_damage);
}

void MapleBoss::HitEnd()
{
	if (IsActive() == false)
		return;

	if (_isDamaged == false && IsActive() == true)
		SetAction(State::STAND);
}

bool MapleBoss::DeathAnimation()
{
	return false;
}

void MapleBoss::Move(shared_ptr<class PlayerManager> player)
{
}

void MapleBoss::ChangeState(State nextState, int duration)
{
}

bool MapleBoss::IsDead()
{
	if (IsActive() == false)
	{
		return true;
	}
	else
	{
		return false;
	};
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
	//action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	sprite->SetPS(ADD_PS(L"Shader/ActionPS.hlsl"));
	_sprites.push_back(sprite);
}
