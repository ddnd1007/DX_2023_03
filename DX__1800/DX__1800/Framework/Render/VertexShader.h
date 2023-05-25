#pragma once
class VertexShader
{
public:
	VertexShader(wstring path);
	~VertexShader();

	void CreateBlob(wstring path);
	void CreateInputLayout();
	void CreateVertexShader();

	void SetIA_InputLayOut();
	void Set_VS();

private:
	ComPtr<ID3DBlob> vertexBlob;

	ComPtr<ID3D11InputLayout> inputLayOut;
	ComPtr<ID3D11VertexShader> vertexShader;
};

