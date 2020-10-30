//#include"Function//Lighting.hlsli"
#include"Function//Noise.hlsli"
#include"Function//Procedural.hlsli"
#include"Function//UV.hlsli"
//#include"Function//UniqueFunction.hlsli"

#ifndef NUM_DIR_LIGHTS
	#define NUM_DIR_LIGHTS 0
#endif

#ifndef NUM_POINT_LIGHTS
	#define NUM_POINT_LIGHTS 0
#endif

#ifndef NUM_SPOT_LIGHTS
	#define NUM_SPOT_LIGHTS 0
#endif
#define MaxLights 16

struct Light
{
	float3 Strength;
	float FalloffStart; // point/spot light only
	float3 Direction; // directional/spot light only
	float FalloffEnd; // point/spot light only
	float3 Position; // point light only
	float SpotPower; // spot light only
};

struct Material
{
	float4 DiffuseAlbedo;
	float3 FresnelR0;
	float Shininess;
};

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
	float4 CameraPos;
	float4 LightColor;
	float4 LightDir;
	float4 AmbientColor;
	Light Lights[MaxLights];
};
cbuffer CBuffer3: register(b3)
{
	float4 DiffuseAlbedo;
	float3 FresnelR0;
	float Roughness;
	float4x4 MatTransform;
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

//void TryAngle(float2 UV,out float Out)
//{
//    float2 p = frac(float2(4.0, 6.7) * UV / iResolution.y);
//    Out = vec4(U.x < .5 == U.x < 1. - U.y == U.x < U.y);
//}

float4 Fire(float2 UV, float3 Color)
{
    float2 tiling_data;
    TilingAndOffset(UV, float2(1.0, 1.0), Time.x, tiling_data);

    float4 voronoi_data;
    Voronoi(tiling_data, 8.0, 4.0, voronoi_data.x, voronoi_data.y, voronoi_data.z, voronoi_data.w);

    float gradient_data;
    GradientNoise(tiling_data, 8.0, gradient_data);

    float3 fire = Color * gradient_data * pow(voronoi_data.x, 0.4);

    float4 flag_color = float4(fire, 1.0f);
    return flag_color;
}
PSOutput PS0(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	//float3 N = mul((float3x3) World, input.Normal);
	//N = normalize(N); //³‹K‰»
	//float3 L = normalize(LightDir.xyz);
	//float3 C = LightColor.rgb;
	//float3 Kd = float3(1, 1, 1);
	//float3 D;
	//Diffuse(N, L, C, Kd,D);
	//float3 E = normalize(CameraPos.xyz - input.Position.xyz);
	//float3 S = BlinnPhongSpecular(N, L, C, E, 1.0, 20);

	// o—Í’lÝ’è.

	//output.Color = float4(input.Position, 1.0);
	float3 check;
	Checkerboard(input.UV, float3(1.0, 1.0, 1.0), float3(0.0, 0.0, 0.0), float2(5.0, 5.0), check);
	float c;
	Grid(input.UV, 10.0, 0.1, c);
	
	output.Color.rgb = check;
    output.Color = Fire(input.UV, float3(1.0,0.4,0.0));
	return output;

//	//// Indirect lighting.
//    float4 ambient = float4(0.25f, 0.25f, 0.35f, 1.0f ) * DiffuseAlbedo;

//    const float shininess = 1.0f - Roughness;
//    Material mat;
//    mat.DiffuseAlbedo =DiffuseAlbedo;
//    mat.FresnelR0 = FresnelR0;
//    mat.Shininess=shininess;
//    float3 shadowFactor = 1.0f;
	//float4 directLight = ComputeLighting(Lights, mat, input.Position.xyz,input.Normal, E, shadowFactor);

//    output.Color.rgb= ambient + directLight;

////   // Common convention to take alpha from diffuse material.
//     output.Color.a= DiffuseAlbedo.a;
//    return output;

}

PSOutput PS1(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float a, b, c, d;
	Voronoi(input.UV,5.0f,5.0f, a, b, c, d);
	output.Color.rgb = a;
	return output;
}

PSOutput PS2(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float a, b, c, d;
	Voronoi(input.UV, 5.0f, 5.0f, a, b, c, d);
	output.Color.rgb = b;
	return output;
}

PSOutput PS3(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float a, b, c, d;
	Voronoi(input.UV, 5.0f, 5.0f, a, b, c, d);
	output.Color.rgb = c;
	return output;
}

PSOutput PS4(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float a, b, c, d;
	Voronoi(input.UV, 5.0f, 5.0f, a, b, c, d);
	output.Color.rgb = d;
	return output;
}