#pragma once
#include "framework.h"

class Zelda
{
public:
	enum State
	{
		IDLE_F,
		IDLE_L,
		IDLE_B,
		IDLE_R,

		RUN_F,
		RUN_L,
		RUN_B,
		RUN_R,
	};
	Zelda();
	~Zelda();

	void Update();
	void Render();

	void Input();

	



//adfsadf

private:
	void CreateActions();

	State _state = State::IDLE_F;

	shared_ptr<Sprite_Clip> _sprite;
	shared_ptr<Transform> _transform;
	
	vector<shared_ptr<Action>> _actions;

	Vector2 _pos = CENTER;
	float _speed = 400.0f;
};