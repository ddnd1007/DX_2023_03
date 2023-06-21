Texture2D resource : register(t0);
SamplerState samp : register(s0);

cbuffer ReverseBuffer : register(b0)
{
	int isReverse;
	int paddint[3];
}

cbuffer ActionBuffer : register(b1)
{
	float2 startPos;
	float2 fullSize;
	float2 size;
	int padding[2];
};

cbuffer FilterBuffer : register(b2)
{
	int type;
	int val1;
	int val2;
	int val3;

	float2 imageSize;
	float2 redialCenter;
}


struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

float4 OctaBlur(float2 uv)
{
	float4 result = 0;

	if (val2 == 0)
		return resource.Sample(samp, uv);

	for (int i = 0; i < val2; i++)
	{
		float divX = (i + 1) / imageSize.x;
		float divY = (i + 1) / imageSize.y;

		result += resource.Sample(samp, float2(uv.x + divX, uv.y)); //¿À
		result += resource.Sample(samp, float2(uv.x - divX, uv.y)); //¿Þ
		result += resource.Sample(samp, float2(uv.x, uv.y + divY)); //¾Æ
		result += resource.Sample(samp, float2(uv.x, uv.y - divY)); //À§

		result += resource.Sample(samp, float2(uv.x + divX, uv.y - divY)); //¿ÀÀ§
		result += resource.Sample(samp, float2(uv.x - divX, uv.y - divY)); //¿ÞÀ§
		result += resource.Sample(samp, float2(uv.x + divX, uv.y - divY)); //¿À¾Æ
		result += resource.Sample(samp, float2(uv.x - divX, uv.y - divY)); //¿Þ¾Æ
	}

	result /= 8 * val2;

	return result;
}


float4 PS(PixelInput input) : SV_TARGET
{
	float2 resultUV;
	if (isReverse == 1)
		input.uv.x = 1 - input.uv.x;

	resultUV.x = (startPos.x) / (fullSize.x) + input.uv.x * (size.x / fullSize.x);
	resultUV.y = (startPos.y) / (fullSize.y) + input.uv.y * (size.y / fullSize.y);

[branch]
	if (type == 0)
		return resource.Sample(samp, resultUV);
	else if (type == 1)
		return OctaBlur(resultUV);

	return resource.Sample(samp, resultUV);;
}