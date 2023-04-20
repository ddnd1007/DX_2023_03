#pragma once
class Line
{
public:
	struct Result
	{
		bool collision = false;
		Vector2 conflict = Vector2();
	};

	Line() {}
	Line(Vector2 start, Vector2 end) : _startPos(start), _endPos(end) {}
	~Line();

	void Update();
	void Render(HDC hdc);

	
	Result IsCollision(shared_ptr<Line> other);
	
	
public:
	

	Vector2 _startPos;
	Vector2 _endPos;

};

