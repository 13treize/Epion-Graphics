//#include"Function//Lighting.hlsli"
#include"Function//Noise.hlsli"
#include"Function//Procedural.hlsli"
#include"Function//UV.hlsli"
#include"Function//UniqueFunction.hlsli"

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
cbuffer CBuffer3 : register(b3)
{
	float4 DiffuseAlbedo;
	float3 FresnelR0;
	float Roughness;
	float4x4 MatTransform;
};

struct VSInput
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
	float4 Color : VTX_COLOR;
};

struct VSOutput
{
	float4 Position : SV_POSITION;
	float3 Normal : NORMAL;
	float2 UV : TEXCOORD;
	float4 Color : VTX_COLOR;
};

struct PSOutput
{
	float4 Color : SV_TARGET0;
};

PSOutput PS0(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float3 check;
	Checkerboard(input.UV, float3(0.9, 0.9, 0.9), float3(0.1, 0.1, 0.1), float2(5.0, 5.0), check);
	float c;
	Grid(input.UV, 10.0, 0.1, c);
	
	output.Color.rgb = check;
	return output;
}

PSOutput PS1(const VSOutput input)
{
	PSOutput output = (PSOutput) 0;
	float a;
	Ellipse(input.UV, 0.5f, 0.5f, a);
	output.Color.rgb = a;
	return output;
}