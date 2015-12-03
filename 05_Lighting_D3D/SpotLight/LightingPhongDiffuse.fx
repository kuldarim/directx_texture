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
    float3 viewVec : TEXCOORD2;
	float4 worldPos :TEXCOORD3;
	
	float3 LightPosition : TEXCOORD4;
	float4 LightDifuseColor : TEXCOORD5;
	float4 LightAmbientColor : TEXCOORD6;
	float3 LightAtt : TEXCOORD7;
	float3 LightDir : TEXCOORD8;
	float LightCone : TEXCOORD9;
	float LightRange : TEXCOORD10;
};




PS_Input VS_Main( VS_Input vertex )
{
	PS_Input vsOut = ( PS_Input )0;
  
    vsOut.worldPos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( vsOut.worldPos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projectionMatrix );

    vsOut.norm = mul( vertex.norm, (float3x3)worldMatrix );
    vsOut.norm = normalize( vsOut.norm );

    vsOut.viewVec = normalize( cameraPos - vsOut.worldPos );
	
	vsOut.LightPosition = (LightPosition1.xyz - vsOut.worldPos.xyz);
	vsOut.LightDifuseColor = LightDifuse1;	
	vsOut.LightAmbientColor = LightAmbient1;
	vsOut.LightAtt = LightAtt;
	vsOut.LightDir = normalize(LightDir);
	vsOut.LightCone = LightCone;
	vsOut.LightRange = LightRange;

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
	frag.norm = normalize(frag.norm);
	float4 diffuse = diffuseMaterColor;
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 lightToPixelVec = frag.LightPosition - frag.worldPos;

	float d = length(lightToPixelVec);
	float3 finalAmbient = diffuse * frag.LightAmbientColor;

	if( d > frag.LightRange )
		return float4(finalAmbient, diffuse.a);

	lightToPixelVec /= d; 

	float howMuchLight = dot(lightToPixelVec, frag.norm);

	float specularPower = specularMaterColor.w;  
	float lightIntensity1 = saturate(dot(frag.norm, frag.LightPosition));	
	float diffuseTerm = clamp( dot( frag.norm , lightToPixelVec ), 0.0f, 1.0f );	
	
	if( howMuchLight > 0.0f )
	{	
		//Add light to the finalColor of the pixel
		finalColor += diffuse * frag.LightDifuseColor;
					
		//Calculate Light's Distance Falloff factor
		finalColor /= ( frag.LightAtt[0] + ( frag.LightAtt[1] * d)) + ( frag.LightAtt[2] * (d*d));		

		//Calculate falloff from center to edge of pointlight cone
		finalColor *= pow(max(dot(-lightToPixelVec,  frag.LightDir), 0.0f),frag.LightCone);
	}

	finalColor *= diffuseTerm*lightIntensity1;

	finalColor = saturate(finalColor + finalAmbient + frag.LightAmbientColor);
    return float4(finalColor, diffuse.a);	
}

