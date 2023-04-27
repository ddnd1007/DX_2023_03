#pragma once
class Cannon
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void MoveByInput();
	void Fire();
	shared_ptr<Bullet> SetBullet();

	void SetPostion(const Vector2& pos) { _pos = pos; }

	vector<shared_ptr<Bullet>>& GetBullets() { return _bullets; }

	bool _isControll = true;

private:
	shared_ptr<CircleCollider> _body;
	
	Vector2 _pos = CENTER;
	float _barrelLength = 100.0f;
	float _speed = 2.0f;

	shared_ptr<Line> _barrel;
	Vector2 _direction;
	float _angle = 0.0f;

	//미리 생성해놓고
	//내가 입력할 때마다 생성(동적할당)하지 않고 벡터로 미리 생성해놓은 풀에서 껏다켯다를 반복
	// -> 오브젝트 풀링
	bool _spacePress = false;
	bool _spaceUp = true;
	float _power; // TODO : 스페이스바 누르면 증가하다가 뎨는 순간 Bullet Speed 수정
	vector <shared_ptr<Bullet>> _bullets;
};

