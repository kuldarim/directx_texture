////////////////////////////////////////////////////////////////////////////////
// Filename: indexmodelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "indexmodelclass.h"


IndexModelClass::IndexModelClass()
{
	m_vertexCount =0;
	m_indexCount = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	// Initialize the world matrix to the identity matrix.
       D3DXMatrixIdentity(&m_modelWorldMatrix);
}


IndexModelClass::IndexModelClass(const IndexModelClass& other)
{
}


IndexModelClass::~IndexModelClass()
{
}


bool IndexModelClass::Initialize(ID3D11Device* device)
{
	bool result;

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}
   
	return true;
}


void IndexModelClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void IndexModelClass::ShutdownBuffers()
{
	// Override in children class
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

int IndexModelClass::GetIndexCount()
{
	return m_indexCount;
}

void IndexModelClass::SetIndexCount(int Count)
{
	m_indexCount = Count;
	return;
}

int IndexModelClass::GetVertexCount()
{
	return m_vertexCount;
}

void IndexModelClass::SetVertexCount(int Count)
{
	m_vertexCount = Count;
	return;
}

D3DXMATRIX IndexModelClass::GetModelWorldMatrix()
{
	return m_modelWorldMatrix;
}

void IndexModelClass::SetModelWorldMatrix(D3DXMATRIX& worldMatrix)
{
	m_modelWorldMatrix = worldMatrix;
	return;
}
