void Diffuse(float3 N, float3 L, float3 C, float3 K,out float3 Out)
{
    float D = dot(N, -L);
    D = max(0, D);
    Out= K * C * D;
}
