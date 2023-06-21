#include "framework.h"
#include "CupMonster.h"

CupMonster::CupMonster()
{
	_col = make_shared<RectCollider>(Vector2(220.0f, 750.0f));
	_transform = make_shared<Transform>();

	_col->GetTransform()->SetPosition(CENTER);
	_transform->SetParent(_col->GetTransform());

	CreateAction("Clown_Page_Last_Idle", 0.1f, Action::Type::LOOP, nullptr);
	_actions[State::IDLE]->Play();

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.imageSize = _sprites[State::IDLE]->GetImageSize();
	_filterBuffer->_data.selected = 1;

}

CupMonster::~CupMonster()
{
}

void CupMonster::Update()
{
	if (_hp <= 5)
	{
		_filterBuffer->_data.value2 += 1;
		_filterBuffer->Update_Resource();
	}
	if (IsDead() == true)
		return;

	if (_isDamaged == true)
	{
		_curTime += DELTA_TIME;
	}

	if (_curTime > _damageTime)
	{
		_isDamaged = false;
		_curTime = 0.0f;
	}
	_col->Update();
	_transform->Update();
	_actions[_curState]->Update();
	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();



}

void CupMonster::Render()
{
	if (IsDead() == true)
		return;

	_transform->SetWorldBuffer(0);
	_filterBuffer->SetPS_Buffer(2);

	_sprites[_curState]->Render();
	_col->Render();
}
void CupMonster::TakeDamage(int damage)
{
	if (_isDamaged == true)
		return;

	_hp -= damage;
	_isDamaged = true;
}

void CupMonster::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void CupMonster::PostRender()
{
	ImGui::SliderInt("Crown_HP", (int*)&_hp, 0, 10);

	ImGui::SliderInt("Playerselected", &_filterBuffer->_data.selected, 0, 5);
	ImGui::SliderInt("Playervalue1", &_filterBuffer->_data.value1, 0, 300);
	ImGui::SliderInt("Playervalue2", &_filterBuffer->_data.value2, 0, 300);
	ImGui::SliderInt("Playervalue3", &_filterBuffer->_data.value3, 0, 300);
}

void CupMonster::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
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
	sprite->SetPS(ADD_PS(L"Shader/CupHeadPS.hlsl"));
	_sprites.push_back(sprite);
}

