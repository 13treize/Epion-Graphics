#include"Function//Noise.hlsli"
#include"Function//Procedural.hlsli"
#include"Function//UV.hlsli"

cbuffer CBuffer0 : register(b0)
{
    float4 Time; // packoffset(c1.xyz);
    float2 ScreenSize; //: packoffset(c0.xy);
    float2 MousePos; //: packoffset(c0.zw);
};
cbuffer CBuffer1 : register(b1)
{
    float4x4 World : packoffset(c0);
    float4x4 View : packoffset(c4);
    float4x4 Proj : packoffset(c8);
};

struct VSInput
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
    float2 UV : TEXCOORD;
};

struct VSOutput
{
    float4 Position : SV_POSITION;
    float4 Normal : NORMAL;
    float2 UV : TEXCOORD;
};


struct PSOutput
{
    float4 Color : SV_TARGET0;
};



float4 Fire(float2 UV, float3 Color)
{
    float2 tiling_data;
    TilingAndOffset(UV, float2(1.000000, 1.000000), Time.x, tiling_data);

    float4 voronoi_data;
    Voronoi(tiling_data, 8.000000, 4.000000, voronoi_data.x, voronoi_data.y, voronoi_data.z, voronoi_data.w);

    float gradient_data;
    GradientNoise(tiling_data, 8.000000, gradient_data);

    float Multiply_float_out3 = gradient_data * pow(voronoi_data.x, 0.4);

    float3 Multiply_float3_out2 = Color * Multiply_float_out3;

    float4 flag_color = float4(Multiply_float3_out2, 1.0f);
    return flag_color;
}


PSOutput PS(const VSOutput input)
{
    PSOutput output = (PSOutput) 0;
    float4 aa;
    //Voronoi(input.UV, 3.0, 5.0, aa.x, aa.y, aa.z, aa.w);
    output.Color.xy = input.UV;
    ////float3 Vector3_out10 = float3(2.0, 0.600000, 0.000000);
    ////output.Color = Fire(input.UV, Vector3_out10);

    return output;
}
