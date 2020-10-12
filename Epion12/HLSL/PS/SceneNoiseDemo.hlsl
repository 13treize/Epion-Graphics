#include"../Function//Noise.hlsli"

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
	float a, b, c, d;
	Voronoi(input.UV, 3.0, 7.0, a, b, c, d);
	output.Color.rgb = a;
	return output;
}
