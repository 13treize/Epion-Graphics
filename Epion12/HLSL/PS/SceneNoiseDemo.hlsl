#include"../Function//Noise.hlsli"
#include"../Function//Procedural.hlsli"
#include"../Function//UV.hlsli"

cbuffer CBuffer : register(b0)
{
    float4 Time; //: packoffset(c1.xyz);
    float2 ScreenSize; //: packoffset(c0.xy);
    float2 MousePos; //: packoffset(c0.zw);
};

cbuffer CBuffer3 : register(b3)
{
    float4 Data[4];
};

struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};

float4 PS0(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    Random(input.uv, Data[0].x, a, b);
    set_color.xyz = a;
    return set_color;
}

float4 PS1(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    Random(input.uv, Data[0].x, a, b);
    set_color.xyz = b;
    return set_color;
}
float4 PS2(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    RandomMaze(input.uv, Data[0].y, a, b, c);
    set_color.xyz = a;
    return set_color;
}
float4 PS3(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    RandomMaze(input.uv, Data[0].y, a, b, c);
    set_color.xyz = b;
    return set_color;
}
float4 PS4(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    RandomMaze(input.uv, Data[0].y, a, b, c);
    set_color.xyz = c;
    return set_color;
}
float4 PS5(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    GradientNoise(input.uv, Data[0].z, a);
    set_color.xyz = a;
    return set_color;
}

float4 PS6(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    PhasorNoise(input.uv, Data[0].w, Data[1].x,Data[1].y,Data[1].z, a, b, c, d);
    set_color.xyz = a;
    return set_color;
}

float4 PS7(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    PhasorNoise(input.uv, Data[0].w, Data[1].x, Data[1].y, Data[1].z, a, b, c, d);
    set_color.xyz = b;
    return set_color;
}
float4 PS8(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    PhasorNoise(input.uv, Data[0].w, Data[1].x, Data[1].y, Data[1].z, a, b, c, d);
    set_color.xyz = c;
    return set_color;
}
float4 PS9(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    PhasorNoise(input.uv, Data[0].w, Data[1].x, Data[1].y, Data[1].z, a, b, c, d);
    set_color.xyz = d;
    return set_color;
}
float4 PS10(Input input) : SV_TARGET
{
    float4 set_color;
    float a, b, c, d;
    Voronoi(input.uv, Data[0].w, Data[1].x, a, b, c, d);
    set_color.xyz = d;
    return set_color;
}