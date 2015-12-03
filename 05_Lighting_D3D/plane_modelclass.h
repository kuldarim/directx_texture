////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Plane_MODEL_CLASS_H_
#define _Plane_MODEL_CLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

#include "indexmodelclass.h"

////////////////////////////////////////////////////////////////////////////////
// Derived class name: PlaneModelClass
////////////////////////////////////////////////////////////////////////////////
class PlaneModelClass : public IndexModelClass
{

public:
	PlaneModelClass();
	PlaneModelClass(const PlaneModelClass&);
	~PlaneModelClass();

	void Render(ID3D11DeviceContext*);
	MaterialBufferType getMaterial();

private:
	bool InitializeBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	MaterialBufferType m_Material;

};

#endif