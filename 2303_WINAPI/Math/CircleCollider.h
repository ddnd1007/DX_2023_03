#pragma once
class CircleCollider
{
public:
	//타입변환생성자

	void Update();
	void Render(HDC);

private:
	//멤버변수
	float _radius;
	Vector2 _center;
};

