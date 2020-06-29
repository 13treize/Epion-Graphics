#include"../Function//Noise.hlsli"
#include"../Function//Procedural.hlsli"
#include"../Function//UV.hlsli"

cbuffer CBuffer : register(b0)
{
    float4 Time; //: packoffset(c1.xyz);
    float2 ScreenSize   ;//: packoffset(c0.xy);
    float2 MousePos     ;//: packoffset(c0.zw);
};

struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};

float4 PS(Input input) : SV_TARGET
{
    float4 set_color;
    float3 AAA;
    float2 data = float2(ScreenSize.x / 100.0, ScreenSize.y / 100.0);
    Checkerboard(input.uv, float3(1.0, 1.0, 1.0), float3(0.0, 0.0, 0.0), data, AAA);

    float a, b, c, d;
    Voronoi(input.uv, 3.0 * abs(sin(Time.x)), 5.0, a, b, c, d);

    set_color.xyz = c;
    set_color.w = 1.0f;

    return set_color;
}