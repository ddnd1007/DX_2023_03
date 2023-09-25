#include "framework.h"
#include "MapleBoss.h"
#include "Bossprojectiles.h"
//#include "BossSkill2.h"

MapleBoss::MapleBoss()
{
	SOUND->Add("skill", "Resource/Sound/BossSkill.mp3", false);
	_circleCol = make_shared<CircleCollider>(80);
	_circleTrans = make_shared<Transform>();

	_ballCol = make_shared<CircleCollider>(5);
	_ballTrans = make_shared<Transform>();

	_rectCol = make_shared<RectCollider>(Vector2(1000.0f, 200.0f));
	_rectCol->GetTransform()->SetParent(_circleCol->GetTransform());
	_rectTrans = make_shared<Transform>();

	CreateAction("stand", 0.1f, Action::LOOP);
	CreateAction("work");
	CreateAction("bosshit", 0.5f);
	CreateAction("skil1");
	CreateAction("dead", 0.1f, Action::END);

	_circleCol->GetTransform()->SetPosition(Vector2(10, 0));

	_circleTrans->SetParent(_circleCol->GetTransform());
	_circleTrans->SetPosition(Vector2(0, 0));
	_rectTrans->SetParent(_rectCol->GetTransform());
	_rectTrans->SetPosition(Vector2(0, 0));
	_ballCol->GetTransform()->SetParent(_circleCol->GetTransform());
	_ballTrans->SetParent(_circleCol->GetTransform());

	_hpBar = make_shared<HpBar>();
	_hpBar->SetPosition(Vector2(0.0f, 700.0f));

	_hpBar->SetRatio(1000.0f);

	_actions[State::WORK]->Play();
	
	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bossprojectiles> skill = make_shared<Bossprojectiles>();
		_skill1.push_back(skill);
	}
	
}

MapleBoss::~MapleBoss()
{
}

void MapleBoss::Update(Vector2 target)
{
	DeathAnimation();
	HitAnimation();
	IsDead();

	Skill(target);
	HitEnd();
	
	_circleCol->Update();
	_circleTrans->Update();

	_ballCol->Update();
	_ballTrans->Update();

	_rectCol->Update();
	_rectTrans->Update();

	_hpBar->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();

	for (auto skill1 : _skill1)
		skill1->Update();
}

void MapleBoss::Render()
{
	if (_isActive == false)
		return;

	_hpBar->PostRender();

	_circleTrans->SetWorldBuffer(0);
	_ballTrans->SetWorldBuffer(0);
	_rectTrans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	/*_circleCol->Render();
	_ballCol->Render();
	_rectCol->Render();*/

	for (auto skill1 : _skill1)
		skill1->Render();
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
	_hpBar->SetRatio(_hp / (float)_maxHp);

	if (!_isDamaged)
	{
		_hitAnimationTimer += DELTA_TIME;
		if (_hitAnimationTimer > _hitAnimationDuration)
		{
			_hitAnimationTimer = 0.0f;
			_isDamaged = false;
		}
		return;
	}
}

void MapleBoss::Hit(shared_ptr<class PlayerManager> player)
{
	if (IsActive() == false)
		return;

	if (_isDamaged == true && _curState != State::BOSSHIT)
	{
		if (player->GetPosition().x > _circleCol->GetTransform()->GetWorldPos().x)
		{
			SetLeft();
			SetAction(State::BOSSHIT);

		}
		else
		{
			SetRight();
			SetAction(State::BOSSHIT);
		}
	}
		
}

//void MapleBoss::Attack(shared_ptr<class PlayerManager> victim)
//{
//	if (IsActive() == false)
//		return;
//	if (_circleCol->IsCollision(victim->GetCollider()) == false || victim->IsDead() == true)
//		return;
//
//	victim->TakeDamage(_damage);
//}

void MapleBoss::HitEnd()
{
	if (IsActive() == false)
		return;

	if (_isDamaged == false && _curState == State::BOSSHIT)
		SetAction(State::WORK);
}

bool MapleBoss::DeathAnimation()
{
	if (IsActive() == false)
	{
		_deathAnimationTimer += DELTA_TIME;

		if (_deathAnimationTimer >= _deathAnimationDuration)
		{
			_deathAnimationTimer = 0.0f;
			_isActive = false;
			_curState = (State::DEAD);
			return true;
		}
		return false;
	}
	return false;
}

bool MapleBoss::HitAnimation()
{
	if (_isDamaged == true)
	{
		_hitAnimationTimer += DELTA_TIME;

		if (_hitAnimationTimer > _hitAnimationDuration)
		{
			_hitAnimationTimer = 0.0f;
			DamagedEvent();
			_isDamaged = false;
			return true;
		}
		return false;
	}
	return false;
}

void MapleBoss::Move(shared_ptr<class PlayerManager> player)
{
	if (!IsActive())
		return;

	if (_curState == State::BOSSHIT || _curState == State::DEAD || _isDamaged == true)
		return;

	if (player->GetCollider()->IsCollision(_circleCol))
		SetAction(State::WORK);

	if (player->GetCollider()->IsCollision(_rectCol))
	{
		if (player->GetPosition().x > _rectCol->GetTransform()->GetWorldPos().x)
		{
			_circleCol->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);
			_ballCol->GetTransform()->SetPosition(Vector2(+70.0f, -20.0f));
			SetLeft();
		}
		else
		{
			_circleCol->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);
			_ballCol->GetTransform()->SetPosition(Vector2(-70.0f, -20.0f));
			SetRight();
		}
	}
}

void MapleBoss::Skill(Vector2 target)
{
	if (IsActive() == false)
		return;

	if (_isSkill)
	{
		_CooldownTimer += DELTA_TIME;
		if (_CooldownTimer > _CooldownDuration)
		{
			_CooldownTimer = 0.0f;
			_isSkill = false;
		}
		return;
	}

	auto skillIter = std::find_if(_skill1.begin(), _skill1.end(),
		[](shared_ptr<Bossprojectiles>& obj)-> bool { return !obj->IsActive(); });

	if (skillIter == _skill1.end())
		return;

	// 타겟의 위치를 받아 발사 방향 정함
	Vector2 dir = target - _ballCol->GetTransform()->GetPos();

	(*skillIter)->Shoot(dir, _ballCol->GetTransform()->GetPos());
	SOUND->Play("skill", 0.1f);


	_isSkill = true;
}

bool MapleBoss::IsDead()
{
	if (IsActive() == true)
	{
		return _hp > 0;
		return false;
	}
	else
	{
		SetAction(State::DEAD);
		CAMERA->ShakeStart(0.5f, 0.5f);
		return true;
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
