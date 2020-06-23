//  GradientNoise
float2 gradientNoise_dir(float2 p)
{
    p = p % 289;
    float x = (34 * p.x + 1) * p.x % 289 + p.y;
    x = (34 * x + 1) * x % 289;
    x = frac(x / 41) * 2 - 1;
    return normalize(float2(x - floor(x + 0.5), abs(x) - 0.5));
}
float gradient_noise(float2 p)
{
    float2 ip = floor(p);
    float2 fp = frac(p);
    float d00 = dot(gradientNoise_dir(ip), fp);
    float d01 = dot(gradientNoise_dir(ip + float2(0, 1)), fp - float2(0, 1));
    float d10 = dot(gradientNoise_dir(ip + float2(1, 0)), fp - float2(1, 0));
    float d11 = dot(gradientNoise_dir(ip + float2(1, 1)), fp - float2(1, 1));
    fp = fp * fp * fp * (fp * (fp * 6 - 15) + 10);
    return lerp(lerp(d00, d01, fp.y), lerp(d10, d11, fp.y), fp.x);
}
void GradientNoise(float2 UV, float Scale, out float Out)
{
    Out = gradient_noise(UV * Scale) + 0.5;
}

//  SimpleNoise
inline float noise_randomValue(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}
inline float noise_interpolate(float a, float b, float t)
{
    return (1.0 - t) * a + (t * b);
}
inline float valueNoise(float2 uv)
{
    float2 i = floor(uv);
    float2 f = frac(uv);
    f = f * f * (3.0 - 2.0 * f);
    uv = abs(frac(uv) - 0.5);
    float2 c0 = i + float2(0.0, 0.0);
    float2 c1 = i + float2(1.0, 0.0);
    float2 c2 = i + float2(0.0, 1.0);
    float2 c3 = i + float2(1.0, 1.0);
    float r0 = noise_randomValue(c0);
    float r1 = noise_randomValue(c1);
    float r2 = noise_randomValue(c2);
    float r3 = noise_randomValue(c3);
    float bottomOfGrid = noise_interpolate(r0, r1, f.x);
    float topOfGrid = noise_interpolate(r2, r3, f.x);
    float t = noise_interpolate(bottomOfGrid, topOfGrid, f.y);
    return t;
}
void SimpleNoise(float2 UV, float Scale, out float Out)
{
    float t = 0.0;
    float freq = pow(2.0, float(0));
    float amp = pow(0.5, float(3 - 0));
    t += valueNoise(float2(UV.x * Scale / freq, UV.y * Scale / freq)) * amp;
    freq = pow(2.0, float(1));
    amp = pow(0.5, float(3 - 1));
    t += valueNoise(float2(UV.x * Scale / freq, UV.y * Scale / freq)) * amp;
    freq = pow(2.0, float(2));
    amp = pow(0.5, float(3 - 2));
    t += valueNoise(float2(UV.x * Scale / freq, UV.y * Scale / freq)) * amp;
    Out = t;
};


//  Voronoi
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