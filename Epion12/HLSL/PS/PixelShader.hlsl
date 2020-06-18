float2 voronoi_noise_randomVector(float2 UV, float2 offset)
{
    float2x2 m = float2x2(15.27, 47.63, 99.41, 89.98);
    UV = frac(sin(mul(UV, m)) * 46839.32);
    return float2(sin(UV.y * +offset.x) * 0.5 + 0.5, cos(UV.x * offset.y) * 0.5 + 0.5);
}

void Voronoi(float2 UV, float2 AngleOffset, float2 CellDensity, out float Out, out float Cells, out float Lines, out float Points)
{
    float2 g = floor(UV * CellDensity);
    float2 f = frac(UV * CellDensity);
    float res = 8.0;
    float md = 8.0;
    float2 mr;
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            float2 lattice = float2(x, y);
            float2 offset = voronoi_noise_randomVector(lattice + g, AngleOffset);
            float2 r = lattice + offset - f;
            float d = dot(r, r);
            if (d < res)
            {
                res = d;
                mr = r;
            }
        }
    }
    res = 8.0;
    for (int yy = -1; yy <= 1; yy++)
    {
        for (int xx = -1; xx <= 1; xx++)
        {
            float2 lattice = float2(xx, yy);
            float2 offset = voronoi_noise_randomVector(lattice + g, AngleOffset);
            float2 r = lattice + offset - f;
            float d = dot(r, r);
            if (d < res)
            {
                res = d;
                Out = res;
                Cells = offset.x;
            }
            if (dot(mr - r, mr - r) > 0.00001)
            {
                md = min(md, dot(0.5 * (mr + r), normalize(r - mr)));
            }
        }
    }
    Lines = lerp(1.0, 0.0, smoothstep(0.03, 0.06, md));
    Points = 1.0 - smoothstep(0.0, 0.1, res);
}
//cbuffer CBuffer : register(b0)
//{
//    float4 A;
//};

struct Input
{
    float4 svpos : SV_POSITION; //システム用頂点座標
    float2 uv : TEXCOORD; //UV値
};
float4 PS(Input input) : SV_TARGET
{
    float a, b, c, d;
    Voronoi(input.uv, 3.0, 5.0, a, b, c, d);
    float4 set_color;
    set_color.x = 1.0f;
    set_color.y = c;
    set_color.z = a;
    set_color.w = 1.0f;
    //set_color.x = A;
    return set_color;
}