////////////////////////////////////////////////////////////////////////////////
// Filename: cube8_modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CUBE_MODELCLASS_H_
#define _CUBE_MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

#include "indexmodelclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: CubeModelClass
////////////////////////////////////////////////////////////////////////////////
class CubeModelClass : public IndexModelClass
{

public:
	CubeModelClass();
	CubeModelClass(const CubeModelClass&);
	~CubeModelClass();

	void Render(ID3D11DeviceContext*);
	MaterialBufferType getMaterial();

private:
	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	MaterialBufferType m_Material;

};

#endif