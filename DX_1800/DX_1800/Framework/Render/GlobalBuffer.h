#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:

	struct Data
	{
		XMMATRIX matrix;
	};

	MatrixBuffer()
	: ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity();
	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX matrix)
	{
		matrix = XMMatrixTranspose(matrix);
		_data.matrix = matrix;
	}

	Data _data;
};