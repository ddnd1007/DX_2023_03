#include "framework.h"
#include "MapleMonster.h"
#include "MaplePlayer.h"

MapleMonster::MapleMonster()
{
	_circleCol = make_shared<CircleCollider>(15);
	_circleTrans = make_shared<Transform>();

	_rectCol = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_rectCol->GetTransform()->SetParent(_circleCol->GetTransform());
	_rectTrans = make_shared<Transform>();

	CreateAction("snail stand");
	CreateAction("snail work");
	CreateAction("snail hit", 0.2, Action::Type::LOOP);
	CreateAction("snail die", 0.1, Action::Type::END);
	
	_circleCol->GetTransform()->SetPosition(Vector2(0,0));
	_rectCol->GetTransform()->SetPosition(Vector2(0,0));

	_circleTrans->SetParent(_circleCol->GetTransform());
	_circleTrans->SetPosition(Vector2(0, 0));
	_rectTrans->SetParent(_rectCol->GetTransform());
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
	IsDead();
	Hit();
	HitEnd();

	if (_isDamaged == true)
	{
		_curTime += DELTA_TIME;
	}

	if (_curTime > _hitTime)
	{
		_isDamaged = false;
		_curTime = 0.0f;
	}

	_rectCol->Update();
	_rectTrans->Update();
	_circleCol->Update();
	_circleTrans->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void MapleMonster::Render()
{
	if (IsActive() == false)
	{
		Dead();
		IsDead();
		return;
	}
	_rectTrans->SetWorldBuffer(0);
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

void MapleMonster::TakeDamage(int damage)
{
	if (_isDamaged == true)
		return;

	_hp -= damage;
	_isDamaged = true;
}

bool MapleMonster::IsDead()
{
	if (IsActive() == true)
		return false;
	else
	{
		SetAction(State::DEAD);
		return true;
	}
}

void MapleMonster::Hit()
{
	if (IsActive() == false)
		return;

	if (_isDamaged && _curState != State::HIT)
	{
		SetLeft();

		ChangeState(State::STAND, HIT_ANIMATION_DURATION_MS);
		SetAction(State::HIT);
	}
}

void MapleMonster::Attack(shared_ptr<class MaplePlayer> victim)
{
	if (IsActive() == false)
		return;
	if (_circleCol->IsCollision(victim->GetCollider()) == false || victim->IsDead() == true)
		return;

	victim->TakeDamage(_damage);
}

void MapleMonster::HitEnd()
{
	if (IsActive() == false)
		return;

	if (_isDamaged == false && IsActive() == true)
		SetAction(State::WORK);
}

void MapleMonster::Dead()
{
	if (IsActive() == true)
		return;
	if (_curState == State::DEAD)
		return;

	SetAction(State::DEAD);
}

void MapleMonster::Move(shared_ptr<class MaplePlayer> player)
{
	if (!IsActive())
		return;

	if (_curState == State::HIT || _curState == State::DEAD || _isDamaged)
		return;

	if (player->GetCollider()->IsCollision(_circleCol))
		SetAction(State::WORK);

	if (player->GetCollider()->IsCollision(_rectCol))
	{
		_circleCol->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);
		SetRight();
	}
	else
	{
		_circleCol->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);
		SetLeft();
	}
}

void MapleMonster::ChangeState(State nextState, int duration)
{
	if (_curState == _oldState)
		return;

	_curState = State::HIT; // 상태 변경을 표시하고 피격 애니메이션을 재생할 수 있도록 한다.

	// 일정 시간이 지난 후에 상태를 변경하는 타이머 시작
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));

	_curState = nextState; // 피격 애니메이션의 재생 시간이 지나면 원래 상태로 돌아감
}


int MapleMonster::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (RAND_MAX + 1.0);
	static bool seedInitialized = false;
	if (!seedInitialized) {
		srand(static_cast<unsigned int>(std::time(0)));
		seedInitialized = true;
	}
	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
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
