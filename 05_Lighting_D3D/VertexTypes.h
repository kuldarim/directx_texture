////////////////////////////////////////////////////////////////////////////////
// Filename: VertexTypes.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _VERTEX_TYPES_H_
#define _VERTEX_TYPES_H_

//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
// Structures defining vertex types
////////////////////////////////////////////////////////////////////////////////
struct VertexType
{
	D3DXVECTOR3 position;
    D3DXVECTOR4 color;
};

struct VertexNorm
{
    D3DXVECTOR3 position;
    D3DXVECTOR3 normal;
    //D3DXVECTOR4 color;
};

struct MaterialBufferType
{
	D3DXVECTOR4 ambientColor;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR4 specularColor;
};


struct LightColorBufferType
{
		D3DXVECTOR3 myLightPosition;
		D3DXVECTOR4 myLightDifuseColor;
		D3DXVECTOR4 myLightAmbientColor;
		D3DXVECTOR3 myLightAtt;
		D3DXVECTOR3 myLightDir;
		float myLightCone;
		float myLightRange;
};

#endif