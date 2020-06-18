#include"../Function//Noise.hlsli"
//cbuffer CBuffer : register(b0)
//{
//    float4 A;
//};

struct Input
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float2 uv : TEXCOORD; //UV�l
};
float4 PS(Input input) : SV_TARGET
{
    float a, b, c, d;
    Voronoi(input.uv, 3.0, 5.0, a, b, c, d);
    float4 set_color;
    set_color.x = d;
    set_color.y = c;
    set_color.z = a;
    set_color.w = 1.0f;
    //set_color.x = A;
    return set_color;
}