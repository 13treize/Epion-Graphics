struct Output
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};
struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};
[maxvertexcount(3)]
void GS(
	triangle Output input[3],
	inout TriangleStream<Input> output
)
{
    Input element;

	for (uint i = 0; i < 3; i++)
	{
		element.svpos = input[i].svpos;
		element.uv = input[i].uv;
		output.Append(element);
	}

    output.RestartStrip();
}
