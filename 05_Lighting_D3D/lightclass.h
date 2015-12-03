/*////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "VertexTypes.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();


	void SetLightPosition(float, float, float);
	void SetLightDiffuseColor(float, float, float, float);
	void SetLightAmbient(float, float, float,float);
	void SetLightAtt(float,float,float);
	void SetLightDir(float,float,float);
	void SetLightCone(float);
	void SetLightRange(float);
	//void SetLightRange(float);

	LightColorBufferType GetLightColorBuffer();

	
	D3DXVECTOR4 GetLightPosition();
	D3DXVECTOR4 GetLightDiffuseColor();
	D3DXVECTOR4 GetLightAmbientColor();
	D3DXVECTOR4 GetLightAtt();
	D3DXVECTOR4 GetLightDir();
	D3DXVECTOR4 GetLightCone();
	D3DXVECTOR4 GetLightRange();

private:
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR4 m_position;
	LightColorBufferType m_LightColorBuffer;
};

#endif
*/
////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "VertexTypes.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();

private:
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
};

#endif