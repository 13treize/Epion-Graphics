struct Output
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};

Output VS(float4 pos : POSITION, float2 uv : TEXCOORD)
{
    Output output; //ピクセルシェーダへ渡す値
    output.svpos = pos;
    output.uv = uv;
    return output;
}