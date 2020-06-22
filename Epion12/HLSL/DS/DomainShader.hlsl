struct DS_OUTPUT
{
	float4 vPosition  : SV_POSITION;
	// TODO: 他のスタッフの変更/追加
};

// 出力制御点
struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : WORLDPOS; 
};

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor; // たとえば、クワド ドメインの [4] になります
	float InsideTessFactor			: SV_InsideTessFactor; // たとえば、クワド ドメインの Inside[2] になります
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
DS_OUTPUT DS(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT Output;

	Output.vPosition = float4(
		patch[0].vPosition*domain.x+patch[1].vPosition*domain.y+patch[2].vPosition*domain.z,1);

	return Output;
}
