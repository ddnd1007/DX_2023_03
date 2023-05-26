#pragma once

class MatrixBuffer : public ConstantBuffer
{
	struct Data
	{
		XMMATRIX matrix;
	};

	MatrixBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{
		_data.matrix = XMMatrixIdentity(); // 항등행렬
	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX matrix)
	{
		matrix = XMMatrixTranspose(matrix); // 전치행렬로 변경
		_data.matrix = matrix;
	}

	Data _data;
};