#pragma once
class Line 
{
public:
	Line(Vector2 start, Vector2 end) :_startPos(start), _endPos(end) { CreatePens(); }
	~Line();
	Line(const Line& line) {}
	void Update();
	void Render(HDC hdc);

	bool IsCollision(shared_ptr<Line> other);

	void SetGreen() { _curPenIdex = 0; }
	void SetRed() { _curPenIdex = 1; }

	

public:
	void CreatePens();

	int _curPenIdex;
	vector<HPEN> _pens;

	Vector2 _startPos;
	Vector2 _endPos;
	
};

