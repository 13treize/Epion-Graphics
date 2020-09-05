#include"Function//Noise.hlsli"
#include"Function//Procedural.hlsli"
#include"Function//UV.hlsli"

cbuffer CBuffer0 : register(b0)
{
    float4 Time;
    float2 ScreenSize;
    float2 MousePos;
};
cbuffer CBuffer1 : register(b1)
{
    float4x4 World;
};
cbuffer CBuffer2 : register(b2)
{
    float4x4 View; //: packoffset(c4);
    float4x4 Proj; //: packoffset(c8);
    //float4 CameraPos;
    float4 LightColor;
    float4 LightDir;
    float4 AmbientColor;
};


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

//void Unity_ColorspaceConversion_RGB_RGB_float(float3 In, out float3 Out)
//{
//    float4 K = float4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
//    float4 P = lerp(float4(In.bg, K.wz), float4(In.gb, K.xy), step(In.b, In.g));
//    float4 Q = lerp(float4(P.xyw, In.r), float4(In.r, P.yzx), step(P.x, In.r));
//    float D = Q.x - min(Q.w, Q.y);
//    float E = 1e-10;
//    Out = float3(abs(Q.z + (Q.w - Q.y) / (6.0 * D + E)), D / (Q.x + E), Q.x);
//}
//float3 hsv2rgb(float3 c)
//{
//    float4 K = float4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
//    float3 p = abs(frac(c.xxx + K.xyz) * 6.0 - K.www);
//    return c.z * lerp(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
//}
//float4 Fire(float2 UV, float3 Color)
//{
//    float2 tiling_data;
//    TilingAndOffset(UV, float2(1.000000, 1.000000), Time.x, tiling_data);

//    float4 voronoi_data;
//    Voronoi(tiling_data, 8.000000, 4.000000, voronoi_data.x, voronoi_data.y, voronoi_data.z, voronoi_data.w);

//    float gradient_data;
//    GradientNoise(tiling_data, 8.000000, gradient_data);

//    float Multiply_float_out3 = gradient_data * pow(voronoi_data.x, 0.4);

//    float3 Multiply_float3_out2 = Color * Multiply_float_out3;

//    float4 flag_color = float4(Multiply_float3_out2, 1.0f);
//    return flag_color;
//}
//void RotateRadians(float2 UV, float2 Center, float Rotation, out float2 Out)
//{
//    UV -= Center;
//    float s = sin(Rotation);
//    float c = cos(Rotation);
//    float2x2 rMatrix = float2x2(c, -s, s, c);
//    rMatrix *= 0.5;
//    rMatrix += 0.5;
//    rMatrix = rMatrix * 2 - 1;
//    UV.xy = mul(UV.xy, rMatrix);
//    UV += Center;
//    Out = UV;
//}

PSOutput PS0(const VSOutput input)
{
    PSOutput output = (PSOutput) 0;
    float3 check;
    Checkerboard(input.UV, float3(1.0, 1.0, 1.0), float3(0.0, 0.0, 0.0), float2(2.0, 2.0), check);
    output.Color.rgb = check;
    return output;
}

PSOutput PS1(const VSOutput input)
{
    PSOutput output = (PSOutput) 0;
    float ellipse;
    Ellipse(input.UV, 0.5, 0.3, ellipse);
    output.Color.rgb = ellipse;
    return output;
}

PSOutput PS2(const VSOutput input)
{
    PSOutput output = (PSOutput) 0;
    float gear;
    RoundedRectangle(input.UV, 0.5, 0.3, (sin(Time.x)), gear);
    output.Color.rgb = gear;
    return output;
}