//shadow effect
//create shadow texture

cbuffer TransformBuffer : register(b0)
{
    matrix wvp;
    int type;
    float param0;
    float param1;
    float param2;
}

Texture2D textureMap0 : register(t0);
Texture2D textureMap1 : register(t1);
Texture2D textureMap2 : register(t2);
Texture2D textureMap3 : register(t3);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float4 lightNDCPosition : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = mul(float4(input.position, 1.0f), wvp);
    output.lightNDCPosition = output.position; //mul(float4(input.position, 1.0f), wvp);
    
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float depth = 0.0f;
    if(type == 0)
    {
        depth = saturate(1.0f - (input.lightNDCPosition.z / input.lightNDCPosition.w)); //////////////////
    }
    else if(type == 1)
    {
        return float4(0.0f, 1.0f, 1.0f, 1.0f);
    }
    else if(type == 2)
    {
        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return float4(depth, 1.0f, 1.0f, 1.0f);
}
