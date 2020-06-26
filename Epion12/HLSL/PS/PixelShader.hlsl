#include"../Function//Noise.hlsli"
#include"../Function//Procedural.hlsli"
#include"../Function//UV.hlsli"
struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};

//void PointDeform(float2 UV, float2 ScreenSize, float2 Pos, float Power, float Dis, out float2 Out)
//{
//    float2 dir_pos = UV - Pos;
//    float dis2 = length(dir_pos);
//    dir_pos = dir_pos / dis2;
//    //float weight = saturate(dis2 / Dis);
//    //float distance_deformed = pow(weight, Power) * Dis;
//    //distance_deformed = lerp(distance_deformed, dis2, weight);
//    //float2 screenpos_deformed = Pos + dir_pos * distance_deformed;
//    //Out = screenpos_deformed / ScreenSize;
//    Out = dir_pos;

//}
float4 PS(Input input) : SV_TARGET
{
    float a, b, c, d;
    float3 AAA;
    Voronoi(input.uv, 3.0, 5.0, a, b, c, d);
    GradientNoise(input.uv, 4.0f, a);
    //float2 aa;
    //PointDeform(input.uv, float2(1280.0f, 720.0f), float2(640.0f, 360.0f), 0.0, 0.0, aa);

    Checkerboard(input.uv, float3(1.0, 1.0, 1.0), float3(0.0, 0.0, 0.0), float2(10.0, 10.0), AAA);
    float4 set_color;
    set_color.x = 0.0f;
    set_color.y = 0.0;
    set_color.z = 1.0;
    set_color.w = 1.0f;
    set_color.xyz = AAA;
    return set_color;
}