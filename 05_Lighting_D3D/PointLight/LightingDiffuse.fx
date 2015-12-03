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
	float1 difterm : TEXCOORD1;
	float3 diffuse : TEXCOORD2;
	float3 ambient : TEXCOORD3;
	float3 LightPosition : TEXCOORD4;
};



PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    float4 worldPos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( worldPos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projectionMatrix );	

	vsOut.diffuse = LightDifuse1;
	vsOut.ambient = LightAmbient1;

    float3 norm = mul( vertex.norm, (float3x3)worldMatrix );
    norm = normalize( norm );

	vsOut.norm = norm;

	float3 lightPos = LightPosition1;
	vsOut.LightPosition = LightPosition1;
    float3 lightVec = normalize( lightPos- worldPos );

	// Prepare viewing vector for interpolation per pixel
    float3 viewVec = normalize( cameraPos - worldPos );

	// Compute diffusive term (interpolation per vertex)
    vsOut.difterm = clamp( dot( norm, lightVec ), 0.0f, 1.0f );
    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{

	float3 normal = normalize( frag.norm );
	float lightIntensity = saturate(dot(frag.norm, frag.LightPosition ));

    float3 finalColor =  frag.ambient *ambientMaterColor*lightIntensity + saturate(diffuseMaterColor* lightIntensity) * frag.diffuse * frag.difterm ;
    return float4( finalColor, 1.0f );
}