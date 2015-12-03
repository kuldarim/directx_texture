////////////////////////////////////////////////////////////////////////////////
// Filename: cube_modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cube_modelclass.h"


CubeModelClass::CubeModelClass():IndexModelClass()
{
	m_Material.ambientColor = D3DXVECTOR4( 0.05f, 0.05f, 0.125f, 1.0f );
	m_Material.diffuseColor = D3DXVECTOR4( 0.0f, 0.0f, 1.0f, 1.0f );
	m_Material.specularColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 25.0f );
}


CubeModelClass::CubeModelClass(const CubeModelClass& other)
{
}


CubeModelClass::~CubeModelClass()
{
}

MaterialBufferType CubeModelClass::getMaterial()
{
	return m_Material;
}

bool CubeModelClass::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;
//
// Process the vertex buffer
//
	VertexNorm* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

	// Set the number of vertices in the vertex array.
	int vCount = 8;
	SetVertexCount(vCount);

	// Create the vertex array.
	vertices = new VertexNorm[vCount];
	if(!vertices)
	{
		return false;
	}

	//D3DXVECTOR3 norm;
	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f,-1.0f,-1.0f);  
	//vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize( &vertices[0].normal , &D3DXVECTOR3(-1.0f,-1.0f,-1.0f));
	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f,-1.0f);  
	//vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize( &vertices[1].normal , &D3DXVECTOR3(-1.0f, 1.0f,-1.0f));
	vertices[2].position = D3DXVECTOR3( 1.0f, 1.0f,-1.0f);  
	//vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize( &vertices[2].normal , &D3DXVECTOR3(1.0f, 1.0f,-1.0f));
	vertices[3].position = D3DXVECTOR3(1.0f,-1.0f,-1.0f);  
	//vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	D3DXVec3Normalize( &vertices[3].normal , &D3DXVECTOR3(1.0f,-1.0f,-1.0f));

	vertices[4].position = D3DXVECTOR3(-1.0f,-1.0f, 1.0f);  
	//vertices[4].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVec3Normalize( &vertices[4].normal , &D3DXVECTOR3(-1.0f,-1.0f, 1.0f));
	vertices[5].position = D3DXVECTOR3(1.0f,-1.0f, 1.0f);  
	//vertices[5].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVec3Normalize( &vertices[5].normal , &D3DXVECTOR3(1.0f,-1.0f, 1.0f));
	vertices[6].position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);  
	//vertices[6].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVec3Normalize( &vertices[6].normal , &D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	vertices[7].position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);  
	//vertices[7].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	D3DXVec3Normalize( &vertices[7].normal , &D3DXVECTOR3(-1.0f, 1.0f, 1.0f));

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexNorm) * vCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	ZeroMemory( &vertexData, sizeof( vertexData ) );
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the array now that the vertex buffer has been created and loaded.
	delete [] vertices;
	vertices = 0;

//
// Process the index buffer	
//
	unsigned long* indices;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	// Set the number of indices in the index array.
	int iCount = 36;
	SetIndexCount(iCount);

	// Create the index array.
	indices = new unsigned long[iCount];
	if(!indices)
	{
		return false;
	}

	// Load the index array with data.
	indices[0] = 0;  
	indices[1] = 1;  
	indices[2] = 2;  
	indices[3] = 2;  
	indices[4] = 3;  
	indices[5] = 0; 

	indices[6] = 4;  
	indices[7] = 5;  
	indices[8] = 6;  
	indices[9] = 6;  
	indices[10] = 7;  
	indices[11] = 4; 

	indices[12] = 0;  
	indices[13] = 3;  
	indices[14] = 5;  
	indices[15] = 5;  
	indices[16] = 4;  
	indices[17] = 0; 
		
	indices[18] = 3;  
	indices[19] = 2;  
	indices[20] = 6;  
	indices[21] = 6;  
	indices[22] = 5;  
	indices[23] = 3; 

	indices[24] = 2;  
	indices[25] = 1;  
	indices[26] = 7;  
	indices[27] = 7;  
	indices[28] = 6;  
	indices[29] = 2; 		

	indices[30] = 1;  
	indices[31] = 0;  
	indices[32] = 4;  
	indices[33] = 4;  
	indices[34] = 7;  
	indices[35] = 1;

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * iCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the array now that the vertex buffer has been created and loaded.
	delete [] indices;
	indices = 0;

	return true;
}


void CubeModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	//Update the world transformations
	UINT  iTime  = timeGetTime() % 6000;
	float fAngle = iTime * 2 * D3DX_PI / 6000.0f;
	D3DXMATRIX rotMatrixX, rotMatrixY, scaleMatrix, transMatrix;
	D3DXMatrixRotationX(&rotMatrixX, fAngle );
	//D3DXMatrixRotationY(&rotMatrixY, fAngle );
	
	D3DXMatrixTranslation(&transMatrix, 2.2f,1.0f,0.0f);
	SetModelWorldMatrix(rotMatrixX*/*rotMatrixY*/transMatrix);

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


void CubeModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexNorm); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case Spheres.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// render primitives
	deviceContext->DrawIndexed(GetIndexCount(), 0, 0);

	return;
}