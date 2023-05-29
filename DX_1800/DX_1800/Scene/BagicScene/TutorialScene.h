#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

	void Move(float x, float y, float z)
	{
		_x += x;
		_y += y;
		_z += z;
	}

	void Rotate(float angle)
	{
		_z += angle;
	}

	void Scale(float factor)
	{
		_x *= factor;
		_y *= factor;
		_z*= factor;
	}


private:

	shared_ptr<Quad> _quad;

	float _x = 0.0f;
	float _y = 0.0f;
	float _z = 0.0f;
	float _scale = 1.0f;
	float _angle = 0.0f;

	shared_ptr<MatrixBuffer> _world;
	shared_ptr<MatrixBuffer> _view;
	shared_ptr<MatrixBuffer> _proj;
};

