/*
    Lighting Shader
*/

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};
/*
cbuffer CameraBuffer
{
    float3 cameraPos;
};
*/
cbuffer MaterialBuffer
{
	float4 ambientMaterColor;
	float4 diffuseMaterColor;
    float4 specularMaterColor;
};

struct VS_Input
{
    float4 pos  : POSITION;
    //float3 norm : NORMAL;
};

struct PS_Input
{
    float4 pos  : SV_POSITION;
};


PS_Input VS_Main( VS_Input vertex )
{
    PS_Input vsOut = ( PS_Input )0;
	// Transformation of vertexes
    vsOut.pos = mul( vertex.pos, worldMatrix );
    vsOut.pos = mul( vsOut.pos, viewMatrix );
    vsOut.pos = mul( vsOut.pos, projectionMatrix );

    return vsOut;
}


float4 PS_Main( PS_Input frag ) : SV_TARGET
{
	float3 finalColor = ambientMaterColor;
    return float4( finalColor, 1.0f );
}