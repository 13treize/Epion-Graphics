
struct VSOutput
{
    float4 Position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 UV : TEXCOORD;
    float4 Color : VTX_COLOR;
};


[maxvertexcount(3)]
void main(
	triangle float4 input[3] : SV_POSITION, 
	inout TriangleStream<VSOutput> output
)
{
	for (uint i = 0; i < 3; i++)
	{
        VSOutput element;
        element.Position = input[i];
		output.Append(element);
	}
}