#include "framework.h"
#include "ArkanoidScene.h"

ArkanoidScene::ArkanoidScene()
{
	_arkanoidBricks = make_shared<ArkanoidBricks>();
	_arkanoidFrame = make_shared<Frame>();
	_arkanoidBar = make_shared<Bar>();
}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoidBricks->Update();
	_arkanoidFrame->Update();
	_arkanoidBar->Update();

	for (auto bricksY : _arkanoidBricks->GetBricks())

		for (auto arkanoidBricks : bricksY)
		{
			if (arkanoidBricks->GetEachBlock()->IsCollision(_arkanoidBar->GetBallByBar()->GetBall()) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y - 5 > (arkanoidBricks->GetEachBlock()->GetCenter().y) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x + 5 > (arkanoidBricks->GetEachBlock()->GetCenter().x - 25) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x - 5 < (arkanoidBricks->GetEachBlock()->GetCenter().x + 25) &&
				_arkanoidBar->GetBallByBar()->GetDir().y < 0)

			{
				if (arkanoidBricks->IsDead() == true)
					return;
				_arkanoidBar->GetBallByBar()->SetDir(Vector2(_arkanoidBar->GetBallByBar()->GetDir().x, (_arkanoidBar->GetBallByBar()->GetDir().y * -1)));
				if (arkanoidBricks->GetType() == ArkanoidBrick::ArkanoidBrickType::BRICK)
					arkanoidBricks->SetDead(true);
					return;
			}

			if (arkanoidBricks->GetEachBlock()->IsCollision(_arkanoidBar->GetBallByBar()->GetBall()) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y + 5 < (arkanoidBricks->GetEachBlock()->GetCenter().y) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x + 5 > (arkanoidBricks->GetEachBlock()->GetCenter().x - 25) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x - 5 < (arkanoidBricks->GetEachBlock()->GetCenter().x + 25) &&
				_arkanoidBar->GetBallByBar()->GetDir().y > 0)
			{
				if (arkanoidBricks->IsDead() == true)
					return;
				_arkanoidBar->GetBallByBar()->SetDir(Vector2(_arkanoidBar->GetBallByBar()->GetDir().x, (_arkanoidBar->GetBallByBar()->GetDir().y * -1)));
				if (arkanoidBricks->GetType() == ArkanoidBrick::ArkanoidBrickType::BRICK)
					arkanoidBricks->SetDead(true);
				return;
			}

			if (arkanoidBricks->GetEachBlock()->IsCollision(_arkanoidBar->GetBallByBar()->GetBall()) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x + 5 < (arkanoidBricks->GetEachBlock()->GetCenter().x) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y + 5 > (arkanoidBricks->GetEachBlock()->GetCenter().y - 10) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y - 5 < (arkanoidBricks->GetEachBlock()->GetCenter().y + 10) &&
				_arkanoidBar->GetBallByBar()->GetDir().x > 0)
			{
				if (arkanoidBricks->IsDead() == true)
					return;
				_arkanoidBar->GetBallByBar()->SetDir(Vector2((_arkanoidBar->GetBallByBar()->GetDir().x * -1), _arkanoidBar->GetBallByBar()->GetDir().y));
				if (arkanoidBricks->GetType() == ArkanoidBrick::ArkanoidBrickType::BRICK)
					arkanoidBricks->SetDead(true);
				return;
			}

			if (arkanoidBricks->GetEachBlock()->IsCollision(_arkanoidBar->GetBallByBar()->GetBall()) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().x - 5 > (arkanoidBricks->GetEachBlock()->GetCenter().x) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y + 5 > (arkanoidBricks->GetEachBlock()->GetCenter().y - 10) &&
				_arkanoidBar->GetBallByBar()->GetBall()->GetCenter().y - 5 < (arkanoidBricks->GetEachBlock()->GetCenter().y + 10) &&
				_arkanoidBar->GetBallByBar()->GetDir().x < 0)
			{
				if (arkanoidBricks->IsDead() == true)
					return;
				_arkanoidBar->GetBallByBar()->SetDir(Vector2((_arkanoidBar->GetBallByBar()->GetDir().x * -1), _arkanoidBar->GetBallByBar()->GetDir().y));
				if (arkanoidBricks->GetType() == ArkanoidBrick::ArkanoidBrickType::BRICK)
					arkanoidBricks->SetDead(true);
				return;
			}
		}
}

	void ArkanoidScene::Render(HDC hdc)
	{
		_arkanoidFrame->Render(hdc);
		_arkanoidBricks->Render(hdc);
		_arkanoidBar->Render(hdc);
	}
