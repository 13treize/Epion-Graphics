//struct VS_OUT
//{
//    float4 position : SV_POSITION;
//    float4 normal : NORMAL;
//    float2 uv : TEXCOORD0;
//};


//float4 PS(VS_OUT pin) : SV_TARGET
//{
//    float4 color_ = { 1, 0, 0, 1 };

//    return color_;
//

// UNIT.10
struct VS_OUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

cbuffer CONSTANT_BUFFER : register(b0)
{
    row_major float4x4 world_view_projection;
    row_major float4x4 world_inverse_transpose;
    //float4 material_color;
    //float4 light_direction;
};


float4 PS(VS_OUT pin) : SV_TARGET
{
    float4 color=float4(1.0f, 1.0f, 1.0f, 1.0f);
    return color;
}
