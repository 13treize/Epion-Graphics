#include"../Function//Noise.hlsli"
#include"../Function//Procedural.hlsli"
#include"../Function//UV.hlsli"

cbuffer CBuffer : register(b0)
{
    float4 Time; //: packoffset(c1.xyz);
    float2 ScreenSize; //: packoffset(c0.xy);
    float2 MousePos; //: packoffset(c0.zw);
};

struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};

float4 PS(Input input) : SV_TARGET
{
    float4 set_color;

    float a, b, c, d;
    Voronoi(input.uv, 3.0 * sin(Time.x), 5.0, a, b, c, d);
    //ManhattanVoronoi(input.uv, 13.0, 15.0, a, b, c, d);
    WaveletNoise(input.uv, 0.0, 4.0, 4.0, 1.0, b);
    set_color.xyz = a;
    return set_color;
}

float4 PS2(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    ManhattanVoronoi(input.uv, 0.5, 5.0, a, b, c, d);
    set_color.xyz = d;
    return set_color;
}
