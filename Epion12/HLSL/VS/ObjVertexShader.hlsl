// UNIT.10

struct VS_OUT
{
    float4 position : SV_POSITION;
    //float4 normal : NORMAL;
    float4 color : COLOR;
};

cbuffer CONSTANT_BUFFER : register(b0)
{
    row_major float4x4 world_view_projection;
    row_major float4x4 world_inverse_transpose;
};


VS_OUT VS(float4 position : POSITION, float4 normal : NORMAL)
{
    VS_OUT vout;
    vout.position = mul(position, world_view_projection);

    normal.w = 0;
    float4 N = normalize(mul(normal, world_inverse_transpose));

    vout.color.xyz = float3(1.0f, 1.0f, 1.0f);
    vout.color.a = 1;
    return vout;
}

//cbuffer WorldCBuffer : register(b0)
//{
//    row_major float4x4 WorldViewProjection;
//    row_major float4x4 World;
//};

//struct VSInput
//{
//    float4 position : SV_POSITION;
//    float4 normal : NORMAL;
//    float2 uv : TEXCOORD0;
//};

//struct PSInput
//{
//    float4 position : SV_POSITION;
//    float4 normal : NORMAL;
//    float2 uv : TEXCOORD0;
//    float4 wpos : TEXCOORD1;
//    float4 lpos : TEXCOORD2;
//};



//PSInput VS(VSInput input)
//{
//    PSInput vout = (PSInput) 0;
//    float4 P = float4(input.position.xyz, 1.0);

//    vout.position = mul(P, WorldViewProjection);
//    float4 W = mul(World, P);


//    float4 N = float4(normalize(mul((float3) input.normal, (float3x3) World)), 0.0f);
//    vout.normal = N;
//    vout.uv = input.uv;
//    vout.wpos = W;
//    vout.lpos = mul(World, float4(0, 0, 0, 1));

//    return vout;
//}
