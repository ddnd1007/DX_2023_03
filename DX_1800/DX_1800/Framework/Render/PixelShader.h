#pragma once
class PixelShader
{
public:
	PixelShader(wstring path);
	~PixelShader();

	void CreateBlob(wstring path);
	void CreatePixelShader();

	void Set_PS();

private:
	ComPtr<ID3DBlob> pixelBlob;
	ComPtr<ID3D11PixelShader> ps;
};

