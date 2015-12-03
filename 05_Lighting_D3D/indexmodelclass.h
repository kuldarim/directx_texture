////////////////////////////////////////////////////////////////////////////////
// Filename: IndexModelClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INDEX_MODEL_CLASS_H_
#define _INDEX_MODEL_CLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

#include "VertexTypes.h"


////////////////////////////////////////////////////////////////////////////////
// Basic class name: IndexModelClass
////////////////////////////////////////////////////////////////////////////////
class IndexModelClass
{

public:
	IndexModelClass();
	IndexModelClass(const IndexModelClass&);
	~IndexModelClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	virtual void Render(ID3D11DeviceContext*) = 0;

	int GetIndexCount();
	int GetVertexCount(); 
	D3DXMATRIX GetModelWorldMatrix();

protected:
	void SetIndexCount(int);
	void SetVertexCount(int);
	void SetModelWorldMatrix(D3DXMATRIX&);

private:
	virtual void RenderBuffers(ID3D11DeviceContext*) = 0;
	virtual bool InitializeBuffers(ID3D11Device*) = 0;
	void ShutdownBuffers();

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

private:
	int m_vertexCount, m_indexCount;	
	D3DXMATRIX m_modelWorldMatrix;
};

#endif