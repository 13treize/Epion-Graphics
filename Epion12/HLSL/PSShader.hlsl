#include"Function//Noise.hlsli"
#include"Function//Procedural.hlsli"
#include"Function//UV.hlsli"
#include"Function//Lighting.hlsli"

cbuffer CBuffer0 : register(b0)
{
    float4 Time;
    float2 ScreenSize;
    float2 MousePos;
};
cbuffer CBuffer1 : register(b1)
{
    float4x4 World : packoffset(c0);
    float4x4 View : packoffset(c4);
    float4x4 Proj : packoffset(c8);
};
//cbuffer CBuffer2 : register(b2)
//{
//    float4 LightColor;
//    float4 LightDir;
//    float4 AmbientColor;
//};


struct VSInput
{
    float3  Position : POSITION;
    float3  Normal   : NORMAL;
    float2  UV       : TEXCOORD;
    float4  Color    : VTX_COLOR;
};


struct VSOutput
{
    float4  Position : SV_POSITION;
    float3  Normal   : NORMAL;
    float2  UV       : TEXCOORD;
    float4  Color    : VTX_COLOR;
};


struct PSOutput
{
    float4  Color   : SV_TARGET0;
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
    //output.Color = input.Color;
    //return output;
    //PSOutput output = (PSOutput) 0;
    float4 aa;
    float3 aaaaaa;
    //Checkerboard(input.UV, float3(1.0, 1.0, 1.0), float3(0.0, 0.0, 0.0), float2(10.0, 10.0), aaaaaa);

    MinkowskiVoronoi(input.UV, 7.0, 7.0,0.25, aa.x, aa.y, aa.z, aa.w);
    //PhasorNoise(input.UV, 25.0, 10.0, 0.1, aa.x, aa.y, aa.z, aa.w);
    ////float3 Vector3_out10 = float3(2.0, 0.600000, 0.000000);
    output.Color.rgb=aa.yyy;

    
 //   float3 N = mul((float3x3) World, input.Normal);
 //   N = normalize(N); //ê≥ãKâª

	////Å@ÉâÉCÉgåvéZ
 //   float3 L = normalize(LightDir.xyz);
	////float D = max(0, dot(-L, N));
 //   float3 C = LightColor.rgb;
	//// îΩéÀó¶
 //   float3 Kd = float3(1, 1, 1);
	//// ägéUîΩéÀåvéZ
 //   float3 D;
 //   Diffuse(N, L, C, Kd, D);
 //   output.Color.rgb = aaaaaa+ D + AmbientColor.rgb;

    return output;
}
