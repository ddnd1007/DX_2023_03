#pragma once
class MazeScene : public Scene
{
public:
	MazeScene();
	virtual ~MazeScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

<<<<<<< HEAD
=======

>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
private:
	shared_ptr<Maze> _maze;
	shared_ptr<Player> _player;
};

