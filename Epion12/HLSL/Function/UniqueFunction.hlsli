#ifndef INCLUDE_GUARD_UNIQUEFUNCTION_HLSLI
#define INCLUDE_GUARD_UNIQUEFUNCTION_HLSLI

//#include"Lighting.hlsli"
//#include"Noise.hlsli"
//#include"Procedural.hlsli"
//#include"UV.hlsli"
float3 Fire(float2 UV, float2 Tiling, float2 Offset, float3 Color)
{
    float2 tiling_data;
    TilingAndOffset(UV, Tiling, Offset, tiling_data);

    float4 voronoi_data;
    Voronoi(tiling_data, 8.0, 4.0, voronoi_data.x, voronoi_data.y, voronoi_data.z, voronoi_data.w);

    float gradient_data;
    GradientNoise(tiling_data, 8.0, gradient_data);

    return float3(Color * gradient_data * pow(voronoi_data.x, 0.4));
}

void Lava(float2 UV,float2 vec,out float3 Out)
{
	float2 uv1 = UV;
	float2 uv2 = UV;
	Spherize(uv1,0.0, 0.2, 7.0, uv1);
	
	float a, b, c, d;
	Voronoi(uv2, 3.0,7.0, a, b, c, d);
	
	float aa, bb, cc, dd;
	float2 uv3= uv1 + vec;
	Voronoi(uv3, 7.0, 11.0, aa, bb, cc, dd);

	float e;
	SimpleNoise(uv1, 200.0, e);
	float3 col = float3(aa + a, aa / 2.0 + a / 2.0 * e, 0.0);
	Out = col;
}

#endif