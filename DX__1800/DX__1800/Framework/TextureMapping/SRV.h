#pragma once
class SRV
{
public:
	SRV(wstring path);
	~SRV();

	void SetSRV(UINT slot = 0);

private:
	ComPtr<ID3D11ShaderResourceView> srv;
};

