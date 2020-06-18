struct Output
{
    float4 svpos : SV_POSITION; //�V�X�e���p���_���W
    float2 uv : TEXCOORD; //UV�l
};

Output VS(float4 pos : POSITION, float2 uv : TEXCOORD)
{
    Output output; //�s�N�Z���V�F�[�_�֓n���l
    output.svpos = pos;
    output.uv = uv;
    return output;
}