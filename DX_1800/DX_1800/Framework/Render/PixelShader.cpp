#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring path)
{
    CreateBlob(path);
    CreatePixelShader();
}

PixelShader::~PixelShader()
{
}

void PixelShader::CreateBlob(wstring path)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    D3DCompileFromFile(L"Shader/TexturePS.hlsl",
        nullptr, nullptr, "PS", "ps_5_0", flags, 0, pixelBlob.GetAddressOf(), nullptr);
}

void PixelShader::CreatePixelShader()
{
    DEVICE->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, IN ps.GetAddressOf());
}

void PixelShader::Set_PS()
{
    DC->PSSetShader(ps.Get(), nullptr, 0);
}
