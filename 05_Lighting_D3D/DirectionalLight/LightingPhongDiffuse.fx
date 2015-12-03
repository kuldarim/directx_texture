/*
    Lighting Shader
*/

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer CameraBuffer
{
    float3 cameraPos;
	float padding1;
	float3 LightPosition1;
	float padding2;
	float4 LightDifuse1;
	float4 LightAmbient1;
	float3 LightAtt;
	float padding3;
	float3 LightDir;
	float padding4;
	float3 padding5;
	float LightCone;
	float3 padding6;
	float LightRange;	
};


cbuffer MaterialBuffer
{
	float4 ambientMaterColor;
	float4 diffuseMaterColor;
    float4 specularMaterColor;
};

struct VS_Input
{
    float4 pos  : POSITION;
    float3 norm : NORMAL;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
    float3 norm : NORMAL;
    float3 lightVec : TEXCOORD1;
	float3 diffuse : TEXCOORD2;
	float3 ambient : TEXCOORD3;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    float4 worldPos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( worldPos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projectionMatrix );

	vsOut.diffuse = LightDifuse1;
	vsOut.ambient = LightAmbient1;

	// Transform the normal for light computations
    vsOut.norm = mul( vertex.norm, (float3x3)worldMatrix );
    vsOut.norm = normalize( vsOut.norm );

	float3 dir1 = float3(LightDir.x*-1,LightDir.y*-1, LightDir.z*-1);
    vsOut.lightVec = normalize(dir1);

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{    
   
    float3 lightVec = normalize( frag.lightVec );
    float3 normal = normalize( frag.norm );

	// Compute diffusive term (interpolation per pixel)
    float diffuseTerm = clamp( dot( normal, lightVec ), 0.0f, 1.0f );

	float3 finalColor = frag.ambient *ambientMaterColor + diffuseMaterColor * frag.diffuse * diffuseTerm;

    return float4( finalColor, 1.0f );
}