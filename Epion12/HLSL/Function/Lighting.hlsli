/*
    Reference materials??
        https://knowledge.autodesk.com/ja/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2015/JPN/Maya/files/Shading-Nodes-htm.html

    Use Support function

    Diffuse

    Luminance
*/
void Diffuse(float3 N, float3 L, float3 C, float3 K,out float3 Out)
{
    float D = dot(N, -L);
    D = max(0, D);
    Out= K * C * D;
}


void Luminance(float3 color, out float3 Out)
{
    Out=(color.r * 0.3) + (color.g * 0.59) + (color.b * 0.11);
}