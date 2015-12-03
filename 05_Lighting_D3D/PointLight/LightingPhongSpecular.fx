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
	float3 viewVec : TEXCOORD2;
	float3 diffuse : TEXCOORD3;
	float3 ambient : TEXCOORD4;
	float3 LightPosition : TEXCOORD5;
};



PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
    float4 worldPos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( worldPos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projectionMatrix );
	
	vsOut.LightPosition = LightPosition1;
	vsOut.diffuse = LightDifuse1;
	vsOut.ambient = LightAmbient1;

	// Transform the normal for light computations
    vsOut.norm = mul( vertex.norm, (float3x3)worldMatrix );
    vsOut.norm = normalize( vsOut.norm );

	// Prepare lighting vector for interpolation per pixel
    float3 lightPos = LightPosition1;
    vsOut.lightVec = normalize( lightPos - worldPos );
	 
    vsOut.viewVec = normalize( cameraPos - worldPos );
	 return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{

	float specularPower = specularMaterColor.w;
    
    float3 lightVec = normalize( frag.lightVec );
    float3 normal = normalize( frag.norm );

	float lightIntensity1 = saturate(dot(frag.norm,frag.LightPosition ));

	// Compute diffusive term (interpolation per pixel)
    float diffuseTerm = clamp( dot( normal, lightVec ), 0.0f, 1.0f );

	// Compute specular term (interpolation per pixel)   
	float specularTerm = 0;
    if( diffuseTerm > 0.0f )
    {
        float3 viewVec = normalize( frag.viewVec );
        float3 halfVec = normalize( lightVec + viewVec );
        specularTerm = pow( saturate( dot( normal, halfVec ) ), specularPower );
    }

	// Final lighting formula
    float3 finalColor = frag.ambient *ambientMaterColor*lightIntensity1 + saturate(diffuseMaterColor*lightIntensity1) * frag.diffuse * diffuseTerm + specularMaterColor * frag.diffuse * specularTerm;

    return float4( finalColor, 1.0f );
}