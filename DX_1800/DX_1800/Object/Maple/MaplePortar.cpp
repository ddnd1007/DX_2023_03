#include "framework.h"
#include "MaplePortar.h"

MaplePortar::MaplePortar()
{
	_col = make_shared<RectCollider>(Vector2(50.0f, 50.0f));
	_trans = make_shared<Transform>();
	_col->GetTransform()->SetParent(_trans);

}

MaplePortar::~MaplePortar()
{
}

void MaplePortar::Update()
{
	_col->Update();
	_trans->Update();
}

void MaplePortar::Render()
{
	_trans->SetWorldBuffer(0);
	_col->Render();
}

void MaplePortar::Interact(shared_ptr<PlayerManager> player)
{
	if (player->GetCollider()->IsCollision(_col))
	{
		if (KEY_PRESS('W'))
		{
			_col->SetColorRed();
			std::string destinationScene = GetDestinationScene();
		}

	}
}



void MaplePortar::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Maple/Character/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Maple/Character/" + name + ".xml";
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
