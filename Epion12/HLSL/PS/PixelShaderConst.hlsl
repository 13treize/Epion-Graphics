#include"../Function//Noise.hlsli"
cbuffer CBuffer : register(b0)
{
    float A;
    float B;
    float C;
    float D;
};

struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};
float4 PS(Input input) : SV_TARGET
{
    float a, b, c, d;
    Voronoi(input.uv, 3.0, 5.0, a, b, c, d);
    float4 set_color;
    //set_color.x = c;
    //set_color.y = c;
    //set_color.z = a;
    //set_color.w = 1.0f;
    set_color.x = A;
    set_color.y = B;
    set_color.z = C;
    set_color.w = D;

    return set_color;
}