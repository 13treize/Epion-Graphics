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


void Step_float(float Edge, float In, out float Out)
{
    Out = step(Edge, In);
}



void OneMinus_float(float In, out float Out)
{
    Out = 1 - In;
};

void Multiply_float3(float3 A, float3 B, out float3 Out)
{
    Out = A * B;
}

float4 Unlit(float4 Pos, float3 Color, float Alpha, float AlphaChipThreshold)
{
    if (Alpha < AlphaChipThreshold)
    {
        Alpha = 0;
    }
    float4 ret_color = float4(Color, Alpha);
    return ret_color;
};

float4 Dissolve(float2 UV)
{
    float Time_ = Time.x;
    float Sin_Time_ = sin(Time.x);
    float Cos_Time_ = cos(Time.x);

    float Add_float_out3 = frac(Time.x*2.0)+0.07;

    float SimpleNoise_out5;
    SimpleNoise(UV, 50.000000, SimpleNoise_out5);

    float Step_float_out4;
    Step_float(Add_float_out3, SimpleNoise_out5, Step_float_out4);


    float OneMinus_float_out7 = 1.0f - Step_float_out4;

    float Multiply_float_out11;

    float3 Color_out6 = float3(0.045937, 0.970414, 0.000000);

    float Fraction_float_out12 = frac(Time.x * 2.0f);

    float SimpleNoise_out10;
    SimpleNoise(UV, 50.000000, SimpleNoise_out10);

    float3 Multiply_float3_out8;
    Multiply_float3(Color_out6, OneMinus_float_out7, Multiply_float3_out8);

    float4 flag_color = Unlit(float4(0.000000, 0.000000, 0.000000, 0.000000), Multiply_float3_out8, SimpleNoise_out10, Fraction_float_out12);
    return flag_color;
}
float4 Fire(float2 UV,float3 Color)
{
    float Time_ = Time.x;
    float Sin_Time_ = sin(Time.x);
    float Cos_Time_ = cos(Time.x);


    float2 tiling_data;
    TilingAndOffset(UV, float2(1.000000, 1.000000), Time_, tiling_data);

    float4 voronoi_data;
    Voronoi(tiling_data, 8.000000, 4.000000, voronoi_data.x, voronoi_data.y, voronoi_data.z, voronoi_data.w);

    float gradient_data;
    GradientNoise(tiling_data, 8.000000, gradient_data);

    float Multiply_float_out3 = gradient_data * pow(voronoi_data.z, 0.4);

    float3 Multiply_float3_out2 = Color * Multiply_float_out3;

    float4 flag_color = float4(Multiply_float3_out2,1.0f);
    return flag_color;
}


float4 PS(Input input) : SV_TARGET
{
    float4 set_color;
    float3 AAA;
    float2 data = float2(ScreenSize.x / 100.0, ScreenSize.y / 100.0);

    float a, b, c, d;
    Voronoi(input.uv, 3.0 * abs(sin(Time.x)), 5.0, a, b, c, d);

    float3 Vector3_out10 = float3(2.0, 0.600000, 0.000000);

    set_color.xyz = c;
    set_color.w = 1.0f;
    //set_color = Dissolve(input.uv);
    
    set_color = Fire(input.uv, Vector3_out10);

    return set_color;
}