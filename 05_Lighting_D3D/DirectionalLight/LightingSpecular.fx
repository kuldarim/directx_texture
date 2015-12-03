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

cbuffer LightColorBuffer
{
	float4 myLightPosition;
	float4 myLightDifuseColor;
	float4 myLightAmbientColor;
	float4 myLightAtt;
	float4 myLightDir;
	float4 myLightCone;
	float4 myLightRange;
};


struct VS_Input
{
    float4 pos  : POSITION;
    float3 norm : NORMAL;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
	float1 speterm : TEXCOORD1;	
	float3 diffuse : TEXCOORD2;
	float3 ambient : TEXCOORD3;
	float difterm : TEXCOORD4;
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
	
    	float3 dir1 = float3(LightDir.x*-1,LightDir.y*-1, LightDir.z*-1);
    float3 lightVec = normalize(dir1);

	// Prepare viewing vector for interpolation per pixel
    float3 viewVec = normalize( cameraPos - worldPos );

	// Compute diffusive term (interpolation per vertex)
    vsOut.difterm = clamp( dot( norm, lightVec ), 0.0f, 1.0f );

	// Compute specular term (interpolation per pixel)   
	float specularPower = 25.0f; //Netechniðkai
    if( vsOut.difterm > 0.0f )
    {
        float3 halfVec = normalize( lightVec + viewVec );
        vsOut.speterm = pow( saturate( dot( norm, halfVec ) ), specularPower );
    }

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{

	float specularPower = specularMaterColor.w;    

    float3 finalColor = frag.ambient *ambientMaterColor + diffuseMaterColor * frag.diffuse * frag.difterm + specularMaterColor * frag.diffuse * frag.speterm;

    return float4( finalColor, 1.0f );
}