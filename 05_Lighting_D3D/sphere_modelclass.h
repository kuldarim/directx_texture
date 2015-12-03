////////////////////////////////////////////////////////////////////////////////
// Filename: Sphere_modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SPHERE_MODELCLASS_H_
#define _SPHERE_MODELCLASS_H_

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>
//#include <xnamath.h>

#include "indexmodelclass.h"

#define CACHE_SIZE    240

////////////////////////////////////////////////////////////////////////////////
// Class name: SphereModelClass
////////////////////////////////////////////////////////////////////////////////
class SphereModelClass : public IndexModelClass
{

public:
	SphereModelClass();
	SphereModelClass(const SphereModelClass&);
	~SphereModelClass();

	void Render(ID3D11DeviceContext*);
	MaterialBufferType getMaterial();

private:
	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);
	void MakeSphere(VertexNorm* , unsigned long*, float , UINT , UINT );

private:
	MaterialBufferType m_Material;

};

#endif