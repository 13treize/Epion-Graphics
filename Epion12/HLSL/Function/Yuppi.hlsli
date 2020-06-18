void Ellipse(float2 UV, float Width, float Height, out float Out)
{
    float d = length((UV * 2 - 1) / float2(Width, Height));
    Out += saturate((1.0 - d) / fwidth(d));
}

void Yuppi(float2 UV, float3 BodyColor, out float3 Out)
{
    //Body
    float body=0.0f;
    Ellipse(UV, 0.7, 0.7, body);

    //Eye
    float2 eye_uv = float2(-0.18f, 0.0f);
    float pupil=0.0f;
    Ellipse(UV + eye_uv, 0.2f, 0.2f, pupil);
    Ellipse(UV + abs(eye_uv), 0.2f, 0.2f, pupil);
    float eye=0.0f;
    Ellipse(UV + eye_uv, 0.1f, 0.1f, eye);
    Ellipse(UV + abs(eye_uv), 0.1f, 0.1f, eye);
 
    //Mouth
    float mouth = 0.0f,mouth2=0.0f;
    float3 mouth_color = float3(1.0f, 1.0f, 0.0f);
    Ellipse(UV + float2(0.0f, 0.2f), 0.5f, 0.2f, mouth);
    Ellipse(UV, 0.6, 0.6f, mouth2);
	
    //Face
    float3 face = body * BodyColor;
    mouth_color *= mouth * mouth2;
    face += mouth_color;
    face += pupil;
    face *= body * 1.0 - eye;
 
    Out = face;
}