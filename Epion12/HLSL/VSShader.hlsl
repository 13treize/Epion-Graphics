cbuffer CBuffer0 : register(b0)
{
    float4 Time; //: packoffset(c0);
    float2 ScreenSize;
    float2 MousePos;
};
cbuffer CBuffer1 : register(b1)
{
    float4x4 World; //: packoffset(c0);
};
cbuffer CBuffer2 : register(b2)
{
    float4x4 View; //: packoffset(c4);
    float4x4 Proj; //: packoffset(c8);
    //float4 CameraPos;
    //float4 LightColor;
    //float4 LightDir;
    //float4 AmbientColor;
};
struct VSInput
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : VTX_COLOR;
};

struct VSOutput
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : VTX_COLOR;
};

struct PSOutput
{
    float4 Color : SV_TARGET0;
};


VSOutput VS(const VSInput input)
{
    VSOutput output = (VSOutput) 0;

    float4 localPos = float4(input.Position, 1.0f);
    float4 worldPos = mul(World, localPos);
    float4 viewPos = mul(View, worldPos);
    float4 projPos = mul(Proj, viewPos);

    output.Position = projPos;
    output.Normal = input.Normal;
    output.UV = input.UV;
    output.Color = input.Color;

    return output;
}

