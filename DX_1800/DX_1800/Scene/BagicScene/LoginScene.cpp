#include "framework.h"
#include "LoginScene.h"

LoginScene::LoginScene()
{
	SOUND->Add("login", "Resource/Sound/loginbgm.mp3", false);
	_quad = make_shared<Quad>();//(L"Resource/Maple/map/loginmap.png");
	_quadCol = make_shared<RectCollider>(_quad->GetImageSize());
	_col1 = make_shared<RectCollider>(Vector2(500.0f, 300.0f));
	_col2 = make_shared<RectCollider>(Vector2(500.0f, 300.0f));
	_quadTrans = make_shared<Transform>();
	_trans1 = make_shared<Transform>();
	_trans2 = make_shared<Transform>();

	_quadTrans->SetParent(_quadCol->GetTransform());
	_trans1->SetParent(_col1->GetTransform());
	_trans2->SetParent(_col2->GetTransform());

}

LoginScene::~LoginScene()
{
}

void LoginScene::Update()
{
	_quadCol->Update();
	_col1->Update();
	_col2->Update();
	_quadTrans->Update();
	_trans1->Update();
	_trans2->Update();
	_quad->Update();

	if (_col1->IsCollision(W_MOUSE_POS) || _col2->IsCollision(W_MOUSE_POS))
	{
		SCENE->NextScene();
		SOUND->Stop("login");
	}
}

void LoginScene::Render()
{
	_quadTrans->SetWorldBuffer(0);
	_trans1->SetWorldBuffer(0);
	_trans2->SetWorldBuffer(0);
	_quad->Render();
	_quadCol->Render();
	_col1->Render();
	_col2->Render();
}

void LoginScene::PostRender()
{
}

Vector2 LoginScene::leftBottom()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _quadCol->GetTransform()->GetWorldPos().x - quadHalfSize.x;
	float y = _quadCol->GetTransform()->GetWorldPos().y - quadHalfSize.y;

	return Vector2(x, y);
}

Vector2 LoginScene::rightTop()
{
	Vector2 quadHalfSize = _quad->GetSize() * 0.5f;

	float x = _quadCol->GetTransform()->GetWorldPos().x + quadHalfSize.x;
	float y = _quadCol->GetTransform()->GetWorldPos().y + quadHalfSize.y;

	return Vector2(x, y);
}
