#pragma once
class MazeBlock
{
public:
<<<<<<< HEAD
=======

>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
	enum class BlockType
	{
		ABLE,
		DISABLE,
		PLAYER,
		END,
<<<<<<< HEAD
		FOOTPRINT,
		NONE
=======
		NONE,
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1
	};

	MazeBlock();
	~MazeBlock();

	void Update();
	void Render(HDC hdc);

<<<<<<< HEAD
	void SetPostion(Vector2 pos) { _rect->SetCenter(pos); }
	void SetType(MazeBlock::BlockType type) { _type = type; }
	MazeBlock::BlockType GetType() { return _type; }
=======
	void SetPosition(Vector2 pos) { _rect->SetCenter(pos); }
	void SetType(MazeBlock::BlockType type) { _type = type; }
>>>>>>> d92ff9ebef6a2ffa38ef1fccfa5049f6a7da8cc1

private:
	BlockType _type = BlockType::NONE;
	vector<HBRUSH> _brushes;

	shared_ptr<RectCollider> _rect;
};

