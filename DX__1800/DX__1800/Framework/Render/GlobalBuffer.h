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
		_data.matrix = XMMatrixIdentity(); // �׵����
	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX matrix)
	{
		matrix = XMMatrixTranspose(matrix); // ��ġ��ķ� ����
		_data.matrix = matrix;
	}

	Data _data;
};