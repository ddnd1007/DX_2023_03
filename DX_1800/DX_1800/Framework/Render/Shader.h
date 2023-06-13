#pragma once
class Shader
{
public:
	Shader();
	virtual ~Shader() {}

	virtual void Set();

protected:
	wstring _file;
	ComPtr<ID3DBlob> _blob;
};

